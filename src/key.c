#include "key.h"

const u16 keyMap[4][4]={
    {1, 2, 3, OK},
    {4, 5, 6, CANCEL},
    {7, 8, 9, BACK},
    {0, NONE, NONE, DOT}
};

// 行掩码和列掩码保持不变
const u8 rowMask[] = {0xEF, 0xDF, 0xBF, 0x7F};
const u8 colMask[] = {0x08, 0x04, 0x02, 0x01};

// 状态机状态定义
#define STATE_IDLE     0
#define STATE_DEBOUNCE 1
#define STATE_PRESSED  2

static u8 scanState = STATE_IDLE;
static u8 currentRow = 0;
static u8 lastColRead = 0x0F;
static u8 stableCount = 0;
u8 keyScan() {
switch(scanState) {
        case STATE_IDLE:
            // 拉低当前行，准备检测
            KEY_PORT = rowMask[currentRow];
            lastColRead = KEY_PORT & 0x0F;

            if (lastColRead != 0x0F) { // 有按键按下
                scanState = STATE_DEBOUNCE;
                stableCount = 0;
            } else {
                // 没有按键，下一行
                currentRow = (currentRow + 1) & 0x03; // 0~3循环
            }
            break;

        case STATE_DEBOUNCE:
            // 再次读取列线，检测防抖
            if ((KEY_PORT & 0x0F) == lastColRead) {
                stableCount++;
                if (stableCount >= 6) { // 连续3次相同认为有效
                    // 查找具体列
                    for (u8 col = 0; col < 4; col++) {
                        if (!(lastColRead & colMask[col])) {
                            scanState = STATE_PRESSED;
                            return keyMap[currentRow][col]; // 返回按键值
                        }
                    }
                }
            } else {
                // 读数不稳定，回空闲重新扫描
                scanState = STATE_IDLE;
            }
            break;

        case STATE_PRESSED:
            // 等待按键松开（列线全高）
            if ((KEY_PORT & 0x0F) == 0x0F) {
                scanState = STATE_IDLE;
                currentRow = (currentRow + 1) & 0x03;
            }
            break;
    }
    return NONE;
}