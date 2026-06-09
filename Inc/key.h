#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

/* 按键值定义 */
#define KEY_NONE        0x00
#define KEY1_PRESS      0x01
#define KEY2_PRESS      0x02
#define KEY3_PRESS      0x03
#define KEY4_PRESS      0x04
#define KEY5_PRESS      0x05
#define SWITCH_1        0x11
#define SWITCH_2        0x12
#define SWITCH_3        0x13
#define SWITCH_4        0x14
#define SWITCH_5        0x15

/* 按键初始化 */
void KEY_Init(void);

/* 按键扫描 */
u8 KEY_Scan(void);          /* 简单扫描 */
u8 KEY_ScanWithFilter(void);/* 带滤波扫描 */

/* 按键状态检测 */
u8 KEY1_GetState(void);     /* 获取按键1状态 */
u8 KEY2_GetState(void);
u8 KEY3_GetState(void);
u8 KEY4_GetState(void);
u8 KEY5_GetState(void);

/* 拨码开关状态 */
u8 Switch_GetValue(void);   /* 获取所有拨码开关值 */
u8 Switch_GetBit(u8 bit);   /* 获取第bit位拨码开关 */

/* 按键处理结构体 */
typedef struct
{
    u8 is_pressed;          /* 是否按下 */
    u8 press_count;         /* 按下计数 */
    u8 release_count;       /* 释放计数 */
    u8 single_click;        /* 单击 */
    u8 long_press;          /* 长按 */
    u16 press_time;         /* 按下时间 */
} KEY_State_t;

extern KEY_State_t Key1_State;
extern KEY_State_t Key2_State;
extern KEY_State_t Key3_State;
extern KEY_State_t Key4_State;
extern KEY_State_t Key5_State;

#endif /* __KEY_H */
