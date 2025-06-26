#include "pwd.h"

SelfPwd_t selfPwd, userPwd;
static u8 cursor_pos = 0;  // 密码输入光标位置

void PWD_Init(void)
{
	selfPwd.pwd_val[0] = 1;
	selfPwd.pwd_val[1] = 0;
	selfPwd.pwd_val[2] = 3;
	selfPwd.pwd_val[3] = 1;
	selfPwd.pwd_len = 4;

	userPwd.pwd_len = 0;
	cursor_pos = 0;
}

__bit PWD_Check(void)
{
	if (selfPwd.pwd_len != userPwd.pwd_len)
		return 0;

	for (u8 i = 0; i < selfPwd.pwd_len; i++)
	{
		if (userPwd.pwd_val[i] != selfPwd.pwd_val[i])
			return 0;
	}

	userPwd.pwd_len = 0;
	cursor_pos = 0;
	return 1;
}

void PWD_Add_Num(u8 num)
{
	if (userPwd.pwd_len >= PWD_LEN)
		return;

	userPwd.pwd_val[userPwd.pwd_len++] = num;
	cursor_pos++;
}

void PWD_Del_Num(void)
{
	if (userPwd.pwd_len == 0)
		return;

	userPwd.pwd_len--;
	cursor_pos--;

	// 在LCD上清除当前光标位置的字符
	LCD_Clear_Char(16 + cursor_pos);  // 第二行起始16
}

__bit PWD_Update(void)
{

	u16 key;
    PWD_Clear_UPwd();
	userPwd.pwd_len = 0;
	cursor_pos = 0;

	while(1)
	{
		key = keyScan();
		if(key == NONE)
			continue;

		if(key == OK)
			break;

		if(key == BACK)
			PWD_Del_Num();
		else
		{
			if(key == 10)
				PWD_Add_Num(0);
			else if(key <= 9)
				PWD_Add_Num(key);

			// 显示实际数字
			LCD_Set_Cursor(16 + cursor_pos - 1);
			LCD_Write_Data(key == 10 ? '0' : '0' + key);
		}
	}

	// 更新密码保存
	for(u8 i = 0; i < userPwd.pwd_len; i++)
	{
		selfPwd.pwd_val[i] = userPwd.pwd_val[i];
	}
	selfPwd.pwd_len = userPwd.pwd_len;

	userPwd.pwd_len = 0;
	cursor_pos = 0;
	return 1;
}

void PWD_Clear_UPwd(void)
{
	userPwd.pwd_len = 0;
	cursor_pos = 0;
}
