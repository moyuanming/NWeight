// ***************************************************************
//  AppFunctionConfig   version:  1.0   ·  date: 12/09/2007
//  -------------------------------------------------------------
//  程序功能开关接口！
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"
int FunCPSB = 1;
int EnabledCPSB()
{	
	return FunCPSB;
}
/******************************************************************************************************
*计重设备是否启用
******************************************************************************************************/
int FunWeight = 1;
int EnabledWeight()
{	
	return FunWeight;
}
/******************************************************************************************************
*打印机是否启用
******************************************************************************************************/
int FunPrinter = 1;
int EnabledPrinter()
{	
	return	FunPrinter;
}
/******************************************************************************************************
*费显是否启用
******************************************************************************************************/
int FunTFI = 1;
int EnabledTFI()
{	
	return FunTFI;
}
/******************************************************************************************************
*字符叠加是否启用
******************************************************************************************************/
int FunVDM = 1;
int EnabledVDM()
{	
	return FunVDM;
}
int FunCICM;
/**
 * 是否为便携收费机方式
 * 
 * @return 
 */
int EnabledCICM(void)
{
	return FunCICM;
}

int FunIOBoard;
/**
 * 是否启用IO版控制功能
 * 
 * @return 
 */
int EnabledIOBoard(void)
{
	return FunIOBoard;
}
int FunIC;
/**
 * 是否启用IC卡功能
 * 
 * @return 
 */
BOOL GetEnableIC(void)
{
	return FunIC;
}
int FunCallTCS;
/**
 * 是否启用 呼叫监控的功能。 
 * 
 * @return 
 */
BOOL EnabledCallTCS(void)
{
	return  FunCallTCS;
}
int FunVideo = 0;
BOOL EnabledVideo(void)
{
	return  FunVideo;
}
char TFIDLL[20];
char *GetTFIDLL()
{
	return TFIDLL;
}
char PrintDLL[20];
char *GetPrintDLL()
{
	return PrintDLL;
}
int _Display = 800;
int GetDisPlay_Resolution()
{
	return _Display;
}
char var_ICReader[100];
 
char * GetICReader(void)
{   
	return var_ICReader;
}
char var_VDMDLL[100];

char * GetVDMDLL(void)
{   
	return var_VDMDLL;
}
char var_IOBoardDLL[100];

char * GetIOBoardDLL(void)
{   
	return var_IOBoardDLL;
}
char var_VPRDLL[100];

char * GetVPRDLL(void)
{   
	return var_VPRDLL;
}
/******************************************************************************************************
*装载程序功能配置
******************************************************************************************************/
void LoadAppFunction(void)
{	
	echoic("正在装载程序功能配置...");  
	LoadIniFile(APPFUNCTIONFILENAMEFILE);   
	FunCICM = atoi(readItemInIniFile("FunCICM"));   
	FunIOBoard = atoi(readItemInIniFile("FunIOBoard")); 
	FunWeight = atoi(readItemInIniFile("FunWeight"));   
	FunPrinter= atoi(readItemInIniFile("FunPrinter"));  
	FunTFI = atoi(readItemInIniFile("FunTFI")); 
	FunVDM = atoi(readItemInIniFile("FunVDM")); 
	FunIC = atoi(readItemInIniFile("FunIC"));   
	FunCallTCS = atoi(readItemInIniFile("FunCallTCS")); 
	FunVideo = atoi(readItemInIniFile("FunVideo")); 
	FunCPSB = atoi(readItemInIniFile("FunVPR"));    
	memset(TFIDLL,0x00,20);
	strcpy(TFIDLL,readItemInIniFile("TFIDLL"));
	memset(PrintDLL,0x00,20);
	strcpy(PrintDLL,readItemInIniFile("PrintDLL"));
	memset(var_ICReader,0x00,100);
	strcpy(var_ICReader,readItemInIniFile("ICReaderDLL"));
	memset(var_VDMDLL,0x00,100);
	strcpy(var_VDMDLL,readItemInIniFile("VDMDLL"));
	memset(var_IOBoardDLL,0x00,100);
	strcpy(var_IOBoardDLL,readItemInIniFile("IOBoardDLL"));
	memset(var_VPRDLL,0x00,100);
	strcpy(var_VPRDLL,readItemInIniFile("VPRDLL"));

}

