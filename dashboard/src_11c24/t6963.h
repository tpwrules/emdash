#ifndef T6963_H
#define T6963_H

#include <stdbool.h>

// initialize lcd controller
void lcd_init(void);

void lcd_send(uint8_t data, bool command);
void lcd_send_auto(uint8_t data, bool command);

// command with no arguments
static inline void lcd_send_0cmd(uint8_t cmd) {
    lcd_send(cmd, true);
}

// command with one argument
static inline void lcd_send_1cmd(uint8_t cmd, uint8_t arg) {
    lcd_send(arg, false);
    lcd_send(cmd, true);
}

// command that takes an address
static inline void lcd_send_acmd(uint8_t cmd, uint16_t addr) {
    lcd_send(addr & 0xFF, false);
    lcd_send(addr >> 8, false);
    lcd_send(cmd, true);
}

#endif