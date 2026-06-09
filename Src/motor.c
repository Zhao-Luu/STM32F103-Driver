/**
  ******************************************************************************
  * @file    motor.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    Motor driver implementation
  ******************************************************************************
  */

#include "motor.h"
#include "timer.h"

MotorState_t Motor1_State = {0, 0, 0, 0};
MotorState_t Motor2_State = {0, 0, 0, 0};

void StepMotor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Stepper 1: PA15(DIR), PB4(PWM) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Stepper 2: PB9(DIR), PA8(PWM) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void StepMotor1_SetDir(u8 dir) { }
void StepMotor1_SetSpeed(u16 speed) { }
void StepMotor1_Run(u16 steps, u8 dir) { }
void StepMotor1_Stop(void) { }
void StepMotor2_SetDir(u8 dir) { }
void StepMotor2_SetSpeed(u16 speed) { }
void StepMotor2_Run(u16 steps, u8 dir) { }
void StepMotor2_Stop(void) { }

void DCMotor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    /* DC Motor 1: PC8(PWM), PC9(DIR) */
    /* DC Motor 2: PC6(PWM), PC7(DIR) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void DCMotor1_SetDir(u8 dir) { if(dir) GPIO_SetBits(GPIOC, GPIO_Pin_9); else GPIO_ResetBits(GPIOC, GPIO_Pin_9); }
void DCMotor1_SetSpeed(u16 speed) { TIM4_SetPWM(3, speed); }
void DCMotor1_Stop(void) { TIM4_SetPWM(3, 0); }
void DCMotor2_SetDir(u8 dir) { if(dir) GPIO_SetBits(GPIOC, GPIO_Pin_7); else GPIO_ResetBits(GPIOC, GPIO_Pin_7); }
void DCMotor2_SetSpeed(u16 speed) { TIM4_SetPWM(4, speed); }
void DCMotor2_Stop(void) { TIM4_SetPWM(4, 0); }

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
