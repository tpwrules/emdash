from cffi import FFI

fb = FFI()

# define the functions we will call from Python
# this includes:
#   * the app entry point
#   * interrupt functions
#   * platform interface callback registrations
fb.cdef(r"""
    void app_entry();

    void app_timer_interrupt();
    void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data);

    extern "Python" void interrupt_wait();
    void pc_reg_interrupt_wait(void (*cb)());

    extern "Python" void scr_draw_text(uint8_t x, uint8_t y, char* text, uint8_t inverted);
    void pc_reg_scr_draw_text(void (*cb)(uint8_t x, uint8_t y, char* text, uint8_t inverted));

    extern "Python" void scr_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t white);
    void pc_reg_scr_draw_rect(void (*cb)(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t white));

    extern "Python" void scr_draw_pic(uint8_t x, uint8_t y, uint32_t pic, uint8_t inverted);
    void pc_reg_scr_draw_pic(void (*cb)(uint8_t x, uint8_t y, uint32_t pic, uint8_t inverted));
""")

# the source is just linking against the app linked library
# we define the macro PLATFORM_PC to tell that this is the PC
fb.set_source('_app',
    r"""
    """,
    libraries=['app'],
    define_macros=[('PLATFORM_PC', 'yes')])

# finally, compile the code into a Python library
fb.compile(verbose=True)