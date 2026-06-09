/**
  ******************************************************************************
  * @file    oled.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    OLED SPI display driver
  ******************************************************************************
  */

#include "oled.h"
#include "spi.h"
#include "sys.h"

u8 OLED_DisplayBuf[8][128];

#define OLED_CS  PDout(10)
#define OLED_DC  PDout(11)
#define OLED_RES PDout(12)

void OLED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    OLED_RES = 0;
    Delay_ms(100);
    OLED_RES = 1;
    
    OLED_Clear();
}

void OLED_WriteCmd(u8 cmd)
{
    OLED_DC = 0;
    OLED_CS = 0;
    SPI1_ReadWriteByte(cmd);
    OLED_CS = 1;
}

void OLED_WriteData(u8 data)
{
    OLED_DC = 1;
    OLED_CS = 0;
    SPI1_ReadWriteByte(data);
    OLED_CS = 1;
}

void OLED_SetPos(u8 x, u8 y)
{
    OLED_WriteCmd(0xb0 + y);
    OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WriteCmd((x & 0x0f) | 0x00);
}

void OLED_Clear(void)
{
    u8 i, j;
    for(i = 0; i < 8; i++)
    {
        OLED_WriteCmd(0xb0 + i);
        OLED_WriteCmd(0x00);
        OLED_WriteCmd(0x10);
        for(j = 0; j < 128; j++)
            OLED_WriteData(0x00);
    }
}

void OLED_Refresh(void)
{
    u8 i, j;
    for(i = 0; i < 8; i++)
    {
        OLED_WriteCmd(0xb0 + i);
        OLED_WriteCmd(0x00);
        OLED_WriteCmd(0x10);
        for(j = 0; j < 128; j++)
            OLED_WriteData(OLED_DisplayBuf[i][j]);
    }
}

void OLED_ShowChar(u8 x, u8 y, u8 chr) { }
void OLED_ShowString(u8 x, u8 y, u8 *str) { }
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len) { }
void OLED_ShowHexNum(u8 x, u8 y, u32 num, u8 len) { }
void OLED_ShowBinary(u8 x, u8 y, u32 num, u8 len) { }
void OLED_DrawPixel(u8 x, u8 y) { }
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2) { }
void OLED_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2) { }
void OLED_FillRectangle(u8 x1, u8 y1, u8 x2, u8 y2) { }
void OLED_DrawCircle(u8 x, u8 y, u8 r) { }
void OLED_DisplayOn(void) { }
void OLED_DisplayOff(void) { }
void OLED_SetContrast(u8 contrast) { }
void OLED_SetBrightness(u8 brightness) { }

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
