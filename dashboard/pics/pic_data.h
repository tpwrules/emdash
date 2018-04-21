#ifndef PIC_DATA_H
#define PIC_DATA_H

#include "pic_ids.h"

typedef struct {
    uint8_t *data; // pointer to picture data
    uint8_t width; // in bytes
    uint8_t height; // in pixels
    uint8_t compress_type;
} pic_data_t;

extern pic_data_t picture_data_records[PIC_NUMBER_OF_IDS];

#endif