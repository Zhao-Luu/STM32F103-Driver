#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

/* ADC采样通道 */
#define ADC_CHANNEL_0    0    /* PA0 */
#define ADC_CHANNEL_1    1    /* PA1 */
#define ADC_CHANNEL_2    2    /* PA2 */
#define ADC_CHANNEL_3    3    /* PA3 */
#define ADC_CHANNEL_4    4    /* PA4 */
#define ADC_CHANNEL_5    5    /* PA5 */
#define ADC_CHANNEL_6    6    /* PA6 */
#define ADC_CHANNEL_7    7    /* PA7 */
#define ADC_CHANNEL_8    8    /* PB0 */
#define ADC_CHANNEL_9    9    /* PB1 */
#define ADC_CHANNEL_10   10   /* PC0 */
#define ADC_CHANNEL_11   11   /* PC1 */
#define ADC_CHANNEL_12   12   /* PC2 */
#define ADC_CHANNEL_13   13   /* PC3 */
#define ADC_CHANNEL_14   14   /* PC4 */
#define ADC_CHANNEL_15   15   /* PC5 */
#define ADC_CHANNEL_16   16   /* 内部温度传感器 */
#define ADC_CHANNEL_17   17   /* Vrefint参考电压 */

/* ADC初始化 */
void ADC_Init(void);

/* 单通道采集 */
u16 ADC_GetValue(u8 channel);

/* 多通道采集 */
u16 ADC_GetValue_DMA(u8 channel, u16 times);

/* 灰度传感器采集 (通道9) */
u16 ADC_GetGrayValue(void);
u16 ADC_GetGrayValue_Avg(u8 times);

/* 温度传感器采集 */
float ADC_GetTemperature(void);

/* 参考电压采集 */
u16 ADC_GetVrefint(void);

#endif /* __ADC_H */
