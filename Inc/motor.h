#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

/* Motor state structure */
typedef struct
{
    s16 speed;      /* Current speed */
    u8 direction;   /* Direction: 0=CW, 1=CCW */
    u16 position;   /* Current position (for stepper) */
    u8 status;      /* Status: 0=stopped, 1=running */
} MotorState_t;

extern MotorState_t Motor1_State;
extern MotorState_t Motor2_State;

/* Stepper motor control (PA15-DIR1, PB4-PWM1; PB9-DIR2, PA8-PWM2) */
void StepMotor_Init(void);
void StepMotor1_SetDir(u8 dir);      /* Set direction: 0=CW, 1=CCW */
void StepMotor1_SetSpeed(u16 speed); /* Set speed (0-1000) */
void StepMotor1_Run(u16 steps, u8 dir);
void StepMotor1_Stop(void);
void StepMotor2_SetDir(u8 dir);
void StepMotor2_SetSpeed(u16 speed);
void StepMotor2_Run(u16 steps, u8 dir);
void StepMotor2_Stop(void);

/* DC motor control (PC8-PWM1, PC9-DIR1; PC6-PWM2, PC7-DIR2) */
void DCMotor_Init(void);
void DCMotor1_SetDir(u8 dir);       /* Set direction: 0=CW, 1=CCW */
void DCMotor1_SetSpeed(u16 speed);  /* Set speed (0-1000 = 0-100%) */
void DCMotor1_Stop(void);
void DCMotor2_SetDir(u8 dir);
void DCMotor2_SetSpeed(u16 speed);
void DCMotor2_Stop(void);

#endif /* __MOTOR_H */
