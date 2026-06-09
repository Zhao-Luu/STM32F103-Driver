#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"

/* UART接收缓冲区大小 */
#define UART_RX_BUF_SIZE  256

/* UART1初始化 PA9(TX) PA10(RX) */
void UART1_Init(u32 BaudRate);
void UART1_SendByte(u8 byte);
void UART1_SendString(u8 *str);
void UART1_SendData(u8 *buf, u16 len);
u8   UART1_ReceiveByte(void);
u16  UART1_ReceiveData(u8 *buf, u16 len);

/* UART2初始化 PA2(TX) PA3(RX) */
void UART2_Init(u32 BaudRate);
void UART2_SendByte(u8 byte);
void UART2_SendString(u8 *str);
void UART2_SendData(u8 *buf, u16 len);

/* UART3初始化 PB10(TX) PB11(RX) */
void UART3_Init(u32 BaudRate);
void UART3_SendByte(u8 byte);
void UART3_SendString(u8 *str);
void UART3_SendData(u8 *buf, u16 len);

/* UART4初始化 PC10(TX) PC11(RX) */
void UART4_Init(u32 BaudRate);
void UART4_SendByte(u8 byte);
void UART4_SendString(u8 *str);

/* UART5初始化 PC12(TX) PD2(RX) */
void UART5_Init(u32 BaudRate);
void UART5_SendByte(u8 byte);
void UART5_SendString(u8 *str);

/* 全局接收缓冲区 */
extern u8 UART1_RxBuf[UART_RX_BUF_SIZE];
extern u16 UART1_RxLen;

#endif /* __UART_H */
