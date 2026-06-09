/**
  ******************************************************************************
  * @file    gpio.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    GPIO driver implementation
  ******************************************************************************
  */

#include "gpio.h"

/**
  * @brief  GPIO initialization
  * @param  None
  * @retval None
  */
void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* LED1 initialization - PB5 (5V) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  /* LED off */
    
    /* LED2 initialization - PE5 (3V3) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);  /* LED off */
    
    /* Key initialization - PE0-PE4 (input floating) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
