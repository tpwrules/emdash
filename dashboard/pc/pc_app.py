#!/usr/bin/env python3

import threading
import queue
import time
import numpy as np
import os

import sys

# in reality, the active area of the display is
# 127.15mm * 33.87mm
SCALE_FACTOR_INT = 3
SCALE_FACTOR_REAL = 2.715

if "realsize" in sys.argv[1:]:
    SCALE = SCALE_FACTOR_REAL
else:
    SCALE = SCALE_FACTOR_INT

do_can_logging = False
if "log" in sys.argv[1:]:
    do_can_logging = True

output_can = False
if "canout" in sys.argv[1:]:
    output_can = True

# import the shared library made by CFFI
from _pc_app import lib, ffi

# import the generator libraries we use
import sys
import os
# change directory to where this file is located
# so we can find the generator libraries
os.chdir(os.path.join(".", os.path.dirname(__file__)))
# add their directories to path
sys.path.append(os.path.join(os.path.abspath(".."), "pics"))
sys.path.append(os.path.join(os.path.abspath(".."), "can"))

# import the picture list
from piclist import piclist
# and canvar interface
import canvars

# exceptions are funky in callbacks
# exceptions raised in callbacks aren't on the main thread,
# so they will not kill the program
# this decorator solves that by sending a signal to the main thread
# so that everything dies gracefully
def term_main_thread(fn):
    def nfn(*args, **kwargs):
        try:
            fn(*args, **kwargs) # call function of interest
        except:
            import traceback
            import os
            import signal
            # print traceback before we die
            traceback.print_exc()
            # send SIGTERM to main thread
            os.kill(os.getpid(), signal.SIGTERM)
    # set new function name to the same as the
    # one being decorated, so that ffi knows
    # which it is still
    nfn.__name__ = fn.__name__
    return nfn

# set up interrupt stuff

# create a lock that is taken when an interrupt is happening
interrupt_busy_lock = threading.Lock()
interrupts_enabled = False
# and a lock to protect whether interrupts are enabled
interrupts_enabled_lock = threading.Lock()

def set_interrupt_state(enabled):
    global interrupts_enabled
    with interrupts_enabled_lock:
        if enabled:
            if interrupts_enabled == False:
                # release interrupt busy lock
                # to allow interrupts to happen
                interrupt_busy_lock.release()
        else:
            if interrupts_enabled == True:
                # acquire interrupt busy lock
                # to prevent interrupts from happening
                interrupt_busy_lock.acquire()
        interrupts_enabled = enabled

# start with interrupts turned off
# i.e. pretend an interrupt is happening
interrupts_enabled = False
interrupt_busy_lock.acquire()

# we create a condition variable for when an interrupt happens
# it is notified after every interrupt finishes
# when interrupt_wait is called, it waits for a notification
interrupt_happened = threading.Condition()

@ffi.def_extern()
@term_main_thread
def pc_interrupt_disable():
    set_interrupt_state(False)
lib.interrupt_disable = lib.pc_interrupt_disable

@ffi.def_extern()
@term_main_thread
def pc_interrupt_enable():
    set_interrupt_state(True)
lib.interrupt_enable = lib.pc_interrupt_enable

@ffi.def_extern()
@term_main_thread
def pc_interrupt_wait():
    with interrupt_happened:
        # enable interrupts so an interrupt we're waiting for
        # can actually happen. if interrupts are currently
        # disabled, we can't lose a notification because we hold the
        # interrupt_happened lock right now
        set_interrupt_state(True)
        interrupt_happened.wait()
lib.interrupt_wait = lib.pc_interrupt_wait

# the first interrupt is a timer
# which fires every 10 milliseconds
def timer_thread_func():
    next_time = time.perf_counter() + 0.01
    while True:
        with interrupt_busy_lock:
            lib.app_timer_interrupt()
            with interrupt_happened:
                interrupt_happened.notify_all()
        now = time.perf_counter()
        if now < next_time:
            time.sleep(next_time - now)
            next_time += 0.01
        else:
            next_time += 0.01 * int((now-next_time)/0.01 + 1)

timer_thread = threading.Thread(target=timer_thread_func, daemon=True)

# set up graphics emulation stiuff

# there is a queue of graphics operations which need to be acted on
gfx_ops = queue.Queue(maxsize=50)

NUM_TEXT_PAGES = 4
NUM_GRAPHICS_PAGES = 4

@ffi.def_extern()
def pc_scr_show_page(text, page):
    gfx_ops.put(("show",
        page + (NUM_GRAPHICS_PAGES if text else 0)
    ))
lib.scr_show_page = lib.pc_scr_show_page

@ffi.def_extern()
def pc_scr_clear_page(text, page):
    gfx_ops.put(("clear",
        page + (NUM_GRAPHICS_PAGES if text else 0)
    ))
lib.scr_clear_page = lib.pc_scr_clear_page

@ffi.def_extern()
def pc_scr_draw_rect(pixel_addr, w, h, color):
    page = (pixel_addr >> 12) & 0xF
    x = ((pixel_addr & 0x3F) * 6) + (pixel_addr >> 16)
    y = (pixel_addr >> 6) & 0x3F

    gfx_ops.put(("rect", page, 
        (x, y), (w, h), (0, 0, 0) if color else (255, 255, 255))
    )
lib.scr_draw_rect = lib.pc_scr_draw_rect

@ffi.def_extern()
def pc_scr_draw_pic(byte_addr, pic_id, inverted):
    gfx_ops.put(("pic",
        byte_addr >> 12, # page
        ((byte_addr & 0x3F)*6, (byte_addr >> 6) & 0x3F), # x, y
        pic_id, bool(inverted)
    ))
lib.scr_draw_pic = lib.pc_scr_draw_pic

@ffi.def_extern()
def pc_scr_draw_text(text_addr, text):
    gfx_ops.put(("text",
        (text_addr >> 9)+NUM_GRAPHICS_PAGES, # page
        ((text_addr & 0x3F)*6, ((text_addr >> 6)&0x7)*8), # x, y
        ffi.string(text)
    ))
lib.scr_draw_text = lib.pc_scr_draw_text

# set up can emulator

# set up can output logging
if do_can_logging:
    log_start_time = time.monotonic()
    flog = open("can_log.log", "w")

# set up can output if asked
canbus = None
can = None
if output_can:
    import can as can_import
    can = can_import
    canbus = can.interface.Bus(
        bustype='vector',
        app_name='emdash',
        channel=0,
        bitrate=500000)

def can_send(msg_id, data):
    if do_can_logging:
        # mark time the message was sent
        send_time = time.monotonic() - log_start_time
    if output_can:
        msg = can.Message(arbitration_id=msg_id,
            data=list(data),
            extended_id=False)
        canbus.send(msg)
        canbus.flush_tx_buffer()
    # create array in C for the data
    d = ffi.new("uint8_t[]", len(data))
    # put the data into it
    ffi.memmove(d, data, len(data))
    # now call C with it
    with interrupt_busy_lock:
        lib.app_can_interrupt(msg_id, len(data), d)
        # since this is an interrupt, alert that an interrupt happened
        with interrupt_happened:
            interrupt_happened.notify_all()
    # free the array we made (not strictly necessary)
    del d
    if do_can_logging:
        # write message to log file
        flog.write("{},${:x}".format(send_time, msg_id))
        if len(data) > 0:
            flog.write(","+",".join(
                ["${:x}".format(datum) for datum in data]))
        flog.write("\n")
        flog.flush()

def canvar_send(canvar_id, val):
    with interrupt_busy_lock:
        lib.app_canvar_interrupt(canvar_id, val)
        # since this is an interrupt, alert that an interrupt happened
        with interrupt_happened:
            interrupt_happened.notify_all()

# construct a canvar interface for it as we need one too
cv = canvars.CanvarInterface(can_send, canvar_send)

import cangen
can_thread = threading.Thread(target=cangen.do, args=(can_send,cv), daemon=True)

# now get pygame up and running to make the graphics go

import pygame

pygame.init()

# open display
screen = pygame.display.set_mode((int(SCALE*240)+32, int(SCALE*64)+32))
screen.fill((90, 90, 90))

# create surfaces for the screen pages
pages = tuple(map(lambda n: pygame.Surface((240, 64)), 
    range(NUM_GRAPHICS_PAGES+NUM_TEXT_PAGES)))
# start off displaying page 0
tcurr, gcurr = NUM_GRAPHICS_PAGES, 0

composite = pygame.Surface((240, 64))
scomposite = pygame.Surface((int(SCALE*240), int(SCALE*64)))
scomposite_size = scomposite.get_size()

# load font bitmap
font_bitmap = pygame.image.load("../pics/font/font_sim.png").convert()

# load pictures from piclist
pics = []
for pic in piclist:
    # load the picture off disk
    pic_in = pygame.image.load(os.path.join("../pics/", pic.path))
    # blit it onto its own surface
    size = pic_in.get_size()
    source = (0, 0)
    if pic.area is not None:
        source = (pic.area[0], pic.area[1])
        size = (pic.area[2], pic.area[3])
    pic_surf = pygame.Surface(size)
    pic_surf.blit(pic_in, (0, 0), area=(source, size))
    # generate the inverted version
    pic_surf_inv = pygame.Surface(size)
    pic_surf_inv.fill((255, 255, 255))
    pic_surf_inv.blit(pic_surf, (0, 0), special_flags=pygame.BLEND_RGB_SUB)
    # and add to the piclist
    pics.append((pic_surf, pic_surf_inv))

# set up thread for the actual app
app_thread = threading.Thread(target=lib.app_entry, daemon=True)
# and get it running
app_thread.start()
timer_thread.start()
can_thread.start()

buttons = {
    pygame.K_w: "wb_upshift",
    pygame.K_s: "wb_downshift",
    pygame.K_r: "wb_radio",
    pygame.K_t: "wb_traction_knob",
    pygame.K_q: "wb_dash_mode",
    pygame.K_c: "nobus_can_status"
}

traction = 0
cv.wb_traction_knob = 0
cv.flush()

# now enter pygame event loop
dirty = True
frame_clock = pygame.time.Clock()
while True:
    button_changed = False
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            break
        elif event.type == pygame.KEYDOWN:
            try:
                attr = buttons[event.key]
            except:
                continue
            if attr == "wb_traction_knob":
                traction = (traction + 1) % 12
                setattr(cv, attr, traction)
            else:
                setattr(cv, attr, 1)
            button_changed = True
        elif event.type == pygame.KEYUP:
            try:
                attr = buttons[event.key]
            except:
                continue
            if attr == "wb_traction_knob": continue
            setattr(cv, attr, 0)
            button_changed = True
    if event.type == pygame.QUIT:
        break

    if button_changed:
        cv.flush()

    # process pending graphics commands
    while True:
        try:
            cmd = gfx_ops.get(block=False)
        except queue.Empty:
            break

        if cmd[0] != "show" and (cmd[1] == tcurr or cmd[1] == gcurr):
            dirty = True
        page = pages[cmd[1]]
        
        if cmd[0] == "show":
            new = cmd[1]
            if new >= NUM_GRAPHICS_PAGES:
                if new != tcurr:
                    dirty = True
                tcurr = new
            else:
                if new != gcurr:
                    dirty = True
                gcurr = new
        elif cmd[0] == "clear":
            if cmd[1] >= NUM_GRAPHICS_PAGES:
                page.fill((0, 0, 0))
            else:
                page.fill((255, 255, 255))
        elif cmd[0] == "rect":
            page.fill(cmd[4], rect=cmd[2:4])
        elif cmd[0] == "pic":
            page.blit(pics[cmd[3]][1 if cmd[4] else 0], cmd[2])
        elif cmd[0] == "text":
            x, y = cmd[2]
            for c in cmd[3]:
                page.blit(font_bitmap, (x, y),
                    area=((6*(c%16), 8*(c>>4)), (6, 8)))
                x += 6

    if dirty:
        aa = pygame.surfarray.pixels2d(pages[gcurr])
        ba = pygame.surfarray.pixels2d(pages[tcurr])
        ca = pygame.surfarray.pixels2d(composite)
        np.bitwise_xor(aa, ba, out=ca)
        del aa, ba, ca
        pygame.transform.scale(composite, scomposite_size, scomposite)
        screen.blit(scomposite, (16, 16))
        dirty = False
        pygame.display.flip()

    frame_clock.tick(40)
