#include "LocalIncludeFile.h"
/******************************/
// ����ƹ���״ֵ̬
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
//��ͨ�ƹ���״ֵ̬
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
//���˹���״ֵ̬
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
//ץ����Ȧ����״ֵ̬
/*******************************************************************************/
BOOL   g_bZhuaPaiXianQuan=FALSE;
void Setg_bZhuaPaiXianQuan(BOOL  value)
{	
	g_bZhuaPaiXianQuan=value;
	UI_Set_Device_State(4,g_bZhuaPaiXianQuan);
	SendLaneInfo_default();
}
int Getg_bZhuaPaiXianQuan(void)
{	
	return g_bZhuaPaiXianQuan;
}
/*******************************************************************************/
//ͨ����Ȧ����״ֵ̬
/*******************************************************************************/
BOOL  g_bTongGuoXianQuan=FALSE;
void Setg_bTongGuoXianQuan(BOOL  value)
{	
	g_bTongGuoXianQuan=value;
	UI_Set_Device_State(5,g_bTongGuoXianQuan);
	SendLaneInfo_default();
}
int Getg_bTongGuoXianQuan(void)
{	
	return g_bTongGuoXianQuan;
}
/*******************************************************************************/
//��ӡ������״ֵ̬
/*******************************************************************************/
BOOL  _PrintState =FALSE;
void Setg_bPrint( BOOL  value)
{	
	_PrintState=value;
	UI_Set_Device_State(6,_PrintState);
	SendLaneInfo_default();
}
int Getg_bPrint(void)
{	
	return _PrintState;
}
/*******************************************************************************/
//���幤��״ֵ̬
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
//���״ֵ̬
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

