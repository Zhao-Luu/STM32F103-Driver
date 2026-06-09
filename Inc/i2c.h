#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"

/* I2C1初始化 PB6(SCL) PB7(SDA) */
void I2C1_Init(void);
void I2C1_Start(void);
void I2C1_Stop(void);
void I2C1_SendAck(void);
void I2C1_SendNoAck(void);
u8   I2C1_WaitAck(void);
void I2C1_SendByte(u8 byte);
u8   I2C1_ReadByte(void);
u8   I2C1_ReadBytes(u8 addr, u8 reg, u8 *buf, u8 len);
u8   I2C1_WriteBytes(u8 addr, u8 reg, u8 *buf, u8 len);

/* I2C2初始化 PB10(SCL) PB11(SDA) */
void I2C2_Init(void);
u8   I2C2_ReadBytes(u8 addr, u8 reg, u8 *buf, u8 len);
u8   I2C2_WriteBytes(u8 addr, u8 reg, u8 *buf, u8 len);

/* 快速操作宏 */
#define I2C_Start()     I2C1_Start()
#define I2C_Stop()      I2C1_Stop()
#define I2C_SendByte(b) I2C1_SendByte(b)
#define I2C_ReadByte()  I2C1_ReadByte()

#endif /* __I2C_H */
