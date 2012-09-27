//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "LocalIncludeFile.h"
struct MSG_EXITBS MsgExitBS;
//初始化上班消息
void InitMsgExitBS(void)
{	
    memset((char*)&MsgExitBS,'0',sizeof(struct MSG_EXITBS));	
}
//取得商标消息体
struct MSG_EXITBS *GetMsgExitBS(void)
{	
    return(struct MSG_EXITBS  *)&MsgExitBS;
}
//设置收费类型
//#define  COLLECTORTYPE_CONLLECTOR '1'//收费员
//#define  COLLECTORTYPE_VINDICATOR  '2'// 维护员
void SetExitBSMsgcollectortype(char Inputcollectortype)
{	
    MsgExitBS.collectortype=Inputcollectortype;
}
//设置工作状态
void SetExitBSMsgWorkStatus(char InputWorkStatus)
{	
    MsgExitBS.WorkStatus=InputWorkStatus;
}
//设置卡箱
void SetExitBSMsgICBox(char* InputICBox)
{	
    strncpy(MsgExitBS.ICBox,InputICBox,sizeof(MsgExitBS.ICBox));	
}
void AddTotalTraffic()
{	
    AddField(MsgExitBS.TotalTraffic,sizeof(MsgExitBS.TotalTraffic));	
}
void SetExitBSMsgBeginSTicketNo(char* InputBeginSTicketNo)
{	
    strncpy(MsgExitBS.BeginSTicketNo,InputBeginSTicketNo,sizeof(MsgExitBS.BeginSTicketNo));	
}
void SetExitBSMsgMARK(char InputMARK)
{	
    MsgExitBS.MARK=InputMARK;
}


 char  _ShowLoginTime_extracted[80];
char * GetUpdatedLoginTime(BOOL bEmpty)
{
	struct tm *rtc_time;
	time_t t = time(NULL);  
	rtc_time = localtime(&t); 
	SetExitESMsgBS_Year(GetFormatTime(DATETIME_FORMAT_YYYY,t)); 
	SetExitESMsgBS_Day(GetFormatTime(DATETIME_FORMAT_MMDD,t));  
	SetExitESMsgBS_Time(GetFormatTime(DATETIME_FORMAT_HHMMSS,t));   
	SetExitESMsgBS_YMD(GetFormatTime(DATETIME_FORMAT_YYYYMMDD,t));  
	SetExitESMsgBS_YMDHM(GetFormatTime(DATETIME_FORMAT_YYYYMMDDHHMMSS,t));  
	if (FALSE == bEmpty)
	{
		sprintf(_ShowLoginTime_extracted, "%04d-%02d-%02d %02d:%02d:%02d",
				rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,
				rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec
			   );  
	}
	else
	{
		sprintf(_ShowLoginTime_extracted, "                   "); 
	}
	return _ShowLoginTime_extracted;
}

