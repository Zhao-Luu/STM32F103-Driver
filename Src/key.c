/**
  ******************************************************************************
  * @file    key.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    Key scan driver
  ******************************************************************************
  */

#include "key.h"
#include "gpio.h"
#include "sys.h"

void KEY_Init(void)
{
    GPIO_Init();  /* Keys on PE0-PE4 */
}

u8 KEY_Scan(void)
{
    static u8 key_down = 0;
    
    if(KEY1 == 0) { Delay_ms(10); if(KEY1 == 0 && !key_down) { key_down = 1; return KEY1_PRESS; } }
    if(KEY2 == 0) { Delay_ms(10); if(KEY2 == 0 && !key_down) { key_down = 1; return KEY2_PRESS; } }
    if(KEY3 == 0) { Delay_ms(10); if(KEY3 == 0 && !key_down) { key_down = 1; return KEY3_PRESS; } }
    if(KEY4 == 0) { Delay_ms(10); if(KEY4 == 0 && !key_down) { key_down = 1; return KEY4_PRESS; } }
    if(KEY5 == 0) { Delay_ms(10); if(KEY5 == 0 && !key_down) { key_down = 1; return KEY5_PRESS; } }
    
    if(KEY1 != 0 && KEY2 != 0 && KEY3 != 0 && KEY4 != 0 && KEY5 != 0)
    {
        key_down = 0;
    }
    
    return KEY_NONE;
}

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
