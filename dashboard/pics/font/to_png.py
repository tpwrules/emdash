import png
import numpy

d = numpy.zeros((8*16, 6*16), dtype='uint8')

f = open("font.h", "r")

def nb():
    while True:
        l = f.readline()
        l = l.split(",")
        if len(l) == 0:
            continue
        n = l[0].strip()
        if len(n) == 4:
            return int(n[2:], 16)

for c in range(256):
    cx = (c % 16)*6
    cy = (int(c / 16))*8
    for l in range(8):
        b = nb()
        for x in range(6):
            if not (b & 0x80):
                d[cy+l,cx+x] = 1
            b <<= 1

f = open("font.png", "wb")
w = png.Writer(6*16, 8*16, greyscale=True, bitdepth=1)
w.write(f, d)