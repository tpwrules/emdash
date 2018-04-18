# this file contains the list of Pictures available to
# scr_draw_pic
# it must be run to generate the pic data headers

import png

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
    Picture("icons/warning.png", "battery", (72, 0, 23, 15))
]

# add all the gear icons
gears = ["park", "reverse", "neutral", "drive"]
gears.extend(range(8)) # 0 to 7
for i, g in enumerate(gears):
    piclist.append(Picture("gears/gears.png", 
        "GEAR_{}".format(g), (i*32, 0, 32, 31)))

if __name__ == "__main__":
    # write out header with picture names
    f = open("pic_ids.h", "w")
    f.write("#ifndef PIC_IDS_H\n#define PIC_IDS_H\n\n")
    for picid, pic in enumerate(piclist):
        f.write("#define PIC_ID_{} ({})\n".format(pic.name, picid))
    f.write("\n#endif\n")
    f.close()