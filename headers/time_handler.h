#ifndef __TimeHandler_H
#define __TimeHandler_H
#endif

#include "main.h"
#include "stm32f4xx_hal.h"

void timebase_init(void);
uint32_t get_timebase_1ms(void);