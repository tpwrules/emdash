import subprocess
import time
import os

def do_write():
    # change directory to where this file is located
    # so all the generated stuff ends up in the right place
    os.chdir(os.path.join(".", os.path.dirname(__file__)))

    # get the current commit hash from git
    commit_hash = subprocess.check_output(
        ("git", "log", "-1", "--format=%H"))

    # we only want the first 8 hex chars
    first = commit_hash[:8]

    commit_num = int(first, 16)

    # now get the current time
    ts = time.strftime('%y%m%d%H%M')
    # and turn it into a number too
    time_num = int(ts)

    # write to file

    f = open("../src_gen/build_version_msg.h", "w")
    f.write("#ifndef BUILD_VERSION_MSG_H\n#define BUILD_VERSION_MSG_H\n\n")
    f.write("#define BUILD_VERSION_COMMIT (0x{:08x})\n".format(commit_num))
    f.write("#define BUILD_VERSION_TIME ({})\n\n".format(time_num))

    # write out CAN message structure
    bignum = time_num << 32 | commit_num
    f.write("#include \"chip.h\"\n\n")
    f.write("static const CCAN_MSG_OBJ_T build_version_msg = {\n")
    f.write("    0x130, 0,\n    {")
    for i in range(8):
        f.write("0x{:02x},".format(bignum&0xFF))
        bignum >>= 8
    f.write("},\n    8, 1\n};\n\n")

    f.write("#endif\n")
    f.close()

if __name__ == "__main__":
    do_write()