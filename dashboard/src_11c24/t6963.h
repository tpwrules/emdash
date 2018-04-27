#ifndef T6963_H
#define T6963_H

// initialize lcd controller
void lcd_init(void);

void lcd_wait_S0S1(void);
void lcd_send_data(uint8_t data);
void lcd_send_command(uint8_t cmd);

// command with no arguments
static inline void lcd_send_0cmd(uint8_t cmd) {
    lcd_send_command(cmd);
}

// command with one argument
static inline void lcd_send_1cmd(uint8_t cmd, uint8_t arg) {
    lcd_send_data(arg);
    lcd_send_command(cmd);
}

// command that takes an address
static inline void lcd_send_acmd(uint8_t cmd, uint16_t addr) {
    lcd_send_data(addr & 0xFF);
    lcd_send_data(addr >> 8);
    lcd_send_command(cmd);
}

#endif