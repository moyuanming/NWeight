//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "LocalIncludeFile.h"

struct  MSG_YHKLIST  YHKListRecordTable[MAXPAEAMRECORDS];

struct PARAM_HEAD	YHKListHead ;
#define YHKListSTRLENGTH  37
int  ParseRecordYHKList(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&YHKListRecordTable[Rowindex],RecordStr,sizeof(struct MSG_YHKLIST));	
	return 0;
}


int LoadYHKListRecord(int IsFirst)
{	
	int ret = LoadRecord(PARAYHKLIST_FILE,&YHKListHead,YHKListSTRLENGTH,ParseRecordYHKList,FRAE,IsFirst);	
	strncpy(GetMsgRevision()->YHKListVer,YHKListHead.VerNo,2);	
	return ret;
}


/*********************************************************************************************************************
检测 优惠卡  ，如果优惠卡参数表中存在 这样的 卡号   函数返回1，否则返回0
*********************************************************************************************************************/
int CheckYHKCardNumber(char *Inputcardnumber)
{	
	int i ;
	int  rowscount;
	rowscount=atoi(YHKListHead.Recordcount);	
	for(i=0;i<rowscount;i++)
	{	
			if(0==strncmp(YHKListRecordTable[i].CardNumber,Inputcardnumber,8)&&0==strncmp("0",YHKListRecordTable[i].Status,1))
			{	
				return 1;
			}
	}
	return 0;
}

char YHcode[4];
char  *GetYHCode(char *Inputcardnumber)
{	
	int i ;
	int  rowscount;
	memset(YHcode,0x00,sizeof(YHcode));	
	rowscount=atoi(YHKListHead.Recordcount);	
	for(i=0;i<rowscount;i++)
	{	
			if(0==strncmp(YHKListRecordTable[i].CardNumber,Inputcardnumber,8)&&0==strncmp("0",YHKListRecordTable[i].Status,1))
			{	
				strncpy(YHcode,YHKListRecordTable[i].YHCode,sizeof(YHKListRecordTable[i].YHCode));	
				return YHcode;
			}
	}
	return YHcode;
}
/************************************************************************************************************
*判断优惠卡的有效期，如果返回值小于0，那么卡过期，不可再使用
*创建日期：2008-07-10
*创建人：王海伟
************************************************************************************************************/
int ValidateYHCarStartDate(char *Inputcardnumber,time_t Currenttime)
{	
	int i ;
	int  rowscount;
	rowscount=atoi(YHKListHead.Recordcount);	
	for(i=0;i<rowscount;i++)
	{	
			if(0==strncmp(YHKListRecordTable[i].CardNumber,Inputcardnumber,8)&&0==strncmp("0",YHKListRecordTable[i].Status,1)
			   &&strcmp(GetFormatTime(DATETIME_FORMAT_YYYYMMDD,Currenttime),YHKListRecordTable[i].BeginDate)<0)
			{	
				return 1;
			}
	}
	return 0;
}
/************************************************************************************************************
*判断优惠卡的有效期，如果返回值小于0，那么卡过期，不可再使用
*创建日期：2008-07-10
*创建人：王海伟
************************************************************************************************************/
int ValidateYHCarEndDate(char *Inputcardnumber,time_t Currenttime)
{	
	int i ;
	int  rowscount;
	rowscount=atoi(YHKListHead.Recordcount);	
	for(i=0;i<rowscount;i++)
	{	
			if(0==strncmp(YHKListRecordTable[i].CardNumber,Inputcardnumber,8)&&0==strncmp("0",YHKListRecordTable[i].Status,1)
			   &&strcmp(GetFormatTime(DATETIME_FORMAT_YYYYMMDD,Currenttime),YHKListRecordTable[i].EndDate)>0)
			{	
				return 1;
			}
	}
	return 0;
}
char tempEndDate[9];
char * GetYHCarEndDate(char *Inputcardnumber)
{	
	int i ;
	int  rowscount;
	memset(tempEndDate,0x00,sizeof(tempEndDate));	
	rowscount=atoi(YHKListHead.Recordcount);	
	for(i=0;i<rowscount;i++)
	{	
			if(0==strncmp(YHKListRecordTable[i].CardNumber,Inputcardnumber,8)&&0==strncmp("0",YHKListRecordTable[i].Status,1))
			{	
				strncpy(tempEndDate,YHKListRecordTable[i].EndDate,sizeof(YHKListRecordTable[i].EndDate));	
				return tempEndDate;
			}
	}
	return tempEndDate;
}
char tempStartTime[9];
char * GetYHCarStartDate(char *Inputcardnumber)
{	
	int i ;
	int  rowscount;
	memset(tempStartTime,0x00,sizeof(tempStartTime));	
	rowscount=atoi(YHKListHead.Recordcount);	
	for(i=0;i<rowscount;i++)
	{	
			if(0==strncmp(YHKListRecordTable[i].CardNumber,Inputcardnumber,8)&&0==strncmp("0",YHKListRecordTable[i].Status,1))
			{	
				strncpy(tempStartTime,YHKListRecordTable[i].BeginDate,sizeof(YHKListRecordTable[i].BeginDate));	
				return tempStartTime;
			}
	}
	return tempStartTime;
}
int  ValidateCardEnable(char *InputTime)
{	
	return  DiffCurrentDataTime(InputTime);	
}


