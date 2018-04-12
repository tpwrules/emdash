import threading
import queue
import time

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

# we create a condition variable for when an interrupt happens
# it is notified after every interrupt finishes
# when interrupt_wait is called, it waits for a notification
interrupt_happened = threading.Condition()

@ffi.def_extern()
@term_main_thread
def interrupt_wait():
    with interrupt_happened:
        interrupt_happened.wait()
lib.pc_reg_interrupt_wait(lib.interrupt_wait)

# the first interrupt is a timer
# which fires (currently) every second
def timer_thread_func():
    while True:
        lib.app_timer_interrupt()
        with interrupt_happened:
            interrupt_happened.notify_all()

        time.sleep(1)
timer_thread = threading.Thread(target=timer_thread_func, daemon=True)

# set up graphics emulation stiuff

# there is a queue of graphics operations which need to be acted on
gfx_ops = queue.Queue(maxsize=100)

@ffi.def_extern()
@term_main_thread
def scr_draw_text(x, y, text, inverted):
    gfx_ops.put(("text",
        x, y,
        ffi.string(text),
        True if inverted else False
    ))
lib.pc_reg_scr_draw_text(lib.scr_draw_text)

@ffi.def_extern()
@term_main_thread
def scr_draw_rect(x, y, w, h, white):
    gfx_ops.put(("rect",
        x, y, w, h,
        True if white else False
    ))
lib.pc_reg_scr_draw_rect(lib.scr_draw_rect)


# set up can emulator

def can_send(msgid, data):
    # create array in C for the data
    d = ffi.new("uint8_t[]", len(data))
    # put the data into it
    ffi.memmove(d, data, len(data))
    # now call C with it
    lib.app_can_interrupt(msgid, len(data), d)
    # free the array we made (not strictly necessary)
    del d
    # since this is an interrupt, alert that an interrupt happened
    with interrupt_happened:
        interrupt_happened.notify_all()

import can
can_thread = threading.Thread(target=can.do, args=(can_send,), daemon=True)

# now get pygame up and running to make the graphics go

import pygame

pygame.init()

# open display
screen = pygame.display.set_mode((3*240+32, 3*64+32))
screen.fill((90, 90, 90))

# create surfaces for the screen data
scr_gfx = pygame.Surface((240, 64))
scr_gfx.fill((255, 255, 255))
scr_text = pygame.Surface((240, 64))
scr_text.fill((255, 255, 255))

# load font bitmap
font_bitmap = pygame.image.load("../pics/font/font.png").convert()
font_bitmap_inv = pygame.Surface(font_bitmap.get_size())
font_bitmap_inv.fill((255, 255, 255))
font_bitmap_inv.blit(font_bitmap, (0, 0), special_flags=pygame.BLEND_RGB_SUB)

# set up thread for the actual app
app_thread = threading.Thread(target=lib.app_entry, daemon=True)
# and get it running
app_thread.start()
timer_thread.start()
can_thread.start()

# now enter pygame event loop
dirty = True
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
        dirty = True

        if cmd[0] == "text":
            y = cmd[2]*8
            x = cmd[1]*6
            bm = font_bitmap_inv if cmd[4] else font_bitmap
            for c in cmd[3]:
                sp = (6*(c%16), 8*(c>>4))
                scr_text.blit(bm, (x, y), area=(sp, (6, 8)))
                x += 6
        elif cmd[0] == "rect":
            color = (255, 255, 255) if cmd[5] else (0, 0, 0)
            scr_gfx.fill(color, rect=((cmd[1], cmd[2]), (cmd[3], cmd[4])))

    if dirty:
        screen.blit(pygame.transform.scale(scr_gfx, (3*240, 3*64)), (16, 16))
        screen.blit(pygame.transform.scale(scr_text, (3*240, 3*64)), (16, 16), 
            special_flags=pygame.BLEND_RGB_MIN)
        dirty = False
        pygame.display.flip()

    time.sleep(0.05)
