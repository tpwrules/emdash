import png
import numpy

d = numpy.zeros((8*16, 6*16), dtype='uint8')
d2 = numpy.zeros((64, 256), dtype='uint8')

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
        b2 = b
        for x in range(6):
            if b & 0x80:
                d[cy+l,cx+x] = 1
            b <<= 1
        for x in range(8):
            if not (b2 & 0x80):
                d2[c >> 2,((c & 3) << 6) + (l << 3) + x] = 1
            b2 <<= 1

f = open("font_sim.png", "wb")
w = png.Writer(6*16, 8*16, greyscale=True, bitdepth=1)
w.write(f, d)

f = open("font_pic.png", "wb")
w = png.Writer(256, 64, greyscale=True, bitdepth=1)
w.write(f, d2)