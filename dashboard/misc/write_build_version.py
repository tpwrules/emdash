import subprocess
import time

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

f = open("../src_gen/build_version.h", "w")
f.write("#ifndef BUILD_VERSION_H\n#define BUILD_VERSION_H\n\n")
f.write("#define BUILD_VERSION_COMMIT (0x{:08x})\n".format(commit_num))
f.write("#define BUILD_VERSION_TIME ({})\n\n".format(time_num))
f.write("#endif\n")