// ***************************************************************/
//  DeviceContext   version:  1.0   ��  date: 5/5/2008
//  -------------------------------------------------------------
//  �豸��Ϣ������
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************/

#include "LocalIncludeFile.h"
char roadCridState = 'A';
void SetroadCridState(char value)
{	
	roadCridState=value;
}
char GetroadCridState(void)
{	
	return roadCridState;
}

/***************************************************************/
////�����������״̬
/***************************************************************/
BOOL connectState = F;
void SetconnectState(BOOL  value)
{	
	connectState=value;
}
BOOL GetconnectState(void)
{	
	return connectState;
}


/***************************************************************/
////���ӷ������ĵļ������
/***************************************************************/
int ConnectCount =0;
void SetConnectCount(int value)
{	
	ConnectCount=value;
}
int GetConnectCount(void)
{	
	return ConnectCount;
}
/***************************************************************/
////�Ƿ�������ӷ�����
/***************************************************************/
BOOL enabledConnect =T;	
void SetenabledConnect(BOOL value)
{	
	enabledConnect=value;
}

BOOL  GetenabledConnect(void)
{	
	return enabledConnect;
}
/***************************************************************/
//��Ϣ�߳����߱�־
/***************************************************************/
BOOL messageThreadSleeped =F;
void SetmessageThreadSleeped(BOOL value)
{	
	messageThreadSleeped=value;
}

BOOL  GetmessageThreadSleeped(void)
{	
	return messageThreadSleeped;
}
/***************************************************************/
////�Żݿ���
/***************************************************************/
char G_AbateNumber[16];

void  SETG_AbateNumber_end(int value)
{	
		G_AbateNumber[value] = '\0';	
}


void  InitG_AbateNumber(void)
{	
	memset(G_AbateNumber, 0x00, sizeof(G_AbateNumber));	
}
void SetG_AbateNumber(char *value)
{	
	strncpy(G_AbateNumber,value,sizeof(G_AbateNumber));	
}

char *GetG_AbateNumber(void)
{	
	return G_AbateNumber;
}
/*************************************************************************************************************/
////��¼�������Żݳ��������������е������� ����������õ����ͺͽ��
/*************************************************************************************************************/
volatile int G_AbateNumber_Index=0;

void SetG_AbateNumber_Index(int value)
{	
	G_AbateNumber_Index=value;
}
int GetG_AbateNumber_Index(void)
{	
	return G_AbateNumber_Index;
}
/***************************************************************/
//
/***************************************************************/
BOOL g_SocketState =F;
void Setg_SocketState(BOOL  value)
{	
	g_SocketState=value;
}
BOOL Getg_SocketState(void)
{	
	return g_SocketState;
}
/***************************************************************/
//
/***************************************************************/
int g_SocketTimeOut =0;
void Setg_SocketTimeOut(int value)
{	
	g_SocketTimeOut=value;
}
int Getg_SocketTimeOut(void)
{	
	return g_SocketTimeOut;
}
/***************************************************************/
//
/***************************************************************/
int g_SocketUseTimeCount=0;
void Setg_SocketUseTimeCount(int value)
{	
	g_SocketUseTimeCount=value;
}
int Getg_SocketUseTimeCount(void)
{	
	return g_SocketUseTimeCount;
}
/***************************************************************/
//
/***************************************************************/
unsigned char G_SerialCommandDev = 0x00;

void SetG_SerialCommandDev( unsigned char value)
{	
	G_SerialCommandDev=value;
}

char GetG_SerialCommandDev(void)
{	
		return G_SerialCommandDev;
}

void SetG_SerialCommandDev_or(unsigned char value)
{	
	G_SerialCommandDev |=value;
}

void SetG_SerialCommandDev_and(unsigned char value)
{	
	G_SerialCommandDev &= ~value;
}

unsigned int  _RequestcardNum;
char _CardNoString[11];
//д�������Ŀ���
void SetCardNO( unsigned int inputequestcardNum )
{
	memset(_CardNoString,0x00,11);
	sprintf( _CardNoString,"%010u",inputequestcardNum);
	_RequestcardNum=inputequestcardNum;
}
//����޷���Int�͵Ŀ���
unsigned int GetCardNO(void)
{
	return _RequestcardNum ;
}
//ʹ���ַ�����ʽ��ÿ���
char * GetCardNOByString(void)
{
    return _CardNoString;
}
BOOL _IsCardExist=F;
//��ǰ���Ƿ����
BOOL IsCardExist(void)
{
	return _IsCardExist;
}
//�����Ƿ����
void SetCardExist(BOOL ice)
{
	_IsCardExist=ice;
}

BOOL _IsCardInReader=F;
//���ÿ��Ƿ��������ϲ���
BOOL IsCardInReader(void)
{
	return _IsCardInReader;
}
//���ÿ��Ƿ��������ϲ���
void SetCardInReader(BOOL ice)
{
	_IsCardInReader=ice;
}

///������
char G_CarAxlesNum[10];
void  InitG_CarAxlesNum(void)
{
	memset(G_CarAxlesNum, 0x00, sizeof(G_CarAxlesNum));	
}
char *GetG_CarAxlesNum(void)
{
	return G_CarAxlesNum;
}
//����
char G_ZhaoLing[10];
void  InitG_ZhaoLing(void)
{
	memset(G_ZhaoLing, 0x00, sizeof(G_ZhaoLing));	
}
char *GetG_ZhaoLing(void)
{
	return G_ZhaoLing;
}
///����״̬
int G_WeightMenuStues = 0;
void SetG_WeightMenuStues(int value)
{
	Set_MenuCZ_Check(G_WeightMenuStues,FALSE);
	G_WeightMenuStues = value;
	Set_MenuCZ_Check(G_WeightMenuStues,TRUE);
}
int GetG_WeightMenuStues(void)
{
	return G_WeightMenuStues;
}
