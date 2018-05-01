#!/bin/bash

cd "$(dirname "$0")"

PYTHON=`which python3`

if [ $? -eq 0 ]; then
    # we have python3
    python3 ../dashboard/build_src_gen.py
else
    # welp, may as well roll with it
    # maybe it's 3 idk lol
    python ../dashboard/build_src_gen.py
fi