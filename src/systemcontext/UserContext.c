// ***************************************************************
//  UserContext   version:  1.0   ��  date: 5/5/2008
//  -------------------------------------------------------------
//  �û���Ϣ������
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************

/***************************************************************/
//��¼�ڹ���״̬ʱȡ���Ĵ���
/***************************************************************/
#include "LocalIncludeFile.h"

volatile int CancelCount;

void InitCancelCount(void)
{	
    CancelCount=0;
}

//����һ��ȡ������
void AddCancelCount(void)
{	
    ++CancelCount;
}
//��ȡȡ����������
int GetCancelCount(void)
{	
    return CancelCount;
}

/***************************************************************/
//���ŵĳ��� ��������
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
//���볤�� �������������
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
//��Ҫ¼����ʱ���¼�����ݵĳ���
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
//����
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
////����
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
//�Ƿ��ǵڶ��ε�½ ����ǵڶ��ε�½��������ļ�û�и��¾���ȥ�������ļ� ��߹���Ч��
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
//����
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
�����
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
��ǰ�ϰ������
1�����շ�
2ģ���շ�
3�豸����
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
        case  WORKSTAUS_NORMAL:  //'1'//�����շ�
            sprintf(str_g_workStatus,"�����շ�");	
            break;
        case WORKSTAUS_SIMULATRO ://'2'//ģ���շ�
            sprintf(str_g_workStatus,"ģ���շ�");	
            break;
        case WORKSTAUS_SETTEST: //'3'//�豸����
            sprintf(str_g_workStatus,"ģ���շ�");	
            break;
        case WORKSTAUS_EXPORTDATA ://'4'//��������
            sprintf(str_g_workStatus,"ģ���շ�");	
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
��ǰ�ϰ����Ա����
1 �շ�Ա
2 ά��Ա
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
    if(0==strcmp(g_collectType,"�շ�Ա"))
    {	
        ret='1';
    }
    else if(0==strcmp(g_collectType,"����Ա"))
    {	
        ret='2';
    }
    return ret;
}
char * GetG_collectTypeStr(void)
{	
	return g_collectType;
}

 
