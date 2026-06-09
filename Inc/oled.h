#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"

/* OLED屏幕分辨率 */
#define OLED_WIDTH   128
#define OLED_HEIGHT  64

/* OLED显示缓存 */
extern u8 OLED_DisplayBuf[8][128];

/* OLED初始化 */
void OLED_Init(void);

/* OLED基础操作 */
void OLED_WriteCmd(u8 cmd);
void OLED_WriteData(u8 data);
void OLED_SetPos(u8 x, u8 y);
void OLED_Clear(void);
void OLED_Refresh(void);

/* OLED显示函数 */
void OLED_ShowChar(u8 x, u8 y, u8 chr);
void OLED_ShowString(u8 x, u8 y, u8 *str);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len);
void OLED_ShowHexNum(u8 x, u8 y, u32 num, u8 len);
void OLED_ShowBinary(u8 x, u8 y, u32 num, u8 len);

/* OLED图形操作 */
void OLED_DrawPixel(u8 x, u8 y);
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_FillRectangle(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_DrawCircle(u8 x, u8 y, u8 r);

/* OLED高级操作 */
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_SetContrast(u8 contrast);
void OLED_SetBrightness(u8 brightness);

#endif /* __OLED_H */
