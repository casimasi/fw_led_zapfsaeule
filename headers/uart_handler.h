#ifndef __TimeHandler_H
#define __TimeHandler_H
#endif

#include <stdbool.h>
#include "stm32f4xx_hal.h"

void UART_InitHandler(void);
void UART_Handler(void);
void UART_ReceiveRoutine(void);
void ACSII_To_DEC_Conv(void);
void UART_Write_Rx_Buffer_To_EEPROM(uint16_t u16_Index);
void UART_Set_Received_Flag(bool b_Flage_State);
bool UART_Get_Received_Flag(void);

void send_ack(uint8_t *read_back);
void send_identification(void);
void serial_send(uint8_t *u8_Tx_Buffer, uint8_t size);
