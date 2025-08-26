/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "WS2812.h"
#include "led_matrix.h"
#include "delay_tick.h"
#include "EEPROM_24AA256.h"

#define PIXELS_PER_MODULE 64
#define MAX_PIXELS 1024

typedef struct {
	uint8_t blue;
	uint8_t red;
	uint8_t green;
	uint8_t led_num;
} rgb_t;
	
typedef union {
	rgb_t rgb;
	uint32_t hexval;
} pixel_t;

typedef struct {
	pixel_t pixels[PIXELS_PER_MODULE];
} module_t;

typedef struct {
	uint8_t pixels_x;
	uint8_t pixels_y;
	module_t module[MAX_PIXELS / PIXELS_PER_MODULE];
} matrix_t;

matrix_t matrix; 

void copy_buffer (uint8_t * dst_prt, uint8_t * src_prt, uint16_t size)
{
    for(uint16_t i = 0; i < size; i++)
	  {
		    *(dst_prt + i) = *(src_prt + i);
	  }
}

void matrix_set_all(void)
{
		uint8_t num_of_modules = (matrix.pixels_x >> 3) * (matrix.pixels_y >> 3);
		for(uint16_t module_num = 0; module_num < num_of_modules; module_num++)
		{
				for(uint8_t pixel_num=0; pixel_num < PIXELS_PER_MODULE; pixel_num++)
				{
						ws2812_set(matrix.module[module_num].pixels[pixel_num].hexval);
				}
		}
}

void matrix_config(uint8_t pixels_x, uint8_t pixels_y) {
	  matrix.pixels_x = pixels_x;
		matrix.pixels_y = pixels_y;
}

void matrix_clear(void)
{
		ws2812_set(0);
		Delay_Tick(62000);
		uint8_t num_of_modules = (matrix.pixels_x >> 3) * (matrix.pixels_y >> 3);
		for(uint16_t module_num = 0; module_num < num_of_modules; module_num++)
		{
				for(uint8_t pixel_num=0; pixel_num < PIXELS_PER_MODULE; pixel_num++)
				{
						ws2812_set(0);
				}
		}
		Delay_Tick(62000);
}

void matrix_write_eeprom(void)
{
		uint8_t num_of_modules = (matrix.pixels_x >> 3) * (matrix.pixels_y >> 3);
		for(uint16_t module_num = 0; module_num < num_of_modules; module_num++)
		{
				for(uint16_t pixel_num = 0; pixel_num < PIXELS_PER_MODULE; pixel_num++)
				{
						EEPROM_24AA256_Write(((uint16_t) (module_num << 8) + (pixel_num << 2)) + 0, matrix.module[module_num].pixels[pixel_num].rgb.red);
						EEPROM_24AA256_Write(((uint16_t) (module_num << 8) + (pixel_num << 2)) + 1, matrix.module[module_num].pixels[pixel_num].rgb.green);
						EEPROM_24AA256_Write(((uint16_t) (module_num << 8) + (pixel_num << 2)) + 2, matrix.module[module_num].pixels[pixel_num].rgb.blue);
				}
		}
}

void matrix_read_eeprom(void)
{
		uint8_t num_of_modules = (matrix.pixels_x >> 3) * (matrix.pixels_y >> 3);
		for(uint16_t module_num = 0; module_num < num_of_modules; module_num++)
		{
				for(uint16_t pixel_num = 0; pixel_num < PIXELS_PER_MODULE; pixel_num++)
				{
						matrix.module[module_num].pixels[pixel_num].rgb.red =   u8_EEPROM_24AA256_Read(((uint16_t) (module_num << 8) + (pixel_num << 2)) + 0);
						matrix.module[module_num].pixels[pixel_num].rgb.green = u8_EEPROM_24AA256_Read(((uint16_t) (module_num << 8) + (pixel_num << 2)) + 1);
						matrix.module[module_num].pixels[pixel_num].rgb.blue =  u8_EEPROM_24AA256_Read(((uint16_t) (module_num << 8) + (pixel_num << 2)) + 2);
				}
		}
}

void write_led_buffer(uint8_t *buf)
{
		uint8_t num_of_modules = (matrix.pixels_x >> 3) * (matrix.pixels_y >> 3);
		for(uint8_t module_num = 0; module_num < num_of_modules; module_num++)
		{
				copy_buffer((uint8_t *)matrix.module[module_num].pixels, buf + (module_num * PIXELS_PER_MODULE * 4) , PIXELS_PER_MODULE * 4);
		}
		matrix_set_all();
		matrix_write_eeprom();
}

void write_single_led(uint8_t module_num, uint8_t pixel_num, uint8_t red, uint8_t green, uint8_t blue)
{
		matrix.module[module_num].pixels[pixel_num].rgb.red = red;
		matrix.module[module_num].pixels[pixel_num].rgb.green = green;
		matrix.module[module_num].pixels[pixel_num].rgb.blue = blue;
}

void matrix_init(void)
{
		matrix_config(8,8);		//configure as 8x8 Matrix -> 1 Module with 8x8 LED's
		matrix_clear();
		matrix_read_eeprom();
	  matrix_set_all();
}




