#ifndef __RTC_H
#define __RTC_H
#endif

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stdbool.h"

void EEPROM_24AA256_Init(void);
void EEPROM_24AA256_Control(void);
void EEPROM_24AA256_Write(uint16_t u16_MemoryAdress, uint8_t u8_Data);
void EEPROM_24AA256_WritePage(uint16_t u16_MemoryAdress, uint32_t u32_Data);
uint8_t u8_EEPROM_24AA256_Read(uint16_t u16_MemoryAdress);
uint32_t u32_EEPROM_24AA256_ReadPage(uint16_t u16_MemoryAdress);
uint8_t u8_EEPROM_24AA256_GetData(void);
uint8_t u8_EEPROM_24AA256_GetDataReadyFlag(void);
void EEPROM_24AA256_SetDataReadyFlag(uint8_t u8_State);
uint8_t u8_EEPROM_24AA256_GetReadCycleFlag(void);
void EEPROM_24AA256_SetReadCycleFlag(uint8_t u8_State);
uint8_t u8_EEPROM_24AA256_GetTransmitCompletedFlag(void);
void EEPROM_24AA256_SetTransmitCompletedFlag(uint8_t u8_State);
uint8_t u8_EEPROM_24AA256_GetReceiveCompletedFlag(void);
void EEPROM_24AA256_SetReceiveCompletedFlag(uint8_t u8_State);