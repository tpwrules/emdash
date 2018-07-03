from struct import pack

import can as can_import
can = can_import
canbus = can.interface.Bus(
    bustype='vector',
    app_name='emdash',
    channel=0,
    bitrate=500000)

def get_response():
    while True:
        m = canbus.recv()
        if m.arbitration_id == 0x7EE:
            if len(m.data) == 2:
                return (m.data[0], m.data[1])

def send_data(data):
    m = can.Message(arbitration_id=0x7EF,
        data=data, extended_id=False)
    canbus.send(m)
    canbus.flush_tx_buffer()

print("waiting for hello")

while True:
    cmd, resp = get_response()
    if cmd == 0 and resp == 1:
        print("found a hello, saying hello back")
        send_data(pack("<B", 0))
        break

while True:
    cmd, resp = get_response()
    if cmd == 0 and resp == 0:
        print("connected!")
        break