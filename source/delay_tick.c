#include <stdint.h>
#include "main.h"

void Delay_Tick(uint32_t u32_Delay_Tick)
{
		for(uint32_t u32_Index=0; u32_Index < u32_Delay_Tick; u32_Index++)
		{
				__NOP();
		}
}
