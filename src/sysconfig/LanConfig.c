
// ***************************************************************
//  LanConfig   version:  1.0   ·  date: 12/09/2007
//  -------------------------------------------------------------
//  车道配置接口！
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"

struct LaneConfig CurrentLanConfig;
struct LaneConfig *GetCurrentLanConfig()
{
	return &CurrentLanConfig;
}
/******************************************************************************************************
*路网号
******************************************************************************************************/
char *GetLanConfigNetNo()
{   
	return GetMsgHead()->NetNo;
}
void SetLanConfigNetNo(char *InputNetNo)
{   
	strncpy(GetMsgHead()->NetNo,InputNetNo,sizeof(GetMsgHead()->NetNo));    
	strncpy(CurrentLanConfig.NetNo,InputNetNo,sizeof(CurrentLanConfig.NetNo));  

}
/******************************************************
* 完整站编号
*********************************************************/
char LanConfigStationNo[5];
char *GetLanConfigStationNo(void)
{   
	memset(LanConfigStationNo,0x00,5);  
	strncpy(LanConfigStationNo,GetLanConfigNetNo(),2);  
	strncpy(&LanConfigStationNo[2],GetLanConfigPlazaNo(),2);    
	return LanConfigStationNo;
}
/******************************************************************************************************
* 站
* 1：站代码
* 2：站类型
* 3：站描述
******************************************************************************************************/
char *GetLanConfigPlazaNo()
{   
	return GetMsgHead()->PlazaNo;
}
void SetLanConfigPlazaNo(char * InputPlazaNo)
{   
	strncpy(GetMsgHead()->PlazaNo,InputPlazaNo,sizeof(GetMsgHead()->PlazaNo));  
	strncpy(CurrentLanConfig.PlazaNo ,InputPlazaNo,sizeof(CurrentLanConfig.PlazaNo ));  

}
char PlazaType[10];
char *GetLanConfigPlazaType()
{   
	return PlazaType;
}
void SetLanConfigPlazaType(char * InputPlazaType)
{   
	strcpy(PlazaType,InputPlazaType);   
}
char PlazaDesc[50];
char * GetLanConfigPlazaDesc()
{   
	return PlazaDesc ;
}
void SetLanConfigPlazaDesc(char *InputPlazaDesc)
{   
	memset(PlazaDesc,0x00,sizeof(PlazaDesc));
	strcpy(PlazaDesc,InputPlazaDesc);   
}
/******************************************************************************************************
*车道
*1：车道号
*2：车道类型
*3：是否是出口站
******************************************************************************************************/
char * GetLanConfigLaneNo(void)
{   
	return SUBSTRING(CurrentLanConfig.LaneNo);
}
void SetLanConfigLaneNo(char *InputLaneNo)
{   
	strncpy(GetMsgHead()->LaneNo  ,InputLaneNo,sizeof(GetMsgHead()->LaneNo ));  
	strncpy(CurrentLanConfig.LaneNo,InputLaneNo,sizeof(CurrentLanConfig.LaneNo));   
}
char GetLanConfigLaneType()
{   
	return GetMsgHead()->LaneType;
}
void SetLanConfigLaneType(char *InputLaneType)
{   
	GetMsgHead()->LaneType = InputLaneType[0];
	CurrentLanConfig.LaneType =  InputLaneType[0];

}
void SetLanConfigLaneMod(char * InputLaneMode)
{   
	GetMsgHead()->LaneMode=InputLaneMode[0];
}
char GetLanConfigLaneMod()
{   
	return GetMsgHead()->LaneMode;
}

//1为出口 0为入口
int LanLanConfigTypeIsExitType()
{   
	int ret=0 ;
	if (GetLanConfigLaneType()==LANETYPE_ENTRY)
	{
		ret =0;
	}
	else
	{
		ret=1;
	}
	return ret;
}

/******************************************************************************************************
* 版本号
******************************************************************************************************/
char VersionNo[50];
char * GetLanConfigVersionNo(void)
{   
	return VersionNo;
}
void SetLanConfigVisionNo(char * version)
{   
	strcpy(VersionNo,version);  
}
/******************************/
// 用户密码长度
/******************************/
int userPasswordLength=0;
void Setg_userPasswordLen(int value)
{   
	userPasswordLength=value;
}
int Getg_userPasswordLen(void)
{   
	return userPasswordLength;
}
/******************************/
// 用户工号长度
/******************************/
int userNumberLength=0;
void Setg_userNumberLen(int value)
{   
	userNumberLength=value;
}
int Getg_userNumberLen(void)
{   
	return userNumberLength;
}
///**************************************************************
//收费站名称
//***************************************************************/
char stationName[20];
void Setg_stationName(char * value)
{   
	strncpy(stationName,value,sizeof(value));   
}
char * Getg_stationName(void)
{   
	return stationName;
}
/******************************************************************************************************
* 车型长度
******************************************************************************************************/
int carTypeLen=0;
void Setg_carTypeLen(int value)
{   
	carTypeLen=value;
}
int Getg_carTypeLen(void)
{   
	return carTypeLen;
}
/******************************************************************************************************
* 车道抓拍如片后缀名
******************************************************************************************************/
char LanConfigPicType[7];
char *GetLanConfigPicType()
{   
	LanConfigPicType[0] = '.';
	LanConfigPicType[1] = GetLanConfigLaneType();   
	memcpy(&LanConfigPicType[2],GetLanConfigNetNo(),2); 
	memcpy(&LanConfigPicType[4],GetLanConfigPlazaNo(),2);   
	LanConfigPicType[6] = 0x00;
	return LanConfigPicType;
}
int UseAutoMan=0;
void SetUseAutoMan(int inputautoman)
{   
	UseAutoMan=inputautoman;
}
int GetUseAutoMan(void)
{   
	return UseAutoMan;
}
int _ICYPKERRGO=0;
//月票卡刷卡后的走向，1 直接转为正常车，0 不跳转，等待取消
void SetICYPKERRGO(int inputICYPKERRGO)
{   
	_ICYPKERRGO=inputICYPKERRGO;
}
//月票卡刷卡后的走向，1 直接转为正常车，0 不跳转，等待取消
int GetICYPKERRGO(void)
{   
	return _ICYPKERRGO;
}


 

char var_BillTitle[100];
void SetBillTitle(char * InputBillTitle)
{   
	memset(var_BillTitle,0x00,sizeof(var_BillTitle));
	strncpy(var_BillTitle,InputBillTitle,strlen(InputBillTitle));
	//echoic("InputBillTitle%s  BillTitle %s",InputBillTitle,var_BillTitle);
}
char * GetBillTitle(void)
{   
	return var_BillTitle;
}



char var_KeyMap[100];
void SetKeyMap(char * InputKeyMap)
{   
	memset(var_KeyMap,0x00,sizeof(var_KeyMap));
	strncpy(var_KeyMap,InputKeyMap,strlen(InputKeyMap));
	//echoic("InputBillTitle%s  BillTitle %s",InputBillTitle,var_BillTitle);
}
char * GetKeyMap(void)
{   
	return var_KeyMap;
}
int _howtologin=0;
//获得如何登录
int GetHowToLogin(void)
{
	return _howtologin;
}
//设置如何登录 0  手动和卡   1  仅手动  2 仅卡
void SetHowToLogin(int inputhowtologin)
{
	_howtologin=inputhowtologin;
}
int DataSaveDays = 10;
int GetDataSaveDays()
{
	return DataSaveDays;
}
//Old 312 Config
int XIAOYU_10T = 5;
int Get_XIAOYU_10T()
{
	return XIAOYU_10T;
}
float DAYU_10T = 3;
float Get_DAYU_10T()
{
	return DAYU_10T;
}
/******************************************************************************************************
* 从Ini文件中加载车道配置信息
******************************************************************************************************/
void LoadLanConfig(void)
{   
	echoic("正在装载车道配置...");
	InitMsgHead();  
	LoadIniFile(LANECONFIGFILENAME_FILE);   
	SetLanConfigNetNo(readItemInIniFile("NetNo"));  
	SetLanConfigPlazaNo(readItemInIniFile("PlazaNo"));  
	SetLanConfigPlazaDesc(readItemInIniFile("PlazaDesc"));  
	Setg_userNumberLen(atoi(readItemInIniFile("UserNumLen")));  
	Setg_userPasswordLen(atoi(readItemInIniFile("UserPwdLen")));    
	Setg_carTypeLen(atoi(readItemInIniFile("CarTypeLen"))); 
	SetLanConfigPlazaType(readItemInIniFile("PlazaType"));  
	SetLanConfigLaneNo(readItemInIniFile("LaneNo"));    
	SetLanConfigLaneType(readItemInIniFile("LaneType"));    
	SetLanConfigLaneMod(readItemInIniFile("LaneMode")); 
	SetLanConfigVisionNo("1.0.0.2.080328"); 
	SetUseAutoMan(atoi(readItemInIniFile("AutoMan")));  
	SetBillTitle(readItemInIniFile("BillTitle"));   
	SetICYPKERRGO(atoi(readItemInIniFile("ICYPKERRGO")));
	SetKeyMap(readItemInIniFile("KeyMap"));
	SetHowToLogin(atoi(readItemInIniFile("HowToLogin")));
	DataSaveDays = atoi(readItemInIniFile("SendClearDays")); 
	XIAOYU_10T=atoi(readItemInIniFile("XIAOYU_10T")); 
	DAYU_10T=atof(readItemInIniFile("DAYU_10T")); 
	echoic("装载车道配置完成");
 
}


