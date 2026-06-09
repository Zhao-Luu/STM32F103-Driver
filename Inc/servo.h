#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"

/* 舵机控制 - 基于PWM */
/* 使用TIM1/TIM3/TIM4/TIM5/TIM8的PWM输出 */

/* 舵机初始化 */
void Servo_Init(void);

/* 舵机角度控制 (0-180度) */
void Servo1_SetAngle(u16 angle);  /* TIM1_CH1: PA8 */
void Servo2_SetAngle(u16 angle);  /* TIM1_CH2: PA9 */
void Servo3_SetAngle(u16 angle);  /* TIM3_CH1: PA6 */
void Servo4_SetAngle(u16 angle);  /* TIM3_CH2: PA7 */
void Servo5_SetAngle(u16 angle);  /* TIM4_CH1: PB6 */

/* 舵机扫描 */
void Servo_Sweep(u8 id, u16 start, u16 end, u16 delay);

#endif /* __SERVO_H */
