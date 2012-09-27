
// ***************************************************************
//  LanConfig   version:  1.0   ��  date: 12/09/2007
//  -------------------------------------------------------------
//  �������ýӿڣ�
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
*·����
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
* ����վ���
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
* վ
* 1��վ����
* 2��վ����
* 3��վ����
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
*����
*1��������
*2����������
*3���Ƿ��ǳ���վ
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

//1Ϊ���� 0Ϊ���
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
* �汾��
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
// �û����볤��
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
// �û����ų���
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
//�շ�վ����
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
* ���ͳ���
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
* ����ץ����Ƭ��׺��
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
//��Ʊ��ˢ���������1 ֱ��תΪ��������0 ����ת���ȴ�ȡ��
void SetICYPKERRGO(int inputICYPKERRGO)
{   
	_ICYPKERRGO=inputICYPKERRGO;
}
//��Ʊ��ˢ���������1 ֱ��תΪ��������0 ����ת���ȴ�ȡ��
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
//�����ε�¼
int GetHowToLogin(void)
{
	return _howtologin;
}
//������ε�¼ 0  �ֶ��Ϳ�   1  ���ֶ�  2 ����
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
* ��Ini�ļ��м��س���������Ϣ
******************************************************************************************************/
void LoadLanConfig(void)
{   
	echoic("����װ�س�������...");
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
	echoic("װ�س����������");
 
}


