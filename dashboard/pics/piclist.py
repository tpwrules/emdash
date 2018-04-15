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
piclist = (
    # the bootsplash
    Picture("bootsplash/boot.png", "bootsplash"),
    # the lame number four
    Picture("four.png", "demo_gear_four")
)

if __name__ == "__main__":
    # write out header with picture names
    f = open("pic_ids.h", "w")
    f.write("#ifndef PIC_IDS_H\n#define PIC_IDS_H\n\n")
    for picid, pic in enumerate(piclist):
        f.write("#define PIC_ID_{} ({})\n".format(pic.name, picid))
    f.write("\n#endif\n")
    f.close()