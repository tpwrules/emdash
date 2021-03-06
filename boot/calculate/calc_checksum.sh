#!/bin/sh

# argument $1 is input filename

# extract memory image
arm-none-eabi-objcopy -O binary "$1" mem_img.bin
# extract just text section (header is at beginning)
arm-none-eabi-objcopy -j .text -O binary "$1" text.bin

PYSRCPATH="$(dirname "$0")"/calc_checksum.py

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

# put the text section (with new header) back into the file
arm-none-eabi-objcopy --update-section .text=text.bin "$1"

rm text.bin mem_img.bin
