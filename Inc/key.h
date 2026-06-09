#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY_NONE    0
#define KEY1_PRESS  1
#define KEY2_PRESS  2
#define KEY3_PRESS  3
#define KEY4_PRESS  4
#define KEY5_PRESS  5

void KEY_Init(void);
u8 KEY_Scan(void);

#endif
