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

    cv.poil = 0
    cv.pfuel = 0
    cv.toil = 40
    cv.tmot = 40
    cv.tmot2 = 40
    cv.tfuel = 40
    cv.ub = 0

    cv.speed = 0

    cv.B_autoshiften_ems = 1
    cv.B_launch = 1
    cv.wb_upshift = 1
    cv.wb_downshift = 1
    cv.wb_traction_knob = 0
    cv.wb_radio = 1
