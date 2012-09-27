//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "include\ClearDebtTmp.h"
struct MSG_CLEARDEBTTMP MsgClearDebtTmp;
void InitMsgClearDebtTmp(void)
{	
memset((char *)&MsgClearDebtTmp,'0',sizeof(struct MSG_CLEARDEBTTMP));	
}
struct MSG_CLEARDEBTTMP *GetMsgClearDebtTmp(void)
{	
return (struct MSG_CLEARDEBTTMP  *)&MsgClearDebtTmp;
}
void SetClearDebtTmpMsgcollname(char* Inputcollname)
{	 
	strncpy(MsgClearDebtTmp.collname,Inputcollname,sizeof(MsgClearDebtTmp.collname));	
}
void SetClearDebtTmpMsgID(char* InputID)
{	
	strncpy(MsgClearDebtTmp.ID,InputID,sizeof(MsgClearDebtTmp.ID));	
}
void SetClearDebtTmpMsgMsgType(char InputMsgType)
{	
MsgClearDebtTmp.MsgType=InputMsgType;
}
void SetClearDebtTmpMsgLaneType(char InputLaneType)
{	
MsgClearDebtTmp.LaneType=InputLaneType;
}
void SetClearDebtTmpMsgLaneMode(char InputLaneMode)
{	
MsgClearDebtTmp.LaneMode=InputLaneMode;
}
void SetClearDebtTmpMsgNetwork(char* InputNetwork)
{	
	strncpy(MsgClearDebtTmp.Network,InputNetwork,sizeof(MsgClearDebtTmp.Network));	
}
void SetClearDebtTmpMsgPlaza(char* InputPlaza)
{	
	strncpy(MsgClearDebtTmp.Plaza,InputPlaza,sizeof(MsgClearDebtTmp.Plaza));	
}
void SetClearDebtTmpMsgYea_(char* InputYea_)
{	
	strncpy(MsgClearDebtTmp.Yea_,InputYea_,sizeof(MsgClearDebtTmp.Yea_));	
}
void SetClearDebtTmpMsgDa_(char* InputDa_)
{	
	strncpy(MsgClearDebtTmp.Da_,InputDa_,sizeof(MsgClearDebtTmp.Da_));	
}
void SetClearDebtTmpMsgHou_(char* InputHou_)
{	
	strncpy(MsgClearDebtTmp.Hou_,InputHou_,sizeof(MsgClearDebtTmp.Hou_));	
}
void SetClearDebtTmpMsgYMD(char* InputYMD)
{	
	strncpy(MsgClearDebtTmp.YMD,InputYMD,sizeof(MsgClearDebtTmp.YMD));	
}
void SetClearDebtTmpMsgYMDHM(char* InputYMDHM)
{	
	strncpy(MsgClearDebtTmp.YMDHM,InputYMDHM,sizeof(MsgClearDebtTmp.YMDHM));	
}
void SetClearDebtTmpMsgLaneNo(char* InputLaneNo)
{	
	strncpy(MsgClearDebtTmp.LaneNo,InputLaneNo,sizeof(MsgClearDebtTmp.LaneNo));	
}
void SetClearDebtTmpMsgCollector(char* InputCollector)
{	
	strncpy(MsgClearDebtTmp.Collector,InputCollector,sizeof(MsgClearDebtTmp.Collector));	
}
void SetClearDebtTmpMsgCollectorType(char InputCollectorType)
{	
MsgClearDebtTmp.CollectorType=InputCollectorType;
}
void SetClearDebtTmpMsgWorkStaus(char InputWorkStaus)
{	
MsgClearDebtTmp.WorkStaus=InputWorkStaus;
}
void SetClearDebtTmpMsgBS_Year(char* InputBS_Year)
{	
	strncpy(MsgClearDebtTmp.BS_Year,InputBS_Year,sizeof(MsgClearDebtTmp.BS_Year));	
}
void SetClearDebtTmpMsgBS_Day(char* InputBS_Day)
{	
	strncpy(MsgClearDebtTmp.BS_Day,InputBS_Day,sizeof(MsgClearDebtTmp.BS_Day));	
}
void SetClearDebtTmpMsgBS_Time(char* InputBS_Time)
{	
	strncpy(MsgClearDebtTmp.BS_Time,InputBS_Time,sizeof(MsgClearDebtTmp.BS_Time));	
}
void SetClearDebtTmpMsgBS_YMD(char* InputBS_YMD)
{	
	strncpy(MsgClearDebtTmp.BS_YMD,InputBS_YMD,sizeof(MsgClearDebtTmp.BS_YMD));	
}
void SetClearDebtTmpMsgBS_YMDHM(char* InputBS_YMDHM)
{	
	strncpy(MsgClearDebtTmp.BS_YMDHM,InputBS_YMDHM,sizeof(MsgClearDebtTmp.BS_YMDHM));	
}
void SetClearDebtTmpMsgBS_TicketNo(char* InputBS_TicketNo)
{	
	strncpy(MsgClearDebtTmp.BS_TicketNo,InputBS_TicketNo,sizeof(MsgClearDebtTmp.BS_TicketNo));	
}
void SetClearDebtTmpMsgTotal_Traffic(int InputTotal_Traffic)
{	
	sprintf(MsgClearDebtTmp.Total_Traffic,"%010d",InputTotal_Traffic);	
}
void SetClearDebtTmpMsgTotal_Violation(int InputTotal_Violation)
{	
	sprintf(MsgClearDebtTmp.Total_Violation,"%010d",InputTotal_Violation);	
}
void SetClearDebtTmpMsgTotal_Emergency(int InputTotal_Emergency)
{	
	sprintf(MsgClearDebtTmp.Total_Emergency,"%010d",InputTotal_Emergency);	
}
void SetClearDebtTmpMsgTotal_MotorCade(int InputTotal_MotorCade)
{	
	sprintf(MsgClearDebtTmp.Total_MotorCade,"%010d",InputTotal_MotorCade);	
}
void SetClearDebtTmpMsgTotal_U(int InputTotal_U)
{	
	sprintf(MsgClearDebtTmp.Total_U,"%010d",InputTotal_U);	
}
void SetClearDebtTmpMsgTotal_IllegalU(int InputTotal_IllegalU)
{	
	sprintf(MsgClearDebtTmp.Total_IllegalU,"%010d",InputTotal_IllegalU);	
}
void SetClearDebtTmpMsgTotal_J(int InputTotal_J)
{	
	sprintf(MsgClearDebtTmp.Total_J,"%010d",InputTotal_J);	
}
void SetClearDebtTmpMsgTotal_IllegalJ(int InputTotal_IllegalJ)
{	
	sprintf(MsgClearDebtTmp.Total_IllegalJ,"%010d",InputTotal_IllegalJ);	
}
void SetClearDebtTmpMsgTotalOfficeCard(int InputTotalOfficeCard)
{	
	sprintf(MsgClearDebtTmp.TotalOfficeCard,"%010d",InputTotalOfficeCard);	
}
void SetClearDebtTmpMsgTotalOfficeNoCard(int InputTotalOfficeNoCard)
{	
	sprintf(MsgClearDebtTmp.TotalOfficeNoCard,"%010d",InputTotalOfficeNoCard);	
}
void SetClearDebtTmpMsgTotal_OverRide(int InputTotal_OverRide)
{	
	sprintf(MsgClearDebtTmp.Total_OverRide,"%010d",InputTotal_OverRide);	
}
void SetClearDebtTmpMsgTotal_ICCard(int InputTotal_ICCard)
{	
	sprintf(MsgClearDebtTmp.Total_ICCard,"%010d",InputTotal_ICCard);	
}
void SetClearDebtTmpMsgTotal_ICStoreBox(int InputTotal_ICStoreBox)
{	
	sprintf(MsgClearDebtTmp.Total_ICStoreBox,"%010d",InputTotal_ICStoreBox);	
}
void SetClearDebtTmpMsgTotal_WrongIC(int InputTotal_WrongIC)
{	
	sprintf(MsgClearDebtTmp.Total_WrongIC,"%010d",InputTotal_WrongIC);	
}
void SetClearDebtTmpMsgTotal_RuinIC(int InputTotal_RuinIC)
{	
	sprintf(MsgClearDebtTmp.Total_RuinIC,"%010d",InputTotal_RuinIC);	
}
void SetClearDebtTmpMsgTotal_NoIC(int InputTotal_NoIC)
{	
	sprintf(MsgClearDebtTmp.Total_NoIC,"%010d",InputTotal_NoIC);	
}
void SetClearDebtTmpMsgTotal_ALARM(int InputTotal_ALARM)
{	
	sprintf(MsgClearDebtTmp.Total_ALARM,"%010d",InputTotal_ALARM);	
}
void SetClearDebtTmpMsgTotal_Receipt(int InputTotal_Receipt)
{	
	sprintf(MsgClearDebtTmp.Total_Receipt,"%010d",InputTotal_Receipt);	
}
void SetClearDebtTmpMsgES_TicketNo(char* InputES_TicketNo)
{	
	strncpy(MsgClearDebtTmp.ES_TicketNo,InputES_TicketNo,sizeof(MsgClearDebtTmp.ES_TicketNo));	
}
void SetClearDebtTmpMsgICBox(char* InputICBox)
{	
	strncpy(MsgClearDebtTmp.ICBox,InputICBox,sizeof(MsgClearDebtTmp.ICBox));	
}
void SetClearDebtTmpMsgTotal_DebtTraffic(int InputTotal_DebtTraffic)
{	
	sprintf(MsgClearDebtTmp.Total_DebtTraffic,"%010d",InputTotal_DebtTraffic);	
}
void SetClearDebtTmpMsgTotal_Debt(int InputTotal_Debt)
{	
	sprintf(MsgClearDebtTmp.Total_Debt,"%010d",InputTotal_Debt);	
}
void SetClearDebtTmpMsgCounter1(int InputCounter1)
{	
	sprintf(MsgClearDebtTmp.Counter1,"%010d",InputCounter1);	
}
void SetClearDebtTmpMsgCounter2(int InputCounter2)
{	
	sprintf(MsgClearDebtTmp.Counter2,"%010d",InputCounter2);	
}
void SetClearDebtTmpMsgCounter3(int InputCounter3)
{	
	sprintf(MsgClearDebtTmp.Counter3,"%010d",InputCounter3);	
}
void SetClearDebtTmpMsgCounter4(int InputCounter4)
{	
	sprintf(MsgClearDebtTmp.Counter4,"%010d",InputCounter4);	
}
void SetClearDebtTmpMsgCounter5(int InputCounter5)
{	
	sprintf(MsgClearDebtTmp.Counter5,"%010d",InputCounter5);	
}
void SetClearDebtTmpMsgCounter6(int InputCounter6)
{	
	sprintf(MsgClearDebtTmp.Counter6,"%010d",InputCounter6);	
}
void SetClearDebtTmpMsgCounter7(int InputCounter7)
{	
	sprintf(MsgClearDebtTmp.Counter7,"%010d",InputCounter7);	
}
void SetClearDebtTmpMsgCounter8(int InputCounter8)
{	
	sprintf(MsgClearDebtTmp.Counter8,"%010d",InputCounter8);	
}
void SetClearDebtTmpMsgCounter9(int InputCounter9)
{	
	sprintf(MsgClearDebtTmp.Counter9,"%010d",InputCounter9);	
}
void SetClearDebtTmpMsgCounter10(int InputCounter10)
{	
	sprintf(MsgClearDebtTmp.Counter10,"%010d",InputCounter10);	
}
void SetClearDebtTmpMsgCounter11(int InputCounter11)
{	
	sprintf(MsgClearDebtTmp.Counter11,"%010d",InputCounter11);	
}
void SetClearDebtTmpMsgCounter12(int InputCounter12)
{	
	sprintf(MsgClearDebtTmp.Counter12,"%010d",InputCounter12);	
}
void SetClearDebtTmpMsgCounter13(int InputCounter13)
{	
	sprintf(MsgClearDebtTmp.Counter13,"%010d",InputCounter13);	
}
void SetClearDebtTmpMsgCounter14(int InputCounter14)
{	
	sprintf(MsgClearDebtTmp.Counter14,"%010d",InputCounter14);	
}
void SetClearDebtTmpMsgCounter15(int InputCounter15)
{	
	sprintf(MsgClearDebtTmp.Counter15,"%010d",InputCounter15);	
}
void SetClearDebtTmpMsgCounter16(int InputCounter16)
{	
	sprintf(MsgClearDebtTmp.Counter16,"%010d",InputCounter16);	
}
void SetClearDebtTmpMsgCounter17(int InputCounter17)
{	
	sprintf(MsgClearDebtTmp.Counter17,"%010d",InputCounter17);	
}
void SetClearDebtTmpMsgCounter18(int InputCounter18)
{	
	sprintf(MsgClearDebtTmp.Counter18,"%010d",InputCounter18);	
}
void SetClearDebtTmpMsgCounter19(int InputCounter19)
{	
	sprintf(MsgClearDebtTmp.Counter19,"%010d",InputCounter19);	
}
void SetClearDebtTmpMsgCounter20(int InputCounter20)
{	
	sprintf(MsgClearDebtTmp.Counter20,"%010d",InputCounter20);	
}
void SetClearDebtTmpMsgTotal_Cash(int InputTotal_Cash)
{	
	sprintf(MsgClearDebtTmp.Total_Cash,"%010d",InputTotal_Cash);	
}
void SetClearDebtTmpMsgCashClass1(int InputCashClass1)
{	
	sprintf(MsgClearDebtTmp.CashClass1,"%010d",InputCashClass1);	
}
void SetClearDebtTmpMsgCashClass2(int InputCashClass2)
{	
	sprintf(MsgClearDebtTmp.CashClass2,"%010d",InputCashClass2);	
}
void SetClearDebtTmpMsgCashClass3(int InputCashClass3)
{	
	sprintf(MsgClearDebtTmp.CashClass3,"%010d",InputCashClass3);	
}
void SetClearDebtTmpMsgCashClass4(int InputCashClass4)
{	
	sprintf(MsgClearDebtTmp.CashClass4,"%010d",InputCashClass4);	
}
void SetClearDebtTmpMsgCashClass5(int InputCashClass5)
{	
	sprintf(MsgClearDebtTmp.CashClass5,"%010d",InputCashClass5);	
}
void SetClearDebtTmpMsgCashClass6(int InputCashClass6)
{	
	sprintf(MsgClearDebtTmp.CashClass6,"%010d",InputCashClass6);	
}
void SetClearDebtTmpMsgCashClass7(int InputCashClass7)
{	
	sprintf(MsgClearDebtTmp.CashClass7,"%010d",InputCashClass7);	
}
void SetClearDebtTmpMsgTotal_Preferential(int InputTotal_Preferential)
{	
	sprintf(MsgClearDebtTmp.Total_Preferential,"%010d",InputTotal_Preferential);	
}
void SetClearDebtTmpMsgLocalPreferential1(int InputLocalPreferential1)
{	
	sprintf(MsgClearDebtTmp.LocalPreferential1,"%010d",InputLocalPreferential1);	
}
void SetClearDebtTmpMsgLocalPreferential2(int InputLocalPreferential2)
{	
	sprintf(MsgClearDebtTmp.LocalPreferential2,"%010d",InputLocalPreferential2);	
}
void SetClearDebtTmpMsgLocalPreferential3(int InputLocalPreferential3)
{	
	sprintf(MsgClearDebtTmp.LocalPreferential3,"%010d",InputLocalPreferential3);	
}
void SetClearDebtTmpMsgLocalPreferential4(int InputLocalPreferential4)
{	
	sprintf(MsgClearDebtTmp.LocalPreferential4,"%010d",InputLocalPreferential4);	
}
void SetClearDebtTmpMsgLocalPreferential5(int InputLocalPreferential5)
{	
	sprintf(MsgClearDebtTmp.LocalPreferential5,"%010d",InputLocalPreferential5);	
}
void SetClearDebtTmpMsgLocalPreferential6(int InputLocalPreferential6)
{	
	sprintf(MsgClearDebtTmp.LocalPreferential6,"%010d",InputLocalPreferential6);	
}
void SetClearDebtTmpMsgLocalPreferential7(int InputLocalPreferential7)
{	
	sprintf(MsgClearDebtTmp.LocalPreferential7,"%010d",InputLocalPreferential7);	
}
void SetClearDebtTmpMsgTotal_SVC(int InputTotal_SVC)
{	
	sprintf(MsgClearDebtTmp.Total_SVC,"%010d",InputTotal_SVC);	
}
void SetClearDebtTmpMsgSVCClass1(int InputSVCClass1)
{	
	sprintf(MsgClearDebtTmp.SVCClass1,"%010d",InputSVCClass1);	
}
void SetClearDebtTmpMsgSVCClass2(int InputSVCClass2)
{	
	sprintf(MsgClearDebtTmp.SVCClass2,"%010d",InputSVCClass2);	
}
void SetClearDebtTmpMsgSVCClass3(int InputSVCClass3)
{	
	sprintf(MsgClearDebtTmp.SVCClass3,"%010d",InputSVCClass3);	
}
void SetClearDebtTmpMsgSVCClass4(int InputSVCClass4)
{	
	sprintf(MsgClearDebtTmp.SVCClass4,"%010d",InputSVCClass4);	
}
void SetClearDebtTmpMsgSVCClass5(int InputSVCClass5)
{	
	sprintf(MsgClearDebtTmp.SVCClass5,"%010d",InputSVCClass5);	
}
void SetClearDebtTmpMsgSVCClass6(int InputSVCClass6)
{	
	sprintf(MsgClearDebtTmp.SVCClass6,"%010d",InputSVCClass6);	
}
void SetClearDebtTmpMsgSVCClass7(int InputSVCClass7)
{	
	sprintf(MsgClearDebtTmp.SVCClass7,"%010d",InputSVCClass7);	
}
void SetClearDebtTmpMsgTotal_Credit(int InputTotal_Credit)
{	
	sprintf(MsgClearDebtTmp.Total_Credit,"%010d",InputTotal_Credit);	
}
void SetClearDebtTmpMsgCreditClass1(int InputCreditClass1)
{	
	sprintf(MsgClearDebtTmp.CreditClass1,"%010d",InputCreditClass1);	
}
void SetClearDebtTmpMsgCreditClass2(int InputCreditClass2)
{	
	sprintf(MsgClearDebtTmp.CreditClass2,"%010d",InputCreditClass2);	
}
void SetClearDebtTmpMsgCreditClass3(int InputCreditClass3)
{	
	sprintf(MsgClearDebtTmp.CreditClass3,"%010d",InputCreditClass3);	
}
void SetClearDebtTmpMsgCreditClass4(int InputCreditClass4)
{	
	sprintf(MsgClearDebtTmp.CreditClass4,"%010d",InputCreditClass4);	
}
void SetClearDebtTmpMsgCreditClass5(int InputCreditClass5)
{	
	sprintf(MsgClearDebtTmp.CreditClass5,"%010d",InputCreditClass5);	
}
void SetClearDebtTmpMsgCreditClass6(int InputCreditClass6)
{	
	sprintf(MsgClearDebtTmp.CreditClass6,"%010d",InputCreditClass6);	
}
void SetClearDebtTmpMsgCreditClass7(int InputCreditClass7)
{	
	sprintf(MsgClearDebtTmp.CreditClass7,"%010d",InputCreditClass7);	
}
void SetClearDebtTmpMsgTotal_Mil(int InputTotal_Mil)
{	
	sprintf(MsgClearDebtTmp.Total_Mil,"%010d",InputTotal_Mil);	
}
void SetClearDebtTmpMsgMilClass1(int InputMilClass1)
{	
	sprintf(MsgClearDebtTmp.MilClass1,"%010d",InputMilClass1);	
}
void SetClearDebtTmpMsgMilClass2(int InputMilClass2)
{	
	sprintf(MsgClearDebtTmp.MilClass2,"%010d",InputMilClass2);	
}
void SetClearDebtTmpMsgMilClass3(int InputMilClass3)
{	
	sprintf(MsgClearDebtTmp.MilClass3,"%010d",InputMilClass3);	
}
void SetClearDebtTmpMsgMilClass4(int InputMilClass4)
{	
	sprintf(MsgClearDebtTmp.MilClass4,"%010d",InputMilClass4);	
}
void SetClearDebtTmpMsgMilClass5(int InputMilClass5)
{	
	sprintf(MsgClearDebtTmp.MilClass5,"%010d",InputMilClass5);	
}
void SetClearDebtTmpMsgMilClass6(int InputMilClass6)
{	
	sprintf(MsgClearDebtTmp.MilClass6,"%010d",InputMilClass6);	
}
void SetClearDebtTmpMsgMilClass7(int InputMilClass7)
{	
	sprintf(MsgClearDebtTmp.MilClass7,"%010d",InputMilClass7);	
}
void SetClearDebtTmpMsgTotal_Off(int InputTotal_Off)
{	
	sprintf(MsgClearDebtTmp.Total_Off,"%010d",InputTotal_Off);	
}
void SetClearDebtTmpMsgOffClass1(int InputOffClass1)
{	
	sprintf(MsgClearDebtTmp.OffClass1,"%010d",InputOffClass1);	
}
void SetClearDebtTmpMsgOffClass2(int InputOffClass2)
{	
	sprintf(MsgClearDebtTmp.OffClass2,"%010d",InputOffClass2);	
}
void SetClearDebtTmpMsgOffClass3(int InputOffClass3)
{	
	sprintf(MsgClearDebtTmp.OffClass3,"%010d",InputOffClass3);	
}
void SetClearDebtTmpMsgOffClass4(int InputOffClass4)
{	
	sprintf(MsgClearDebtTmp.OffClass4,"%010d",InputOffClass4);	
}
void SetClearDebtTmpMsgOffClass5(int InputOffClass5)
{	
	sprintf(MsgClearDebtTmp.OffClass5,"%010d",InputOffClass5);	
}
void SetClearDebtTmpMsgOffClass6(int InputOffClass6)
{	
	sprintf(MsgClearDebtTmp.OffClass6,"%010d",InputOffClass6);	
}
void SetClearDebtTmpMsgOffClass7(int InputOffClass7)
{	
	sprintf(MsgClearDebtTmp.OffClass7,"%010d",InputOffClass7);	
}
void SetClearDebtTmpMsgTotal_Police(int InputTotal_Police)
{	
	sprintf(MsgClearDebtTmp.Total_Police,"%010d",InputTotal_Police);	
}
void SetClearDebtTmpMsgPoliceClass1(int InputPoliceClass1)
{	
	sprintf(MsgClearDebtTmp.PoliceClass1,"%010d",InputPoliceClass1);	
}
void SetClearDebtTmpMsgPoliceClass2(int InputPoliceClass2)
{	
	sprintf(MsgClearDebtTmp.PoliceClass2,"%010d",InputPoliceClass2);	
}
void SetClearDebtTmpMsgPoliceClass3(int InputPoliceClass3)
{	
	sprintf(MsgClearDebtTmp.PoliceClass3,"%010d",InputPoliceClass3);	
}
void SetClearDebtTmpMsgPoliceClass4(int InputPoliceClass4)
{	
	sprintf(MsgClearDebtTmp.PoliceClass4,"%010d",InputPoliceClass4);	
}
void SetClearDebtTmpMsgPoliceClass5(int InputPoliceClass5)
{	
	sprintf(MsgClearDebtTmp.PoliceClass5,"%010d",InputPoliceClass5);	
}
void SetClearDebtTmpMsgPoliceClass6(int InputPoliceClass6)
{	
	sprintf(MsgClearDebtTmp.PoliceClass6,"%010d",InputPoliceClass6);	
}
void SetClearDebtTmpMsgPoliceClass7(int InputPoliceClass7)
{	
	sprintf(MsgClearDebtTmp.PoliceClass7,"%010d",InputPoliceClass7);	
}
void SetClearDebtTmpMsgTotal_MonthTicket(int InputTotal_MonthTicket)
{	
	sprintf(MsgClearDebtTmp.Total_MonthTicket,"%010d",InputTotal_MonthTicket);	
}
void SetClearDebtTmpMsgMonthTicket1(int InputMonthTicket1)
{	
	sprintf(MsgClearDebtTmp.MonthTicket1,"%010d",InputMonthTicket1);	
}
void SetClearDebtTmpMsgMonthTicket2(int InputMonthTicket2)
{	
	sprintf(MsgClearDebtTmp.MonthTicket2,"%010d",InputMonthTicket2);	
}
void SetClearDebtTmpMsgMonthTicket3(int InputMonthTicket3)
{	
	sprintf(MsgClearDebtTmp.MonthTicket3,"%010d",InputMonthTicket3);	
}
void SetClearDebtTmpMsgMonthTicket4(int InputMonthTicket4)
{	
	sprintf(MsgClearDebtTmp.MonthTicket4,"%010d",InputMonthTicket4);	
}
void SetClearDebtTmpMsgMonthTicket5(int InputMonthTicket5)
{	
	sprintf(MsgClearDebtTmp.MonthTicket5,"%010d",InputMonthTicket5);	
}
void SetClearDebtTmpMsgMonthTicket6(int InputMonthTicket6)
{	
	sprintf(MsgClearDebtTmp.MonthTicket6,"%010d",InputMonthTicket6);	
}
void SetClearDebtTmpMsgMonthTicket7(int InputMonthTicket7)
{	
	sprintf(MsgClearDebtTmp.MonthTicket7,"%010d",InputMonthTicket7);	
}
void SetClearDebtTmpMsgTotal_Paid(int InputTotal_Paid)
{	
	sprintf(MsgClearDebtTmp.Total_Paid,"%010d",InputTotal_Paid);	
}
void SetClearDebtTmpMsgPaidClass1(int InputPaidClass1)
{	
	sprintf(MsgClearDebtTmp.PaidClass1,"%010d",InputPaidClass1);	
}
void SetClearDebtTmpMsgPaidClass2(int InputPaidClass2)
{	
	sprintf(MsgClearDebtTmp.PaidClass2,"%010d",InputPaidClass2);	
}
void SetClearDebtTmpMsgPaidClass3(int InputPaidClass3)
{	
	sprintf(MsgClearDebtTmp.PaidClass3,"%010d",InputPaidClass3);	
}
void SetClearDebtTmpMsgPaidClass4(int InputPaidClass4)
{	
	sprintf(MsgClearDebtTmp.PaidClass4,"%010d",InputPaidClass4);	
}
void SetClearDebtTmpMsgPaidClass5(int InputPaidClass5)
{	
	sprintf(MsgClearDebtTmp.PaidClass5,"%010d",InputPaidClass5);	
}
void SetClearDebtTmpMsgPaidClass6(int InputPaidClass6)
{	
	sprintf(MsgClearDebtTmp.PaidClass6,"%010d",InputPaidClass6);	
}
void SetClearDebtTmpMsgPaidClass7(int InputPaidClass7)
{	
	sprintf(MsgClearDebtTmp.PaidClass7,"%010d",InputPaidClass7);	
}
void SetClearDebtTmpMsgTotal_PreferPaid(int InputTotal_PreferPaid)
{	
	sprintf(MsgClearDebtTmp.Total_PreferPaid,"%010d",InputTotal_PreferPaid);	
}
void SetClearDebtTmpMsgPreferPaidClass1(int InputPreferPaidClass1)
{	
	sprintf(MsgClearDebtTmp.PreferPaidClass1,"%010d",InputPreferPaidClass1);	
}
void SetClearDebtTmpMsgPreferPaidClass2(int InputPreferPaidClass2)
{	
	sprintf(MsgClearDebtTmp.PreferPaidClass2,"%010d",InputPreferPaidClass2);	
}
void SetClearDebtTmpMsgPreferPaidClass3(int InputPreferPaidClass3)
{	
	sprintf(MsgClearDebtTmp.PreferPaidClass3,"%010d",InputPreferPaidClass3);	
}
void SetClearDebtTmpMsgPreferPaidClass4(int InputPreferPaidClass4)
{	
	sprintf(MsgClearDebtTmp.PreferPaidClass4,"%010d",InputPreferPaidClass4);	
}
void SetClearDebtTmpMsgPreferPaidClass5(int InputPreferPaidClass5)
{	
	sprintf(MsgClearDebtTmp.PreferPaidClass5,"%010d",InputPreferPaidClass5);	
}
void SetClearDebtTmpMsgPreferPaidClass6(int InputPreferPaidClass6)
{	
	sprintf(MsgClearDebtTmp.PreferPaidClass6,"%010d",InputPreferPaidClass6);	
}
void SetClearDebtTmpMsgPreferPaidClass7(int InputPreferPaidClass7)
{	
	sprintf(MsgClearDebtTmp.PreferPaidClass7,"%010d",InputPreferPaidClass7);	
}
void SetClearDebtTmpMsgTotal_SVCPaid(int InputTotal_SVCPaid)
{	
	sprintf(MsgClearDebtTmp.Total_SVCPaid,"%010d",InputTotal_SVCPaid);	
}
void SetClearDebtTmpMsgSVCPaidClass1(int InputSVCPaidClass1)
{	
	sprintf(MsgClearDebtTmp.SVCPaidClass1,"%010d",InputSVCPaidClass1);	
}
void SetClearDebtTmpMsgSVCPaidClass2(int InputSVCPaidClass2)
{	
	sprintf(MsgClearDebtTmp.SVCPaidClass2,"%010d",InputSVCPaidClass2);	
}
void SetClearDebtTmpMsgSVCPaidClass3(int InputSVCPaidClass3)
{	
	sprintf(MsgClearDebtTmp.SVCPaidClass3,"%010d",InputSVCPaidClass3);	
}
void SetClearDebtTmpMsgSVCPaidClass4(int InputSVCPaidClass4)
{	
	sprintf(MsgClearDebtTmp.SVCPaidClass4,"%010d",InputSVCPaidClass4);	
}
void SetClearDebtTmpMsgSVCPaidClass5(int InputSVCPaidClass5)
{	
	sprintf(MsgClearDebtTmp.SVCPaidClass5,"%010d",InputSVCPaidClass5);	
}
void SetClearDebtTmpMsgSVCPaidClass6(int InputSVCPaidClass6)
{	
	sprintf(MsgClearDebtTmp.SVCPaidClass6,"%010d",InputSVCPaidClass6);	
}
void SetClearDebtTmpMsgSVCPaidClass7(int InputSVCPaidClass7)
{	
	sprintf(MsgClearDebtTmp.SVCPaidClass7,"%010d",InputSVCPaidClass7);	
}
void SetClearDebtTmpMsgTotal_CreditPaid(int InputTotal_CreditPaid)
{	
	sprintf(MsgClearDebtTmp.Total_CreditPaid,"%010d",InputTotal_CreditPaid);	
}
void SetClearDebtTmpMsgCreditPaidClass1(int InputCreditPaidClass1)
{	
	sprintf(MsgClearDebtTmp.CreditPaidClass1,"%010d",InputCreditPaidClass1);	
}
void SetClearDebtTmpMsgCreditPaidClass2(int InputCreditPaidClass2)
{	
	sprintf(MsgClearDebtTmp.CreditPaidClass2,"%010d",InputCreditPaidClass2);	
}
void SetClearDebtTmpMsgCreditPaidClass3(int InputCreditPaidClass3)
{	
	sprintf(MsgClearDebtTmp.CreditPaidClass3,"%010d",InputCreditPaidClass3);	
}
void SetClearDebtTmpMsgCreditPaidClass4(int InputCreditPaidClass4)
{	
	sprintf(MsgClearDebtTmp.CreditPaidClass4,"%010d",InputCreditPaidClass4);	
}
void SetClearDebtTmpMsgCreditPaidClass5(int InputCreditPaidClass5)
{	
	sprintf(MsgClearDebtTmp.CreditPaidClass5,"%010d",InputCreditPaidClass5);	
}
void SetClearDebtTmpMsgCreditPaidClass6(int InputCreditPaidClass6)
{	
	sprintf(MsgClearDebtTmp.CreditPaidClass6,"%010d",InputCreditPaidClass6);	
}
void SetClearDebtTmpMsgCreditPaidClass7(int InputCreditPaidClass7)
{	
	sprintf(MsgClearDebtTmp.CreditPaidClass7,"%010d",InputCreditPaidClass7);	
}
void SetClearDebtTmpMsgWorkTime(int InputWorkTime)
{	
	sprintf(MsgClearDebtTmp.WorkTime,"%010d",InputWorkTime);	
}
void SetClearDebtTmpMsgShift(char InputShift)
{	
MsgClearDebtTmp.Shift=InputShift;
}
void SetClearDebtTmpMsgMARK(char InputMARK)
{	
MsgClearDebtTmp.MARK=InputMARK;
}
void SetClearDebtTmpMsgScheduDate(char* InputScheduDate)
{	
	strncpy(MsgClearDebtTmp.ScheduDate,InputScheduDate,sizeof(MsgClearDebtTmp.ScheduDate));	
}
void SetClearDebtTmpMsgSchedu(char InputSchedu)
{	
MsgClearDebtTmp.Schedu=InputSchedu;
}

//end_ClearDebtTmp
