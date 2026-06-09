#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

/* 步进电机1: U1接口 PA15(DIR1) PB4(PWM1) */
/* 步进电机2: U2接口 PB9(DIR2) PA8(PWM2) */

/* 步进电机初始化 */
void StepMotor_Init(void);

/* 步进电机1控制 */
void StepMotor1_SetDir(u8 dir);      /* 0-顺时针 1-逆时针 */
void StepMotor1_SetSpeed(u16 speed); /* 速度: 0-1000 */
void StepMotor1_Run(u16 steps, u8 dir);
void StepMotor1_Stop(void);

/* 步进电机2控制 */
void StepMotor2_SetDir(u8 dir);
void StepMotor2_SetSpeed(u16 speed);
void StepMotor2_Run(u16 steps, u8 dir);
void StepMotor2_Stop(void);

/* 直流电机: MOS驱动 */
/* MOS1: PC8(PWM1) PC9(DIR1) 控制电机1 */
/* MOS2: PC6(PWM2) PC7(DIR2) 控制电机2 */

/* 直流电机初始化 */
void DCMotor_Init(void);

/* 直流电机1控制 */
void DCMotor1_SetDir(u8 dir);       /* 0-正转 1-反转 */
void DCMotor1_SetSpeed(u16 speed);  /* 速度: 0-1000对应0-100% */
void DCMotor1_Stop(void);

/* 直流电机2控制 */
void DCMotor2_SetDir(u8 dir);
void DCMotor2_SetSpeed(u16 speed);
void DCMotor2_Stop(void);

/* 电机状态 */
typedef struct
{
    u8   dir;       /* 转向 */
    u16  speed;     /* 速度 */
    u32  steps;     /* 步数(步进电机) */
    u8   running;   /* 运行状态 */
} MotorState_t;

extern MotorState_t Motor1_State;
extern MotorState_t Motor2_State;

#endif /* __MOTOR_H */
