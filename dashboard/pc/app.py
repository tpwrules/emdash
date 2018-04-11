import threading
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
timer_thread.start()

# call entry point
lib.app_entry()