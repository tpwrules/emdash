#!/usr/bin/env python3

from cffi import FFI
from glob import glob

# call build_src_gen.py to make sure that is up to date
import sys
import os
# change directory to where this file is located
# so we can find everything
fpath = os.path.abspath(os.path.join(".", os.path.dirname(__file__)))
os.chdir(fpath)
sys.path.append(os.path.abspath(".."))
import build_src_gen
build_src_gen.build()

# re change directory cause the above changed it
os.chdir(fpath)

# build list of source files for the PC version
sources = [
    "../src_gen/canvar_defs.c"
]
sources.extend(glob("../src/*.c"))

fb = FFI()

# define the functions we will call from Python
# this includes:
#   * the app entry point
#   * interrupt functions
#   * platform interface callback registrations
fb.cdef(r"""
    void app_entry(void);
    void app_timer_interrupt(void);
    void app_can_interrupt(uint32_t msg_id, uint8_t dlc, const uint8_t *data);
    void app_canvar_interrupt(uint8_t cv_id, uint32_t val);

    extern "Python" void pc_interrupt_disable();
    extern "Python" void pc_interrupt_enable();
    extern "Python" void pc_interrupt_wait();

    void (*interrupt_disable)(void);
    void (*interrupt_enable)(void);
    void (*interrupt_wait)(void);

    extern "Python" void pc_scr_show_page(uint8_t text, uint8_t page);
    extern "Python" void pc_scr_clear_page(uint8_t text, uint8_t page);
    extern "Python" void pc_scr_draw_rect(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color);
    extern "Python" void pc_scr_draw_pic(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted);
    extern "Python" void pc_scr_draw_text(uint32_t text_addr, char *text);

    void (*scr_show_page)(uint8_t text, uint8_t page);
    void (*scr_clear_page)(uint8_t text, uint8_t page);
    void (*scr_draw_rect)(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color);
    void (*scr_draw_pic)(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted);
    void (*scr_draw_text)(uint32_t text_addr, char *text);

""")

# the source is just linking against the app linked library
# we define the macro PLATFORM_PC to tell that this is the PC
fb.set_source('_pc_app',
    r"""
    void app_entry(void);
    void app_timer_interrupt(void);
    void app_can_interrupt(uint32_t msg_id, uint8_t dlc, const uint8_t *data);
    void app_canvar_interrupt(uint8_t cv_id, uint32_t val);

    void (*interrupt_disable)(void);
    void (*interrupt_enable)(void);
    void (*interrupt_wait)(void);

    #define PCFUNC(type, name) type (*name)
    PCFUNC(void, scr_show_page)(uint8_t text, uint8_t page);
    PCFUNC(void, scr_clear_page)(uint8_t text, uint8_t page);
    PCFUNC(void, scr_draw_rect)(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color);
    PCFUNC(void, scr_draw_pic)(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted);
    PCFUNC(void, scr_draw_text)(uint32_t text_addr, char *text);

    """,
    sources=sources,
    define_macros=[('PLATFORM_PC', 'yes')])

# finally, compile the code into a Python library
fb.compile(verbose=True)

print("PC APP BUILT SUCCESSFULLY")