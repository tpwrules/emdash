import threading
import queue
import time
import numpy as np

# import the shared library made by CFFI
from _app import lib, ffi

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

# create a lock that represents interrupts being enable
# when the lock is taken, interrupts cannot happen
interrupt_lock = threading.Lock()
# start with interrupts turned off
interrupt_lock.acquire()

# we create a condition variable for when an interrupt happens
# it is notified after every interrupt finishes
# when interrupt_wait is called, it waits for a notification
interrupt_happened = threading.Condition()

@ffi.def_extern()
@term_main_thread
def pc_interrupt_disable():
    interrupt_lock.acquire()
lib.interrupt_disable = lib.pc_interrupt_disable

@ffi.def_extern()
@term_main_thread
def pc_interrupt_enable():
    interrupt_lock.release()
lib.interrupt_enable = lib.pc_interrupt_enable

@ffi.def_extern()
@term_main_thread
def pc_interrupt_wait():
    with interrupt_happened:
        interrupt_lock.release()
        interrupt_happened.wait()
lib.interrupt_wait = lib.pc_interrupt_wait

# the first interrupt is a timer
# which fires every 10 milliseconds
def timer_thread_func():
    next_time = time.perf_counter() + 0.01
    while True:
        with interrupt_lock:
            lib.app_timer_interrupt()
            with interrupt_happened:
                interrupt_happened.notify_all()
        now = time.perf_counter()
        if now < next_time:
            time.sleep(next_time - now)
        next_time += 0.01

timer_thread = threading.Thread(target=timer_thread_func, daemon=True)

# set up graphics emulation stiuff

# there is a queue of graphics operations which need to be acted on
gfx_ops = queue.Queue(maxsize=10)

NUM_TEXT_PAGES = 2
NUM_GRAPHICS_PAGES = 2

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
    # here we do the hard work of selecting the rectangles
    page = pixel_addr >> 14
    x = pixel_addr & 0xFF
    y = (pixel_addr >> 8) & 0x3F

    # get RGB triplet for color bit
    gc = lambda b: (0, 0, 0) if b else (255, 255, 255)

    # there are three regions:
    #   * the start of the byte to the start of the rect
    l = x & 0xF8
    #   * the start of the rect to the end of the rect
    m = x
    #   * the end of the rect to the end of the byte
    r = m + w
    e = (m+w+7)&0xF8

    # collapse regions if they have the same color
    if bool(color & 2) == bool(color & 1):
        l = m
    if bool(color & 4) == bool(color & 1):
        r = e

    rects = []
    # draw regions if they are > 0
    if m > l:
        rects.append(((l, y), (m-l, h), gc(color & 2)))
    rects.append(((m, y), (r-m, h), gc(color & 1)))
    if e > r:
        rects.append(((r, y), (e-r, h), gc(color & 4)))

    gfx_ops.put(("rect", page, tuple(rects)))
lib.scr_draw_rect = lib.pc_scr_draw_rect

@ffi.def_extern()
def pc_scr_draw_pic(byte_addr, pic_id, inverted):
    gfx_ops.put(("pic",
        byte_addr >> 11, # page
        ((byte_addr & 0x1F)*8, (byte_addr >> 5) & 0x3F), # x, y
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

def can_send(msgid, data):
    # create array in C for the data
    d = ffi.new("uint8_t[]", len(data))
    # put the data into it
    ffi.memmove(d, data, len(data))
    # now call C with it
    with interrupt_lock:
        lib.app_can_interrupt(msgid, len(data), d)
        # since this is an interrupt, alert that an interrupt happened
        with interrupt_happened:
            interrupt_happened.notify_all()
    # free the array we made (not strictly necessary)
    del d

import can
can_thread = threading.Thread(target=can.do, args=(can_send,), daemon=True)

# now get pygame up and running to make the graphics go

import pygame

pygame.init()

# open display
screen = pygame.display.set_mode((3*240+32, 3*64+32))
screen.fill((90, 90, 90))

# create surfaces for the screen pages
pages = tuple(map(lambda n: pygame.Surface((240, 64)), 
    range(NUM_GRAPHICS_PAGES+NUM_TEXT_PAGES)))
# start off displaying page 0
tcurr, gcurr = NUM_GRAPHICS_PAGES, 0

composite = pygame.Surface((240, 64))
scomposite = pygame.Surface((3*240, 3*64))

# load font bitmap
font_bitmap_inv = pygame.image.load("../pics/font/font.png").convert()
font_bitmap = pygame.Surface(font_bitmap_inv.get_size())
font_bitmap.fill((255, 255, 255))
font_bitmap.blit(font_bitmap_inv, (0, 0), special_flags=pygame.BLEND_RGB_SUB)
del font_bitmap_inv

# just for testing
four = pygame.image.load("../pics/four.png").convert()
four_inv = pygame.Surface(four.get_size())
four_inv.fill((255, 255, 255))
four_inv.blit(four, (0, 0), special_flags=pygame.BLEND_RGB_SUB)

# set up thread for the actual app
app_thread = threading.Thread(target=lib.app_entry, daemon=True)
# and get it running
app_thread.start()
timer_thread.start()
can_thread.start()

# now enter pygame event loop
dirty = True
frame_clock = pygame.time.Clock()
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            break
    if event.type == pygame.QUIT:
        break

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
            for r in cmd[2]:
                page.fill(r[2], rect=r[:2])
        elif cmd[0] == "pic":
            pic = four_inv if cmd[4] else four
            page.blit(pic, cmd[2])
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
        pygame.transform.scale(composite, (3*240, 3*64), scomposite)
        screen.blit(scomposite, (16, 16))
        dirty = False
        pygame.display.flip()

    frame_clock.tick(40)
