/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stdbool.h"

#include "WS2812.h"
#include "stm32f4xx_hal_tim.h"
#include "EEPROM_24AA256.h"
#include "led_matrix.h"

#define BITS_IN_BYTE 8
#define NUM_OF_COLOR 3
#define BIT_MASK_OFFSET (BITS_IN_BYTE * NUM_OF_COLOR - 1) //23
#define COLOR_MASK 0x00FFFFFFF


void ws2812_set_dout_pin(bool b_State)
{
		if(b_State)
		{
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);		//Gate Driver Output
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); 	//FET Output
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET); //SPI Output Test
		}
		else
		{
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);			//Gate Driver Output
				//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);	//FET Output
				//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET); //SPI Output Test
		}
}

void ws2812_bit_h_seq(void)
{
		ws2812_set_dout_pin(true);
		for(volatile uint32_t u32_Delay = 0; u32_Delay < 10; u32_Delay++);   //T1H (0.8us) 

		ws2812_set_dout_pin(false);
		for(volatile uint32_t u32_Delay = 0; u32_Delay < 3; u32_Delay++);   //T1L (0.45us)
}
	
void ws2812_bit_l_seq(void)
{
		ws2812_set_dout_pin(true);
		for(volatile uint32_t u32_Delay = 0; u32_Delay < 2; u32_Delay++);   //T0H (0.4us)

		ws2812_set_dout_pin(false);
		for(volatile uint32_t u32_Delay = 0; u32_Delay < 11; u32_Delay++);   //T0L (0.85us)
}

void ws2812_set(uint32_t hexval)
{
		for(uint8_t i = 0; i < (NUM_OF_COLOR * BITS_IN_BYTE); i++)
		{
				if (hexval & ((uint32_t)(0x01 << BIT_MASK_OFFSET)) >> i & COLOR_MASK)
				{
						ws2812_bit_h_seq();
				}
				else
				{
						ws2812_bit_l_seq();
				}
		}
}
