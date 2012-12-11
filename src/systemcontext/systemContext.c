// ***************************************************************
//  systemContext   version:  1.0   ��  date: 12/11/2007
//  -------------------------------------------------------------
//  ϵͳ��������Ϣ��
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"
 int YuPengState=0;
void SetYuPengState(int inputYuPengState)
{	
	YuPengState=inputYuPengState;
}
int GetYuPengState(void )
{	
	return YuPengState;
}
 
//ȫ�������
volatile int g_TranNo=0;
//������������Ϣ�����־
volatile int g_nHelpTimer = 0;
volatile int SynOn=0;//ͬ������
volatile int wzCarType = 0;
volatile int YaxianquanNum=0;
 
/**************************************************************
��ǣ�Ϊͳ���ϳ���ʱ��������Ŷ�����
�����ˣ�����ΰ
�������ڣ�2008-07-09
***************************************************************/
int subTransNo;
void InitSubTransNo(void)
{	
	subTransNo=0;
}
void AddSubTransNo(void)
{	
	subTransNo++;
}
int GetSubTransNo(void)
{	
	return subTransNo;
}
 
 
 
 
int G_Lane_carTypeCount ;	//������������ �ڶ����ñ��ʱ��õ��� 
int g_tuocheNum;
void Initg_tuocheNum(void)
{	
	g_tuocheNum=0;
}
void Addg_tuocheNum(void)
{	
	g_tuocheNum++;
}
int Getg_tuocheNum(void)
{	
	return g_tuocheNum;
}
/******************************************************************************************************
*������״̬���
******************************************************************************************************/
volatile int WorkState = 1;
volatile int LastWorkState = 1;
/****************
* ���õ�ǰ״ֵ̬
****************/
void SetWorkState(int value)
{	
	WorkState=value;
}
void SetLastWorkState(int value)
{	
	LastWorkState=value;
}
/******************************
* ��ù���״ֵ̬��ù���״ֵ̬
******************************/
int GetWorkState(void)
{	
	return WorkState;
}
int GetLastWorkState(void)
{	
	return LastWorkState;
}
/******************************************************************************************************
*��ʾ��Ϣ����
******************************************************************************************************/
static char MsgTitle[50];
char * GetMsgTitle(void)
{	
	return MsgTitle;
}
/******************************************************************************************************
*��ʾ��Ϣ����
******************************************************************************************************/
static  char MsgContext[200];
char *GetMsgContext(void)
{	
	return MsgContext;
}


/******************************************************************************************************
*�ϰ�ʱ��
******************************************************************************************************/
char OnJobDateTime[14];
void InitOnJobDateTime()
{	
	memset(OnJobDateTime,' ',14);	
}
char *GetOnJobDateTime(void)
{	
    return OnJobDateTime;
}
void SetOnJobDateTime(char *jbtimetime)
{	
    strncpy(OnJobDateTime, jbtimetime,14);	

}
/******************************************************************************************************
*��κ�
******************************************************************************************************/
char SystemContextSihtNo;
void SetSystemContextSihtNo(char InputSystemContextSihtNo)
{	
	SystemContextSihtNo = InputSystemContextSihtNo;
}
char GetSystemContextSihtNo()
{	
	return SystemContextSihtNo;
}
/******************************************************************************************************
* ʹ�ô�ֵ��
******************************************************************************************************/
int SystemContextIsSVC = 0;
void InitSystemContextIsSVC()
{	
	SystemContextIsSVC = 0;
}
int GetSystemContextIsSVC()
{	
	return SystemContextIsSVC;
}
void SetSystemContextIsSVC()
{	
	SystemContextIsSVC = 1;
}



 
int DiscountRate=0;
void Setg_DiscountRate(float tollFare,float actualFare)
{	
	DiscountRate=(int)((actualFare/tollFare)*100);	
}
int Getg_DiscountRate(void)
{	
	return DiscountRate;
}
///**************************************************************
//
//***************************************************************/

/**************************************************************
�����ϰ�ʱ��
***************************************************************/
long GetEixtEsWorkTime(char * Bs_time,char * EixtEstime)
{	
	struct tm Bstime,Estime;
	long start,end,retSec;
	char BsYear[5],BsMonth[3],BsDay[3],BsHour[3],BsMini[3],BsSec[3];
	char EsYear[5],EsMonth[3],EsDay[3],EsHour[3],EsMini[3],EsSec[3];
	memset(BsYear,0x00,sizeof(BsYear));	
	memset(BsMonth,0x00,sizeof(BsMonth));	
	memset(BsDay,0x00,sizeof(BsDay));	
	memset(BsHour,0x00,sizeof(BsHour));	
	memset(BsMini,0x00,sizeof(BsMini));	
	memset(BsSec,0x00,sizeof(BsSec));	

	memset(EsYear,0x00,sizeof(EsYear));	
	memset(EsMonth,0x00,sizeof(EsMonth));	
	memset(EsDay,0x00,sizeof(EsDay));	
	memset(EsHour,0x00,sizeof(EsHour));	
	memset(EsMini,0x00,sizeof(EsMini));	
	memset(EsSec,0x00,sizeof(EsSec));	
	memset(&Bstime,0,sizeof(Bstime));	
	memset(&Estime,0,sizeof(Estime));	
	strncpy(BsYear,Bs_time,4);	
	strncpy(BsMonth,Bs_time+4,2);	
	strncpy(BsDay,Bs_time+6,2);	
	strncpy(BsHour,Bs_time+8,2);	
	strncpy(BsMini,Bs_time+10,2);	
	strncpy(BsSec,Bs_time+12,2);	

	strncpy(EsYear,EixtEstime,4);	
	strncpy(EsMonth,EixtEstime+4,2);	
	strncpy(EsDay,EixtEstime+6,2);	
	strncpy(EsHour,EixtEstime+8,2);	
	strncpy(EsMini,EixtEstime+10,2);	
	strncpy(EsSec,EixtEstime+12,2);	

	Bstime.tm_year=atoi(BsYear)-1900;
	Bstime.tm_mon=atoi(BsMonth)-1;
	Bstime.tm_mday=atoi(BsDay);	
	Bstime.tm_hour=atoi(BsHour);	
	Bstime.tm_min=atoi(BsMini);	
	Bstime.tm_sec=atoi(BsSec);	

	Estime.tm_year=atoi(EsYear)-1900;
	Estime.tm_mon=atoi(EsMonth)-1;
	Estime.tm_mday=atoi(EsDay);	
	Estime.tm_hour=atoi(EsHour);	
	Estime.tm_min=atoi(EsMini);	
	Estime.tm_sec=atoi(EsSec);	

	start=mktime(&Bstime);	
	end=mktime(&Estime);	
	retSec=end-start;

	return retSec;
}

/************************************************************************
�������ƣ�      void BeforeOfTransDo(void)
���ã�          ���׿�ʼǰһЩ��ʼ��������
������          ��
����ֵ��        ��
�������ڣ�      2008.07
������:         ����ΰ
����޸�����:   2008.07
����޸���:     ����ΰ
*************************************************************************/
void BeforeOfTransDo()
{	
	Setg_DisputeType(0);	
	InitMsgExitTR();
	InitCarNember();
	SetG_reprintbillnum(0);	
	InitSubTransNo();	
	Initg_tuocheNum();	
	InitG_AbateNumber();
}
/************************************************************************
�������ƣ�      void AfterOfTransDo(void)
���ã�          ���׽�����һЩ��ʼ��������
������          ��
����ֵ��        ��
�������ڣ�      2008.07
������:         ����ΰ
����޸�����:   2008.07
����޸���:     ����ΰ
*************************************************************************/
void AfterOfTransDo(int value,BOOL urgen)
{	
	
	char tempTranNo[5];
	memset(tempTranNo,0x00,sizeof(tempTranNo));	
	SetExitTRMsgEntryLane(GetCarNember());
	if(urgen)
	{	
		Validate_Car_Kind(VK_URGENT);
	}	
	Set_AllKindData();	
    if(WORKSTAUS_NORMAL==Getg_workStatus())
    {	
		
		if(0!=Getg_DisputeType())
		{	
			SetExitTRMsgMethod_Pay(MP_NotPay);	
		}	
		sprintf(tempTranNo,"%04d",g_TranNo);	
		SetExitTRMsgtranNo(tempTranNo);	
		//������ĳ��͡����ֵ�ʱ�������
		if(0==Getg_DisputeType())
		{	
			g_TranNo++;
			SetMsg_ES_HT_WeightInfo();
			SetExitESData();	
			SetEixtHTData();	
		}			
    }
    else
    {			
		SetExitESData();	
    }
 	SetICExitTRPayMethod();
	SendMessageToQueue(ID_MSGEXITTR);	
	
}
/************************************************************************
�������ƣ�      void AfterOfTransDo(void)
���ã�         ���׹����д����ϳ���ʱ��
������          ��
����ֵ��        ��
�������ڣ�      2008.07
������:         ����ΰ
����޸�����:   2008.07
����޸���:     ����ΰ
*************************************************************************/
void TransDoTuoche(void)
{	
	
	char tempTranNo[5];
	memset(tempTranNo,0x00,sizeof(tempTranNo));		
	Set_AllKindData();	
    if('1'==Getg_workStatus())
    {	
		
		if(0==Getg_DisputeType())
		{	
			g_TranNo++;
			SetMsg_ES_HT_WeightInfo();
			SetExitESData();	
			SetEixtHTData();	
		}
		sprintf(tempTranNo,"%04d",g_TranNo);	
		SetExitTRMsgtranNo(tempTranNo);	
		
    }
    else
    {	
		
		SetExitESData();	
    }
	SetICExitTRPayMethod();
	SetExitTRMsgEntryLane(GetCarNember());
	SendMessageToQueue(ID_MSGEXITTR);	 
	Setg_DisputeType(0);	
	SetG_reprintbillnum(0);	
}
///**************************************************************
//TR������������
//***************************************************************/
int DisputeType=0;
void Setg_DisputeType(int value)
{	
	DisputeType=value;
}
int Getg_DisputeType(void)
{	
	return DisputeType;
}

///*************e*************************************************
//
//***************************************************************/
int Violation=0;
void Setg_Violation(int value)
{	
	Violation=value;
}
int Getg_Violation()
{	
	return Violation;
}
//������ǰ״̬
//***************************************************************/
int CurrentLaneState;
void Setg_CurrentLaneState(int value)
{	
	CurrentLaneState=value;
}
int Getg_CurrentLaneState(void)
{	
	return CurrentLaneState;
}
/**********************************************************
��ʼ�����֡����͡��շѶ
**********************************************************/
void InitUserNumAndNameAndOnJobDateTime()
{	
	InitOnJobDateTime();	
	InitG_Number();	
	Initg_szName();	
}
void InitCarTypeKindCharge()
{	
	UI_Out_SetHistory();
	Init_G_Current_Actual_pay();
	//SetG_IsTeZhongChe(0);	
	SetWeightCarClass(WeightCarClassBUS);
	Init_Current_Car_Type();	
	InitG_Current_Handl_Car_Kind();	
	UI_ClearCarKind(); 
	UI_ClearCarType(); 
	UI_ClearCarMoney(); 
	LedClare(F);
}



char carTypeStand[20];
void Setg_CurrentCarTypeStand(int value)
{	
	switch(value)
	{	
		case 1:
			strncpy(carTypeStand,"һ�ͳ�",sizeof("һ�ͳ�"));	
			break;
		case 2:
			strncpy(carTypeStand,"���ͳ�",sizeof("һ�ͳ�"));	
			break;
		case 3:
			strncpy(carTypeStand,"���ͳ�",sizeof("һ�ͳ�"));	
			break;
		case 4:
			strncpy(carTypeStand,"���ͳ�",sizeof("һ�ͳ�"));	
			break;
		case 5:
			strncpy(carTypeStand,"���ͳ�",sizeof("һ�ͳ�"));	
			break;
		default:
			strncpy(carTypeStand," ",sizeof(" "));	
			break;
	}
}
char * Getg_CurrentCarTypeStand(void)
{	
	return carTypeStand;
}

void SetBillNumber(void)
{	
	char tempBillNumber[9];
	memset(tempBillNumber,'0',sizeof(tempBillNumber));	
	tempBillNumber[8]=0x00;
	sprintf(tempBillNumber,"%08d",GetbillCount());	
	if(0==Getg_DisputeType())
	{	
		SetExitTRMsgReceiptNo(tempBillNumber);	
	}
}
void SetEixtTRInfo(int carTypeIndex,int carKindIndex)
{	
	
}
/***************************************************************************************
�������ƣ�      void Set_AllKindData(int carTypeIndex,int carKindIndex,float charge)
���ã�          �趨�������ݱ����ݡ�
������          int carTypeIndex,int carKindIndex,float charge
����ֵ��        ��
�������ڣ�      2008.07
������:         ����ΰ
����޸�����:   2009.2.12  
����޸���:     �����
***************************************************************************************/
void Set_AllKindData()
{   
	
char cphm[50];

	SetExitTRMsgExitClass(GetCarKindChar(Getg_CurrentCarKindIndex()));	
	SetExitTRMsgExitType(Get_Current_Car_Type());	
		SetExitTRMsgEntrySignal(GetCPHM(cphm));
	if(0==(int)Get_G_Current_Actual_pay())
	{	
		SetExitTRMsgReceipt('0');	
	}
	else
	{	
		if(0==Getg_DisputeType())
		{	
			SetExitTRMsgReceipt('R');
			AddExitESMsgTotal_Receipt();
		}
		else
		{	
			SetExitTRMsgReceipt('0');	
		}
	}
	if(0==Getg_DisputeType())
	{	
		SetExitTRMsgActual_pay((int)Get_G_Current_Actual_pay());	
	}
	SetExitTRMsgTollFare(Get_G_Current_Toll_Fare());	
	SetExitTRMsgMethod_Pay(GetCarKindCharge(Getg_CurrentCarKindIndex()));
	if (	GetBillFlagbyIndex(Getg_CurrentCarKindIndex()))
	{
			SetBillNumber();
	}


	SetExitTRMsgDiscountRate(Getg_DiscountRate());
	SetExitTRMsgServiceCard(GetG_AbateNumber());
}
