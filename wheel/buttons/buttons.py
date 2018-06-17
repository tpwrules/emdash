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
        debounce_release=50, # time when new button value is zero
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
    Button(
        name="wb_clutch", msg_id=0x131, byte=0,
        update="br_clutch"
    ),
    Button(
        name="wb_upshift", msg_id=0x131, byte=1,
        update="br_upshift"
    ),
    Button(
        name="wb_downshift", msg_id=0x131, byte=2,
        update="br_downshift"
    ),

    Button(
        name="wb_radio", msg_id=0x131, byte=4,
        update="br_radio"
    ),
    Button(
        name="wb_autoshift", msg_id=0x131, byte=5,
        update="br_autoshift"
    ),
    Button(
        name="wb_launch", msg_id=0x131, byte=7,
        update="br_launch"
    ),
    Button(
        name="wb_lap", msg_id=0x132, byte=0,
        update="br_lap"
    )

]

import os

def write_buttons():
    # change directory to where this file is located
    # so all the generated stuff ends up in the right place
    os.chdir(os.path.join(".", os.path.dirname(__file__)))

    # write out header file
    f = open("../src_gen/button_defs.h", "w")
    f.write("#ifndef BUTTON_DEFS_H\n#define BUTTON_DEFS_H\n\n")
    f.write("#include <inttypes.h>\n")
    f.write("#include \"../src_11c24/button_processor.h\"\n\n")

    # build dict of unique message IDs
    # mapped to indexes
    msg_ids = {}
    for button in buttons:
        if button.msg_id not in msg_ids:
            msg_ids[button.msg_id] = len(msg_ids)
    if len(msg_ids) > 31:
        raise Exception("maximum of 31 unique message IDs allowed")
    if version_message_id in msg_ids:
        raise Exception("version message ID not allowed as button message ID")

    # write out top definitions
    f.write("#define WHEEL_VERSION_MESSAGE_ID (0x{:03x})\n\n".format(
        version_message_id))
    f.write("#define BP_NUM_BUTTONS ({})\n".format(len(buttons)))
    f.write("#define BP_NUM_CAN_MESSAGES ({})\n\n".format(len(msg_ids)))

    # write out button table definitions
    for i, button in enumerate(buttons):
        f.write("#define BTN_ID_{} ({})\n".format(button.name.upper(), i))
        f.write("#define btn_{} (button_states[{}])\n".format(button.name, i))

    # write out extern defs
    f.write("\nextern msg_state_t msg_states[BP_NUM_CAN_MESSAGES];\n")
    f.write("extern button_state_t button_states[BP_NUM_BUTTONS];\n")
    f.write("extern const button_def_t button_defs[BP_NUM_BUTTONS];\n\n")

    f.write("#endif\n")
    f.close()

    # now it's real definition time
    f = open("../src_gen/button_defs.c", "w")
    f.write("#include \"../src_11c24/button_processor.h\"\n")
    f.write("#include \"button_defs.h\"\n\n")

    # write out message states
    # these actually get initialized
    f.write("msg_state_t msg_states[BP_NUM_CAN_MESSAGES] = {\n")
    for msg_id, msg_idx in msg_ids.items():
        f.write("    {{{{0x{:03x}, 0, {{0,0,0,0,0,0,0,0}}, 8, {}}}".format(
            msg_id, msg_idx+2))
        f.write(", 0},\n")

    f.write("};\n\n")

    # write out button function prototypes
    for button in buttons:
        f.write("uint8_t {}(void);\n".format(button.update))

    # write out button definitions
    f.write("\nconst button_def_t button_defs[BP_NUM_BUTTONS] = {\n")
    for bi, button in enumerate(buttons):
        f.write("    {{{}, {}, {}, {}, {}}},\n".format(
            button.update, msg_ids[button.msg_id],
            button.byte, button.debounce_press, button.debounce_release))

    f.write("};\n\n")

    # button states just get initialized to zero
    f.write("button_state_t button_states[BP_NUM_BUTTONS];\n")

    # and now we are done
    f.close()

if __name__ == "__main__":
    write_buttons()