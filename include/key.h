#ifndef __KEY_H
#define __KEY_H

#include "sys/reg51.h"
#include "delay.h"
#include "type.h"

#define KEY_PORT P1
#define OK      11   // 确定
#define BACK    12   // 退格
#define CANCEL  13   // 取消
#define DOT     14   // 小数点
#define NONE    0xFF // 无效/空键

extern const u16 keyMap[4][4];
u8 keyScan();

#endif //KEY_H