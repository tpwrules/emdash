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

// initializer: draws default screen state
void warn_init(void) {
    // draw all the icons
    scr_draw_pic(SCR_BYTE_ADDR(0, 0, 8), PIC_ID_OIL_PRESSURE, 0);
    scr_draw_pic(SCR_BYTE_ADDR(0, 0, 24), PIC_ID_OIL_TEMP, 0);

    scr_draw_pic(SCR_BYTE_ADDR(0, 3, 8), PIC_ID_WATER_TEMP, 0);
    scr_draw_pic(SCR_BYTE_ADDR(0, 3, 24), PIC_ID_BLOCK_TEMP, 0);

    scr_draw_pic(SCR_BYTE_ADDR(0, 6, 8), PIC_ID_FUEL_PRESSURE, 0);
    scr_draw_pic(SCR_BYTE_ADDR(0, 6, 24), PIC_ID_FUEL_TEMP, 0);

    scr_draw_pic(SCR_BYTE_ADDR(0, 9, 8), PIC_ID_BATTERY, 0);

    // draw the value placeholders
    scr_draw_text(SCR_TEXT_ADDR(0, 0, 5), "Oil:  ??bar  ???C");
    scr_draw_text(SCR_TEXT_ADDR(0, 0, 6), "En: W:???C B:???C");
    scr_draw_text(SCR_TEXT_ADDR(0, 0, 7), "Fuel: ??bar  ???C");
}

// update handlers

void warn_poil_update(uint32_t val) {
    char str[8];
    sprintf(str, "%2d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 6, 5), str);
}

void warn_toil_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 13, 5), str);
}

void warn_tmot2_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 6, 6), str);
}

void warn_tmot_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 13, 6), str);
}

void warn_pfuel_update(uint32_t val) {
    char str[8];
    sprintf(str, "%2d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 6, 7), str);
}

void warn_tfuel_update(uint32_t val) {
    char str[8];
    sprintf(str, "%3d", val);
    scr_draw_text(SCR_TEXT_ADDR(0, 13, 7), str);
}