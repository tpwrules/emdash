from struct import pack

import can
canbus = can.interface.Bus(
    bustype='vector',
    app_name='emdash',
    channel=0,
    bitrate=500000,
    can_filters=[{"can_id":0x7EE, "can_mask":0x7FF}],
    receive_own_messages=False)

def get_response(timeout=5):
    m = canbus.recv(timeout=timeout)
    if m is None: raise Exception("CAN receive timeout!")
    if len(m.data) == 2:
        return (m.data[0], m.data[1])

def send_data(data):
    m = can.Message(arbitration_id=0x7EF,
        data=data, extended_id=False)
    canbus.send(m)
    canbus.flush_tx_buffer()

def process_response(success=True):
    cmd, resp = get_response()
    if resp == 0:
        if success:
            print("success!")
    else:
        raise Exception("got {} for command {}".format(resp, cmd))

import sys
import binascii

img = open(sys.argv[1], "rb").read()
if len(img) % 256 != 0:
    # pad with 0xFF for checksumming purposes
    img += b"\xFF"*(256-(len(img)%256))

system_id = struct.unpack("<I", img[32:36])&0xFFFF

print("saying hello")
m = None
for hi in range(10):
    send_data(pack("<BHI", 0, system_id, 0xb00710ad))
    try:
        m = get_response(timeout=0.2)
        break
    except:
        continue

if m is None:
    print("hello timed out!")
    exit()

cmd, resp = m
if cmd == 0 and resp == 1:
    print("they said hello back!")

print("erasing chip... ", end="")
send_data(pack("<B", 1))
process_response()

print("programming {} pages...".format(len(img)>>8))

for pi in range(0, len(img), 256):
    print("{}/{}... ".format(pi, len(img)), end="")
    pd = img[pi:pi+256]
    # empty page buffer
    send_data(pack("<B", 2))
    process_response(False)
    # send data
    for pdi in range(0, 256, 8):
        send_data(pd[pdi:pdi+8])
    # checksum page
    crc = binascii.crc32(pd, 0)
    # and program it
    send_data(pack("<BHI", 3, pi>>8, crc))
    process_response()

print("rebooting into app... ")
send_data(pack("<BB", 4, 1))
process_response()
canbus.shutdown()