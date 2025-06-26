// lcd.c
#include "lcd.h"

#define nop(void) { for(volatile int i=0; i<1; i++); }

void LCD_Init(void)
{
    LCD_Write_Cmd(LCD_SHOW_MODE);
    LCD_Write_Cmd(LCD_SHOW_MODE);
    LCD_Write_Cmd(LCD_SHOW_CMD);
    LCD_Write_Cmd(LCD_MSE_RMODE);
    LCD_Write_Cmd(LCD_CLEAR);
    LCD_Write_Cmd(LCD_MSE_FLEFT);
}

void LCD_Write_Data(uchar Data)
{
    LCD_DATA_MODE;
    LCD_WR_CMD;
    LCD_CMD;
    DATA_PORT = Data;
    nop();
    LCD_NCMD;
    delay(10);
}

void LCD_Write_Cmd(uchar Cmd)
{
    LCD_CMD_MODE;
    LCD_WR_CMD;
    LCD_CMD;
    DATA_PORT = Cmd;
    nop();
    LCD_NCMD;
    delay(10);
}

void LCD_Show_String(const char *s)
{
    while(*s != '\0')
    {
        LCD_Write_Data(*s++);
    }
}

// 设置光标位置，pos是0~15 (第一行0~15，第二行16~31)
void LCD_Set_Cursor(u8 pos)
{
    if(pos < 16)
        LCD_Write_Cmd(0x80 + pos);        // 第一行起始地址0x80
    else
        LCD_Write_Cmd(0x80 + 0x40 + pos - 16);  // 第二行起始地址0xC0
}

// 清除指定位置字符
void LCD_Clear_Char(u8 pos)
{
    LCD_Set_Cursor(pos);
    LCD_Write_Data(' ');
    LCD_Set_Cursor(pos);
}