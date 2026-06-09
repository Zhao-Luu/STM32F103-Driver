/**
  ******************************************************************************
  * @file    buzzer.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    Buzzer driver implementation
  ******************************************************************************
  */

#include "buzzer.h"
#include "sys.h"

#define BUZZER_PORT GPIOB
#define BUZZER_PIN GPIO_Pin_8

void BUZZER_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
    
    BUZZER_Off();
}

void BUZZER_On(void)
{
    GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
}

void BUZZER_Off(void)
{
    GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
}

void BUZZER_Toggle(void)
{
    GPIO_WriteBit(BUZZER_PORT, BUZZER_PIN, 
                  (BitAction)(1 - GPIO_ReadOutputDataBit(BUZZER_PORT, BUZZER_PIN)));
}

void BUZZER_Beep(u16 ms)
{
    BUZZER_On();
    Delay_ms(ms);
    BUZZER_Off();
}

void BUZZER_Tone(u16 freq, u16 duration)
{
    u16 period = 1000 / freq;  /* Period in ms */
    u16 count = duration / period;
    u16 i;
    
    for(i = 0; i < count; i++)
    {
        BUZZER_On();
        Delay_ms(period / 2);
        BUZZER_Off();
        Delay_ms(period / 2);
    }
}

void BUZZER_Alert(void)
{
    u8 i;
    for(i = 0; i < 3; i++)
    {
        BUZZER_Beep(50);
        Delay_ms(100);
    }
}

void BUZZER_Success(void)
{
    BUZZER_Beep(100);
    Delay_ms(50);
    BUZZER_Beep(100);
}

void BUZZER_Error(void)
{
    BUZZER_Beep(200);
    Delay_ms(100);
    BUZZER_Beep(200);
}

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
