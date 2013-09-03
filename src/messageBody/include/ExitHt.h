//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _ExitHt_H_
#define _ExitHt_H_
//Ð¡Ê±¼ÇÂ¼
struct MSG_EXITHT
{
	struct MSG_HEAD  EXITES_HEAD;
	char Total_Traffic[10];
	char Total_Violation[10];
	char total_emergency[10];
	char total_official[10];
	struct  CARKINDUNTYPE CarInfoContext[12]; //1152 
	char Opentime[10];
	char MARK;
	char WeightCount[10];
	char WeightFareTotal[10];
	char UnOverloadWeightCount[10];
	char UnOverloadWeightFareTotal[10];
	char OverloadWeight30Count[10];
	char OverloadWeight30FareTotal[10];
	char OverloadWeight30_100Count[10];
	char OverloadWeight30_100FareTotal[10];
	char OverloadWeight100Count[10];
	char OverloadWeight100FareTotal[10];
};//endstructExitHt
#define  LENGHT_MSG_EXITHT 1376 //1152+111+70+40
#define  LENGHT_MSG_EXITHTHEAD 72+40
#define  LENGHT_MSG_EXITHTEND 111+1
#define  LENGHT_MSG_NEWEXITHT (MSG_NewTifficStatLenght+LENGHT_MSG_EXITHTHEAD+LENGHT_MSG_EXITHTEND)
void InitMsgExitHt(void);
struct MSG_EXITHT *GetMsgExitHt(void);
struct MSG_NewTifficStat *GetMsgNewExitHT(void);
void SetExitHtMsgTotal_Traffic(void);
void AddMsgTotal_Violation(void);
void AddMsgtotal_emergency(void);
void AddMsgtotal_official(void);
void SetExitHtMsgtotal_emergency(void);
void AddMsgtotal_official(void);
 
void SetExitHtMsgOpentime(char * InputOpentime);
void SetExitHtMsgMARK(char InputMARK);
void LoadMsgExitHT(void);
void CheckHourSend(void);
void CheckHourSend_extracted(void);
void SendHT(char *MessageBody);
void Sync_ExitHT(void);
//By GER.Cmd.buildgcc   CreateDate:2011/8/11 15:56:10
void SetExitHtMsgWeightCount(int InputWeightCount);
void SetExitHtMsgWeightFareTotal(int InputWeightFareTotal);
void SetExitHtMsgUnOverloadWeightCount(int InputUnOverloadWeightCount);
void SetExitHtMsgUnOverloadWeightFareTotal(int InputUnOverloadWeightFareTotal);
void SetExitHtMsgOverloadWeight30Count(int InputOverloadWeight30Count);
void SetExitHtMsgOverloadWeight30FareTotal(int InputOverloadWeight30FareTotal);
void SetExitHtMsgOverloadWeight30_100Count(int InputOverloadWeight30_100Count);
void SetExitHtMsgOverloadWeight30_100FareTotal(int InputOverloadWeight30_100FareTotal);
void SetExitHtMsgOverloadWeight100Count(int InputOverloadWeight100Count);
void SetExitHtMsgOverloadWeight100FareTotal(int InputOverloadWeight100FareTotal);
#endif //define t_tablename


