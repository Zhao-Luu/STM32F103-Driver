/**
  ******************************************************************************
  * @file    timer.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    Timer and PWM driver implementation
  ******************************************************************************
  */

#include "timer.h"

/**
  * @brief  TIM1 PWM initialization (1kHz default)
  * @param  arr: Auto reload register
  * @param  psc: Prescaler
  * @retval None
  */
void TIM1_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* Configure PA8, PA9, PA10, PA11 as PWM outputs */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* TIM1 configuration */
    TIM_TimeBaseStructure.TIM_Period = arr - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    /* PWM mode configuration */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}

/**
  * @brief  TIM1 set PWM pulse
  * @param  channel: Channel (1-4)
  * @param  pulse: Pulse value (0-arr)
  * @retval None
  */
void TIM1_SetPWM(uint8_t channel, u16 pulse)
{
    switch(channel)
    {
        case 1: TIM1->CCR1 = pulse; break;
        case 2: TIM1->CCR2 = pulse; break;
        case 3: TIM1->CCR3 = pulse; break;
        case 4: TIM1->CCR4 = pulse; break;
        default: break;
    }
}

/**
  * @brief  TIM3 PWM initialization
  * @param  arr: Auto reload register
  * @param  psc: Prescaler
  * @retval None
  */
void TIM3_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Configure PA6, PA7 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure PB0, PB1 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    TIM_TimeBaseStructure.TIM_Period = arr - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    
    TIM_Cmd(TIM3, ENABLE);
}

void TIM3_SetPWM(uint8_t channel, u16 pulse)
{
    switch(channel)
    {
        case 1: TIM3->CCR1 = pulse; break;
        case 2: TIM3->CCR2 = pulse; break;
        case 3: TIM3->CCR3 = pulse; break;
        case 4: TIM3->CCR4 = pulse; break;
        default: break;
    }
}

/**
  * @brief  TIM4 PWM initialization
  * @param  arr: Auto reload register
  * @param  psc: Prescaler
  * @retval None
  */
void TIM4_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    TIM_TimeBaseStructure.TIM_Period = arr - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    
    TIM_Cmd(TIM4, ENABLE);
}

void TIM4_SetPWM(uint8_t channel, u16 pulse)
{
    switch(channel)
    {
        case 1: TIM4->CCR1 = pulse; break;
        case 2: TIM4->CCR2 = pulse; break;
        case 3: TIM4->CCR3 = pulse; break;
        case 4: TIM4->CCR4 = pulse; break;
        default: break;
    }
}

void TIM5_PWM_Init(u16 arr, u16 psc) { }
void TIM5_SetPWM(uint8_t channel, u16 pulse) { }
void TIM8_PWM_Init(u16 arr, u16 psc) { }
void TIM8_SetPWM(uint8_t channel, u16 pulse) { }
void TIM2_Init(u16 arr, u16 psc) { }
void TIM6_Init(u16 arr, u16 psc) { }
void TIM7_Init(u16 arr, u16 psc) { }

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
