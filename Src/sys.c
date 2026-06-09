/**
  ******************************************************************************
  * @file    sys.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    System initialization
  ******************************************************************************
  */

#include "sys.h"

static u32 fac_us = 0;  /* us延时倍数 */
static u32 fac_ms = 0;  /* ms延时倍数 */

/**
  * @brief  System clock initialization - 72MHz from 8MHz HSE
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
    RCC_DeInit();  /* Reset to default clock configuration */
    
    /* Enable HSE (High Speed External oscillator) */
    RCC_HSEConfig(RCC_HSE_ON);
    while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);  /* Wait for HSE ready */
    
    /* Configure PLL: HSE clock divided by 1, multiplied by 9 = 72MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);  /* Wait for PLL ready */
    
    /* Configure Flash memory access time */
    FLASH_SetLatency(FLASH_Latency_2);
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    
    /* Configure AHB, APB1, APB2 clock prescalers */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);      /* HCLK = SYSCLK = 72MHz */
    RCC_PCLK1Config(RCC_HCLK_Div2);       /* PCLK1 = HCLK/2 = 36MHz */
    RCC_PCLK2Config(RCC_HCLK_Div1);       /* PCLK2 = HCLK = 72MHz */
    
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x08);  /* Wait for PLL to be system clock */
    
    /* Enable GPIO clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    /* Initialize SysTick */
    SysTick_Init();
}

/**
  * @brief  SysTick timer initialization for delay functions
  * @param  None
  * @retval None
  */
void SysTick_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    fac_us = SystemCoreClock / 1000000;  /* Calculate microsecond factor */
    fac_ms = (u16)fac_us * 1000;         /* Calculate millisecond factor */
}

/**
  * @brief  Microsecond delay function
  * @param  nus: Microseconds to delay
  * @retval None
  */
void Delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;   /* Load reload value */
    SysTick->VAL = 0x00;             /* Clear counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  /* Enable counter */
    
    do
    {
        temp = SysTick->CTRL;
    }while((temp & 0x01) && !(temp & (1 << 16)));  /* Wait for count complete */
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Disable counter */
    SysTick->VAL = 0x00;             /* Clear counter */
}

/**
  * @brief  Millisecond delay function
  * @param  nms: Milliseconds to delay
  * @retval None
  */
void Delay_ms(u32 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;  /* Load reload value */
    SysTick->VAL = 0x00;                /* Clear counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  /* Enable counter */
    
    do
    {
        temp = SysTick->CTRL;
    }while((temp & 0x01) && !(temp & (1 << 16)));  /* Wait for count complete */
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Disable counter */
    SysTick->VAL = 0x00;             /* Clear counter */
}

/**
  * @brief  NVIC interrupt priority group configuration
  * @param  NVIC_PriorityGroup: Priority grouping
  * @retval None
  */
void NVIC_PriorityGroup_Config(uint32_t NVIC_PriorityGroup)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
}

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
