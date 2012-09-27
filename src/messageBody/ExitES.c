//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "LocalIncludeFile.h"

volatile struct MSG_NewTifficStat *MsgNewExitES;
struct MSG_EXITES *MsgExitES;
void inline Sync_ExitES(void)
{   
	memcpy((char*)&MsgExitES->EXITES_HEAD,GetMessageHead(ID_MSGEXITES),MSG_HEAD_LENGTH);
	if (msync((void *)MsgExitES,sizeof(struct MSG_EXITES),MS_SYNC)<0)
	{
		LogCAppLog("Msync Faile!");
	}
	if (msync((void *)MsgNewExitES,sizeof(struct MSG_NewTifficStat),MS_SYNC)<0)
	{
		echo_debugESCOUNT("Msync Faile!");
	}
}
void InitMsgExitES(void)
{   
	memset((char *)MsgExitES,'0',sizeof(struct MSG_EXITES));	
	memset((char *)MsgNewExitES,'0',sizeof(struct MSG_NewTifficStat));
	Sync_ExitES();
}

struct MSG_NewTifficStat *GetMsgNewExitES(void)
{
	return (struct MSG_NewTifficStat *)MsgNewExitES;
}



struct MSG_EXITES *GetMsgExitES(void)
{
	return MsgExitES;
}
int Get_Total_Traffic(void)
{
	char temp[11];
	memset(temp,0,11);
	strncpy(temp,MsgExitES->Total_Traffic,sizeof(MsgExitES->Total_Traffic));
	return atoi(temp);
}
void SetExitESMsgCollectorType(char InputCollectorType)
{   
	MsgExitES->CollectorType=InputCollectorType;
	Sync_ExitES();
}
void SetExitESMsgWorkStaus(char InputWorkStaus)
{   
	MsgExitES->WorkStaus=InputWorkStaus;
	Sync_ExitES();
}
/*************************************************************************************
* 上班年份
**************************************************************************************/
void SetExitESMsgBS_Year(char* InputBS_Year)
{   
	strncpy(MsgExitES->BS_Year,InputBS_Year,sizeof(MsgExitES->BS_Year));
	Sync_ExitES();
}
/*************************************************************************************
* 上班日期
**************************************************************************************/
void SetExitESMsgBS_Day(char* InputBS_Day)
{   
	strncpy(MsgExitES->BS_Day,InputBS_Day,sizeof(MsgExitES->BS_Day));
	Sync_ExitES();
}
/*************************************************************************************
* 上班时间
**************************************************************************************/
void SetExitESMsgBS_Time(char* InputBS_Time)
{   
	strncpy(MsgExitES->BS_Time,InputBS_Time,sizeof(MsgExitES->BS_Time));
	Sync_ExitES();
}
/*************************************************************************************
* 上班日期
**************************************************************************************/
void SetExitESMsgBS_YMD(char* InputBS_YMD)
{   
	strncpy(MsgExitES->BS_YMD,InputBS_YMD,sizeof(MsgExitES->BS_YMD));
	Sync_ExitES();
}
/*************************************************************************************
* 上班时间
**************************************************************************************/
void SetExitESMsgBS_YMDHM(char* InputBS_YMDHM)
{   
	strncpy(MsgExitES->BS_YMDHM,InputBS_YMDHM,sizeof(MsgExitES->BS_YMDHM));
	Sync_ExitES();
}
/*************************************************************************************
* 上班时的发票序列号
**************************************************************************************/
void SetExitESMsgBS_TicketNo(char* InputBS_TicketNo)
{   
	strncpy(MsgExitES->BS_TicketNo,InputBS_TicketNo,sizeof(MsgExitES->BS_TicketNo));
	Sync_ExitES();
}
/*************************************************************************************
* 总交通量
**************************************************************************************/
void SetExitESMsgTotal_Traffic()
{   
	Sync_ExitES();

}
/*************************************************************************************
* 总违章数
**************************************************************************************/
void AddExitESMsgTotal_Violation()
{   
	AddField(MsgExitES->Total_Violation,sizeof(MsgExitES->Total_Violation));
	AddField(MsgExitES->Total_Traffic,sizeof(MsgExitES->Total_Traffic));
	Sync_ExitES();
}
/*************************************************************************************
* 紧急车总数
**************************************************************************************/
void AddExitESMsgTotal_Emergency(void)
{   
	AddField(MsgExitES->Total_Traffic,sizeof(MsgExitES->Total_Traffic));
	AddField(MsgExitES->Total_Emergency,sizeof(MsgExitES->Total_Emergency));
	Sync_ExitES();
}
/*************************************************************************************
* 车队过车总数
**************************************************************************************/
void AddExitESMsgTotal_MotorCade()
{   
	AddField(MsgExitES->Total_MotorCade,sizeof(MsgExitES->Total_MotorCade));
	Sync_ExitES();
}


void SetExitESMsgTotal_U(int InputTotal_U)
{   
	sprintf(MsgExitES->Total_U,"%010d",InputTotal_U);
	Sync_ExitES();
}
void SetExitESMsgTotal_IllegalU(int InputTotal_IllegalU)
{   
	sprintf(MsgExitES->Total_IllegalU,"%010d",InputTotal_IllegalU);
	Sync_ExitES();
}
void SetExitESMsgTotal_J(int InputTotal_J)
{   
	sprintf(MsgExitES->Total_J,"%010d",InputTotal_J);
	Sync_ExitES();
}
void SetExitESMsgTotal_IllegalJ(int InputTotal_IllegalJ)
{   
	sprintf(MsgExitES->Total_IllegalJ,"%010d",InputTotal_IllegalJ);
	Sync_ExitES();
}
void SetExitESMsgTotalOfficeCard(int InputTotalOfficeCard)
{   
	sprintf(MsgExitES->TotalOfficeCard,"%010d",InputTotalOfficeCard);
	Sync_ExitES();
}
void SetExitESMsgTotalOfficeNoCard(int InputTotalOfficeNoCard)
{   
	sprintf(MsgExitES->TotalOfficeNoCard,"%010d",InputTotalOfficeNoCard);
	Sync_ExitES();
}
void SetExitESMsgTotal_OverRide(int InputTotal_OverRide)
{   
	sprintf(MsgExitES->Total_OverRide,"%010d",InputTotal_OverRide);
	Sync_ExitES();
}
void SetExitESMsgTotal_ICCard(int InputTotal_ICCard)
{   
	sprintf(MsgExitES->Total_ICCard,"%010d",InputTotal_ICCard);
	Sync_ExitES();
}
void SetExitESMsgTotal_ICStoreBox(int InputTotal_ICStoreBox)
{   
	sprintf(MsgExitES->Total_ICStoreBox,"%010d",InputTotal_ICStoreBox);
	Sync_ExitES();
}
void SetExitESMsgTotal_WrongIC(int InputTotal_WrongIC)
{   
	sprintf(MsgExitES->Total_WrongIC,"%010d",InputTotal_WrongIC);
	Sync_ExitES();
}
void SetExitESMsgTotal_RuinIC(int InputTotal_RuinIC)
{   
	sprintf(MsgExitES->Total_RuinIC,"%010d",InputTotal_RuinIC);
	Sync_ExitES();
}
void SetExitESMsgTotal_NoIC(int InputTotal_NoIC)
{   
	sprintf(MsgExitES->Total_NoIC,"%010d",InputTotal_NoIC);
	Sync_ExitES();
}
void SetExitESMsgTotal_ALARM(int InputTotal_ALARM)
{   
	sprintf(MsgExitES->Total_ALARM,"%010d",InputTotal_ALARM);
	Sync_ExitES();
}
void AddExitESMsgTotal_Receipt(void)
{   
	AddField(MsgExitES->Total_Receipt,sizeof(MsgExitES->Total_Receipt));
	Sync_ExitES();
}
void SetExitESMsgES_TicketNo(char* InputES_TicketNo)
{   
	strncpy(MsgExitES->ES_TicketNo,InputES_TicketNo,sizeof(MsgExitES->ES_TicketNo));
	Sync_ExitES();
}
void SetExitESMsgICBox(char* InputICBox)
{   
	strncpy(MsgExitES->ICBox,InputICBox,sizeof(MsgExitES->ICBox));
	Sync_ExitES();
}
void SetExitESMsgTotal_DebtTraffic(int InputTotal_DebtTraffic)
{   
	sprintf(MsgExitES->Total_DebtTraffic,"%010d",InputTotal_DebtTraffic);
	Sync_ExitES();
}
void SetExitESMsgTotal_Debt(int InputTotal_Debt)
{   
	sprintf(MsgExitES->Total_Debt,"%010d",InputTotal_Debt);
	Sync_ExitES();
}
void AddExitESMsgCounter1(void)
{   
	AddField(MsgExitES->Counter1,sizeof(MsgExitES->Counter1));
	Sync_ExitES();
}
/*************************************************************************************
* 更改车型
**************************************************************************************/
void AddExitESMsgCounter2(void)
{   
	AddField(MsgExitES->Counter2,sizeof(MsgExitES->Counter2));
	Sync_ExitES();
}
/*************************************************************************************
* 更改车种
**************************************************************************************/
void AddExitESMsgCounter3(void)
{   
	AddField(MsgExitES->Counter3,sizeof(MsgExitES->Counter3));
	Sync_ExitES();
}
/*************************************************************************************
* 拖车
**************************************************************************************/
void AddExitESMsgCounter4(void)
{   
	AddField(MsgExitES->Counter4,sizeof(MsgExitES->Counter4));
	Sync_ExitES();
}
/*************************************************************************************
* 重打票据次数
**************************************************************************************/
void AddExitESMsgCounter5(void)
{   
	AddField(MsgExitES->Counter5,sizeof(MsgExitES->Counter5));
	Sync_ExitES();
}
void SetExitESMsgCounter6(int InputCounter6)
{   
	sprintf(MsgExitES->Counter6,"%010d",InputCounter6);
	Sync_ExitES();
}
void SetExitESMsgCounter7(int InputCounter7)
{   
	sprintf(MsgExitES->Counter7,"%010d",InputCounter7);
	Sync_ExitES();
}
void SetExitESMsgCounter8(int InputCounter8)
{   
	sprintf(MsgExitES->Counter8,"%010d",InputCounter8);
	Sync_ExitES();
}
void SetExitESMsgCounter9(int InputCounter9)
{   
	sprintf(MsgExitES->Counter9,"%010d",InputCounter9);
	Sync_ExitES();
}
void SetExitESMsgCounter10(int InputCounter10)
{   
	sprintf(MsgExitES->Counter10,"%010d",InputCounter10);
	Sync_ExitES();
}
void SetExitESMsgCounter11(int InputCounter11)
{   
	sprintf(MsgExitES->Counter11,"%010d",InputCounter11);
	Sync_ExitES();
}
void SetExitESMsgCounter12(int InputCounter12)
{   
	sprintf(MsgExitES->Counter12,"%010d",InputCounter12);
	Sync_ExitES();
}
void SetExitESMsgCounter13(int InputCounter13)
{   
	sprintf(MsgExitES->Counter13,"%010d",InputCounter13);
	Sync_ExitES();
}
void SetExitESMsgCounter14(int InputCounter14)
{   
	sprintf(MsgExitES->Counter14,"%010d",InputCounter14);
	Sync_ExitES();
}
void SetExitESMsgCounter15(int InputCounter15)
{   
	sprintf(MsgExitES->Counter15,"%010d",InputCounter15);
	Sync_ExitES();
}
void SetExitESMsgCounter16(int InputCounter16)
{   
	sprintf(MsgExitES->Counter16,"%010d",InputCounter16);
	Sync_ExitES();
}
void SetExitESMsgCounter17(int InputCounter17)
{   
	sprintf(MsgExitES->Counter17,"%010d",InputCounter17);
	Sync_ExitES();
}
void SetExitESMsgCounter18(int InputCounter18)
{   
	sprintf(MsgExitES->Counter18,"%010d",InputCounter18);
	Sync_ExitES();
}
void SetExitESMsgCounter19(int InputCounter19)
{   
	sprintf(MsgExitES->Counter19,"%010d",InputCounter19);
	Sync_ExitES();
}
void SetExitESMsgCounter20(int InputCounter20)
{   
	sprintf(MsgExitES->Counter20,"%010d",InputCounter20);
	Sync_ExitES();
}



/*********************************************************************************
* 工作时间
**************************************************************************************/
void SetExitESMsgWorkTime(long  InputWorkTime)
{   
	sprintf(MsgExitES->WorkTime,"%010ld",InputWorkTime);
	// Sync_ExitES();	 不能同步时间，因为这个值是在发送时计算并赋值的。 否则断电上传时无法上传正确数据
	if (1==SynOn)
	{
		Sync_ExitES();
	}
}
void SetExitESMsgShift(char InputShift)
{   
	MsgExitES->Shift=InputShift;
	Sync_ExitES();
}
void SetExitESMsgMARK(char InputMARK)
{   
	MsgExitES->MARK=InputMARK;
	Sync_ExitES();
}
//加载下班记录，加载后，如果工作状态不为0，则说明上班途中断电了。 这时需要上传下班记录。
void LoadMsgExitES()
{   
	MsgExitES=LoadMsgExitESFromFile();
	MsgNewExitES = LoadMsgNewCountFromFile(FILENAME_ASVE_NEWEXITES);	
	echo_debugESCOUNT("LoadMsgExitES-------------------------");
	// echo("MsgExitES->WorkStaus %c",MsgExitES->WorkStaus);	
	if ( '0'!=MsgExitES->WorkStaus )
	{
		SendMessageToQueue(ID_MSGEXITES);
		SetExitESMsgWorkStaus('0');
	}
	InitMsgExitES();
}
//处理小时记录
void SetEixtHTData()
{   
	int pos ;
	int sumpos;
	pos=charstoint(CarKindRecord[Getg_CurrentCarKindIndex()].PosCount,sizeof(CarKindRecord[Getg_CurrentCarKindIndex()].PosCount));
	sumpos=charstoint(CarKindRecord[Getg_CurrentCarKindIndex()].PaidSum,sizeof(CarKindRecord[Getg_CurrentCarKindIndex()].PaidSum));
	 
	if (GetIs_CardContext_SVCCard_Paid())
	{
		pos=3;
		sumpos=11;
	}
	echoic("pos %d  sumpos %d ",pos,sumpos);
	if (0!=pos)
	{
		pos=pos-1;
		AddField(GetMsgExitHt()->CarInfoContext[pos].CarTypes[Get_Current_Car_Type_Index()].CarType,sizeof(GetMsgExitHt()->CarInfoContext[ pos].CarTypes[Get_Current_Car_Type_Index()].CarType));
		AddField(GetMsgExitHt()->CarInfoContext[ pos].Kind_Total ,sizeof(GetMsgExitHt()->CarInfoContext[ pos].Kind_Total));
		AddField(GetMsgExitHt()->Total_Traffic,sizeof(GetMsgExitHt()->Total_Traffic));
		if (0!=Get_G_Current_Actual_pay()   && 0!=sumpos  )
		{
			sumpos=sumpos-1;
			AddFieldAtValue(GetMsgExitHt()->CarInfoContext[sumpos].CarTypes[Get_Current_Car_Type_Index()].CarType ,sizeof(GetMsgExitHt()->CarInfoContext[ sumpos].CarTypes[Get_Current_Car_Type_Index()].CarType),Get_G_Current_Actual_pay());
			AddFieldAtValue(GetMsgExitHt()->CarInfoContext[sumpos].Kind_Total ,sizeof(GetMsgExitHt()->CarInfoContext[ sumpos].Kind_Total),Get_G_Current_Actual_pay());
		}
		Sync_ExitHT();
	}
	strncpy(GetMsgExitHt()->Opentime,GetTime(DATETIME_FORMAT_YYYYMMDDHH),sizeof(GetMsgExitHt()->Opentime));
	SetExitHtMsgOpentime(MsgHour->tmGreen);
	Sync_ExitES();
}

static void SetMSG_NewTifficStatFree(struct CarGroup *StatType,float Fare)
{
	echoic("SetMSG_NewTifficStatFree <%f>",Fare);
	AddFieldAtValue(StatType->Total,
					sizeof(StatType->Total),
					(int)Fare);
	AddFieldAtValue(StatType->CarClassGroup[Get_Current_Car_Type_Index()].Class ,
					sizeof(StatType->CarClassGroup[Get_Current_Car_Type_Index()].Class),
					(int)Fare);	
	Sync_ExitES();
}



static  void SetMSG_NewTifficStat(struct Group *StatType,int NewCarKindSite)
{
	AddField(StatType->Stat[NewCarKindSite].Traffic.Total,
	sizeof(StatType->Stat[NewCarKindSite].Traffic.Total));


	AddField(StatType->Stat[NewCarKindSite].Traffic.CarClassGroup[Get_Current_Car_Type_Index()].Class,
		sizeof(StatType->Stat[NewCarKindSite].Traffic.CarClassGroup[Get_Current_Car_Type_Index()].Class));
	
	if (0!=(int)Get_G_Current_Actual_pay())
	{
		AddFieldAtValue(StatType->Stat[NewCarKindSite].Paid.Total,sizeof(StatType->Stat[NewCarKindSite].Paid.Total),Get_G_Current_Actual_pay());
		AddFieldAtValue(StatType->Stat[NewCarKindSite].Paid.CarClassGroup[Get_Current_Car_Type_Index()].Class ,
						sizeof(StatType->Stat[NewCarKindSite].Paid.CarClassGroup[Get_Current_Car_Type_Index()].Class),Get_G_Current_Actual_pay());			
	}
	else
	{
		if(0!=NewCarKindSite)
		{
			AddFieldAtValue(StatType->Stat[NewCarKindSite].Paid.Total,sizeof(StatType->Stat[NewCarKindSite].Paid.Total),Get_G_Current_Toll_Fare());
			AddFieldAtValue(StatType->Stat[NewCarKindSite].Paid.CarClassGroup[Get_Current_Car_Type_Index()].Class ,
				sizeof(StatType->Stat[NewCarKindSite].Paid.CarClassGroup[Get_Current_Car_Type_Index()].Class),Get_G_Current_Toll_Fare());	
		}		
	}
	
	//echo_debugESCOUNT(",SetMSG_NewTifficStat<%d,%d>ADD<%d>StatType.Stat[NewCarKindSite].Traffic.Total = <%s>",NewCarKindSite,Getg_CurrentCarKindIndex(),&StatType.Stat[NewCarKindSite].Traffic.Total,StatType.Stat[NewCarKindSite].Traffic.Total); 
}
static void SetAllAndCarKind(struct Group *StatType,int NewCarKindSite)
{	
	SetMSG_NewTifficStat(StatType,0);
	SetMSG_NewTifficStat(StatType,NewCarKindSite);
	echoic("Get_G_Current_Actual_pay <%f>Get_G_Current_Toll_Fare<%f>",Get_G_Current_Actual_pay(),Get_G_Current_Toll_Fare());
	if (0==(int)Get_G_Current_Actual_pay())
	{
		echoic("Get_G_Current_Actual_pay ");
		SetMSG_NewTifficStatFree(&(StatType->Stat[1].Traffic),Get_G_Current_Toll_Fare());
	}
	else if((int)Get_G_Current_Actual_pay() < (int)Get_G_Current_Toll_Fare())
	{
		echoic("Get_G_Current_Toll_Fare ");
		SetMSG_NewTifficStatFree(&(StatType->Stat[1].Traffic),(Get_G_Current_Toll_Fare()-Get_G_Current_Actual_pay()));
		if(3 == NewCarKindSite  )
		{
			SetMSG_NewTifficStatFree(&(StatType->Stat[1].Paid),(Get_G_Current_Toll_Fare()-Get_G_Current_Actual_pay()));
		}
	}

}

void SetNewCarKindCount( struct MSG_NewTifficStat *NewCount,int NewCarKindSite )
{

	SetAllAndCarKind(&(NewCount->Total),NewCarKindSite);	
	if (WeightCarClassBUS == GetWeightCarClass())
	{
		SetAllAndCarKind(&(NewCount->Five),NewCarKindSite);
	}
	else if(WeightCarClassTruck == GetWeightCarClass() )
	{
		SetAllAndCarKind(&(NewCount->Truck),NewCarKindSite);
	}
	else
	{
		SetAllAndCarKind(&(NewCount->Truck_Five),NewCarKindSite);
	}
	Sync_ExitES();

}
//处理下班记录 
void SetExitESData()
{   
	char tempBillNumber[9];
	int pos;
	int sumpos;
	int NewCarKindSite ;	
	tempBillNumber[8]=0x00;
	memset(tempBillNumber,0x00,sizeof(tempBillNumber));
	pos=charstoint(CarKindRecord[Getg_CurrentCarKindIndex()].PosCount,sizeof(CarKindRecord[Getg_CurrentCarKindIndex()].PosCount));
	sumpos=charstoint(CarKindRecord[Getg_CurrentCarKindIndex()].PaidSum,sizeof(CarKindRecord[Getg_CurrentCarKindIndex()].PaidSum));
	NewCarKindSite  =charstoint(CarKindRecord[Getg_CurrentCarKindIndex()].NewCarKindSite,sizeof(CarKindRecord[Getg_CurrentCarKindIndex()].NewCarKindSite));

	

	
	 if (GetIs_CardContext_SVCCard_Paid())
	{
		pos=3;
		sumpos=11;
	}
	if (0!=pos)
	{
		pos=pos-1;
		echo_debugESCOUNT("NewCarKindSite = <%d>",NewCarKindSite);
		SetNewCarKindCount((struct MSG_NewTifficStat *)MsgNewExitES,NewCarKindSite);
		SetNewCarKindCount(GetMsgNewExitHT(),NewCarKindSite);
		AddField(MsgExitES->CarInfoContext[pos].CarTypes[ Get_Current_Car_Type_Index()].CarType,sizeof(MsgExitES->CarInfoContext[pos].CarTypes[ Get_Current_Car_Type_Index()].CarType));
		AddField(MsgExitES->CarInfoContext[pos].Kind_Total,sizeof(MsgExitES->CarInfoContext[pos].Kind_Total));
		AddField(MsgExitES->Total_Traffic,sizeof(MsgExitES->Total_Traffic));
		if (0!=Get_G_Current_Actual_pay()   && 0!=sumpos  )
		{
			sumpos=sumpos-1;
			AddFieldAtValue(MsgExitES->CarInfoContext[sumpos].CarTypes[Get_Current_Car_Type_Index()].CarType,sizeof(MsgExitES->CarInfoContext[sumpos].CarTypes[Get_Current_Car_Type_Index()].CarType),Get_G_Current_Actual_pay());
			AddFieldAtValue(MsgExitES->CarInfoContext[sumpos].Kind_Total,sizeof(MsgExitES->CarInfoContext[sumpos].Kind_Total),Get_G_Current_Actual_pay());
		}
		Sync_ExitES();
	}
	sprintf(tempBillNumber,"%08d",GetbillCount());
	SetExitESMsgES_TicketNo(tempBillNumber);
}

 

void SetExitESMsgWeightCount(int InputWeightCount)
{
	SetExitHtMsgWeightCount(InputWeightCount);
	AddFieldAtValue(MsgExitES->WeightCount,10,InputWeightCount);
}
void SetExitESMsgWeightFareTotal(int InputWeightFareTotal)
{
	SetExitHtMsgWeightFareTotal(InputWeightFareTotal);
	AddFieldAtValue(MsgExitES->WeightFareTotal,10,InputWeightFareTotal);
}
void SetExitESMsgUnOverloadWeightCount(int InputUnOverloadWeightCount)
{
	SetExitHtMsgUnOverloadWeightCount(InputUnOverloadWeightCount);
	AddFieldAtValue(MsgExitES->UnOverloadWeightCount,10,InputUnOverloadWeightCount);
}
void SetExitESMsgUnOverloadWeightFareTotal(int InputUnOverloadWeightFareTotal)
{
	SetExitHtMsgUnOverloadWeightFareTotal(InputUnOverloadWeightFareTotal);
	AddFieldAtValue(MsgExitES->UnOverloadWeightFareTotal,10,InputUnOverloadWeightFareTotal);
}
void SetExitESMsgOverloadWeight30Count(int InputOverloadWeight30Count)
{
	SetExitHtMsgOverloadWeight30Count(InputOverloadWeight30Count);
	AddFieldAtValue(MsgExitES->OverloadWeight30Count,10,InputOverloadWeight30Count);
}
void SetExitESMsgOverloadWeight30FareTotal(int InputOverloadWeight30FareTotal)
{
	SetExitHtMsgOverloadWeight30FareTotal(InputOverloadWeight30FareTotal);
	AddFieldAtValue(MsgExitES->OverloadWeight30FareTotal,10,InputOverloadWeight30FareTotal);
}
void SetExitESMsgOverloadWeight30_100Count(int InputOverloadWeight30_100Count)
{
	 SetExitHtMsgOverloadWeight30_100Count(InputOverloadWeight30_100Count);
	AddFieldAtValue(MsgExitES->OverloadWeight30_100Count,10,InputOverloadWeight30_100Count);
}
void SetExitESMsgOverloadWeight30_100FareTotal(int InputOverloadWeight30_100FareTotal)
{
	SetExitHtMsgOverloadWeight30_100FareTotal(InputOverloadWeight30_100FareTotal);
	AddFieldAtValue(MsgExitES->OverloadWeight30_100FareTotal,10,InputOverloadWeight30_100FareTotal);
}
void SetExitESMsgOverloadWeight100Count(int InputOverloadWeight100Count)
{
	SetExitHtMsgOverloadWeight100Count(InputOverloadWeight100Count);
	AddFieldAtValue(MsgExitES->OverloadWeight100Count,10,InputOverloadWeight100Count);
}
void SetExitESMsgOverloadWeight100FareTotal(int InputOverloadWeight100FareTotal)
{
	SetExitHtMsgOverloadWeight100FareTotal(InputOverloadWeight100FareTotal);
	AddFieldAtValue(MsgExitES->OverloadWeight100FareTotal,10,InputOverloadWeight100FareTotal);
}



