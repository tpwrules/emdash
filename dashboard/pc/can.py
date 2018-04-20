# send CAN messages to the application for simulation purposes

import time
import random
import struct
import math

import sys
sys.path.append("../can/")
import canvars

import random
rr = random.randrange

def do(fn):
    global can_send
    can_send = fn

    cv = canvars.CanvarInterface(fn)

    cv.nmot = 0
    cv.gear = 0

    cv.poil = 1
    cv.pfuel = 2
    cv.toil = 3
    cv.tmot = 4
    cv.tmot2 = 5
    cv.tfuel = 6
    cv.ub = 7

    a = 0
    b = 0
    gear = 0
    while True:
        v = max(int(math.sin(a)*6100+6000), 0)
        cv.nmot = 3300
        cv.speed = int(max(min(v*255/12000, 255), 0))
        if b % 40 == 0:
            cv.poil = rr(0, 100)
            cv.pfuel = rr(0, 100)
            cv.toil = rr(0, 256)
            cv.tmot = rr(0, 256)
            cv.tmot2 = rr(0, 256)
            cv.tfuel = rr(0, 256)
            cv.ub = rr(0, 21)
        if b % 10 == 0:
            cv.gear = gear % 5
            cv.B_autoshiften_ems = gear % 2
            cv.B_launch = 1-(gear % 2)
            gear += 1
        cv.flush()
        a += 0.05
        b += 1
        time.sleep(0.05)
