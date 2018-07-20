# this file contains the list of Pictures available to
# scr_draw_pic
# it must be run to generate the pic data headers

import png
import os

class Picture:
    def __init__(self,
            # path to image as a PNG relative to this file
            path,
            # name of the image. uppercased, then used as PIC_ID_name
            # so only C identifier valid characters please!
            name,
            # area of the original image to use (x, y, w, h)
            # if None, the entire image is used
            area=None):

        self.path = path
        self.name = name.upper()
        self.area = area

# the list itself!
piclist = [
    # the bootsplash
    Picture("bootsplash/boot.png", "bootsplash"),

    # the font (stored as a picture so it can be programmed
    #   into the screen)
    Picture("font/font_pic.png", "font_6x8"),

    # oil pressure warning
    Picture("icons/warning.png", "oil_pressure", (0, 0, 23, 15)),
    # oil temperature warning
    Picture("icons/warning.png", "oil_temp", (0, 16, 23, 15)),
    # water temperature warning
    Picture("icons/warning.png", "water_temp", (24, 0, 23, 15)),
    # block temperature warning
    Picture("icons/warning.png", "block_temp", (24, 16, 23, 15)),
    # fuel pressure warning
    Picture("icons/warning.png", "fuel_pressure", (48, 0, 23, 15)),
    # fuel temperature warning
    Picture("icons/warning.png", "fuel_temp", (48, 16, 23, 15)),
    # battery warning
    Picture("icons/warning.png", "battery", (72, 0, 23, 15)),
    # oil temperature low warning
    Picture("icons/warning.png", "oil_temp_low", (72, 16, 23, 15)),

    # headset icon for radio active
    Picture("icons/buttons.png", "radio", (0, 0, 16, 15)),
    # upshift button icon
    Picture("icons/buttons.png", "upshift_btn", (16, 0, 16, 15)),
    # downshift button icon
    Picture("icons/buttons.png", "downshift_btn", (32, 0, 16, 15)),

    # gear icons
    # these must stay in exactly this order! N, 1, 2, 3, 4
    Picture("gears/gears.png", "gear_neutral", (32*2, 0, 30, 31)),
    Picture("gears/gears.png", "gear_1", (32*5, 0, 30, 31)),
    Picture("gears/gears.png", "gear_2", (32*6, 0, 30, 31)),
    Picture("gears/gears.png", "gear_3", (32*7, 0, 30, 31)),
    Picture("gears/gears.png", "gear_4", (32*8, 0, 30, 31))
]

def pic_encode(pixels):
    # picture data is split into 6 pixel chunks, to be compatible
    # with 6x8 mode on the controller
    # encode pictures by using high two bits of byte as RLE
    # low six bits are picture data
    # 00 -> no zero chunks before picture chunk
    # 01 -> one zero chunk before picture chunk
    # 10 -> two zero chunks before picture chunk
    # 11 -> picture chunk is instead amount of zero chunks - 1

    zeros = 0
    data = bytearray()
    for row in pixels:
        bits = 0
        chunk = 0
        for pixel in row:
            chunk = (chunk << 1) | pixel
            bits += 1
            if bits == 6:
                if chunk == 0:
                    zeros += 1
                else:
                    while zeros > 2:
                        outzeros = min(zeros, 64)
                        data.append((outzeros-1) | 0xC0)
                        zeros -= outzeros
                    if zeros == 0:
                        data.append(chunk)
                    elif zeros == 1:
                        data.append(chunk | 0x40)
                    elif zeros == 2:
                        data.append(chunk | 0x80)
                    zeros = 0
                bits = 0
                chunk = 0

    while zeros > 0:
        outzeros = min(zeros, 64)
        data.append((outzeros-1) | 0xC0)
        zeros -= outzeros

    return data

def write_pic_data():
    # change directory to where this file is located
    # so all the generated stuff ends up in the right place
    os.chdir(os.path.join(".", os.path.dirname(__file__)))

    # write out header with picture names
    f = open("../src_gen/pic_ids.h", "w")
    f.write("#ifndef PIC_IDS_H\n#define PIC_IDS_H\n\n")
    f.write("#define PIC_NUMBER_OF_IDS ({})\n\n".format(len(piclist)))
    for picid, pic in enumerate(piclist):
        f.write("#define PIC_ID_{} ({})\n".format(pic.name, picid))
    f.write("\n#endif\n")
    f.close()

    pic_bytes = bytearray()
    pic_records = []
    for picid, picture in enumerate(piclist):
        # load picture
        pr = png.Reader(picture.path)
        # convert it to RGBA8 and hope that's a good format
        pr = pr.asRGBA8()
        if picture.area is None:
            picture.area = (0, 0, pr[0], pr[1])

        # enumerate rows
        new_img = []
        for ri, row in enumerate(list(pr[2])):
            # crop image row-wise
            if ri < picture.area[1] or ri >= picture.area[1]+picture.area[3]:
                continue
            new_row = []
            # only operate on red pixels
            for pi, pixel in enumerate(row[::4]):
                # and crop it
                if pi < picture.area[0] or \
                        pi >= picture.area[0]+picture.area[2]:
                    continue
                # assume if red is > 128 it's white (0 bit)
                # else it's black
                new_row.append(0 if pixel > 128 else 1)
            # pad out row to a byte boundary with white
            while len(new_row) % 6 != 0:
                new_row.append(0)
            new_img.append(new_row)

        # now that we have only the image pixels, encode them
        encoded = pic_encode(new_img)

        pic_records.append((
            int(len(new_img[0])/6), # width (in bytes)
            len(new_img), # height
            len(pic_bytes))) # offset within pic_bytes
        pic_bytes.extend(encoded)

    # add padding byte so last picture won't read off the end of the array
    pic_bytes.append(0)

    print("total picture bytes: {}".format(len(pic_bytes)))

    # now write out the pictures
    f = open("../src_gen/pic_data.c", "w")
    f.write("#include <inttypes.h>\n#include \"../src/pic_data.h\"\n\n")
    f.write("static const uint8_t pic_bytes[{}] = {{\n".format(len(pic_bytes)))

    for bi, b in enumerate(pic_bytes):
        f.write("{},".format(b))
        if bi % 20 == 19:
            f.write("\n")
    f.write("\n};\n\n")

    f.write("const pic_data_t picture_data_records[{}] = {{\n".format(
        len(pic_records)))

    for ri, r in enumerate(pic_records):
        f.write("{{&pic_bytes[{}], {}, {}}},\n".format(
            r[2], r[0], r[1]))

    f.write("};\n")

    f.close()

if __name__ == "__main__":
    write_pic_data()