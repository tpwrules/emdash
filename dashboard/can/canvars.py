# this file contains the definition of all the relevant can variables
# it generates the appropriate C definitions for the CAN variable processor

class Variable:
    def __init__(self,
            # information to get the variable from the message
            name, # variable name. variable is called cv_name
            msg_id, # can ID the variable is in
            start, # first byte of the variable
            size, # size of variable in bytes. multibyte values are little endian
            signed, # True if variable is a signed type

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
        self.callback = callback
        self.call_every_time = call_every_time

variables = [
    # current engine speed in RPM
    Variable(
        name="nmot",
        msg_id=0x121, start=2, size=2, signed=False,
        callback="gear_rpm_update", call_every_time=False
    ),

    # current gear (units ?????)
    Variable(
        name="gear",
        msg_id=0x119, start=7, size=1, signed=False,
        callback="gear_gear_update", call_every_time=False
    )
]

if len(variables) > 255:
    raise Exception("too many variables")

# sort variables by message ID then start byte
variables.sort(key=lambda v: (v.msg_id, v.start))

# write out header file first
f = open("canvar_defs.h", "w")
f.write("#ifndef CANVAR_DEFS_H\n#define CANVAR_DEFS_H\n\n")
f.write("#include <inttypes.h>\n")
f.write("#include \"canvar.h\"\n\n")

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
ci_vals = [0xFF]*ci_count
for ci, i in can_ids:
    ci_vals[ci-ci_first] = i

# write out the extern defs
f.write("\nextern canvar_state_t canvar_states[{}];\n".format(len(variables)))
f.write("extern const canvar_def_t canvar_defs[{}];\n\n".format(len(variables)))

# and the can id stuff
f.write("#define CANVAR_ID_MAP_FIRST ({})\n".format(ci_first))
f.write("#define CANVAR_ID_MAP_COUNT ({})\n".format(ci_count))
f.write("extern const uint8_t canvar_id_map[{}];\n\n".format(ci_count))

f.write("#endif\n")
f.close()

# now it's time to write out the actual definitions
f = open("canvar_defs.c", "w")
f.write("#include \"canvar.h\"\n")
f.write("#include \"canvar_defs.h\"\n\n")

f.write("canvar_state_t canvar_states[{}];\n\n".format(len(variables)))

f.write("const canvar_def_t canvar_defs[{}] = {{\n".format(len(variables)))
for var in variables:
    f.write("{{{}, {}, {}, {}, {}, {}}},\n".format(
        var.callback if var.callback is not None else 0,
        var.msg_id,
        var.start,
        var.size,
        1 if var.signed else 0,
        1 if var.call_every_time else 0
    ))

f.write("};\n\n")

f.write("const uint8_t canvar_id_map[{}] = {{\n".format(ci_count))
for val in ci_vals:
    f.write("{},\n".format(val))
f.write("};\n")