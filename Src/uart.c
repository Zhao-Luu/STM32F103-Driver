/**
  ******************************************************************************
  * @file    uart.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    UART driver implementation
  ******************************************************************************
  */

#include "uart.h"

/* Global receive buffer */
u8 UART1_RxBuf[UART_RX_BUF_SIZE];
u16 UART1_RxLen = 0;

/**
  * @brief  UART1 initialization (PA9-TX, PA10-RX)
  * @param  BaudRate: Baud rate (115200, 9600, etc.)
  * @retval None
  */
void UART1_Init(u32 BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* Enable UART1 and GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* Configure PA9 as TX (push-pull output) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure PA10 as RX (input floating) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* UART1 configuration */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART1, &USART_InitStructure);
    
    /* Enable UART1 receive interrupt */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    /* Configure NVIC for UART1 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Enable UART1 */
    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  UART1 send one byte
  * @param  byte: Byte to send
  * @retval None
  */
void UART1_SendByte(u8 byte)
{
    USART_SendData(USART1, byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/**
  * @brief  UART1 send string
  * @param  str: String pointer
  * @retval None
  */
void UART1_SendString(u8 *str)
{
    while(*str != '\0')
    {
        UART1_SendByte(*str);
        str++;
    }
}

/**
  * @brief  UART1 send data
  * @param  buf: Data buffer pointer
  * @param  len: Data length
  * @retval None
  */
void UART1_SendData(u8 *buf, u16 len)
{
    u16 i;
    for(i = 0; i < len; i++)
    {
        UART1_SendByte(buf[i]);
    }
}

/**
  * @brief  UART1 receive one byte
  * @param  None
  * @retval Received byte
  */
u8 UART1_ReceiveByte(void)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART1);
}

/**
  * @brief  UART1 receive data
  * @param  buf: Buffer to store received data
  * @param  len: Number of bytes to receive
  * @retval Actual bytes received
  */
u16 UART1_ReceiveData(u8 *buf, u16 len)
{
    u16 i = 0;
    while(i < len && USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
    {
        buf[i++] = USART_ReceiveData(USART1);
    }
    return i;
}

/**
  * @brief  UART2 initialization (PA2-TX, PA3-RX)
  * @param  BaudRate: Baud rate
  * @retval None
  */
void UART2_Init(u32 BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    /* Enable UART2 and GPIOA clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* Configure PA2 as TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure PA3 as RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* UART2 configuration */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  UART2 send one byte
  * @param  byte: Byte to send
  * @retval None
  */
void UART2_SendByte(u8 byte)
{
    USART_SendData(USART2, byte);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

/**
  * @brief  UART2 send string
  * @param  str: String pointer
  * @retval None
  */
void UART2_SendString(u8 *str)
{
    while(*str != '\0')
    {
        UART2_SendByte(*str);
        str++;
    }
}

/**
  * @brief  UART2 send data
  * @param  buf: Data buffer pointer
  * @param  len: Data length
  * @retval None
  */
void UART2_SendData(u8 *buf, u16 len)
{
    u16 i;
    for(i = 0; i < len; i++)
    {
        UART2_SendByte(buf[i]);
    }
}

/**
  * @brief  UART3 initialization (PB10-TX, PB11-RX)
  * @param  BaudRate: Baud rate
  * @retval None
  */
void UART3_Init(u32 BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    /* Enable UART3 and GPIOB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Configure PB10 as TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* Configure PB11 as RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* UART3 configuration */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);
}

/**
  * @brief  UART3 send one byte
  * @param  byte: Byte to send
  * @retval None
  */
void UART3_SendByte(u8 byte)
{
    USART_SendData(USART3, byte);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}

/**
  * @brief  UART3 send string
  * @param  str: String pointer
  * @retval None
  */
void UART3_SendString(u8 *str)
{
    while(*str != '\0')
    {
        UART3_SendByte(*str);
        str++;
    }
}

/**
  * @brief  UART3 send data
  * @param  buf: Data buffer pointer
  * @param  len: Data length
  * @retval None
  */
void UART3_SendData(u8 *buf, u16 len)
{
    u16 i;
    for(i = 0; i < len; i++)
    {
        UART3_SendByte(buf[i]);
    }
}

/**
  * @brief  UART4 initialization (PC10-TX, PC11-RX)
  * @param  BaudRate: Baud rate
  * @retval None
  */
void UART4_Init(u32 BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(UART4, &USART_InitStructure);
    USART_Cmd(UART4, ENABLE);
}

/**
  * @brief  UART4 send one byte
  * @param  byte: Byte to send
  * @retval None
  */
void UART4_SendByte(u8 byte)
{
    USART_SendData(UART4, byte);
    while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
}

/**
  * @brief  UART4 send string
  * @param  str: String pointer
  * @retval None
  */
void UART4_SendString(u8 *str)
{
    while(*str != '\0')
    {
        UART4_SendByte(*str);
        str++;
    }
}

/**
  * @brief  UART4 send data
  * @param  buf: Data buffer pointer
  * @param  len: Data length
  * @retval None
  */
void UART4_SendData(u8 *buf, u16 len)
{
    u16 i;
    for(i = 0; i < len; i++)
    {
        UART4_SendByte(buf[i]);
    }
}

/**
  * @brief  UART5 initialization (PC12-TX, PD2-RX)
  * @param  BaudRate: Baud rate
  * @retval None
  */
void UART5_Init(u32 BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(UART5, &USART_InitStructure);
    USART_Cmd(UART5, ENABLE);
}

/**
  * @brief  UART5 send one byte
  * @param  byte: Byte to send
  * @retval None
  */
void UART5_SendByte(u8 byte)
{
    USART_SendData(UART5, byte);
    while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
}

/**
  * @brief  UART5 send string
  * @param  str: String pointer
  * @retval None
  */
void UART5_SendString(u8 *str)
{
    while(*str != '\0')
    {
        UART5_SendByte(*str);
        str++;
    }
}

/**
  * @brief  USART1 interrupt handler
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
    u8 res;
    
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        res = USART_ReceiveData(USART1);
        
        if(UART1_RxLen < UART_RX_BUF_SIZE)
        {
            UART1_RxBuf[UART1_RxLen++] = res;
        }
        else
        {
            UART1_RxLen = 0;
            UART1_RxBuf[UART1_RxLen++] = res;
        }
    }
}

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
