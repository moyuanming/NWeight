// ***************************************************************
//  MemSyncFile   version:  1.0   ·  date: 12/27/2007
//  -------------------------------------------------------------
//  内存 映射文件操作
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"

/******************************************************************************************************
* 小时交通量 车型支付方式
******************************************************************************************************/
struct MSG_HOUR *GetSyncMsgHour(void)
{
    struct MSG_HOUR *SyncmFile;
    int FilePointer;
    if(!FileExists(FILENAME_SAVE_TrafficHour))
    {
        CreateMsgFile(FILENAME_SAVE_TrafficHour,sizeof(struct MSG_HOUR));
    }
    FilePointer = open(FILENAME_SAVE_TrafficHour,O_RDWR);
    SyncmFile = (struct MSG_HOUR *)mmap(0,sizeof(struct MSG_HOUR),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);
    return SyncmFile;
}

/******************************************************************************************************
* 参数表版本信息
******************************************************************************************************/
struct ParameterVersion *GetSyncParameterVersion(void)
{
    struct ParameterVersion *SyncmFile;
    int FilePointer;
    if(!FileExists(FILENAME_SAVE_ParameterVersion))
    {
        CreateMsgFile(FILENAME_SAVE_ParameterVersion,sizeof(struct ParameterVersion));
    }
    FilePointer = open(FILENAME_SAVE_ParameterVersion,O_RDWR);
    SyncmFile = (struct ParameterVersion *)mmap(0,sizeof(struct ParameterVersion),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);
    return SyncmFile;
}
/******************************************************************************************************
* 统一装载 内存映射文件
******************************************************************************************************/
struct MSG_EXITES *LoadMsgExitESFromFile(void)
{
	struct MSG_EXITES *SyncmFile;
	int FilePointer;
	if(!FileExists(FILENAME_ASVE_EXITES))
	{
		CreateMsgFile(FILENAME_ASVE_EXITES,sizeof(struct MSG_EXITES));
	}
	FilePointer = open(FILENAME_ASVE_EXITES,O_RDWR);
	SyncmFile = (struct MSG_EXITES*)mmap(0,sizeof(struct MSG_EXITES),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);
	return SyncmFile;
}
struct MSG_NewTifficStat *LoadMsgNewCountFromFile(char *FileName)
{
	struct MSG_NewTifficStat *SyncmFile;
	int FilePointer;
	if(!FileExists(FileName))
	{
		CreateMsgFile(FileName,sizeof(struct MSG_NewTifficStat));
	}
	FilePointer = open(FileName,O_RDWR);
	SyncmFile = (struct MSG_NewTifficStat*)mmap(0,sizeof(struct MSG_NewTifficStat),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);
	return SyncmFile;
}



struct MSG_EXITHT *LoadMsgExitHtFromFile(void)
{
	struct MSG_EXITHT *SyncmFile;
	int FilePointer;
	if(!FileExists(FILENAME_ASVE_EXITHT))
	{
		CreateMsgFile(FILENAME_ASVE_EXITHT,sizeof(struct MSG_EXITHT));
	}
	FilePointer = open(FILENAME_ASVE_EXITHT,O_RDWR);
	SyncmFile = (struct MSG_EXITHT*)mmap(0,sizeof(struct MSG_EXITHT),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);
	return SyncmFile;
}

void LoadMemSyncFile(void)
{
    LoadMsgHour();
    LoadMsgExitES();
	LoadMsgExitHT();
	echoic("Load LoadMsgExitHT");
    LoadCurrentUseParameterVersionNumber();
	echoic("Load LoadCurrentUseParameterVersionNumber");
    LoadImageHeader();
}
