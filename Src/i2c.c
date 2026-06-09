/**
  ******************************************************************************
  * @file    i2c.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    I2C driver implementation (software)
  ******************************************************************************
  */

#include "i2c.h"

#define I2C1_SCL PBout(6)
#define I2C1_SDA PBout(7)
#define I2C1_SDA_IN PBin(7)

/**
  * @brief  I2C1 initialization (PB6-SCL, PB7-SDA)
  * @param  None
  * @retval None
  */
void I2C1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    I2C1_SCL = 1;
    I2C1_SDA = 1;
}

void I2C1_Start(void)
{
    I2C1_SDA = 1;
    I2C1_SCL = 1;
    I2C1_SDA = 0;
    I2C1_SCL = 0;
}

void I2C1_Stop(void)
{
    I2C1_SCL = 0;
    I2C1_SDA = 0;
    I2C1_SCL = 1;
    I2C1_SDA = 1;
}

void I2C1_SendAck(void)
{
    I2C1_SCL = 0;
    I2C1_SDA = 0;
    I2C1_SCL = 1;
    I2C1_SCL = 0;
}

void I2C1_SendNoAck(void)
{
    I2C1_SCL = 0;
    I2C1_SDA = 1;
    I2C1_SCL = 1;
    I2C1_SCL = 0;
}

u8 I2C1_WaitAck(void)
{
    u8 ack = 0;
    I2C1_SCL = 0;
    I2C1_SDA = 1;
    I2C1_SCL = 1;
    
    if(I2C1_SDA_IN) ack = 1;
    else ack = 0;
    
    I2C1_SCL = 0;
    return ack;
}

void I2C1_SendByte(u8 byte)
{
    u8 i = 8;
    I2C1_SCL = 0;
    while(i--)
    {
        if(byte & 0x80) I2C1_SDA = 1;
        else I2C1_SDA = 0;
        byte <<= 1;
        I2C1_SCL = 1;
        I2C1_SCL = 0;
    }
}

u8 I2C1_ReadByte(void)
{
    u8 i = 8;
    u8 byte = 0;
    I2C1_SDA = 1;
    while(i--)
    {
        I2C1_SCL = 0;
        I2C1_SCL = 1;
        byte <<= 1;
        if(I2C1_SDA_IN) byte |= 0x01;
    }
    I2C1_SCL = 0;
    return byte;
}

u8 I2C1_ReadBytes(u8 addr, u8 reg, u8 *buf, u8 len)
{
    u8 i;
    I2C1_Start();
    I2C1_SendByte((addr << 1) | 0);
    if(I2C1_WaitAck()) return 0;
    I2C1_SendByte(reg);
    I2C1_WaitAck();
    I2C1_Start();
    I2C1_SendByte((addr << 1) | 1);
    I2C1_WaitAck();
    
    for(i = 0; i < len; i++)
    {
        buf[i] = I2C1_ReadByte();
        if(i < len - 1) I2C1_SendAck();
        else I2C1_SendNoAck();
    }
    I2C1_Stop();
    return 1;
}

u8 I2C1_WriteBytes(u8 addr, u8 reg, u8 *buf, u8 len)
{
    u8 i;
    I2C1_Start();
    I2C1_SendByte((addr << 1) | 0);
    if(I2C1_WaitAck()) return 0;
    I2C1_SendByte(reg);
    I2C1_WaitAck();
    
    for(i = 0; i < len; i++)
    {
        I2C1_SendByte(buf[i]);
        I2C1_WaitAck();
    }
    I2C1_Stop();
    return 1;
}

void I2C2_Init(void) { }
u8 I2C2_ReadBytes(u8 addr, u8 reg, u8 *buf, u8 len) { return 0; }
u8 I2C2_WriteBytes(u8 addr, u8 reg, u8 *buf, u8 len) { return 0; }

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
