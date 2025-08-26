/******************************************************************************
  * File Name          : DisplayCommands.c
  * Description        : Here are all functions for driving the display
******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "time_handler.h"
#include "ws2812.h"
#include "stm32f4xx_hal_tim.h"
#include "uart_handler.h"


uint32_t timebase_10us = 0;

void timebase_init(void)
{
		timebase_10us = 0;
}

uint32_t get_timebase_10us(void)
{
		return timebase_10us;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		timebase_10us++;
		TimeHandler();
}

void TimeHandler(void)
{
		TimerTick10us();
		if(timebase_10us % 100 == 0)
		{
			TimerTick1ms();
		}
}

void TimerTick10us(void)
{
		UART_Handler();
}

void TimerTick1ms(void)
{
	
}
