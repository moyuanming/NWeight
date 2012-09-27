//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "LocalIncludeFile.h"

struct MSG_HEAD *MsgHead;
struct MSG_EXITHT *MsgExitHt;
struct MSG_NewTifficStat *MsgNewExitHT;
// 绿色通道放到 Credit 4
// 农用车 放到 7
void Sync_ExitHT(void)
{	
    memcpy((char*)&MsgExitHt->EXITES_HEAD,GetMessageHead(ID_MSGEXITHT),MSG_HEAD_LENGTH);	
    if (msync((void *)MsgExitHt,sizeof(struct MSG_EXITHT),MS_SYNC)<0)
    {	
        LogCAppLog("Msync Faile!");	
    }
	if (msync((void *)MsgNewExitHT,sizeof(struct MSG_NewTifficStat),MS_SYNC)<0)
	{	
		LogCAppLog("Msync Faile!");	
	}
}
void InitMsgExitHt(void)
{	
    memset((char *)MsgExitHt,'0',sizeof(struct MSG_EXITHT));	
	memset((char *)MsgNewExitHT,'0',sizeof(struct MSG_NewTifficStat));
	Sync_ExitHT();	
}
struct MSG_EXITHT *GetMsgExitHt(void)
{	
    return MsgExitHt;
}
struct MSG_NewTifficStat *GetMsgNewExitHT(void)
{
	return MsgNewExitHT;
}
void LoadMsgExitHT(void)
{	
	
    MsgExitHt=LoadMsgExitHtFromFile();	
	MsgNewExitHT =  LoadMsgNewCountFromFile(FILENAME_ASVE_NEWEXITHT);
    CheckHourSend_extracted();	
	

}
/*************************************************************************************
* 违章车总数
**************************************************************************************/
void AddMsgTotal_Violation(void)
{	
    AddField(MsgExitHt->Total_Violation,sizeof(MsgExitHt->Total_Violation));	
	Sync_ExitHT();	
}
/*************************************************************************************
* 紧急车数量
**************************************************************************************/
void AddMsgtotal_emergency(void)
{	
    AddField(MsgExitHt->total_emergency,sizeof(MsgExitHt->total_emergency));	
	AddField(MsgExitHt->Total_Traffic,sizeof(MsgExitHt->Total_Traffic));	
	Sync_ExitHT();	
}
  
/*************************************************************************************
* 车道开放时间
**************************************************************************************/
void SetExitHtMsgOpentime(char * InputOpentime)
{	
    strncpy(MsgExitHt->Opentime,InputOpentime,sizeof(MsgExitHt->Opentime));	
}
/*************************************************************************************
* 标志位
**************************************************************************************/
void SetExitHtMsgMARK(char InputMARK)
{	
    MsgExitHt->MARK=InputMARK;
}
/***************************************************************
* 雨棚灯 工作开放时间计数 小时发生变化就产生记录
****************************************************************/
int HourCount = 0;
void CheckHourSend_extracted(void)
{	
	if (0!=strncmp(MsgHour->HourTime,GetTime(DATETIME_FORMAT_YYYYMMDDHH),sizeof(MsgHour->HourTime)))
	{	


        SendMessageToQueue(ID_MSGEXITHT);
        InitMsgExitHt();
		fprintf(stderr,"InitMsgExitHt\n");
        InitMsgHour();	
		fprintf(stderr,"InitMsgHour\n");
		SetG_weiZhangType(4);	
        SendMsgInfo("小时交通量消息","","小时交通量统计");
        	
    }
}
void SendHT(char *MessageBody)
{	
	struct MSG_EXITHT *ExitHT;
	if(1==SynOn)
	{	
		Sync_ExitHT();	
	}
	ExitHT = GetMsgExitHt();	
	strncpy(ExitHT->EXITES_HEAD.Year,MsgHour->HourTime,4);	
	strncpy(ExitHT->EXITES_HEAD.Day,&MsgHour->HourTime[4],4);	
	strncpy(ExitHT->EXITES_HEAD.Hour,&MsgHour->HourTime[8],2);	
	strncpy(&ExitHT->EXITES_HEAD.Hour[2],"0000",4);	
	strncpy(ExitHT->EXITES_HEAD.YYYYMMDD,MsgHour->HourTime,8);	
	strncpy(ExitHT->EXITES_HEAD.YYYYMMDDHHMMSS,MsgHour->HourTime,10);	
	strncpy(&ExitHT->EXITES_HEAD.YYYYMMDDHHMMSS[10],"0000",4);	
	memcpy(MessageBody,(char *)ExitHT,LENGHT_MSG_EXITHT);	

}
void CheckHourSend(void)
{	
    if (Getg_bYuPeng())
	{	
        AddMsgHourtmGreene();	
    }
    CheckHourSend_extracted();	
}
//By GER.Cmd.buildgcc   CreateDate:2011/8/11 15:56:10
void SetExitHtMsgWeightCount(int InputWeightCount)
{
	AddFieldAtValue(MsgExitHt->WeightCount,10,InputWeightCount);
}
void SetExitHtMsgWeightFareTotal(int InputWeightFareTotal)
{
	AddFieldAtValue(MsgExitHt->WeightFareTotal,10,InputWeightFareTotal);
}
void SetExitHtMsgUnOverloadWeightCount(int InputUnOverloadWeightCount)
{
	AddFieldAtValue(MsgExitHt->UnOverloadWeightCount,10,InputUnOverloadWeightCount);
}
void SetExitHtMsgUnOverloadWeightFareTotal(int InputUnOverloadWeightFareTotal)
{
	AddFieldAtValue(MsgExitHt->UnOverloadWeightFareTotal,10,InputUnOverloadWeightFareTotal);
}
void SetExitHtMsgOverloadWeight30Count(int InputOverloadWeight30Count)
{
	AddFieldAtValue(MsgExitHt->OverloadWeight30Count,10,InputOverloadWeight30Count);
}
void SetExitHtMsgOverloadWeight30FareTotal(int InputOverloadWeight30FareTotal)
{
	AddFieldAtValue(MsgExitHt->OverloadWeight30FareTotal,10,InputOverloadWeight30FareTotal);
}
void SetExitHtMsgOverloadWeight30_100Count(int InputOverloadWeight30_100Count)
{
	AddFieldAtValue(MsgExitHt->OverloadWeight30_100Count,10,InputOverloadWeight30_100Count);
}
void SetExitHtMsgOverloadWeight30_100FareTotal(int InputOverloadWeight30_100FareTotal)
{
	AddFieldAtValue(MsgExitHt->OverloadWeight30_100FareTotal,10,InputOverloadWeight30_100FareTotal);
}
void SetExitHtMsgOverloadWeight100Count(int InputOverloadWeight100Count)
{
	AddFieldAtValue(MsgExitHt->OverloadWeight100Count,10,InputOverloadWeight100Count);
}
void SetExitHtMsgOverloadWeight100FareTotal(int InputOverloadWeight100FareTotal)
{
	AddFieldAtValue(MsgExitHt->OverloadWeight100FareTotal,10,InputOverloadWeight100FareTotal);
}
