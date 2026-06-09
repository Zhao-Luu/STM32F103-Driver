#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"

/* 系统初始化函数 */
void SystemInit(void);           /* 系统时钟初始化 */
void SysTick_Init(void);         /* SysTick定时器初始化 */
void Delay_us(u32 nus);          /* 微秒延时 */
void Delay_ms(u32 nms);          /* 毫秒延时 */

/* 中断优先级设置 */
void NVIC_PriorityGroup_Config(uint32_t NVIC_PriorityGroup);

/* 硬件看门狗 */
void WWDG_Init(void);
void IWDG_Init(void);
void IWDG_Feed(void);

/* 内存管理 */
void Mem_Init(void);

#endif /* __SYS_H */
