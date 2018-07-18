#!/usr/bin/env python3

# this script calls the various scripts which build the code
# in the src_gen directory

import sys
import os

def build():
    # change directory to where this file is located
    # so we can find the other scripts
    os.chdir(os.path.join(".", os.path.dirname(__file__)))

    # add the other scripts to the path so we can import them
    sys.path.append(os.path.abspath("misc"))

    # import said other scripts
    import write_build_version


    # call their functions
    write_build_version.do_write()

    print("SOURCE GENERATED SUCCESSFULLY")

if __name__ == "__main__":
    build()