import binascii
import struct

# read in the whole memory image
mem = open("mem_img.bin", "rb").read()

# crc32 everything but the first 32 bytes
crc = binascii.crc32(mem[32:], 0) & 0xFFFFFFFF

# get header and sub checksum in
header = list(struct.unpack("<8I", mem[:32]))
header[4] = crc
header[5] = (len(mem) - 32)&0xFFFFFFFF
# recalculate header checksum
header[7] = 0
checksum = 0
for he in header:
    checksum += he
header[7] = (-checksum)&0xFFFFFFFF

# open up text section and write header back in
ts = open("text.bin", "rb+")
ts.seek(0, 0)
ts.write(struct.pack("<8I", *header))
ts.close()