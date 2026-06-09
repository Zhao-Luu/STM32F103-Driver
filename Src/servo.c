/**
  ******************************************************************************
  * @file    servo.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    Servo motor control implementation
  ******************************************************************************
  */

#include "servo.h"
#include "timer.h"
#include "sys.h"

void Servo_Init(void)
{
    /* Servos use PWM from TIM1 and TIM3 */
    /* Initialization done in timer setup */
}

/* Servo pulse mapping: 0.5ms = 0deg, 1.5ms = 90deg, 2.5ms = 180deg */
/* With 1kHz PWM (1ms period), pulse ranges from 50 to 250 */
void Servo1_SetAngle(u16 angle)
{
    u16 pulse = 50 + (angle * 200) / 180;  /* Map 0-180 to 50-250 */
    TIM1_SetPWM(1, pulse);
}

void Servo2_SetAngle(u16 angle)
{
    u16 pulse = 50 + (angle * 200) / 180;
    TIM1_SetPWM(2, pulse);
}

void Servo3_SetAngle(u16 angle)
{
    u16 pulse = 50 + (angle * 200) / 180;
    TIM3_SetPWM(1, pulse);
}

void Servo4_SetAngle(u16 angle)
{
    u16 pulse = 50 + (angle * 200) / 180;
    TIM3_SetPWM(2, pulse);
}

void Servo5_SetAngle(u16 angle)
{
    u16 pulse = 50 + (angle * 200) / 180;
    TIM4_SetPWM(1, pulse);
}

void Servo_Sweep(u8 id, u16 start, u16 end, u16 delay)
{
    void (*servo_func)(u16) = NULL;
    
    switch(id)
    {
        case 1: servo_func = Servo1_SetAngle; break;
        case 2: servo_func = Servo2_SetAngle; break;
        case 3: servo_func = Servo3_SetAngle; break;
        case 4: servo_func = Servo4_SetAngle; break;
        case 5: servo_func = Servo5_SetAngle; break;
        default: return;
    }
    
    if(start < end)
    {
        for(u16 i = start; i <= end; i++)
        {
            servo_func(i);
            Delay_ms(delay);
        }
    }
    else
    {
        for(u16 i = start; i >= end; i--)
        {
            servo_func(i);
            Delay_ms(delay);
            if(i == 0) break;
        }
    }
}

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
