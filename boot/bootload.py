# connection information
VECTOR_APP_NAME = "emdash"
VECTOR_CHANNEL = 0
CAN_BAUDRATE = 500000

# bootloader information
BOOTLOAD_CAN_CMD_ADDR = 0x7EF
BOOTLOAD_CAN_RESP_ADDR = 0x7EE

import argparse
import struct
import binascii
import time

parser = argparse.ArgumentParser(description=
    "Program the Einstein Motorsport dashboard or wheelboard over CAN. "
    "The device to program is read from the application image.")
parser.add_argument('application', type=argparse.FileType('rb'),
    help="Application memory image (.bin) to program.")
parser.add_argument('-u', '--utilization', type=int, default=25,
    help="Maximum bus utilization permitted, in percent. Higher values "
         "allow faster programming, but may cause other devices on the "
         "bus to function incorrectly. Integer between 1 and 100, "
         "default value is 25.")
parser.add_argument('-v', '--verbose', action="store_true", default=False,
    help="Provide more detail during programming and after errors.")

args = parser.parse_args()

class BootloadError(Exception):
    pass

class ImageError(BootloadError):
    def __str__(self):
        return "Application image is corrupt: "+super().__str__()

class CANError(BootloadError):
    def __str__(self):
        return "CAN bus error: "+super().__str__()

class ProgramError(BootloadError):
    def __str__(self):
        return "Programming failed: "+super().__str__()

def read_image():
    image = args.application.read()
    # header is 32 bytes
    if len(image) < 32:
        raise ImageError("header is missing.")

    # note that the bootloader does the same tests
    # and checksums

    # validate the header checksum
    header = struct.unpack("<8I", image[:32])
    if sum(header) & 0xFFFFFFFF != 0:
        raise ImageError("header checksum failed.")

    # get the header size and crc, then validate it that way
    app_crc = header[4]
    app_size = header[5]
    if app_size < 40*8 or app_size > (0x7000-(4*8)):
        raise ImageError("application size in header is invalid.")
    if app_size != len(image)-32:
        raise ImageError("application size in header is incorrect.")

    crc = binascii.crc32(image[32:], 0)
    if crc != app_crc:
        raise ImageError("application checksum failed.")

    # pad the image with 0xFF to be a multiple of 256 bytes
    # (because the image is sent in 256 byte pages)
    if len(image) % 256 != 0:
        image += b"\xFF"*(256-(len(image)%256))

    # finally, return the validated and padded image
    return image

import logging
# this prints out some garbage on startup that we don't want to see
# so we shut it up until import is finished
logging.disable(logging.CRITICAL)
import can
logging.disable(logging.NOTSET)

CMD_HELLO = 0
CMD_ERASE_ALL = 1
CMD_EMPTY = 2
CMD_PROGRAM_VERIFY = 3
CMD_REBOOT = 4

RESP_SUCCESS = 0
RESP_HELLO = 1
RESP_INVALID_COMMAND = 2
RESP_ERROR = 3
RESP_PROGRAM_FAILURE = 4
RESP_CHECKSUM_INCORRECT = 5

CMD_HELLO_KEY = 0xb00710ad

class CAN:
    def __init__(self, app_name, channel, baudrate, utilization):
        if utilization < 1 or utilization > 100:
            raise CANError("utilization percent must be an integer between 1 and 100.")
        try:
            self.bus = can.interface.Bus(
                bustype='vector',
                app_name=app_name,
                channel=channel,
                bitrate=baudrate,
                receive_own_messages=True
            )
        except can.interfaces.vector.exceptions.VectorError as e:
            msg = str(e)
            if "xlGetApplConfig" in msg or "XL_ERROR" in msg:
                raise CANError("could not initialize. "
                    "Is the Vector Hardware application configuration correct?") from e
            elif "XL_ERR_WRONG_PARAMETER" in msg or \
                    "XL_ERR_HW_NOT_PRESENT" in msg: # how i want it to be reported
                raise CANError("could not initialize. "
                    "Is the interface plugged in?") from e
            else:
                raise CANError("could not initialize: "+str(e)) from e
        except ValueError as e:
            # thrown by python-can 2.2.0 in this case
            # may be hiding something else but idk what to do
            raise CANError("could not initialize. "
                "Is the interface plugged in?") from e
        except Exception as e:
            raise CANError("could not initialize: "+str(e)) from e

        # calculate message interval allowed by the utilization factor
        # a CAN message can be at most 132 bits long, assuming DLC of 8
        # and worst-case stuffing
        msgs_per_sec = (baudrate/132) * (utilization/100)
        self.msg_interval = 1/msgs_per_sec

        self.last_cmd = None
        self.msgs_sent = 0
        self.next_msg_time = time.perf_counter()

    def recv_filtered(self, timeout):
        # apparently can_filters just doesn't work
        # so we'll have to do it ourselves!
        while timeout > 0:
            start = time.monotonic()
            m = self.bus.recv(timeout)
            # subtract time elapsed from timeout duration
            # in case we need to recv again
            timeout -= time.monotonic()-start
            # but if m is None, we've timed out for real
            if m is None:
                return None

            if (m.arbitration_id == BOOTLOAD_CAN_CMD_ADDR or
                    m.arbitration_id == BOOTLOAD_CAN_RESP_ADDR) and \
                    m.is_error_frame is False:
                # a message made it past the filter
                return m

    def send_data(self, data):
        self.last_cmd = data[0] # used to verify response
        m = can.Message(arbitration_id=BOOTLOAD_CAN_CMD_ADDR,
            data=data, extended_id=False)
        self.msgs_sent += 1

        # busywait until we're allowed to send the next message
        # putting > 0 for sleep is way too slow
        now = time.perf_counter()
        while self.next_msg_time > now:
            time.sleep(0)
            now = time.perf_counter()
        self.bus.send(m)
        self.bus.flush_tx_buffer()
        # allow next message to be sent at the interval
        # calculated to allow the desired bus utilizaton
        self.next_msg_time = now + self.msg_interval

        # next received message should be the transmission receipt
        m = self.recv_filtered(timeout=5)
        if m is None:
            raise CANError("timed out waiting for message to be transmitted. "
                "Are CANH and CANL connected properly?")
        if m.arbitration_id != BOOTLOAD_CAN_CMD_ADDR or m.data != data:
            raise CANError("received message unexpectedly: "+str(m))

    def recv_response(self, timeout=5, expected_resp=None):
        m = self.recv_filtered(timeout=timeout)
        if m is None:
            raise CANError("timed out waiting for message to be received.")
        if len(m.data) != 2:
            raise ProgramError("response length is incorrect: {}".format(len(m.data)))
        cmd, resp = m.data[0], m.data[1]
        # some responses we can deal with here
        if cmd != self.last_cmd:
            raise ProgramError("received response to incorrect command: {}".format(cmd))
        elif cmd > CMD_REBOOT:
            raise ProgramError("received response for invalid command: {}".format(cmd))
        if resp == RESP_INVALID_COMMAND:
            raise ProgramError("received 'invalid command' response.")
        elif resp == RESP_ERROR:
            raise ProgramError("unexpected error inside bootloader.")
        elif resp == RESP_PROGRAM_FAILURE:
            raise ProgramError("Flash programming failure. Chip may be damaged.")
        elif expected_resp is not None and resp != expected_resp:
            raise ProgramError("unexpected response: {}".format(cmd))
        # otherwise, return it for the caller
        return resp


class Programmer:
    def __init__(self, bus, image):
        self.bus = bus
        self.image = image

    def connect(self):
        # retrieve the system ID from the image
        system_id = struct.unpack("<I", self.image[32:36])[0]&0xFFFF
        # try to send the Hello command until we get a response
        for hi in range(10):
            self.bus.send_data(struct.pack("<BHI",
                CMD_HELLO, system_id, CMD_HELLO_KEY))
            try:
                self.bus.recv_response(timeout=0.2, expected_resp=RESP_HELLO)
                break
            except CANError:
                continue
        else: # loop did not break -> receive always timed out
            raise ProgramError("connection failed. Device did not respond "
                "to 'Hello'. Is it turned on?")

    def erase(self):
        # send erase command and wait for it to happen
        self.bus.send_data(struct.pack("<B", CMD_ERASE_ALL))
        self.bus.recv_response(expected_resp=RESP_SUCCESS)

    def program_page(self, page):
        # try multiple times in case data transfer failed
        for program_try in range(5):
            # empty page buffer
            self.bus.send_data(struct.pack("<B", CMD_EMPTY))
            self.bus.recv_response(expected_resp=RESP_SUCCESS)

            pdata = self.image[page*256:page*256+256]
            # send the page in 8 byte chunks
            for pos in range(0, 256, 8):
                self.bus.send_data(pdata[pos:pos+8])

            # checksum the page
            crc = binascii.crc32(pdata, 0)
            # and now program it
            self.bus.send_data(struct.pack("<BHI", CMD_PROGRAM_VERIFY,
                page, crc))
            r = self.bus.recv_response()
            if r == RESP_CHECKSUM_INCORRECT:
                continue
            if r == RESP_SUCCESS:
                break
            raise ProgramError("unexpected response: {}".format(response))
        else: # loop did not break -> we were never successful
            raise ProgramError("page transfer failed 5 times. "
                "Are CANH and CANL connected properly? Is there noise on the bus?")

    def reboot(self):
        # send reboot command and wait for it to happen
        # True to reboot into app
        self.bus.send_data(struct.pack("<BB", CMD_REBOOT, True))
        self.bus.recv_response(expected_resp=RESP_SUCCESS)


def main():
    # start out by reading in the image data
    image = read_image()

    # now that is done, initialize the CAN interface
    bus = CAN(VECTOR_APP_NAME,
        VECTOR_CHANNEL,
        CAN_BAUDRATE,
        args.utilization)

    # now we can do the programming! make a programmer
    prog = Programmer(bus, image)

    # and run through all the steps
    print("Connecting to device... ", end="", flush=True)
    prog.connect()
    print("connected!")
    print("Erasing Flash... ", end="", flush=True)
    prog.erase()
    print("erased!")

    num_pages = int(len(image)/256)
    for page in range(num_pages):
        print("\rProgramming page {}/{}... ".format(page+1, num_pages),
            end="", flush=True)
        prog.program_page(page)
    print("programmed!")

    print("Rebooting into application... ", end="", flush=True)
    prog.reboot()
    print("rebooted!")
    print("")
    print("Programming Complete")

if args.verbose:
    main()
else:
    try:
        main()
    except BootloadError as e:
        print(str(e))
        exit(1)