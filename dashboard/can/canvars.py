# this file contains the definition of all the relevant can variables
# it generates the appropriate C definitions for the CAN variable processor
# it also contains an interface class that allows Python to easily
# generate compliant can messages

import struct

class Variable:
    def __init__(self,
            # information to get the variable from the message
            name, # variable name. variable is called cv_name
            msg_id, # can ID the variable is in
            start, # first byte of the variable
            size, # size of variable in bytes. multibyte values are little endian
            signed, # True if variable is a signed type
            multiplex=None, # Multiplexer Value. if None, entire msg is not
                            # multiplexed

            # information on acting on the variable
            callback=None, # name of the C function to call when this
                           # variable updates. if None, nothing is called
            call_every_time=False # if True, the function is called every time
                                  # the message is received. If false, it is
                                  # only called when the value has changed
            ):

        self.name = name
        self.msg_id = msg_id
        self.start = start
        self.size = size
        self.signed = signed
        self.multiplex = multiplex
        self.callback = callback
        self.call_every_time = call_every_time

variables = [
    # current engine speed in units of 1 RPM, max 20000rpm
    Variable(
        name="nmot",
        msg_id=0x773, start=2, size=2, signed=False,
        callback="drive_rpm_update", call_every_time=False
    ),

    # current gear
    # 0 = neutral
    # 1-4 = gears 1-4
    Variable(
        name="gear",
        msg_id=0x119, start=7, size=1, signed=False,
        callback="drive_gear_update", call_every_time=False
    ),

    # oil pressure in units of 0.05 bar, max 10 bar
    Variable(
        name="poil",
        msg_id=0x77A, start=5, size=1, signed=False, multiplex=1,
        callback="warn_poil_update", call_every_time=False
    ),

    # fuel pressure in units of 0.05 bar, max 10 bar
    Variable(
        name="pfuel",
        msg_id=0x77A, start=7, size=1, signed=False, multiplex=1,
        callback="warn_pfuel_update", call_every_time=False
    ),

    # oil temperature in units of 1 C, max 150C
    # 0 = -40C
    Variable(
        name="toil",
        msg_id=0x77A, start=5, size=1, signed=False, multiplex=4,
        callback="warn_toil_update", call_every_time=False
    ),

    # engine block temperature in units of 1 C, max 150C
    # 0 = -40C
    Variable(
        name="tmot",
        msg_id=0x77A, start=4, size=1, signed=False, multiplex=5,
        callback="warn_tmot_update", call_every_time=False
    ),

    # engine water temperature in units of 1 C, max 150C
    # 0 = -40C
    Variable(
        name="tmot2",
        msg_id=0x77A, start=7, size=1, signed=False, multiplex=2,
        callback="warn_tmot2_update", call_every_time=False
    ),

    # fuel temperature in units of 1 C, max 80C
    # 0 = -40C
    Variable(
        name="tfuel",
        msg_id=0x77A, start=4, size=1, signed=False, multiplex=4,
        callback="warn_tfuel_update", call_every_time=False
    ),

    # vehicle speed in units of 0.01kph, max 120kph
    Variable(
        name="speed",
        msg_id=0x121, start=6, size=2, signed=False,
        callback="drive_speed_update", call_every_time=False
    ),

    # battery voltage in millivolts, max 25.5 volts
    Variable(
        name="ub",
        msg_id=0x779, start=0, size=2, signed=False,
        callback="warn_ub_update", call_every_time=False
    ),

    # nonzero if transmission is in automatic mode
    Variable(
        name="B_autoshiften_ems",
        msg_id=0x101, start=2, size=1, signed=False,
        callback="drive_B_autoshiften_ems_update", call_every_time=False
    ),

    # nonzero if launch control is active
    Variable(
        name="B_launch",
        msg_id=0x119, start=2, size=1, signed=False,
        callback="drive_B_launch_update", call_every_time=False
    ),

    # first four bytes of git commit hash in wheel firmware
    Variable(
        name="wb_version_commit",
        msg_id=0x130, start=0, size=4, signed=False,
        callback="version_wb_commit_update", call_every_time=False
    ),

    # integer time value of wheel firmware build
    # e.g. for build of 2018-04-20 at 17:55,
    # value is 1804201755
    Variable(
        name="wb_version_build",
        msg_id=0x130, start=4, size=4, signed=False,
        callback="version_wb_build_update", call_every_time=False
    ),

    # relevant buttons from wheel

    Variable(
        name="wb_upshift",
        msg_id=0x131, start=1, size=1, signed=False,
        callback="drive_wb_upshift_update", call_every_time=False
    ),

    Variable(
        name="wb_downshift",
        msg_id=0x131, start=2, size=1, signed=False,
        callback="drive_wb_downshift_update", call_every_time=False
    ),

    Variable(
        name="wb_radio",
        msg_id=0x131, start=4, size=1, signed=False,
        callback="drive_wb_radio_update", call_every_time=False
    ),

    Variable(
        name="wb_traction_knob",
        msg_id=0x131, start=6, size=1, signed=False,
        callback="drive_wb_traction_knob_update", call_every_time=False
    ),

    Variable(
        name="wb_dash_mode",
        msg_id=0x131, start=3, size=1, signed=False,
        callback="app_wb_dash_mode_update", call_every_time=False
    ),

    # throttle plate percentage in units of 0.01%, max 110%
    Variable(
        name="ath",
        msg_id=0x101, start=0, size=2, signed=False,
        callback="modes_m1_ath_update", call_every_time=False
    ),

    # clutch pressure in units of 0.005 bar, max 25 bar
    Variable(
        name="pclutch",
        msg_id=0x37C, start=0, size=2, signed=False,
        callback="modes_m1_pclutch_update", call_every_time=False
    )
]

# sort variables by message ID then start byte
variables.sort(key=lambda v: (v.msg_id, v.start))

if len(variables) > 256:
    raise Exception("too many variables")

import threading

class CanvarInterface:
    def __init__(self, fn):
        self.lock = threading.RLock()

        # the can_send function
        self.can_send = fn

        # build maps of name -> variable
        # and msg id -> variable
        self.cv_names = {}
        self.cv_msg_ids = {}
        for var in variables:
            self.cv_names[var.name] = var
            vars_in_id = self.cv_msg_ids.get(var.msg_id, [])
            vars_in_id.append(var)
            self.cv_msg_ids[var.msg_id] = vars_in_id

        self.dirty_ids = set()
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
            self.dirty_ids = set()

    def flush_id(self, msg_id, clean=True):
        with self.lock:
            if clean:
                del self.dirty_ids[msg_id]

            pstr = "<" # struct definition for this message
            data = [] # data for this definition
            byte = 0 # byte we are at
            for var in self.cv_msg_ids[msg_id]:
                # pad message to this variable
                while byte < var.start:
                    pstr += "x"
                    byte += 1
                # generate appropriate type character
                c = " bh i"[var.size]
                if not var.signed:
                    c = c.upper()
                pstr += c # and add it to the struct
                # append the data for this var (or 0 if there's none yet)
                try:
                    data.append(var.val)
                except:
                    data.append(0)
                byte += var.size

            # pack up the message
            pdata = struct.pack(pstr, *data)
            # and send it!
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
            # or flush the id in nonbuffered mode
            if self.buffered:
                self.dirty_ids.add(var.msg_id)
            else:
                self.flush_id(var.msg_id)

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
        if var.msg_id not in can_id_dict:
            can_id_dict[var.msg_id] = i
        
        f.write("#define cv_{} (canvar_states[{}])\n".format(var.name, i))

    # build the can id map array
    can_ids = list(can_id_dict.items())
    can_ids.sort()
    ci_first = can_ids[0][0]
    ci_count = can_ids[-1][0] - ci_first + 1
    ci_vals = [0]*ci_count
    for ci, i in can_ids:
        ci_vals[ci-ci_first] = i

    # write out the extern defs
    f.write("\nextern volatile canvar_state_t canvar_states[{}];\n".format(len(variables)))
    f.write("extern const canvar_def_t canvar_defs[{}];\n\n".format(len(variables)))

    # and the can id stuff
    f.write("#define CANVAR_NUM_VARS ({})\n".format(len(variables)))
    f.write("#define CANVAR_ID_MAP_FIRST ({})\n".format(ci_first))
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
    for var in variables:
        if var.callback is not None:
            f.write("void {}(uint32_t val);\n".format(var.callback))

    f.write("\nconst canvar_def_t canvar_defs[{}] = {{\n".format(len(variables)))
    for var in variables:
        f.write("{{{}, {}, {}, {}, {}, {}, {}}},\n".format(
            var.callback if var.callback is not None else 0,
            var.msg_id,
            var.start,
            var.size,
            1 if var.signed else 0,
            1 if var.call_every_time else 0,
            0xFF if var.multiplex is None else var.multiplex
        ))

    f.write("};\n\n")

    f.write("const uint8_t canvar_id_map[{}] = {{\n".format(ci_count))
    for val in ci_vals:
        f.write("{},\n".format(val))
    f.write("};\n")
    
    f.close()

if __name__ == "__main__":
    build_defs()