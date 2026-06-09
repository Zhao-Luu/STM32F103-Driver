#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

/* 定时器PWM初始化 */
void TIM1_PWM_Init(u16 arr, u16 psc);   /* TIM1: PA8(CH1) PA9(CH2) PA10(CH3) PA11(CH4) */
void TIM3_PWM_Init(u16 arr, u16 psc);   /* TIM3: PA6(CH1) PA7(CH2) PB0(CH3) PB1(CH4) */
void TIM4_PWM_Init(u16 arr, u16 psc);   /* TIM4: PB6(CH1) PB7(CH2) PB8(CH3) PB9(CH4) */
void TIM5_PWM_Init(u16 arr, u16 psc);   /* TIM5: PA0(CH1) PA1(CH2) PA2(CH3) PA3(CH4) */
void TIM8_PWM_Init(u16 arr, u16 psc);   /* TIM8: PC6(CH1) PC7(CH2) PC8(CH3) PC9(CH4) */

/* 设置PWM占空比 (0-1000对应0-100%) */
void TIM1_SetPWM(uint8_t channel, u16 pulse);
void TIM3_SetPWM(uint8_t channel, u16 pulse);
void TIM4_SetPWM(uint8_t channel, u16 pulse);
void TIM5_SetPWM(uint8_t channel, u16 pulse);
void TIM8_SetPWM(uint8_t channel, u16 pulse);

/* 基本定时器 */
void TIM2_Init(u16 arr, u16 psc);       /* 通用定时器2 */
void TIM6_Init(u16 arr, u16 psc);       /* 基本定时器6 */
void TIM7_Init(u16 arr, u16 psc);       /* 基本定时器7 */

/* 定时器通道定义 */
#define TIMER_CHANNEL_1    1
#define TIMER_CHANNEL_2    2
#define TIMER_CHANNEL_3    3
#define TIMER_CHANNEL_4    4

#endif /* __TIMER_H */
