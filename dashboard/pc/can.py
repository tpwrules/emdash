# send CAN messages to the application for simulation purposes

import time
import random
import struct
import math

def do(fn):
    global can_send
    can_send = fn

    time.sleep(3)

    a = 0
    data = struct.pack("<BBBxxxxx", 0, 0, 0)
    can_send(0x122, data)
    data = struct.pack("<xxxxxxBx", 0)
    can_send(0x114, data)
    while True:
        v = max(int(math.sin(a)*6100+6000), 0)
        data = struct.pack("<xxHBBxx", v, 0, 0)
        can_send(0x121, data)
        a += 0.05
        time.sleep(0.05)
