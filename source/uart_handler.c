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
#include "usart.h"
#include "eeprom_24aa256.h"
#include "main.h"
#include "led_matrix.h"
#include "uart_handler.h"

#define NUM_OF_ALL_DATA 64*4*2

uint8_t u8_Rx_Buffer[10];
//uint8_t u8_Tx_Buffer[10]; //id, dlc, 8*data

bool b_UART_Received_Flag;

void UART_InitHandler(void)
{
		HAL_UART_Receive_IT(&huart4, u8_Rx_Buffer, 10);
}

void UART_Handler(void)
{
	UART_ReceiveRoutine();
}

void UART_ReceiveRoutine(void)
{
	//HAL_UART_Receive(&huart4,u8_Rx_Buffer,16,50);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	__NOP();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		UART_Set_Received_Flag(true);
		
		uint8_t id = u8_Rx_Buffer[0];
		uint8_t dlc = u8_Rx_Buffer[1];
		if (id == 0x55)
		{
				uint8_t module_num = u8_Rx_Buffer[2];
				uint8_t pixel_num = u8_Rx_Buffer[3];
				uint8_t red = u8_Rx_Buffer[4];
				uint8_t green = u8_Rx_Buffer[5];
				uint8_t blue = u8_Rx_Buffer[6];
				write_single_led(module_num, pixel_num, red, green, blue);
				send_ack(u8_Rx_Buffer);
		}
		if(id == 0x60)
		{
				uint8_t cmd_num = u8_Rx_Buffer[2];
				if (cmd_num == 0x01)
				{
						matrix_set_all();
						matrix_write_eeprom();
				}
				send_ack(u8_Rx_Buffer);
		}
		
		UART_Set_Received_Flag(false);
		
		HAL_UART_Receive_IT(&huart4, u8_Rx_Buffer, 10);
}

void ACSII_To_DEC_Conv(void)
{

}

void send_ack(uint8_t *read_back)
{
		uint8_t data[10];
		data[0] = 0xAC;
		for (uint8_t ind=1; ind < 10; ind++)
		{
				data[ind] = read_back[ind];
		}
	  serial_send(data, 10);
}

void send_identification(void)
{
		uint8_t data[10];
		data[0] = 0xAA;
		data[2] = 0x01;
		uint8_t size = sizeof(data);
		data[1] = size - 2; //dlc = tx_buffer - id - dlc
		serial_send(data, 10);
}

void serial_send(uint8_t *u8_Tx_Buffer, uint8_t size)
{
		HAL_UART_Transmit(&huart4, u8_Tx_Buffer,  size, 1000);
}

void UART_Write_Rx_Buffer_To_EEPROM(uint16_t u16_Index)
{
	EEPROM_24AA256_Write(u16_Index,u8_Rx_Buffer[u16_Index]);
}

void UART_Set_Received_Flag(bool b_Flage_State)
{
	b_UART_Received_Flag = b_Flage_State;
}

bool UART_Get_Received_Flag(void)
{
	return b_UART_Received_Flag;
}