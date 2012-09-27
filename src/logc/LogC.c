// ***************************************************************
//  LogC   version:  1.0   ·  date: 12/09/2007
//  -------------------------------------------------------------
//  日志信息接口！
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"
#include "../global/include/linux_include.h"
static sem_t LogcSync;
static char LogHexbuf[2000];

struct LogConfing LogCon;
void postLogcSync()
{	
	LoadIniFile(LANECONFIGFILENAME_FILE);	
	/*fprintf(stderr,"readItemInIniFile= %s",readItemInIniFile("NetNo"));*/
	LogCon.EnableDebug = atoi(readItemInIniFile("EnableDebug"));	
	LogCon.EnableError = atoi(readItemInIniFile("EnableError"));	
	LogCon.EnableInfor = atoi(readItemInIniFile("EnableInfor"));	
	LogCon.EnableWarni = atoi(readItemInIniFile("EnableWarni"));	
	LogCon.IsPrint = atoi(readItemInIniFile("IsPrint"));	

	sem_post((sem_t *)&LogcSync);	
}

void LogC(char *ModName,char *LogType,char *File,int LineNumber,char *Format,...)
{	
      int LogEnable = 0;
		if(!strcmp(LogType,LOG_DEBUG) && LogCon.EnableDebug)
		{	
			LogEnable = 1;
		}
		else if(!strcmp(LogType,LOG_ERROR) && LogCon.EnableError)
		{	
			LogEnable = 1;
		}
		else if(!strcmp(LogType,LOG_INFOR) && LogCon.EnableInfor)
		{	
			LogEnable = 1;
		}
		else if(!strcmp(LogType,LOG_WARNI) && LogCon.EnableWarni )
		{	
			LogEnable = 1;
		}
		sem_wait((sem_t *)&LogcSync);	
        if(LogEnable)
        {	
            char buffer[20000];
            char LogFileName[200];
			char FileInfor[200];
            FILE *fp;
            va_list args;
		    memset(FileInfor,0x00,200);	
			if(0!=strncmp(LogType,LOG_INFOR,5))
			{	
				sprintf(FileInfor,"[%s:%d]:",File,LineNumber);	
			}
			memset(buffer,0x00,20000);	
            va_start(args,Format);	
            vsprintf(buffer,Format,args);	
            va_end(args);	
			memset(LogFileName,0x00 ,200);	
            sprintf(LogFileName,"%s%s%s.Log",FILENAME_LOG_FILE_PATH,ModName,GetTime(DATETIME_FORMAT_YYYY_MM_DD));	
            if((fp=fopen(LogFileName,"at+"))==NULL)
            {	
				fp=fopen(LogFileName,"wt+");	
            }
			fputs(GetTime(DATETIME_FORMAT_HHMMSS),fp);	
			fputs(" ",fp);	
			fputs(LogType,fp);	
			fputs(":",fp);	
			fputs(FileInfor,fp);	
            fputs(buffer,fp);	
            fputs("\n",fp);	
            fclose(fp);	

        }
		sem_post((sem_t *)&LogcSync);	
}


char *StrToHexStr(char * Strbuffer,int strlen)
{	
	int i;
	memset(LogHexbuf,0x00,2000);	
	for(i=0;i<strlen;i++)
	{	
		sprintf(LogHexbuf+i*3,"%02X",Strbuffer[i]);	
		LogHexbuf[i*3+2]=' ';
	}
	//sprintf(Hexbuffer,"%02X",'a');	
	//sprintf(&Hexbuffer[2],"%02X",'b');	
	return LogHexbuf;
}

