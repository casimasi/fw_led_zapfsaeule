#include <stddef.h>
#include <stdint.h>

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

void write_led_buffer(uint8_t *buf);
void write_single_led(uint8_t module_num, uint8_t pixel_num, uint8_t red, uint8_t green, uint8_t blue);
void matrix_set_all(void);
void matrix_write_eeprom(void);
void matrix_init(void);

#endif /* LED_MATRIX_H */