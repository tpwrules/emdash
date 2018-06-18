#include "platform.h"
#include "canvar.h"
#include "../src_gen/canvar_defs.h"
#include "screen.h"
#include "app.h"

#include <stdio.h>
#include <stdbool.h>

volatile int canvar_was_updated = 0;

void app_can_interrupt(uint32_t msg_id, uint8_t dlc, const uint8_t *data) {
    // step 1: find the first variable in this message

    // calculate the message id hash
    uint32_t msg_idx = msg_id % CANVAR_ID_MAP_COUNT;
    const canvar_def_t *def; // we want msg definition
    uint8_t var_idx;
    while (1) {
        var_idx = canvar_id_map[msg_idx];
        if (var_idx == 0xFF)
            return; // this message isn't recognized
        def = &canvar_defs[var_idx];
        if (def->msg_id == msg_id)
            break; // we found it
        msg_idx = (msg_idx + 1) % CANVAR_ID_MAP_COUNT;
    }

    volatile canvar_state_t *st = &canvar_states[var_idx];

    // step 2: loop over all the vars with this message ID
    while (def->msg_id == msg_id) {
        // step 3: make sure this can message has this variable
        if (def->multiplex != 0xFF && def->multiplex != data[0]) {
            def++;
            st++;
            continue;
        }
        
        // step 4: extract the value for this variable
        uint32_t val = 0;
        int bi;
        for (bi = 0; bi<def->size; bi++)
            // value is little endian
            val |= data[bi+def->start] << (8*bi);
        // sign extend if required
        if (def->is_signed && def->size < 4) {
            uint32_t sign = (val >> ((8*bi)-1)) ? 0xFFFFFFFF : 0;
            val |= sign << (8*bi);
        }

        // step 5: update canvar state
        if (st->val != val || st->st == CV_ST_INVALID) {
            st->val = val;
            st->st = CV_ST_NEW;
            canvar_was_updated = 1;
        }

        // increment to next variable
        def++;
        st++;
    }
}

void app_canvar_interrupt(uint8_t cv_id, uint32_t val) {
    if (cv_id >= CANVAR_NUM_VARS)
        return;

    volatile canvar_state_t *st = &canvar_states[cv_id];

    // just do step 5 above: update canvar state
    if (st->val != val || st->st == CV_ST_INVALID) {
        st->val = val;
        st->st = CV_ST_NEW;
        canvar_was_updated = 1;
    }
}

void cv_status_mode_change(bool next) {
    if (next) {
        // set the next mode
        app_mode_change_func = app_blank_mode;
        return;
    }

    // draw placeholder values
    scr_draw_text(SCR_TEXT_ADDR(0, 30, 2), "CAN:  good");
    scr_draw_text(SCR_TEXT_ADDR(0, 32, 3), "00000000");

    // set messages to new so that they will be redrawn
    interrupt_disable();
    CV_RENEW(cv_nobus_can_status);
    interrupt_enable();
}

// CAN error meanings
#define CAN_ERROR_NONE 0x00000000UL
#define CAN_ERROR_PASS 0x00000001UL
#define CAN_ERROR_WARN 0x00000002UL
#define CAN_ERROR_BOFF 0x00000004UL
#define CAN_ERROR_STUF 0x00000008UL
#define CAN_ERROR_FORM 0x00000010UL
#define CAN_ERROR_ACK 0x00000020UL
#define CAN_ERROR_BIT1 0x00000040UL
#define CAN_ERROR_BIT0 0x00000080UL
#define CAN_ERROR_CRC 0x00000100UL

void cv_can_status_update(uint32_t val) {
    char str[20];
    if (app_mode_change_func == cv_status_mode_change) {
        sprintf(str, "%08x", (unsigned int)val);
        scr_draw_text(SCR_TEXT_ADDR(0, 32, 3), str);
        if (val == 0) {
            scr_draw_text(SCR_TEXT_ADDR(0, 30, 2), "CAN:  good");
            scr_draw_rect(SCR_PIXEL_ADDR_AT_TEXT(0, 30, 2),
                6*10, 8, 0);
        } else {
            scr_draw_text(SCR_TEXT_ADDR(0, 30, 2), "CAN: ERROR");
            scr_draw_rect(SCR_PIXEL_ADDR_AT_TEXT(0, 30, 2),
                6*10, 8, 1);
        }
    }

    static uint32_t last_val = 0;
    if (last_val == 0 && val != 0 &&
            app_mode_change_func != cv_status_mode_change) {
        // force mode switch if something goes wrong CAN-wise
        app_mode_change_func = cv_status_mode_change;
        app_show_next_mode();
    }
    last_val = val;
}