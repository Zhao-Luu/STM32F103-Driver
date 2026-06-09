#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

/* GPIO初始化 */
void GPIO_Init(void);

/* LED控制 */
#define LED1_ON()   GPIO_ResetBits(GPIOB, GPIO_Pin_5)    // PB5 - LED1 (5V)
#define LED1_OFF()  GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LED2_ON()   GPIO_ResetBits(GPIOE, GPIO_Pin_5)    // PE5 - LED2 (3V3)
#define LED2_OFF()  GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define LED1_TOGGLE() GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5)))
#define LED2_TOGGLE() GPIO_WriteBit(GPIOE, GPIO_Pin_5, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5)))

/* 按键定义 */
#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)    // PE4
#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)    // PE3
#define KEY3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)    // PE2
#define KEY4 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)    // PE1
#define KEY5 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)    // PE0

#endif /* __GPIO_H */
