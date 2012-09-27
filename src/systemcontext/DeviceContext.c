// ***************************************************************/
//  DeviceContext   version:  1.0   ·  date: 5/5/2008
//  -------------------------------------------------------------
//  设备信息上下文
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
////与服务器连接状态
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
////连接服务器的的间隔次数
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
////是否可以连接服务器
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
//消息线程休眠标志
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
////优惠卡号
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
////记录检索到优惠车卡号所在数组中的索引号 由这个索引得到车型和金额
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
//写入上下文卡号
void SetCardNO( unsigned int inputequestcardNum )
{
	memset(_CardNoString,0x00,11);
	sprintf( _CardNoString,"%010u",inputequestcardNum);
	_RequestcardNum=inputequestcardNum;
}
//获得无符号Int型的卡号
unsigned int GetCardNO(void)
{
	return _RequestcardNum ;
}
//使用字符串方式获得卡号
char * GetCardNOByString(void)
{
    return _CardNoString;
}
BOOL _IsCardExist=F;
//当前卡是否存在
BOOL IsCardExist(void)
{
	return _IsCardExist;
}
//设置是否存在
void SetCardExist(BOOL ice)
{
	_IsCardExist=ice;
}

BOOL _IsCardInReader=F;
//设置卡是否在天线上操作
BOOL IsCardInReader(void)
{
	return _IsCardInReader;
}
//设置卡是否在天线上操作
void SetCardInReader(BOOL ice)
{
	_IsCardInReader=ice;
}

///车轴数
char G_CarAxlesNum[10];
void  InitG_CarAxlesNum(void)
{
	memset(G_CarAxlesNum, 0x00, sizeof(G_CarAxlesNum));	
}
char *GetG_CarAxlesNum(void)
{
	return G_CarAxlesNum;
}
//找零
char G_ZhaoLing[10];
void  InitG_ZhaoLing(void)
{
	memset(G_ZhaoLing, 0x00, sizeof(G_ZhaoLing));	
}
char *GetG_ZhaoLing(void)
{
	return G_ZhaoLing;
}
///计重状态
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
