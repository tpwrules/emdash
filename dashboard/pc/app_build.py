from cffi import FFI

fb = FFI()

# define the functions we will call from Python
# this includes:
#   * the app entry point
fb.cdef(r"""
    void app_entry();
""")

# the source is just linking against the app linked library
# we define the macro PLATFORM_PC to tell that this is the PC
fb.set_source('_app',
    "",
    libraries=['app'],
    define_macros=[('PLATFORM_PC', 'yes')])

# finally, compile the code into a Python library
fb.compile(verbose=True)