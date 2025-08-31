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


uint32_t timebase_1ms = 0;

void timebase_init(void)
{
		timebase_1ms = 0;
}

uint32_t get_timebase_1ms(void)
{
		return timebase_1ms;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		timebase_1ms++;
}

