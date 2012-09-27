// ***************************************************************
//  FileContext   version:  1.0   ·  date: 5/5/2008
//  -------------------------------------------------------------
//  文件信息上下文
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************

#include "LocalIncludeFile.h"
/*******************************************************************************/
////当前提示消息
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
////提示信息的临时存放 用于违章处理结束后返回时用
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
//优惠车型
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
//当前音量
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
//最大音量
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
//最小音量
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
*加载参数文件是否成功    1成功   0失败；初始状态是成功
*AUTHOR ：lzp
* DATE :12/7/2008
******************************************************************************************/
int  LoadYPKListRecordFlag=1;  //月票卡
void SetLoadYPKListRecordFlag(int  value)
{	
	LoadYPKListRecordFlag=value;
}

int  GetLoadYPKListRecordFlag(void)
{	
	return LoadYPKListRecordFlag;
}

//加载优惠卡表标志
int  LoadYHKListRecordFlag=1;
void SetLoadYHKListRecordFlag(int  value)
{	
	LoadYHKListRecordFlag=value;
}

int  GetLoadYHKListRecordFlag(void)
{	
	return LoadYHKListRecordFlag;
}

//加载优惠率描述表标志
int  LoadYHRateDescriptionRecordFlag=1;
void SetLoadYHRateDescriptionRecordFlag(int  value)
{	
	LoadYHRateDescriptionRecordFlag=value;
}

int  GetLoadYHRateDescriptionRecordFlag(void)
{	
	return LoadYHRateDescriptionRecordFlag;
}

//加载职员表标志
int  LoadCollectRecordFlag=1;
void SetLoadCollectRecordFlag(int  value)
{	
	LoadYPKListRecordFlag=value;
}

int  GetLoadCollectRecordFlag(void)
{	
	return LoadCollectRecordFlag;
}

//加载费率标志
int  LoadFareRecordFlag=1;
void SetLoadFareRecordFlag(int  value)
{	
	LoadFareRecordFlag=value;
}

int  GetFareRecordFlag(void)
{	
	return LoadFareRecordFlag;
}

//加载车种表标识
int  LoadCarKindRecordFlag=1;
void SetLoadCarKindRecordFlag(int  value)
{	
	LoadCarKindRecordFlag=value;
}

int  GetLoadCarKindRecordFlag(void)
{	
	return LoadCarKindRecordFlag;
}


