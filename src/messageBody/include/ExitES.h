//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _ExitES_H_
#define _ExitES_H_
//ÏÂ°à¼ÇÂ¼
struct MSG_EXITES
{
	struct MSG_HEAD  EXITES_HEAD;
	char CollectorType;
	char WorkStaus;
	char BS_Year[4];
	char BS_Day[4];
	char BS_Time[6];
	char BS_YMD[8];
	char BS_YMDHM[14];
	char BS_TicketNo[8];
	char Total_Traffic[10];
	char Total_Violation[10];
	char Total_Emergency[10];
	char Total_MotorCade[10];
	char Total_U[10];
	char Total_IllegalU[10];
	char Total_J[10];
	char Total_IllegalJ[10];
	char TotalOfficeCard[10];
	char TotalOfficeNoCard[10];
	char Total_OverRide[10];
	char Total_ICCard[10];
	char Total_ICStoreBox[10];
	char Total_WrongIC[10];
	char Total_RuinIC[10];
	char Total_NoIC[10];
	char Total_ALARM[10];
	char Total_Receipt[10];
	char ES_TicketNo[8];
	char ICBox[4];
	char Total_DebtTraffic[10];
	char Total_Debt[10];
	char Counter1[10];
	char Counter2[10];
	char Counter3[10];
	char Counter4[10];
	char Counter5[10];
	char Counter6[10];
	char Counter7[10];
	char Counter8[10];
	char Counter9[10];
	char Counter10[10];
	char Counter11[10];
	char Counter12[10];
	char Counter13[10];
	char Counter14[10];
	char Counter15[10];
	char Counter16[10];
	char Counter17[10];
	char Counter18[10];
	char Counter19[10];
	char Counter20[10]; // 1796 - 1152 - 112 = 532
	struct  CARKINDUNTYPE CarInfoContext[12];//12 * 8 * 12  = 1152
	char WorkTime[10];
	char Shift;
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
	char OverloadWeight100FareTotal[10]; //11*10 + 2  = 112
};//endstructExitES
#define LENGHT_MSG_EXITESHEAD 532
#define LENGHT_MSG_EXITESEND 112
#define  LENGHT_MSG_EXITES 1796
#define  LENGHT_MSG_NEWEXITES (MSG_NewTifficStatLenght+LENGHT_MSG_EXITESHEAD+LENGHT_MSG_EXITESEND)
void InitMsgExitES(void);
struct MSG_EXITES *GetMsgExitES(void);
struct MSG_NewTifficStat *GetMsgNewExitES(void);
void SetExitESMsgCollectorType(char InputCollectorType);
void SetExitESMsgWorkStaus(char InputWorkStaus);
void SetExitESMsgBS_Year(char* InputBS_Year);
void SetExitESMsgBS_Day(char* InputBS_Day);
void SetExitESMsgBS_Time(char* InputBS_Time);
void SetExitESMsgBS_YMD(char* InputBS_YMD);
void SetExitESMsgBS_YMDHM(char* InputBS_YMDHM);
void SetExitESMsgBS_TicketNo(char* InputBS_TicketNo);
void SetExitESMsgTotal_Traffic(void);
void AddExitESMsgTotal_Violation(void);
void AddExitESMsgTotal_Emergency(void);
void AddExitESMsgTotal_MotorCade(void);
void SetExitESMsgTotal_U(int InputTotal_U);
void Sync_ExitES(void);
void SetExitESMsgTotal_IllegalU(int InputTotal_IllegalU);
void SetExitESMsgTotal_J(int InputTotal_J);
void SetExitESMsgTotal_IllegalJ(int InputTotal_IllegalJ);
void SetExitESMsgTotalOfficeCard(int InputTotalOfficeCard);
void SetExitESMsgTotalOfficeNoCard(int InputTotalOfficeNoCard);
void SetExitESMsgTotal_OverRide(int InputTotal_OverRide);
void SetExitESMsgTotal_ICCard(int InputTotal_ICCard);
void SetExitESMsgTotal_ICStoreBox(int InputTotal_ICStoreBox);
void SetExitESMsgTotal_WrongIC(int InputTotal_WrongIC);
void SetExitESMsgTotal_RuinIC(int InputTotal_RuinIC);
void SetExitESMsgTotal_NoIC(int InputTotal_NoIC);
void SetExitESMsgTotal_ALARM(int InputTotal_ALARM);
void AddExitESMsgTotal_Receipt(void);
void SetExitESMsgES_TicketNo(char* InputES_TicketNo);
void SetExitESMsgICBox(char* InputICBox);
void SetExitESMsgTotal_DebtTraffic(int InputTotal_DebtTraffic);
void SetExitESMsgTotal_Debt(int InputTotal_Debt);
void AddExitESMsgCounter1(void);
void AddExitESMsgCounter2(void);
void AddExitESMsgCounter3(void);
void SetExitESMsgCounter2(void);
void SetExitESMsgCounter3(void);
void AddExitESMsgCounter4(void);
void AddExitESMsgCounter5(void);
void SetExitESMsgCounter6(int InputCounter6);
void SetExitESMsgCounter7(int InputCounter7);
void SetExitESMsgCounter8(int InputCounter8);
void SetExitESMsgCounter9(int InputCounter9);
void SetExitESMsgCounter10(int InputCounter10);
void SetExitESMsgCounter11(int InputCounter11);
void SetExitESMsgCounter12(int InputCounter12);
void SetExitESMsgCounter13(int InputCounter13);
void SetExitESMsgCounter14(int InputCounter14);
void SetExitESMsgCounter15(int InputCounter15);
void SetExitESMsgCounter16(int InputCounter16);
void SetExitESMsgCounter17(int InputCounter17);
void SetExitESMsgCounter18(int InputCounter18);
void SetExitESMsgCounter19(int InputCounter19);
void SetExitESMsgCounter20(int InputCounter20);
 
void SetExitESMsgWorkTime(long InputWorkTime);
void SetExitESMsgShift(char InputShift);
void SetExitESMsgMARK(char InputMARK);
void LoadMsgExitES(void);
void SetExitESData(void);
void SetEixtHTData(void);
 
 
void SetExitESMsgWeightCount(int InputWeightCount);
void SetExitESMsgWeightFareTotal(int InputWeightFareTotal);
void SetExitESMsgUnOverloadWeightCount(int InputUnOverloadWeightCount);
void SetExitESMsgUnOverloadWeightFareTotal(int InputUnOverloadWeightFareTotal);
void SetExitESMsgOverloadWeight30Count(int InputOverloadWeight30Count);
void SetExitESMsgOverloadWeight30FareTotal(int InputOverloadWeight30FareTotal);
void SetExitESMsgOverloadWeight30_100Count(int InputOverloadWeight30_100Count);
void SetExitESMsgOverloadWeight30_100FareTotal(int InputOverloadWeight30_100FareTotal);
void SetExitESMsgOverloadWeight100Count(int InputOverloadWeight100Count);
void SetExitESMsgOverloadWeight100FareTotal(int InputOverloadWeight100FareTotal);
int Get_Total_Traffic(void);
#endif //define t_tablename

