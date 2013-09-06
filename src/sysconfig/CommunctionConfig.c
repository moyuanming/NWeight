// ***************************************************************
//  CommunctionConfig   version:  1.0   ·  date: 12/10/2007
//  -------------------------------------------------------------
//  通讯配置接口
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "LocalIncludeFile.h"
char MagServerIP[25];
char *GetMagServerIP(void)
{	
	
	return MagServerIP;
}
int MsgServerProt = 0;
int GetMsgServerProt(void)
{	 
	return MsgServerProt;
}
char FtpServerIP[25];
char *GetFtpServerIP(void)
{	 
	return FtpServerIP;
}
char ParamFtpServerIP[25];
char *GetParamFtpServerIP(void)
{	 
	return ParamFtpServerIP;
}
int FtpServerProt = 0;
int GetFtpServerProt(void)
{	 
	return FtpServerProt;
}
char FtpUserName[20];
char *GetFtpUserName(void)
{	
	return FtpUserName;
}
char FtpPwd[20];
char *GetFtpPwd(void)
{   
	return FtpPwd;
}
char TimeServerIP[25];
char *GetTimeServerIP(void)
{	
	return TimeServerIP;
}
char NtpDateCommand[55];
char *GetNtpDateCommand(void)
{	
	memset(NtpDateCommand,0x00,55);	
	sprintf(NtpDateCommand,"ntpdate %s ;hwclock -w ",GetTimeServerIP());	
	return NtpDateCommand;
}
char TCOServerIP[25];
void SetTCOServerIP(char *IP)
{
	memset(TCOServerIP,0x00,25);
	strncpy(TCOServerIP,IP,25);
}

char *GetTCOServerIP(void)
{
	return TCOServerIP;
}
int TCOPort = 0;
int GetTCOPort(void)
{
	return TCOPort;
}

char _VPRIP[25];
char *GetVPRIP(void)
{
	return _VPRIP;
}
void SetVPRIP(char *IP)
{
	memset(_VPRIP,0x00,25);
	strncpy(_VPRIP,IP,25);
}
int _VPRPort = 0;
int GetVPRPort(void)
{
	return _VPRPort;
}
 
 
void LoadCommunctionConfig(void)
{	
	echoic("正在装载通讯配置...");	
	LoadIniFile(CONFCOMMUNCTION_FILE);	

	strcpy(MagServerIP,readItemInIniFile("MagServerIP"));	
	MsgServerProt = atoi(readItemInIniFile("MsgServerProt"));	
	strcpy(FtpServerIP,readItemInIniFile("FtpServerIP"));	
	strcpy(ParamFtpServerIP,readItemInIniFile("ParamFtpServerIP"));
	FtpServerProt = atoi(readItemInIniFile("FtpServerProt"));	
	strcpy(FtpUserName,readItemInIniFile("FtpUserName"));	
	strcpy(FtpPwd,readItemInIniFile("FtpPwd"));	
	strcpy(TimeServerIP,readItemInIniFile("TimeServerIP")); 
	SetTCOServerIP(readItemInIniFile("TCOServerIP"));
	TCOPort = atoi(readItemInIniFile("TCOServerPort"));
  	SetVPRIP(readItemInIniFile("VPRIP"));
	_VPRPort = atoi(readItemInIniFile("VPRPort"));
	echoic("装载通讯配置完成"); 
}

