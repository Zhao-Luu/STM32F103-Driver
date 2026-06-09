#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"

/* SPI1初始化 PB3(CLK) PB4(MISO) PB5(MOSI) */
void SPI1_Init(void);
u8   SPI1_ReadWriteByte(u8 byte);
void SPI1_SendData(u8 *buf, u16 len);
void SPI1_ReadData(u8 *buf, u16 len);

/* SPI2初始化 PB13(CLK) PB14(MISO) PB15(MOSI) */
void SPI2_Init(void);
u8   SPI2_ReadWriteByte(u8 byte);
void SPI2_SendData(u8 *buf, u16 len);

/* SPI3初始化 PB3(CLK) PB4(MISO) PB5(MOSI) */
void SPI3_Init(void);
u8   SPI3_ReadWriteByte(u8 byte);

/* 快速读写单字节 */
#define SPI_ReadWriteByte(byte)  SPI1_ReadWriteByte(byte)

#endif /* __SPI_H */
