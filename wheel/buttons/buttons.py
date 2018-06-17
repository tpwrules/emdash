# this file contains the definitions of the buttons and their
# CAN variables
# it generates the appropriate C definitions for the button processor

class Button:
    def __init__(self,
        # information about the button's CAN variable
        name, # variable name
        msg_id, # can ID the variable is in
        byte, # which byte of the message the variable is in

        # information about the button itself
        update, # name of the C function to call to get button's value
        # debouncing information
        # the processor waits for the button state to be stable for this
        # amount of ms before accepting it
        debounce_press=10, # time when new button value is non-zero
        debounce_release=100, # time when new button value is zero
        ):

    self.name = name
    self.msg_id = msg_id
    self.byte = byte
    self.update = update
    self.debounce_press = debounce_press
    self.debounce_release = debounce_release

# can ID of the version number message sent by the wheel
version_message_id = 0x130

buttons = [
    Button(
        name="wb_dash_mode", msg_id=0x131, byte=3,
        update="br_dash_mode"
    ),
]