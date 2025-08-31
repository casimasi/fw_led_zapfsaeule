#include "light_handler.h"
#include "led_matrix.h"
#include <stdbool.h>

#define NUM_OF_LEDS 10

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

typedef enum {
	color_red = 0,
	color_orange,
	color_yellow,
	color_green,
	color_blue,
	color_cyan,
	color_purple,
} color_t;

color_t e_color;

bool counter_mode_up = true;

void write_single_color(uint8_t red, uint8_t green, uint8_t blue)
{
		for(uint8_t i = 0; i < NUM_OF_LEDS; i++)
		{
				write_single_led(0, i, red, green, blue);
		}
		matrix_set_all();
}

void brightness_sweep(uint8_t *color)
{
		if (*color == 255) {
				counter_mode_up = false;
		}
		if (*color == 0) {
				counter_mode_up = true;
		}
		if (counter_mode_up) {
				(*color)++;
		} else {
				(*color)--;
		}
}

void light_handler(void)
{
		if (e_color == color_red) {
				brightness_sweep(&red);
				green = 0;
				blue = 0;
				if (red == 0) {
					 e_color = color_orange;
				}
		}
		else if (e_color == color_orange) {
				brightness_sweep(&red);
				green = (red >> 2);
				blue = 0;
				if (red == 0) {
					 e_color = color_yellow;
				}			
		}
		else if (e_color == color_yellow) {	
				brightness_sweep(&red);
				brightness_sweep(&green);
				blue = 0;
				if (red == 0) {
					 e_color = color_green;
				}			
		}
		else if (e_color == color_green) {
				brightness_sweep(&green);
				red = 0;
				blue = 0;
				if (green == 0) {
					 e_color = color_blue;
				}			
		}
		else if (e_color == color_blue) {	
				brightness_sweep(&blue);
				red = 0;
				green = 0;
				if (blue == 0) {
					 e_color = color_cyan;
				}			
		}
		else if (e_color == color_cyan) {	
				brightness_sweep(&blue);
				green = (blue >> 1);
				red = 0;
				if (blue == 0) {
					 e_color = color_purple;
				}			
		}
		else if (e_color == color_purple) {	
				brightness_sweep(&red);
				brightness_sweep(&blue);
				green = 0;
				if (red == 0) {
					 e_color = color_red;
				}			
		}
		write_single_color(red, green, blue);
}
