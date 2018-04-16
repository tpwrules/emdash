from cffi import FFI

fb = FFI()

# define the functions we will call from Python
# this includes:
#   * the app entry point
#   * interrupt functions
#   * platform interface callback registrations
fb.cdef(r"""
    void app_entry(void);
    void app_timer_interrupt(void);
    void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data);

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
    void app_can_interrupt(uint32_t msgid, uint8_t dlc, uint8_t *data);

    extern void (*interrupt_disable)(void);
    extern void (*interrupt_enable)(void);
    extern void (*interrupt_wait)(void);

    #define PCFUNC(type, name) extern type (*name)
    PCFUNC(void, scr_show_page)(uint8_t text, uint8_t page);
    PCFUNC(void, scr_clear_page)(uint8_t text, uint8_t page);
    PCFUNC(void, scr_draw_rect)(uint32_t pixel_addr, uint8_t w, uint8_t h, uint8_t color);
    PCFUNC(void, scr_draw_pic)(uint32_t byte_addr, uint32_t pic_id, uint8_t inverted);
    PCFUNC(void, scr_draw_text)(uint32_t text_addr, char *text);

    """,
    libraries=['app'],
    define_macros=[('PLATFORM_PC', 'yes')])

# finally, compile the code into a Python library
fb.compile(verbose=True)