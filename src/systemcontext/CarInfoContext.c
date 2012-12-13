// ***************************************************************
//  UserContext   version:  1.0   ·  date: 5/05/2008
//  -------------------------------------------------------------
//  车、车队过车信息事务上下文
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************

#include "LocalIncludeFile.h"


//车型相关处理
char G_Car_Type[9];
void Init_Current_Car_Type(void)
{	
	memset(G_Car_Type, '\0', 9);
	I_DEV_VDM_CarType(" ");		
}
char  *Get_Current_Car_Type(void)
{	
	return G_Car_Type;
}
int Get_Current_Car_Type_Index()
{	
	int ret = -1;
	ret=atoi(Get_Current_Car_Type());
	if(OLD312CalculateFare==GetCalculateFareMode())
	{
		if(ret<=2)
		{
			ret = 0;
		}
		else if( ret<=5)
		{
			ret = 1;
		}
		else if(ret<=10)
		{
			ret = 2;
		}
		else if(ret<=15)
		{
			ret = 3;
		}
		else
		{
			ret = 4;
		}
	}
	else if((WeightCarClassBUS == GetWeightCarClass() && OLD312JaoKeCalculateFareMode == GetJaoKeCalculateFareMode())) //Compatible Old 312 
	{
	
		echoic("Get_Current_Car_Type_Index ret = %d",ret);
		if(ret==1)
		{
			ret = 0;
		}
		else if( ret==2)
		{
			ret = 1;
		}
		else if(ret==3 ||ret==4  )
		{
			ret = 2;
		}
		else
		{
			ret = 3;
		}
	}
	else
	{
		ret = ret -1;
	}
	
	return ret;
}

//车种
char carKindExplain[20];
void InitG_Current_Handl_Car_Kind()
{	
	memset(carKindExplain,' ',20);	
	I_DEV_VDM_CarKind(-2);	
}
char * Getg_CurrentCarKindExplain(void)
{	
	return carKindExplain;
}
//车种Index
int Current_Kind_Index=-2;
int Getg_CurrentCarKindIndex()
{	
	return Current_Kind_Index;
}
int Validate_Car_Kind(int keyboardValue)
{		
	int i;
	char tempKeyboardValue[3];
	Current_Kind_Index = -1;
	memset(tempKeyboardValue,0x00,sizeof(tempKeyboardValue));
	echoic("车型数量:%d 键码:%d",GetG_Lane_carKindCount(),keyboardValue);
	for(i=0;i<GetG_Lane_carKindCount();	 i++)
	{	

		strncpy(tempKeyboardValue,CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue));	
		if(keyboardValue == atoi(tempKeyboardValue))
		{	
			Current_Kind_Index = i;
			memset(carKindExplain,0x00,20);
			strncpy(carKindExplain,CarKindRecord[i].carKindExplian,8);
			SetG_BillPrintFlag(CarKindRecord[i].BillFlag[0]=='1' ? 1:0);	
			UI_SetCarKind(Current_Kind_Index);
			I_DEV_VDM_CarKind(Current_Kind_Index);	
			break;
		}
	}		
	return Current_Kind_Index;
}
/*******************************************************************************
*票据打印标志
*0 不要
*1只一次就正确打印出收据
2 备用手撕票
3 重打的次数(16进制)
4-   为了发送SendMsgInfo消息的方便，发消息时它对应空字符
*******************************************************************************/
int G_BillPrintFlag = -1;
void SetG_BillPrintFlag(int value)
{	
     G_BillPrintFlag=value;
}

int GetG_BillPrintFlag(void)
{	
    return G_BillPrintFlag;
}


/*******************************************************************************/
////计重车辆类型
/*******************************************************************************/
char WeightCarClass = WeightCarClassBUS;
void SetWeightCarClass(char _WeightCarClass)
{
	WeightCarClass = _WeightCarClass;
	
}
char  GetWeightCarClass()
{
	return WeightCarClass;
}


/**
 * 发送监控呼叫
 */
void SendTcoWaingMsg(char *Msg)
{
	char title[80];
	char context[80];
	char path [80];
	memset(title,0x00,strlen(title));
	memset(context,0x00,strlen(context));
	memset(path,0x00,strlen(path));
	if (EnabledCallTCS()==F)
	{
		return;
	}
	if (0== 1 && GetDevCStatePlazaServerState())
	{
		return;
	}
	InitMsgTCO();   
	GetMsgTCO()->MsgType =MSGTCO_CMD_TCOWAING ;
	sprintf(title,"%s%-60s","提示",SUBSTRING(GetMsgHead()->LaneNo));
	strncpy(GetMsgTCO()->MsgTitle,title,sizeof(GetMsgTCO()->MsgTitle));
	sprintf(context,"%-60s",Msg);
	strncpy(GetMsgTCO()->MsgContext,context,sizeof(GetMsgTCO()->MsgContext));
	sprintf(path,"%-60s",BuildTCOImage(MSGTCO_CMD_TCOWAING,Msg));
	strncpy(GetMsgTCO()->MsgImagePath,path,sizeof(GetMsgTCO()->MsgImagePath));
	SendMessageToQueue(ID_TCOMSG ); 
	echoic("消息%s \n图片地址%s",Msg,SUBSTRING(GetMsgTCO()->MsgImagePath));
}
char _YCQK[100];
void InitYCQK(void)
{
	memset(_YCQK,0x00,100);
}
void AddYCQK(char * tmp)
{
	int l=0;
	if (tmp==NULL || strlen(tmp)>32)
	{
		return;
	}
	if (strlen(_YCQK)>0)
	{
		l =strlen(_YCQK)+strlen(tmp);
		echoic("LLLLLLLLLLLLLLL=%d   :::%s",l,_YCQK);
		if (l<=31)
		{
			sprintf(_YCQK,"%s/%s",_YCQK,tmp);
			_YCQK[33]=0;
		}
	}
	else
	{
		sprintf(_YCQK,"%s",tmp);
	}
}
char * GetYCQK(void)
{
	strncpy(_YCQK,_YCQK,32);
	return _YCQK;
}
