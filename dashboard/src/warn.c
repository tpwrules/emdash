// this file handles the warning variables on the left
// side of the screen
// this includes
//  * oil temperature and pressure
//  * engine block and water temperature
//  * fuel temperature and pressure

#include <stdio.h>

#include "platform.h"
#include "warn.h"
#include "canvar.h"
#include "screen.h"
#include "limits.h"

// the first bit of this is the blinker stuff
// this keeps track of the blink state of each icon
#define NUM_BLINK_ICONS (8)
static uint8_t blink_state[NUM_BLINK_ICONS];

// this holds the information on a particular icon to be blinked
typedef struct {
    uint16_t pic_loc; // address of icon picture in bytes
    uint16_t text_loc; // address of value text in pixels

    uint8_t pic_id; // id of picture for icon
    uint8_t text_width; // number of pixels in value text
} blink_icon_t;

static const blink_icon_t blink_icons[NUM_BLINK_ICONS] = {
#define BLINK_OIL_PRESSURE (0)
    {SCR_BYTE_ADDR(0, 0, 8), SCR_PIXEL_ADDR_AT_TEXT(0, 6, 5),
        PIC_ID_OIL_PRESSURE, 5*6+1},
#define BLINK_OIL_TEMP (1)
    {SCR_BYTE_ADDR(0, 0, 24), SCR_PIXEL_ADDR_AT_TEXT(0, 13, 5),
        PIC_ID_OIL_TEMP, 4*6+1},
#define BLINK_WATER_TEMP (2)
    {SCR_BYTE_ADDR(0, 3, 8), SCR_PIXEL_ADDR_AT_TEXT(0, 6, 6),
        PIC_ID_WATER_TEMP, 4*6+1},
#define BLINK_BLOCK_TEMP (3)
    {SCR_BYTE_ADDR(0, 3, 24), SCR_PIXEL_ADDR_AT_TEXT(0, 13, 6),
        PIC_ID_BLOCK_TEMP, 4*6+1},
#define BLINK_FUEL_PRESSURE (4)
    {SCR_BYTE_ADDR(0, 6, 8), SCR_PIXEL_ADDR_AT_TEXT(0, 6, 7),
        PIC_ID_FUEL_PRESSURE, 5*6+1},
#define BLINK_FUEL_TEMP (5)
    {SCR_BYTE_ADDR(0, 6, 24), SCR_PIXEL_ADDR_AT_TEXT(0, 13, 7),
        PIC_ID_FUEL_TEMP, 4*6+1},
#define BLINK_BATTERY (6)
    {SCR_BYTE_ADDR(0, 9, 8), SCR_PIXEL_ADDR_AT_TEXT(0, 35, 7),
        PIC_ID_BATTERY, 5*6},
#define BLINK_OIL_TEMP_LOW (7)
    {SCR_BYTE_ADDR(0, 9, 24), SCR_PIXEL_ADDR_AT_TEXT(0, 13, 5),
        PIC_ID_OIL_TEMP_LOW, 0}
};

// call to set or clear a warning condition for a blinker
static void warn_set(int blink_id, uint8_t should_warn) {
    const blink_icon_t *blinker = &blink_icons[blink_id];

    if (should_warn && !blink_state[blink_id]) {
        // draw the icon
        scr_draw_pic(blinker->pic_loc, blinker->pic_id, 0);
        // invert the text
        if (blinker->text_width > 0)
            scr_draw_rect(blinker->text_loc, blinker->text_width, 8, 1);
    } else if (!should_warn && blink_state[blink_id]) {
        // clear the icon
        scr_draw_rect(blinker->pic_loc<<3, 23, 15, 0);
        // and un-invert the text
        if (blinker->text_width > 0)
            scr_draw_rect(blinker->text_loc, blinker->text_width, 8, 0);
    }

    blink_state[blink_id] = should_warn;
}

// initializer: draws default screen state
void warn_init(void) {
    // draw the value placeholders
    scr_draw_text(SCR_TEXT_ADDR(0, 0, 5), "Oil:  ??bar  ???C");
    scr_draw_text(SCR_TEXT_ADDR(0, 0, 6), "En: W:???C B:???C");
    scr_draw_text(SCR_TEXT_ADDR(0, 0, 7), "Fuel: ??bar  ???C");
    scr_draw_text(SCR_TEXT_ADDR(0, 29, 7), "Batt: ????V");
}

// update handlers

void warn_poil_update(uint32_t val) {
    char str[8];
    sprintf(str, "%2d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 6, 5), str);
    warn_set(BLINK_OIL_PRESSURE, val < LIM_OIL_PRESSURE_MIN);
}

void warn_toil_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 13, 5), str);
    warn_set(BLINK_OIL_TEMP, val > LIM_OIL_TEMP_MAX);
    warn_set(BLINK_OIL_TEMP_LOW, val < LIM_OIL_TEMP_MIN);
}

void warn_tmot2_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 6, 6), str);
    warn_set(BLINK_WATER_TEMP, val > LIM_WATER_TEMP_MAX);
}

void warn_tmot_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 13, 6), str);
    warn_set(BLINK_BLOCK_TEMP, val > LIM_BLOCK_TEMP_MAX);
}

void warn_pfuel_update(uint32_t val) {
    char str[8];
    sprintf(str, "%2d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 6, 7), str);
    warn_set(BLINK_FUEL_PRESSURE, val < LIM_FUEL_PRESSURE_MIN);
}

void warn_tfuel_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 13, 7), str);
    warn_set(BLINK_FUEL_TEMP, val > LIM_FUEL_PRESSURE_MAX);
}

// battery voltage
void warn_ub_update(uint32_t val) {
    char str[8];
    sprintf(str, "%4d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 35, 7), str);
    warn_set(BLINK_BATTERY, val < LIM_BATTERY_MIN);
}