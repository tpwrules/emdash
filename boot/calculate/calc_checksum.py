import binascii
import struct

# read in the whole memory image
mem = open("mem_img.bin", "rb").read()
# unpack header (first 8 vectors) into 8 32-bit words
header = list(struct.unpack("<8I", mem[:32]))

# crc32 everything but the header
crc = binascii.crc32(mem[32:], 0) & 0xFFFFFFFF
# put CRC and image length into header
header[4] = crc
header[5] = (len(mem) - 32)&0xFFFFFFFF

# recalculate header checksum
# entries must sum to 0, so 8th entry is 0 - sum of first 7 entries
header[7] = 0
for he in header[:7]:
    header[7] -= he
header[7] &= 0xFFFFFFFF

# open up text section and write new header back in
ts = open("text.bin", "rb+")
ts.seek(0, 0)
ts.write(struct.pack("<8I", *header))
ts.close()