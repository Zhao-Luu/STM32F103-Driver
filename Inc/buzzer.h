#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"

/* 蜂鸣器初始化 PB8 */
void BUZZER_Init(void);

/* 蜂鸣器控制 */
void BUZZER_On(void);           /* 开启蜂鸣器 */
void BUZZER_Off(void);          /* 关闭蜂鸣器 */
void BUZZER_Toggle(void);       /* 切换蜂鸣器状态 */
void BUZZER_Beep(u16 ms);       /* 鸣叫指定时间 */

/* 蜂鸣器音调 */
void BUZZER_Tone(u16 freq, u16 duration);  /* 指定频率鸣叫 */
void BUZZER_Alert(void);        /* 警报音 */
void BUZZER_Success(void);      /* 成功提示音 */
void BUZZER_Error(void);        /* 错误提示音 */

#endif /* __BUZZER_H */
