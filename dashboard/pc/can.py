# send CAN messages to the application for simulation purposes

import time
import random
import struct
import math

def do(fn):
    global can_send
    can_send = fn
    a = 0
    while True:
        v = max(int(math.sin(a)*6100+6000), 0)
        data = struct.pack("<xxHxxxx", v)
        can_send(0x121, data)
        a += 0.05
        time.sleep(0.05)
