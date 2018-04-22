# send CAN messages to the application for simulation purposes

import time
import random
import struct
import math

import random
rr = random.randrange

def do(fn, cv):
    global can_send
    can_send = fn

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
        cv.speed = int(max(min(v, 12000), 0))
        if b % 40 == 0:
            cv.poil = rr(0, 201)
            cv.pfuel = rr(0, 201)
            cv.toil = rr(-40, 151)+40
            cv.tmot = rr(-40, 151)+40
            cv.tmot2 = rr(-40, 151)+40
            cv.tfuel = rr(-40, 81)+40
            cv.ub = rr(0, 25501)
            cv.ath = rr(0, 11101)
            cv.pclutch = rr(0, 501)
        if b % 10 == 0:
            cv.gear = gear % 5
            cv.B_autoshiften_ems = gear % 2
            cv.B_launch = 1-(gear % 2)
            gear += 1
        cv.flush()
        a += 0.05
        b += 1
        time.sleep(0.05)
