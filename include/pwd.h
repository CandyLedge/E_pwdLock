#ifndef  __PWD_H
#define  __PWD_H

#include "sys/reg51.h"
#include "lcd.h"
#include "key.h"
#include "type.h"



#define  PWD_LEN	15	/*密码长度*/

/*密码结构体定义*/
typedef struct
{
	u8 pwd_val[PWD_LEN];	/*密码值*/
	u8 pwd_len;				/*密码长度*/
} SelfPwd_t;
extern __bit up_pwd_flag;
void PWD_Init(void);				/*初始化自定义密码结构体*/
__bit PWD_Check(void);				/*密码校验*/
void PWD_Add_Num(u8 num);		/*添加数字到密码数组中*/
void PWD_Del_Num(void);				/*删除一个密码*/
__bit PWD_Update(void);				/*修改密码*/
void PWD_Clear_UPwd(void);			/*清空用户密码*/

#endif