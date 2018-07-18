import subprocess
import time
import os

def do_write():
    # change directory to where this file is located
    # so all the generated stuff ends up in the right place
    os.chdir(os.path.join(".", os.path.dirname(__file__)))

    # get the current commit hash from git
    commit_hash = subprocess.check_output(
        ("git", "log", "-1", "--format=%H",
            "../../dashboard", "../../dash_11c24"))

    # we only want the first 8 hex chars
    first = commit_hash[:8]

    commit_num = int(first, 16)

    # now get the current time
    ts = time.strftime('%y%m%d%H%M')
    # and turn it into a number too
    time_num = int(ts)

    # write to file

    f = open("../src_gen/build_version.h", "w")
    f.write("#ifndef BUILD_VERSION_H\n#define BUILD_VERSION_H\n\n")
    f.write("#define BUILD_VERSION_COMMIT (0x{:08x})\n".format(commit_num))
    f.write("#define BUILD_VERSION_TIME ({})\n\n".format(time_num))
    f.write("#endif\n")
    f.close()

if __name__ == "__main__":
    do_write()