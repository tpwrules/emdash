# send CAN messages to the application for simulation purposes

import time
import random
import struct

def do(fn):
    global can_send
    can_send = fn
    while True:
        rpm = int(random.random()*10000)
        data = struct.pack("<xxHxxxx", rpm)
        can_send(0x121, data)
        time.sleep(0.3)
