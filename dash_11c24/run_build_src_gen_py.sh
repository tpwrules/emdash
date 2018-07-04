#!/bin/sh

PYSRCPATH="$(dirname "$0")"/../dashboard/build_src_gen.py

PYTHON=`which python3`
if [ $? -eq 0 ]; then
    # we have python3
    python3 "$PYSRCPATH"
else
    # check for the Windows `py` shortcut
    PY=`which py`
    if [ $? -eq 0 ]; then
        # ask to run it as python 3
        py -3 "$PYSRCPATH"
    else
        # python 3 doesn't seem to be installed
        echo "Python 3 not installed?"
        exit 1
    fi
fi
