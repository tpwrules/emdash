#!/bin/bash

set -e

# argument $1 is input filename

arm-none-eabi-objcopy -O binary "$1" mem_img.bin
arm-none-eabi-objcopy -j .text -O binary "$1" text.bin

PYSRCPATH="$(dirname "$0")"/calc_checksum.py

PYTHON=`which python3`

if [ $? -eq 0 ]; then
    # we have python3
    python3 "$PYSRCPATH"
else
    # welp, may as well roll with it
    # maybe it's 3 idk lol
    python "$PYSRCPATH"
fi

arm-none-eabi-objcopy --update-section .text=text.bin "$1"

rm text.bin mem_img.bin