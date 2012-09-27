#include "LocalIncludeFile.h"
/******************************/
// 雨棚灯工作状态值
/******************************/
BOOL   g_bYuPeng=F;
void Setg_bYuPeng(BOOL  value)
{	
	g_bYuPeng=value;
	UI_Set_Device_State(1,g_bYuPeng);
}
BOOL Getg_bYuPeng(void)
{	
	return g_bYuPeng;
}
/*******************************************************************************/
//交通灯工作状态值
/*******************************************************************************/
volatile BOOL g_bJiaoTong=F;

void Setg_bJiaoTong(BOOL  value)
{	
	g_bJiaoTong=value;
	UI_Set_Device_State(2,g_bJiaoTong);
}
int Getg_bJiaoTong(void)
{	
	return g_bJiaoTong;
}
/*******************************************************************************/
//栏杆工作状态值
/*******************************************************************************/

volatile BOOL  g_bLanGan=F;

void Setg_bLanGan(BOOL  value)
{	
	g_bLanGan=value;
	UI_Set_Device_State(3,g_bLanGan);
}
int Getg_bLanGan(void)
{	
	return g_bLanGan;
}
/*******************************************************************************/
//抓拍线圈工作状态值
/*******************************************************************************/
BOOL   g_bZhuaPaiXianQuan=FALSE;
void Setg_bZhuaPaiXianQuan(BOOL  value)
{	
	g_bZhuaPaiXianQuan=value;
	UI_Set_Device_State(4,g_bZhuaPaiXianQuan);
}
int Getg_bZhuaPaiXianQuan(void)
{	
	return g_bZhuaPaiXianQuan;
}
/*******************************************************************************/
//通过线圈工作状态值
/*******************************************************************************/
BOOL  g_bTongGuoXianQuan=FALSE;
void Setg_bTongGuoXianQuan(BOOL  value)
{	
	g_bTongGuoXianQuan=value;
	UI_Set_Device_State(5,g_bTongGuoXianQuan);
}
int Getg_bTongGuoXianQuan(void)
{	
	return g_bTongGuoXianQuan;
}
/*******************************************************************************/
//打印机工作状态值
/*******************************************************************************/
BOOL  _PrintState =FALSE;
void Setg_bPrint( BOOL  value)
{	
	_PrintState=value;
	UI_Set_Device_State(6,_PrintState);
}
int Getg_bPrint(void)
{	
	return _PrintState;
}
/*******************************************************************************/
//闹铃工作状态值
/*******************************************************************************/
volatile BOOL  g_Ring =F;
void Setg_Ring(BOOL  value)
{	
	g_Ring=value;
	UI_Set_Device_State(7,value);
}
int Getg_Ring(void)
{	
	return g_Ring;
}
/*******************************************************************************/
//输出状态值
/*******************************************************************************/
char  g_printfState ='s';
void Setg_printfState(char value)
{	
	g_printfState=value;
}
int Getg_printfState(void)
{	
	return g_printfState;
}

