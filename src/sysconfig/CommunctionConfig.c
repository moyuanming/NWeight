// ***************************************************************
//  CommunctionConfig   version:  1.0   ��  date: 12/10/2007
//  -------------------------------------------------------------
//  ͨѶ���ýӿ�
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

char ___SVRCARDLIST[512];
char *GetSVRCARDLIST(void)
{	
	return ___SVRCARDLIST;
}
char ___JOUCODE[512];
char *GetJOUCODE(void)
{	
	return ___JOUCODE;
}
char ___KEYFILE[512];
char *GetKEYFILE(void)
{	
	return ___KEYFILE;
}
void LoadCommunctionConfig(void)
{	
	echoic("����װ��ͨѶ����...");	
	LoadIniFile(CONFCOMMUNCTION_FILE);	

	strcpy(MagServerIP,readItemInIniFile("MagServerIP"));	
	MsgServerProt = atoi(readItemInIniFile("MsgServerProt"));	
	strcpy(FtpServerIP,readItemInIniFile("FtpServerIP"));	
	FtpServerProt = atoi(readItemInIniFile("FtpServerProt"));	
	strcpy(FtpUserName,readItemInIniFile("FtpUserName"));	
	strcpy(FtpPwd,readItemInIniFile("FtpPwd"));	
	strcpy(TimeServerIP,readItemInIniFile("TimeServerIP")); 
	SetTCOServerIP(readItemInIniFile("TCOServerIP"));
	TCOPort = atoi(readItemInIniFile("TCOServerPort"));
	/*IC���б���Ϣ������·��*/
	memset(___SVRCARDLIST,0x00,512);
	memset(___JOUCODE,0x00,512);
	strcpy(___SVRCARDLIST,readItemInIniFile("SVRCARDLIST"));    
	strcpy(___JOUCODE,readItemInIniFile("JOUCODE"));    
	strcpy(___KEYFILE,readItemInIniFile("KEYFILE"));  
	echoic("װ��ͨѶ�������"); 
	//*--*/18999188155
}

