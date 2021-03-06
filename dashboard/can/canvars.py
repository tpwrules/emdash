# this file contains the definition of all the relevant can variables
# it generates the appropriate C definitions for the CAN variable processor
# it also contains an interface class that allows Python to easily
# generate compliant can messages

import struct

class Variable:
    def __init__(self,
            # information to get the variable from the message
            # messages are assumed little endian
            name, # variable name. variable is called cv_name
            msg_id, # can ID the variable is in
            size, # size of variable in bits
            start=0, # first bit of the variable
                        # bit 0 is the LSB of byte 0
                        # bit 63 is the MSB of byte 7
            signed=False, # True if variable is signed
            multiplex=None, # Bosch Multiplexer Value. if None, entire msg is not
                            # multiplexed

            # information on acting on the variable
            callback=None, # name of the C function to call when this
                           # variable updates. if None, nothing is called
            ):

        self.name = name
        self.msg_id = msg_id
        self.start = start
        self.size = size
        self.signed = signed
        self.multiplex = multiplex
        self.callback = callback

variables = [
    # current engine speed in units of 1 RPM, max 20000rpm
    Variable(
        name="nmot",
        msg_id=0x773, start=16, size=16, signed=False,
        callback="drive_rpm_update"
    ),

    # current gear
    # 0 = neutral
    # 1-4 = gears 1-4
    Variable(
        name="gear",
        msg_id=0x777, start=0, size=8, signed=False,
        callback="drive_gear_update"
    ),

    # oil pressure in units of 0.05 bar, max 10 bar
    Variable(
        name="poil",
        msg_id=0x77A, start=40, size=8, signed=False, multiplex=1,
        callback="warn_poil_update"
    ),

    # fuel pressure in units of 0.05 bar, max 10 bar
    Variable(
        name="pfuel",
        msg_id=0x77A, start=56, size=8, signed=False, multiplex=1,
        callback="warn_pfuel_update"
    ),

    # oil temperature in units of 1 C, max 150C
    # 0 = -40C
    Variable(
        name="toil",
        msg_id=0x77A, start=40, size=8, signed=False, multiplex=4,
        callback="warn_toil_update"
    ),

    # engine block temperature in units of 1 C, max 150C
    # 0 = -40C
    Variable(
        name="tmot",
        msg_id=0x77A, start=32, size=8, signed=False, multiplex=5,
        callback="warn_tmot_update"
    ),

    # engine water temperature in units of 1 C, max 150C
    # 0 = -40C
    Variable(
        name="tmot2",
        msg_id=0x77A, start=56, size=8, signed=False, multiplex=2,
        callback="warn_tmot2_update"
    ),

    # fuel temperature in units of 1 C, max 80C
    # 0 = -40C
    Variable(
        name="tfuel",
        msg_id=0x77A, start=32, size=8, signed=False, multiplex=4,
        callback="warn_tfuel_update"
    ),

    # vehicle speed in units of 0.01kph, max 120kph
    Variable(
        name="speed",
        msg_id=0x773, start=0, size=16, signed=False,
        callback="drive_speed_update"
    ),

    # battery voltage in millivolts, max 25.5 volts
    Variable(
        name="ub",
        msg_id=0x779, start=0, size=16, signed=False,
        callback="warn_ub_update"
    ),

    # nonzero if transmission is in automatic mode
    Variable(
        name="B_autoshiften_ems",
        msg_id=0x750, start=24, size=8, signed=False,
        callback="drive_B_autoshiften_ems_update"
    ),

    # nonzero if launch control is active
    Variable(
        name="B_launch",
        msg_id=0x750, start=32, size=8, signed=False,
        callback="drive_B_launch_update"
    ),

    # first four bytes of git commit hash in wheel firmware
    Variable(
        name="wb_version_commit",
        msg_id=0x130, start=0, size=32, signed=False,
        callback="version_wb_commit_update"
    ),

    # integer time value of wheel firmware build
    # e.g. for build of 2018-04-20 at 17:55,
    # value is 1804201755
    Variable(
        name="wb_version_build",
        msg_id=0x130, start=32, size=32, signed=False,
        callback="version_wb_build_update"
    ),

    # relevant buttons from wheel
    # all are 0 = released, 1 = pressed
    Variable(
        name="wb_upshift",
        msg_id=0x131, start=8, size=8, signed=False,
        callback="drive_wb_upshift_update"
    ),

    Variable(
        name="wb_downshift",
        msg_id=0x131, start=16, size=8, signed=False,
        callback="drive_wb_downshift_update"
    ),

    Variable(
        name="wb_radio",
        msg_id=0x131, start=32, size=8, signed=False,
        callback="drive_wb_radio_update"
    ),

    # 0-11 to represent the 12 traction knob positions
    Variable(
        name="wb_traction_knob",
        msg_id=0x131, start=48, size=8, signed=False,
        callback="drive_wb_traction_knob_update"
    ),

    Variable(
        name="wb_dash_mode",
        msg_id=0x131, start=24, size=8, signed=False,
        callback="app_wb_dash_mode_update"
    ),

    # throttle plate percentage in units of 0.01%, max 110%
    Variable(
        name="ath",
        msg_id=0x773, start=32, size=16, signed=False,
        callback="modes_m1_ath_update"
    ),

    # throttle pedal percentage in units of 0.01%, max 110%
    Variable(
        name="aps",
        msg_id=0x112, start=0, size=16, signed=False,
        callback="modes_m1_aps_update"
    ),

    # clutch pressure in units of 0.005 bar, max 25 bar
    Variable(
        name="pclutch",
        msg_id=0x500, start=32, size=16, signed=False,
        callback="modes_m1_pclutch_update"
    ),

    # current canbus status (sent internally)
    Variable(
        name="nobus_can_status",
        msg_id=None, size=32, signed=False,
        callback="cv_can_status_update"
    ),

    # current idle cpu percent (sent internally)
    Variable(
        name="nobus_cpu_idle_percent",
        msg_id=None, size=32, signed=False,
        callback="app_cpu_idle_percent_update"
    ),
]

# sort variables by message ID then start byte
variables.sort(key=lambda v: 
    (v.msg_id if v.msg_id is not None else 0xFFFF, v.start))

for i, var in enumerate(variables):
    var.canvar_id = i

if len(variables) >= 255:
    raise Exception("maximum of 254 variables supported")

import threading

class CanvarInterface:
    def __init__(self, can_send, canvar_send):
        self.lock = threading.RLock()

        # the can_send function
        self.can_send = can_send
        self.canvar_send = canvar_send

        # build maps of name -> variable
        # and msg id -> variable
        self.cv_names = {}
        self.cv_msg_ids = {}
        for var in variables:
            self.cv_names[var.name] = var
            if var.msg_id == None: continue
            vars_in_id = self.cv_msg_ids.get(var.msg_id, {})
            vars_for_mpx = vars_in_id.get(var.multiplex, [])
            vars_for_mpx.append(var)
            vars_in_id[var.multiplex]= vars_for_mpx
            self.cv_msg_ids[var.msg_id] = vars_in_id

        self.dirty_ids = {}
        self.dirty_canvars = {}
        self.buffered = True

    def set_buffering(self, buffered):
        # if buffered, can messages are not sent until
        # self.flush() is called
        # if not buffered, they are sent every time
        # a variable is set
        with self.lock:
            if self.buffered:
                self.flush()
            self.buffered = buffered

    def flush(self):
        with self.lock:
            for msg_id in self.dirty_ids:
                self.flush_id(msg_id, clean=False)
            self.dirty_ids = {}
            for canvar_id, val in self.dirty_canvars.items():
                self.canvar_send(canvar_id, val)
            self.dirty_canvars = {}

    def flush_id(self, msg_id, clean=True):
        with self.lock:
            if clean:
                del self.dirty_ids[msg_id]

            for mpx, mpx_vars in self.cv_msg_ids[msg_id].items():
                data = 0 # packed into a 64 bit number
                if mpx is not None:
                    # multiplex ID is first byte
                    data |= mpx

                for var in mpx_vars:
                    # mask the var according to the number of bits
                    # it is declared as
                    try:
                        vm = var.val & (0xFFFFFFFFFFFFFFFF) >> (64-var.size)
                    except:
                        vm = 0
                    # and then OR it into the data number
                    data |= (vm << var.start)

                # pack up the message
                pdata = struct.pack("<Q", data)
                # and send it! it might be longer than necessary
                # but the canvar system won't care
                self.can_send(msg_id, pdata)

    def __setattr__(self, name, value):
        if name == "lock":
            super().__setattr__(name, value)
            return
        with self.lock:
            try:
                # is this setting a variable?
                var = self.cv_names[name]
            except:
                # no, do the regular set thing
                super().__setattr__(name, value)
                return
            # it is, set it
            var.val = value
            # and either mark id as dirty if in buffered mode
            # if in unbuffered mode, flush immediately
            if var.msg_id is not None:
                self.dirty_ids[var.msg_id] = True
            else:
                self.dirty_canvars[var.canvar_id] = value
            if not self.buffered:
                if var.msg_id is not None:
                    self.flush_id(var.msg_id)
                else:
                    self.canvar_send(var.canvar_id, value)

import os

def build_defs():
    # change directory to where this file is located
    # so all the generated stuff ends up in the right place
    os.chdir(os.path.join(".", os.path.dirname(__file__)))

    # write out header file first
    f = open("../src_gen/canvar_defs.h", "w")
    f.write("#ifndef CANVAR_DEFS_H\n#define CANVAR_DEFS_H\n\n")
    f.write("#include <inttypes.h>\n")
    f.write("#include \"../src/canvar.h\"\n\n")

    # write out name definitions first while building the can id map
    # the map contains the index of the first message in that can ID
    can_id_dict = {}
    old_can_id = -1
    for i, var in enumerate(variables):
        if var.msg_id is not None and var.msg_id not in can_id_dict:
            can_id_dict[var.msg_id] = i
        
        f.write("#define CV_ID_{} ({})\n".format(var.name.upper(), i))
        f.write("#define cv_{} (canvar_states[{}])\n".format(var.name, i))

    # build the can id hash map
    can_ids = list(can_id_dict.items())
    can_ids.sort()
    ci_count = 2*len(can_ids)
    ci_map = [0xFF]*ci_count
    for ci, i in can_ids:
        idx = ci % ci_count
        while ci_map[idx] != 0xFF:
            idx = (idx + 1) % ci_count
        ci_map[idx] = i

    # write out the extern defs
    f.write("\nextern volatile canvar_state_t canvar_states[{}];\n".format(len(variables)))
    f.write("extern const canvar_def_t canvar_defs[{}];\n\n".format(len(variables)))

    # and the can id stuff
    f.write("#define CANVAR_NUM_VARS ({})\n".format(len(variables)))
    f.write("#define CANVAR_ID_MAP_COUNT ({})\n".format(ci_count))
    f.write("extern const uint8_t canvar_id_map[{}];\n\n".format(ci_count))

    f.write("#endif\n")
    f.close()

    # now it's time to write out the actual definitions
    f = open("../src_gen/canvar_defs.c", "w")
    f.write("#include \"../src/canvar.h\"\n")
    f.write("#include \"canvar_defs.h\"\n")

    f.write("volatile canvar_state_t canvar_states[{}];\n\n".format(len(variables)))

    # write out prototypes for the callbacks
    unused_callback = False
    for var in variables:
        if var.callback is not None:
            f.write("void {}(uint32_t val);\n".format(var.callback))
        else:
            unused_callback = True

    # only write unused callback if there is such
    # to prevent the compiler whining about an unused unused function
    if unused_callback:
        f.write("\nstatic void unused_callback_dummy(uint32_t val) {}\n")

    f.write("\nconst canvar_def_t canvar_defs[{}] = {{\n".format(len(variables)))
    for var in variables:
        f.write("{{{}, {}, {}, {}, {}, {}}},\n".format(
            var.callback if var.callback is not None else "unused_callback_dummy",
            var.msg_id if var.msg_id is not None else 0xFFFF,
            var.start,
            var.size,
            1 if var.signed and var.size < 32 else 0,
            0xFF if var.multiplex is None else var.multiplex
        ))

    f.write("};\n\n")

    f.write("const uint8_t canvar_id_map[{}] = {{\n".format(ci_count))
    for val in ci_map:
        f.write("{},\n".format(val))
    f.write("};\n")
    
    f.close()

if __name__ == "__main__":
    build_defs()