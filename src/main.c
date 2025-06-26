#include "../include/key.h"
#include "../include/sys/reg51.h"
#include "../include/lcd.h"
#include "../include/pwd.h"

// 简单数字转字符串函数
void u8_to_str(u8 num, char *buf) {
    if (num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    u8 i = 0;
    char temp[4];
    while (num > 0) {
        temp[i++] = '0' + (num % 10);
        num /= 10;
    }
    for (u8 j = 0; j < i; j++)
        buf[j] = temp[i - 1 - j];
    buf[i] = '\0';
}

// 提示宏定义（LCD 限制：≤ 16 字符）
#define MSG_ENTER      "> Enter:"
#define MSG_OLD        "> Old:"
#define MSG_NEW        "> New:"
#define MSG_LOGIN_OK   "Welcome  ^_^"
#define MSG_LOGIN_ERR  "Wrong!    :("
#define MSG_UPDATE_OK  "Updated! ^_^"
#define MSG_UPDATE_ERR "Update!   :("
#define MSG_OLD_ERR    "Bad Old!  :("

u16 key;
__bit up_pwd_flag = 0;
extern SelfPwd_t userPwd;

int main(void)
{
    __bit result;
    char key_str[4];

    LCD_Init();
    PWD_Init();

    LCD_Reshow();
    LCD_Show_String(MSG_ENTER);
    LCD_Write_Cmd(LCD_MSE_SLEFT);

    while (1)
    {
        key = keyScan();
        if (key == NONE)
            continue;

        else if (key == BACK)
        {
            PWD_Del_Num();
        }
        else if (key == OK)
        {
            if (up_pwd_flag)
            {
                result = PWD_Check();
                if (!result)
                {
                    LCD_Reshow();
                    LCD_Show_String(MSG_OLD_ERR);
                    delay(800);
                }
                else
                {
                    LCD_Reshow();
                    LCD_Show_String(MSG_NEW);
                    LCD_Write_Cmd(LCD_MSE_SLEFT);
                    result = PWD_Update();
                    LCD_Reshow();
                    LCD_Show_String(result ? MSG_UPDATE_OK : MSG_UPDATE_ERR);
                    delay(800);
                }

                up_pwd_flag = 0;
                LCD_Reshow();
                LCD_Show_String(MSG_ENTER);
                LCD_Write_Cmd(LCD_MSE_SLEFT);
            }
            else
            {
                result = PWD_Check();
                LCD_Reshow();
                LCD_Show_String(result ? MSG_LOGIN_OK : MSG_LOGIN_ERR);
                delay(1500);

                PWD_Clear_UPwd();
                LCD_Reshow();
                LCD_Show_String(MSG_ENTER);
                LCD_Write_Cmd(LCD_MSE_SLEFT);
            }
        }
        else if (key == CANCEL)
        {
            PWD_Clear_UPwd();
            LCD_Reshow();
            LCD_Show_String(MSG_ENTER);
            LCD_Write_Cmd(LCD_MSE_SLEFT);
        }
        else if (key == DOT)
        {
            up_pwd_flag = 1;
            LCD_Reshow();
            PWD_Clear_UPwd();
            LCD_Show_String(MSG_OLD);
            LCD_Write_Cmd(LCD_MSE_SLEFT);
        }
        else
        {
            u8 num = (key == 10) ? 0 : key;
            if (userPwd.pwd_len < PWD_LEN)
            {
                PWD_Add_Num(num);
                u8_to_str(num, key_str);
                for (char *p = key_str; *p; p++)
                    LCD_Write_Data(*p);
            }
        }
    }

    return 0;
}