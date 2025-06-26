#ifndef  __LCD_H
#define  __LCD_H

#include "sys/reg51.h"
#include "delay.h"
#include "type.h"
//#include <intrins.h>


//sbit RW = 0xA5;  // P2.5的绝对地址是0xA5
//sbit RS = 0xA6;  // P2.6的绝对地址是0xA6
//sbit E  = 0xA7;  // P2.7的绝对地址是0xA7
__sbit __at (0xA5) RW;
__sbit __at (0xA6) RS;
__sbit __at (0xA7) E;

#define  DATA_PORT 	P0

#define  LCD_DATA_MODE			RS = 1			/*数据信号*/
#define  LCD_CMD_MODE			RS = 0			/*指令信号*/
#define  LCD_RD_CMD				RW = 1			/*读LCD*/
#define  LCD_WR_CMD				RW = 0			/*写LCD*/
#define  LCD_CMD				E = 1			/*使能LCD*/
#define  LCD_NCMD				E = 0			/*失能LCD*/

#define  LCD_SHOW_MODE		0x38	/*两行显示，5x8点阵*/
#define  LCD_SHOW_CMD		0x0F	/*屏幕显示，光标显示，光标闪烁*/
#define  LCD_MSE_RMODE		0x06	/*光标右移，画面不跟随移动*/
#define  LCD_CLEAR			0x01	/*清屏*/
#define  LCD_MSE_FLEFT		0x80	/*设置光标为第一行左边*/
#define  LCD_MSE_SLEFT		0xC0	/*设置光标为第二行左边*/

#define LCD_Reshow(void) do { LCD_Write_Cmd(LCD_CLEAR); LCD_Write_Cmd(LCD_MSE_FLEFT); } while(0);

void LCD_Init(void);							/*初始化LCD*/
void LCD_Write_Data(uchar Data);			/*写指令*/
void LCD_Write_Cmd(uchar Cmd);				/*写数据*/
void LCD_Show_String(const char *s); 			/*显示字符串*/
void LCD_Clear_Char(u8 pos);
void LCD_Set_Cursor(u8 pos);

#endif