// ***************************************************************
//  FileContext   version:  1.0   ��  date: 5/5/2008
//  -------------------------------------------------------------
//  �ļ���Ϣ������
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************

#include "LocalIncludeFile.h"
/*******************************************************************************/
////��ǰ��ʾ��Ϣ
/********************************************************************************/
char G_CurrentInfo[350];
void SetG_CurrentInfo(char * value)
{	
	strncpy(G_CurrentInfo,value,sizeof(G_CurrentInfo));	
}

char *GetG_CurrentInfo(void)
{	
	return G_CurrentInfo;
}

/*****************************************************************************************************/
////��ʾ��Ϣ����ʱ��� ����Υ�´�������󷵻�ʱ��
/*****************************************************************************************************/
char G_CurrentInfoTemp[350];
void SetG_CurrentInfoTemp(char * value)
{	
	strncpy(G_CurrentInfoTemp,value,sizeof(G_CurrentInfoTemp));	
}

char *GetG_CurrentInfoTemp(void)
{	
	return G_CurrentInfoTemp;
}


/**************************************************************/
//�Żݳ���
/**************************************************************/
int g_AbateType=0;
void Setg_AbateType(int value)
{	
	g_AbateType=value;
}
int Getg_AbateType(void)
{	
	return g_AbateType;
}
/**************************************************************/
//��ǰ����
/**************************************************************/
int Currentvolume = 3;
void SetCurrentvolume(int value)
{	
	Currentvolume=value;
}
int GetCurrentvolume(void)
{	
	return Currentvolume ;
}
/**************************************************************/
//�������
/**************************************************************/
int Maxvolume = 0x16;
void SetMaxvolume(int value)
{	
	Maxvolume=value;
}
int GetMaxvolume(void)
{	
	return Maxvolume;
}
/**************************************************************/
//��С����
/**************************************************************/
int Minvolume =0x22;
void SetMinvolume(int value)
{	
	Minvolume=value;
}
int GetMinvolume(void)
{	
	return Minvolume;
}
/******************************************************************************************
*���ز����ļ��Ƿ�ɹ�    1�ɹ�   0ʧ�ܣ���ʼ״̬�ǳɹ�
*AUTHOR ��lzp
* DATE :12/7/2008
******************************************************************************************/
int  LoadYPKListRecordFlag=1;  //��Ʊ��
void SetLoadYPKListRecordFlag(int  value)
{	
	LoadYPKListRecordFlag=value;
}

int  GetLoadYPKListRecordFlag(void)
{	
	return LoadYPKListRecordFlag;
}

//�����Żݿ����־
int  LoadYHKListRecordFlag=1;
void SetLoadYHKListRecordFlag(int  value)
{	
	LoadYHKListRecordFlag=value;
}

int  GetLoadYHKListRecordFlag(void)
{	
	return LoadYHKListRecordFlag;
}

//�����Ż����������־
int  LoadYHRateDescriptionRecordFlag=1;
void SetLoadYHRateDescriptionRecordFlag(int  value)
{	
	LoadYHRateDescriptionRecordFlag=value;
}

int  GetLoadYHRateDescriptionRecordFlag(void)
{	
	return LoadYHRateDescriptionRecordFlag;
}

//����ְԱ���־
int  LoadCollectRecordFlag=1;
void SetLoadCollectRecordFlag(int  value)
{	
	LoadYPKListRecordFlag=value;
}

int  GetLoadCollectRecordFlag(void)
{	
	return LoadCollectRecordFlag;
}

//���ط��ʱ�־
int  LoadFareRecordFlag=1;
void SetLoadFareRecordFlag(int  value)
{	
	LoadFareRecordFlag=value;
}

int  GetFareRecordFlag(void)
{	
	return LoadFareRecordFlag;
}

//���س��ֱ��ʶ
int  LoadCarKindRecordFlag=1;
void SetLoadCarKindRecordFlag(int  value)
{	
	LoadCarKindRecordFlag=value;
}

int  GetLoadCarKindRecordFlag(void)
{	
	return LoadCarKindRecordFlag;
}


