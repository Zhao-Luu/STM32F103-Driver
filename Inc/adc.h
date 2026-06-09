#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

/* ADC channel definitions */
#define ADC_CHANNEL_0   0
#define ADC_CHANNEL_1   1
#define ADC_CHANNEL_2   2
#define ADC_CHANNEL_3   3
#define ADC_CHANNEL_4   4
#define ADC_CHANNEL_5   5
#define ADC_CHANNEL_6   6
#define ADC_CHANNEL_7   7
#define ADC_CHANNEL_8   8
#define ADC_CHANNEL_9   9   /* PB1 - Grayscale sensor */
#define ADC_CHANNEL_10  10
#define ADC_CHANNEL_11  11
#define ADC_CHANNEL_12  12
#define ADC_CHANNEL_13  13
#define ADC_CHANNEL_14  14
#define ADC_CHANNEL_15  15
#define ADC_CHANNEL_16  16  /* Internal temperature sensor */
#define ADC_CHANNEL_17  17  /* Internal Vrefint */

/* ADC initialization */
void ADC_Init(void);

/* Get ADC value from specified channel (0-4095) */
u16 ADC_GetValue(u8 channel);

/* Get average ADC value */
u16 ADC_GetValue_DMA(u8 channel, u16 times);

/* Grayscale sensor functions */
u16 ADC_GetGrayValue(void);          /* Single sample */
u16 ADC_GetGrayValue_Avg(u8 times); /* Average of multiple samples */

/* Temperature and Vref functions */
float ADC_GetTemperature(void);
u16 ADC_GetVrefint(void);

#endif /* __ADC_H */
