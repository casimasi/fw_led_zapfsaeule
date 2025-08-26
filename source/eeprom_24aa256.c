/******************************************************************************
  * File Name          : DisplayCommands.c
  * Description        : Here are all functions for driving the display
******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "time_handler.h"
#include "WS2812.h"
#include "stm32f4xx_hal_tim.h"
#include "I2C_Handler.h"
#include "EEPROM_24AA256.h"
#include "stm32f4xx_hal_i2c.h"
#include "i2c.h"
#include "delay_tick.h"

#define DEVICE_0_READ 0xA1
#define DEVICE_0_WRITE 0xA0

#define I2C3_Timeout_ms 100

uint8_t u8_EEPROM_24AA256_TransmitCompletedFlag;
uint8_t u8_EEPROM_24AA256_ReceiveCompletedFlag;

void EEPROM_24AA256_Init(void)
{
    
}

void EEPROM_24AA256_Control(void)
{
    static uint8_t u8_ReadData_1 = 0;
    static uint8_t u8_ReadData_2 = 0;
    __NOP();
}

void EEPROM_24AA256_Write(uint16_t u16_MemoryAdress, uint8_t u8_Data)
{
    __disable_irq();
    uint8_t u8_DataSendPackage[3]; 
    u8_DataSendPackage[0] = ((u16_MemoryAdress & 0xFF00)>>8);  //Memory Adress High Nibble
    u8_DataSendPackage[1] = u16_MemoryAdress & 0x00FF;         //Memory Adress Low Nibble
    u8_DataSendPackage[2] = u8_Data;
    HAL_I2C_Master_Transmit(&hi2c3,DEVICE_0_WRITE,u8_DataSendPackage,3,1000);
		Delay_Tick(500000);
    __enable_irq();    
}

void EEPROM_24AA256_WritePage(uint16_t u16_MemoryAdress, uint32_t u32_Data)
{
    __disable_irq();
    uint8_t u8_DataSendPackage[6]; 
    u8_DataSendPackage[0] = ((u16_MemoryAdress & 0xFF00)>>8);  //Memory Adress High Nibble
    u8_DataSendPackage[1] = u16_MemoryAdress & 0x00FF;         //Memory Adress Low Nibble
    u8_DataSendPackage[2] = ((u32_Data & 0xFF000000)>>24);
    u8_DataSendPackage[3] = ((u32_Data & 0x00FF0000)>>16);
    u8_DataSendPackage[4] = ((u32_Data & 0x0000FF00)>>8);
    u8_DataSendPackage[5] = (u32_Data & 0x000000FF);
    HAL_I2C_Master_Transmit(&hi2c3,DEVICE_0_WRITE,u8_DataSendPackage,6,1000);
    __enable_irq();
}
    

uint8_t u8_EEPROM_24AA256_Read(uint16_t u16_MemoryAdress)
{
    __disable_irq();
    uint8_t u8_Data = 172;
    uint8_t u8_DataSendPackage[2]; 
    u8_DataSendPackage[0] = ((u16_MemoryAdress & 0xFF00)>>8);  //Memory Adress High Nibble
    u8_DataSendPackage[1] = u16_MemoryAdress & 0x00FF;         //Memory Adress Low Nibble
    HAL_I2C_Master_Transmit(&hi2c3,DEVICE_0_WRITE,u8_DataSendPackage,2,I2C3_Timeout_ms);
    HAL_I2C_Master_Receive(&hi2c3,DEVICE_0_READ,&u8_Data,1,I2C3_Timeout_ms);
    __enable_irq();
		Delay_Tick(140000);
    return u8_Data;
}

uint32_t u32_EEPROM_24AA256_ReadPage(uint16_t u16_MemoryAdress)
{
    __disable_irq();
    uint32_t u32_Data = 0;
    uint8_t u8_Data[4];
    uint8_t u8_DataSendPackage[2]; 
    u8_DataSendPackage[0] = ((u16_MemoryAdress & 0xFF00)>>8);  //Memory Adress High Nibble
    u8_DataSendPackage[1] = u16_MemoryAdress & 0x00FF;         //Memory Adress Low Nibble
    HAL_I2C_Master_Transmit(&hi2c3,DEVICE_0_WRITE,u8_DataSendPackage,2,I2C3_Timeout_ms);
    HAL_I2C_Master_Receive(&hi2c3,DEVICE_0_READ,u8_Data,4,I2C3_Timeout_ms);
    u32_Data |= u8_Data[0] << 24;
    u32_Data |= u8_Data[1] << 16;
    u32_Data |= u8_Data[2] << 8;
    u32_Data |= u8_Data[3];   
    __enable_irq();
    return u32_Data;
}

uint8_t u8_EEPROM_24AA256_GetTransmitCompletedFlag(void)
{
    return u8_EEPROM_24AA256_TransmitCompletedFlag;
}

void EEPROM_24AA256_SetTransmitCompletedFlag(uint8_t u8_State)
{
    u8_EEPROM_24AA256_TransmitCompletedFlag = u8_State;
}

uint8_t u8_EEPROM_24AA256_GetReceiveCompletedFlag(void)
{
    return u8_EEPROM_24AA256_ReceiveCompletedFlag;
}

void EEPROM_24AA256_SetReceiveCompletedFlag(uint8_t u8_State)
{
    u8_EEPROM_24AA256_ReceiveCompletedFlag = u8_State;
}