// ***************************************************************
//  UserContext   version:  1.0   ·  date: 5/5/2008
//  -------------------------------------------------------------
//  用户信息上下文
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************

/***************************************************************/
//记录在工作状态时取消的次数
/***************************************************************/
#include "LocalIncludeFile.h"

volatile int CancelCount;

void InitCancelCount(void)
{	
    CancelCount=0;
}

//增加一次取消操作
void AddCancelCount(void)
{	
    ++CancelCount;
}
//获取取消操作次数
int GetCancelCount(void)
{	
    return CancelCount;
}

/***************************************************************/
//工号的长度 配置属性
/***************************************************************/
volatile int Input_Number_Count;
void SetInput_Number_Count(int var)
{
  Input_Number_Count=var;
}
void InitInput_Number_Count(void)
{	
    Input_Number_Count = 0;
}

void AddInput_Number_Count(void)
{	
    ++Input_Number_Count;
}

int GetInput_Number_Count(void)
{	
    return Input_Number_Count;
}

/***************************************************************/
//密码长度 配置软件的属性
/***************************************************************/
volatile int Input_Password_Count;

void InitInput_Password_Count(void)
{	
    Input_Password_Count = 0;
}

void AddInput_Password_Count(void)
{	
    ++Input_Password_Count;
}

int GetInput_Password_Count(void)
{	
    return Input_Password_Count;
}

/**************************************************************/
//需要录数据时存放录入数据的长度
/***************************************************************/
volatile int  InputLen ;

void InitInputInputLen(void)
{	
      InputLen = 0;
}


void AddInputLen(void)
{	
    ++InputLen;
}
void SetInputLen(int value)
{	
    InputLen=value;
}


int GetInputLen(void)
{	
    return InputLen;
}

/**************************************************************/
  int G_User_Index=0;
void SetG_User_Index(int value)
{	
    G_User_Index=value;
}

int GetG_User_Index(void)
{	
    return G_User_Index;
}
/**************************************************************/
//工号
/**************************************************************/
char G_Number[7];
void InitG_Number(void)
{	
    memset(G_Number, 0x00, 7);	
    I_DEV_VDM_CollectNo("");	
}

void SetG_Number(char *value)
{	
	memset(G_Number, 0x00, 7);	
    strncpy(G_Number,value,6);	
 
}
void SetG_NumberByChar(char  _C)
{
	int Len = strlen(G_Number);
	G_Number[Len] = _C;
}
char *GetG_Number(void)
{	
    return G_Number;
}
/**************************************************************/
////密码
/**************************************************************/
char G_Password[8];

void IntiG_Password(void)
{	
        memset(G_Password, '\0', 8);	
}

void SetG_Password(char *value)
{	
    strncpy(G_Password,value,sizeof(G_Password));	
}
void SetG_PasswordByChar(char _C)
{
	G_Password[strlen(G_Password)] = _C;
}
char *GetG_Password(void)
{	
    return G_Password;
}
/**********************************************************************************************************************************/
//是否是第二次登陆 如果是第二次登陆如果配置文件没有更新就免去读配置文件 提高工作效率
/**********************************************************************************************************************************/
BOOL secondLogin = F;
void SetsecondLogin(BOOL  value)
{	
    secondLogin=value;
}

BOOL GetsecondLogin(void)
{	
    return secondLogin;
}
/**************************************************************/
//姓名
/***************************************************************/
char g_szName[255];
void Initg_szName()
{	
	memset(g_szName,' ',sizeof(g_szName));	
}
void Setg_szName(char *value)
{	
    strncpy(g_szName,value,18);	
}

char *Getg_szName(void)
{	
    return g_szName;
}
/********************************************************************
卡箱号
********************************************************************/
char g_carboxNo[6];
void Setg_carboxNo(char * value)
{	
    strncpy(g_carboxNo,value,sizeof(g_carboxNo));	
}
char * Getg_carboxNo(void)
{	
    return g_carboxNo;
}
/********************************************************************
当前上班的类型
1正常收费
2模拟收费
3设备测试
********************************************************************/
char g_workStatus;
void Setg_workStatus(char value)
{	
    g_workStatus=value;
    SetExitESMsgWorkStaus(value);	
}

char Getg_workStatus(void)
{	
    return g_workStatus;
}
char str_g_workStatus[16];
char * Getg_workStatus_str(void)
{	
    switch (Getg_workStatus())
    {	
        case  WORKSTAUS_NORMAL:  //'1'//正常收费
            sprintf(str_g_workStatus,"正常收费");	
            break;
        case WORKSTAUS_SIMULATRO ://'2'//模拟收费
            sprintf(str_g_workStatus,"模拟收费");	
            break;
        case WORKSTAUS_SETTEST: //'3'//设备测试
            sprintf(str_g_workStatus,"模拟收费");	
            break;
        case WORKSTAUS_EXPORTDATA ://'4'//导出数据
            sprintf(str_g_workStatus,"模拟收费");	
            break;
        case WORKSTAUS_XIABAN:
            memset(str_g_workStatus,0x00,sizeof(str_g_workStatus));	
        default:
            memset(str_g_workStatus,0x00,sizeof(str_g_workStatus));	
            break;
    }
    return str_g_workStatus;
}

/********************************************************************
当前上班的人员类型
1 收费员
2 维护员
********************************************************************/
char g_collectType[50];
void SetG_collectType(char *value)
{	
    strncpy(g_collectType,value,sizeof(g_collectType));	
    SetExitESMsgCollectorType(GetG_collectType());	
}

char GetG_collectType(void)
{	
    char ret='0';
    if(0==strcmp(g_collectType,"收费员"))
    {	
        ret='1';
    }
    else if(0==strcmp(g_collectType,"管理员"))
    {	
        ret='2';
    }
    return ret;
}
char * GetG_collectTypeStr(void)
{	
	return g_collectType;
}

 
