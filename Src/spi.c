/**
  ******************************************************************************
  * @file    spi.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    SPI driver implementation
  ******************************************************************************
  */

#include "spi.h"

/**
  * @brief  SPI1 initialization (PB3-CLK, PB4-MISO, PB5-MOSI)
  * @param  None
  * @retval None
  */
void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Configure PB3 (CLK), PB5 (MOSI) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB4 (MISO) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* SPI configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  /* 18MHz */
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
}

/**
  * @brief  SPI1 read/write one byte
  * @param  byte: Byte to send
  * @retval Received byte
  */
u8 SPI1_ReadWriteByte(u8 byte)
{
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, byte);
    
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
}

void SPI1_SendData(u8 *buf, u16 len)
{
    u16 i;
    for(i = 0; i < len; i++) SPI1_ReadWriteByte(buf[i]);
}

void SPI1_ReadData(u8 *buf, u16 len)
{
    u16 i;
    for(i = 0; i < len; i++) buf[i] = SPI1_ReadWriteByte(0xFF);
}

void SPI2_Init(void) { }
u8 SPI2_ReadWriteByte(u8 byte) { return 0; }
void SPI2_SendData(u8 *buf, u16 len) { }

void SPI3_Init(void) { }
u8 SPI3_ReadWriteByte(u8 byte) { return 0; }

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
