/**
  ******************************************************************************
  * @file    adc.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    ADC driver implementation
  ******************************************************************************
  */

#include "adc.h"

/**
  * @brief  ADC initialization
  * @param  None
  * @retval None
  */
void ADC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    /* Configure analog input pins */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                  GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  /* ADC clock = 72MHz / 6 = 12MHz */
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_Cmd(ADC1, ENABLE);
    
    /* Calibrate ADC */
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

/**
  * @brief  Get ADC value from specified channel
  * @param  channel: ADC channel (0-17)
  * @retval ADC value (0-4095)
  */
u16 ADC_GetValue(u8 channel)
{
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    
    return ADC_GetConversionValue(ADC1);
}

/**
  * @brief  Get average ADC value
  * @param  channel: ADC channel
  * @param  times: Number of samples
  * @retval Average ADC value
  */
u16 ADC_GetValue_DMA(u8 channel, u16 times)
{
    u32 sum = 0;
    u16 i;
    
    for(i = 0; i < times; i++)
    {
        sum += ADC_GetValue(channel);
    }
    
    return sum / times;
}

/**
  * @brief  Get grayscale sensor value (channel 9 - PB1)
  * @param  None
  * @retval Grayscale value (0-4095)
  */
u16 ADC_GetGrayValue(void)
{
    return ADC_GetValue(ADC_CHANNEL_9);
}

/**
  * @brief  Get average grayscale sensor value
  * @param  times: Number of samples
  * @retval Average grayscale value
  */
u16 ADC_GetGrayValue_Avg(u8 times)
{
    return ADC_GetValue_DMA(ADC_CHANNEL_9, times);
}

/**
  * @brief  Get temperature from internal sensor
  * @param  None
  * @retval Temperature in Celsius
  */
float ADC_GetTemperature(void)
{
    u16 adc_val = ADC_GetValue(ADC_CHANNEL_16);
    float temp = (1.43f - (adc_val * 3.3f / 4096.0f)) / 0.0043f + 25.0f;
    return temp;
}

/**
  * @brief  Get reference voltage
  * @param  None
  * @retval Vrefint ADC value
  */
u16 ADC_GetVrefint(void)
{
    return ADC_GetValue(ADC_CHANNEL_17);
}

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
