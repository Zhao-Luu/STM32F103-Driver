#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"

/* I2C1 initialization (PB6-SCL, PB7-SDA) */
void I2C1_Init(void);

/* I2C start/stop conditions */
void I2C1_Start(void);
void I2C1_Stop(void);

/* I2C acknowledge */
void I2C1_SendAck(void);
void I2C1_SendNoAck(void);
u8 I2C1_WaitAck(void);

/* I2C data transfer */
void I2C1_SendByte(u8 byte);
u8 I2C1_ReadByte(void);

/* I2C read/write multiple bytes */
u8 I2C1_ReadBytes(u8 addr, u8 reg, u8 *buf, u8 len);
u8 I2C1_WriteBytes(u8 addr, u8 reg, u8 *buf, u8 len);

/* I2C2 initialization (PB10-SCL, PB11-SDA) */
void I2C2_Init(void);
u8 I2C2_ReadBytes(u8 addr, u8 reg, u8 *buf, u8 len);
u8 I2C2_WriteBytes(u8 addr, u8 reg, u8 *buf, u8 len);

#endif /* __I2C_H */
