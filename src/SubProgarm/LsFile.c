#include "LocalIncludeFile.h"
#include "common_main.h"
int FileExists(char *filename)
{	
	return (access(filename, 0) == 0);	
}

/******************************************************************************************************
* 创建指定文件名的文件
******************************************************************************************************/
void CreateMsgFile(char *FilePath,int FileLength)
{	
	FILE *fp;
	char *temp;
	if((fp=fopen(FilePath,"wt+"))==NULL)
	{	
		printf("Cannot open file strike any key exit!");	
		//exit(1);	
	}
	if(FileLength>0)
	{	
		temp =(char*) malloc(FileLength);	
		memset(temp,'0',FileLength);	
		fwrite(temp,FileLength,1,fp);	
		free(temp);	
	}
	fclose(fp);	
}

void LsExitEs(void)
{
	struct MSG_EXITES *MsgExitES;
	int FilePointer;
	if(!FileExists(FILENAME_ASVE_EXITES))
	{	
		CreateMsgFile(FILENAME_ASVE_EXITES,sizeof(struct MSG_EXITES));	
	}
	FilePointer = open(FILENAME_ASVE_EXITES,O_RDWR);	
	MsgExitES = (struct MSG_EXITES*)mmap(0,sizeof(struct MSG_EXITES),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);	
    printf("\n");
	fprintf(stderr,"MsgType           :%c\nLaneMode          :%d\nLaneType          :%c\nNetNo             :%1.2s\nPlazaNo           :%1.2s\n"
            "LaneNo            :%1.3s\nWorkStaus         :%c\nCollectorType     :%c\nCollector         :%1.6s\n",
            MsgExitES->EXITES_HEAD.MsgType,
            MsgExitES->EXITES_HEAD.LaneMode,
            MsgExitES->EXITES_HEAD.LaneType,
            MsgExitES->EXITES_HEAD.NetNo,
            MsgExitES->EXITES_HEAD.PlazaNo,
            MsgExitES->EXITES_HEAD.LaneNo,
            MsgExitES->WorkStaus,
            MsgExitES->CollectorType,
            MsgExitES->EXITES_HEAD.Collector);
    fprintf(stderr,"YYYYMMDDHHMMSS    :%10.14s\nBS_YMDHM          :%10.14s\n"
                   "BS_TicketNo       :%6.8s\nTotal_Traffic     :%6.10s\nTotal_Violation   :%6.10s\n"
                   "Total_Emergency   :%6.10s\nTotal_MotorCade   :%6.10s\n",
            MsgExitES->EXITES_HEAD.YYYYMMDDHHMMSS,
            MsgExitES->BS_YMDHM,
            MsgExitES->BS_TicketNo,
            MsgExitES->Total_Traffic,
            MsgExitES->Total_Violation,
            MsgExitES->Total_Emergency,
            MsgExitES->Total_MotorCade);
	fprintf(stderr,"Total_U           :%6.10s\nTotal_IllegalU    :%6.10s\nTotal_J           :%6.10s\nTotal_IllegalJ    :%6.10s\n"
                   "TotalOfficeCard   :%6.10s\nTotalOfficeNoCard :%6.10s\nTotal_OverRide    :%6.10s\nTotal_ICCard      :%6.10s\n",
            MsgExitES->Total_U,
            MsgExitES->Total_IllegalU,
            MsgExitES->Total_J,
            MsgExitES->Total_IllegalJ,
            MsgExitES->TotalOfficeCard,
            MsgExitES->TotalOfficeNoCard,
            MsgExitES->Total_OverRide,
            MsgExitES->Total_ICCard);
	fprintf(stderr,"Total_ICStoreBox  :%6.10s\nTotal_WrongIC     :%6.10s\nTotal_RuinIC      :%6.10s\nTotal_NoIC        :%6.10s\n"
                   "Total_ALARM       :%6.10s\nTotal_Receipt     :%6.10s\nES_TicketNo       :%6.8s\nICBox             :%1.4s\n",
            MsgExitES->Total_ICStoreBox,
            MsgExitES->Total_WrongIC,
            MsgExitES->Total_RuinIC,
            MsgExitES->Total_NoIC,
            MsgExitES->Total_ALARM,
            MsgExitES->Total_Receipt,
            MsgExitES->ES_TicketNo,
            MsgExitES->ICBox);
	fprintf(stderr,"Total_DebtTraffic :%6.10s\nTotal_Debt        :%6.10s\nCounter1          :%6.10s\nCounter2          :%6.10s\nCounter3          :%6.10s\n"
                   "Counter4          :%6.10s\nCounter5          :%6.10s\n",
            MsgExitES->Total_DebtTraffic,
            MsgExitES->Total_Debt,
            MsgExitES->Counter1,
            MsgExitES->Counter2,
            MsgExitES->Counter3,
            MsgExitES->Counter4,
            MsgExitES->Counter5);
    fprintf(stderr,"Total_Cash        :%6.12s\nCashClass1        :%6.12s\nCashClass2        :%6.12s\nCashClass3        :%6.12s\nCashClass4        :%6.12s\n"
                   "CashClass5        :%6.12s\nCashClass6        :%6.12s\nCashClass7        :%6.12s\nTotal_Preferential:%6.12s\nLocalPreferential1:%6.12s\n"
                   "LocalPreferential2:%6.12s\nLocalPreferential3:%6.12s\nLocalPreferential4:%6.12s\nLocalPreferential5:%6.12s\nLocalPreferential6:%6.12s\n"
                   "LocalPreferential7:%6.12s\nTotal_svc         :%6.12s\nsvcClass1         :%6.12s\nsvcClass2         :%6.12s\nsvcClass3         :%6.12s\n"
                   "svcClass4         :%6.12s\nsvcClass5         :%6.12s\nsvcClass6         :%6.12s\nsvcClass7         :%6.12s\nTotal_Credit      :%6.12s\n"
                   "CreditClass1      :%6.12s\nCreditClass2      :%6.12s\nCreditClass3      :%6.12s\nCreditClass4      :%6.12s\nCreditClass5      :%6.12s\n"
                   "CreditClass6      :%6.12s\nCreditClass7      :%6.12s\nTotal_Mil         :%6.12s\nMilClass1         :%6.12s\nMilClass2         :%6.12s\n"
                   "MilClass3         :%6.12s\nMilClass4         :%6.12s\nMilClass5         :%6.12s\nMilClass6         :%6.12s\nMilClass7         :%6.12s\n"
                   "Total_Off         :%6.12s\nOffClass1         :%6.12s\nOffClass2         :%6.12s\nOffClass3         :%6.12s\nOffClass4         :%6.12s\n"
                   "OffClass5         :%6.12s\nOffClass6         :%6.12s\nOffClass7         :%6.12s\nTotal_Police      :%6.12s\nPoliceClass1      :%6.12s\n"
                   "PoliceClass2      :%6.12s\nPoliceClass3      :%6.12s\nPoliceClass4      :%6.12s\nPoliceClass5      :%6.12s\nPoliceClass6      :%6.12s\n"
                   "PoliceClass7      :%6.12s\nTotal_MonthTicket :%6.12s\nMonthTicket1      :%6.12s\nMonthTicket2      :%6.12s\nMonthTicket3      :%6.12s\n"
                   "MonthTicket4      :%6.12s\nMonthTicket5      :%6.12s\nMonthTicket6      :%6.12s\nMonthTicket7      :%6.12s\nTotal_Paid        :%6.12s\n"
                   "PaidClass1        :%6.12s\nPaidClass2        :%6.12s\nPaidClass3        :%6.12s\nPaidClass4        :%6.12s\nPaidClass5        :%6.12s\n"
                   "PaidClass6        :%6.12s\nPaidClass7        :%6.12s\nTotal_PreferPaid  :%6.12s\nPreferPaidClass1  :%6.12s\nPreferPaidClass2  :%6.12s\n"
                   "PreferPaidClass3  :%6.12s\nPreferPaidClass4  :%6.12s\nPreferPaidClass5  :%6.12s\nPreferPaidClass6  :%6.12s\nPreferPaidClass7  :%6.12s\n"
                   "Total_svcPaid     :%6.12s\nsvcPaidClass1     :%6.12s\nsvcPaidClass2     :%6.12s\nsvcPaidClass3     :%6.12s\nsvcPaidClass4     :%6.12s\n"
                   "svcPaidClass5     :%6.12s\nsvcPaidClass6     :%6.12s\nsvcPaidClass7     :%6.12s\nTotal_CreditPaid  :%6.12s\nCreditPaidClass1  :%6.12s\n"
                   "CreditPaidClass2  :%6.12s\nCreditPaidClass3  :%6.12s\nCreditPaidClass4  :%6.12s\nCreditPaidClass5  :%6.12s\nCreditPaidClass6  :%6.12s\n"
                   "CreditPaidClass7  :%6.12s\nWorkTime          :%6.10s\nShift             :%c\n",
            MsgExitES->CarInfoContext[0].Kind_Total,
            MsgExitES->CarInfoContext[0].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[0].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[0].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[0].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[0].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[0].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[0].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[1].Kind_Total,
            MsgExitES->CarInfoContext[1].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[1].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[1].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[1].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[1].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[1].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[1].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[2].Kind_Total,
            MsgExitES->CarInfoContext[2].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[2].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[2].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[2].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[2].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[2].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[2].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[3].Kind_Total,
            MsgExitES->CarInfoContext[3].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[3].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[3].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[3].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[3].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[3].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[3].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[4].Kind_Total,
            MsgExitES->CarInfoContext[4].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[4].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[4].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[4].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[4].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[4].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[4].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[5].Kind_Total,
            MsgExitES->CarInfoContext[5].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[5].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[5].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[5].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[5].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[5].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[5].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[6].Kind_Total,
            MsgExitES->CarInfoContext[6].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[6].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[6].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[6].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[6].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[6].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[6].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[7].Kind_Total,
            MsgExitES->CarInfoContext[7].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[7].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[7].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[7].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[7].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[7].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[7].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[8].Kind_Total,
            MsgExitES->CarInfoContext[8].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[8].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[8].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[8].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[8].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[8].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[8].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[9].Kind_Total,
            MsgExitES->CarInfoContext[9].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[9].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[9].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[9].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[9].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[9].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[9].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[10].Kind_Total,
            MsgExitES->CarInfoContext[10].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[10].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[10].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[10].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[10].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[10].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[10].CarTypes[6].CarType,
            MsgExitES->CarInfoContext[11].Kind_Total,
            MsgExitES->CarInfoContext[11].CarTypes[0].CarType,
            MsgExitES->CarInfoContext[11].CarTypes[1].CarType,
            MsgExitES->CarInfoContext[11].CarTypes[2].CarType,
            MsgExitES->CarInfoContext[11].CarTypes[3].CarType,
            MsgExitES->CarInfoContext[11].CarTypes[4].CarType,
            MsgExitES->CarInfoContext[11].CarTypes[5].CarType,
            MsgExitES->CarInfoContext[11].CarTypes[6].CarType,
            MsgExitES->WorkTime,
            MsgExitES->Shift);
}

void LsExitHt(void)
{
    struct MSG_EXITHT *MsgExitHt;
    int FilePointer;
    if(!FileExists(FILENAME_ASVE_EXITHT)) 
    {
        CreateMsgFile(FILENAME_ASVE_EXITHT,sizeof(struct MSG_EXITHT));
    }
    FilePointer=open(FILENAME_ASVE_EXITHT,O_RDWR);
	MsgExitHt = (struct MSG_EXITHT*)mmap(0,sizeof(struct MSG_EXITHT),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);	
    printf("\n");
    fprintf(stderr,"Collector         :%4.6s\nLaneMode          :%d\nLaneNo            :%1.3s\nLaneType          :%c\nMsgType           :%c\n"
            "NetNo             :%1.2s\nPlazaNo           :%1.2s\nYYYYMMDDHHMMSS    :%10.14s\n",
            MsgExitHt->EXITES_HEAD.Collector,
            MsgExitHt->EXITES_HEAD.LaneMode,
            MsgExitHt->EXITES_HEAD.LaneNo,
            MsgExitHt->EXITES_HEAD.LaneType,
            MsgExitHt->EXITES_HEAD.MsgType,
            MsgExitHt->EXITES_HEAD.NetNo,
            MsgExitHt->EXITES_HEAD.PlazaNo,
            MsgExitHt->EXITES_HEAD.YYYYMMDDHHMMSS);
    fprintf(stderr,"Total_Cash        :%6.12s\nCashClass1        :%6.12s\nCashClass2        :%6.12s\nCashClass3        :%6.12s\nCashClass4        :%6.12s\n"
                   "CashClass5        :%6.12s\nCashClass6        :%6.12s\nCashClass7        :%6.12s\nTotal_Preferential:%6.12s\nLocalPreferential1:%6.12s\n"
                   "LocalPreferential2:%6.12s\nLocalPreferential3:%6.12s\nLocalPreferential4:%6.12s\nLocalPreferential5:%6.12s\nLocalPreferential6:%6.12s\n"
                   "LocalPreferential7:%6.12s\nTotal_svc         :%6.12s\nsvcClass1         :%6.12s\nsvcClass2         :%6.12s\nsvcClass3         :%6.12s\n"
                   "svcClass4         :%6.12s\nsvcClass5         :%6.12s\nsvcClass6         :%6.12s\nsvcClass7         :%6.12s\nTotal_Credit      :%6.12s\n"
                   "CreditClass1      :%6.12s\nCreditClass2      :%6.12s\nCreditClass3      :%6.12s\nCreditClass4      :%6.12s\nCreditClass5      :%6.12s\n"
                   "CreditClass6      :%6.12s\nCreditClass7      :%6.12s\nTotal_Mil         :%6.12s\nMilClass1         :%6.12s\nMilClass2         :%6.12s\n"
                   "MilClass3         :%6.12s\nMilClass4         :%6.12s\nMilClass5         :%6.12s\nMilClass6         :%6.12s\nMilClass7         :%6.12s\n"
                   "Total_Off         :%6.12s\nOffClass1         :%6.12s\nOffClass2         :%6.12s\nOffClass3         :%6.12s\nOffClass4         :%6.12s\n"
                   "OffClass5         :%6.12s\nOffClass6         :%6.12s\nOffClass7         :%6.12s\nTotal_Police      :%6.12s\nPoliceClass1      :%6.12s\n"
                   "PoliceClass2      :%6.12s\nPoliceClass3      :%6.12s\nPoliceClass4      :%6.12s\nPoliceClass5      :%6.12s\nPoliceClass6      :%6.12s\n"
                   "PoliceClass7      :%6.12s\nTotal_MonthTicket :%6.12s\nMonthTicket1      :%6.12s\nMonthTicket2      :%6.12s\nMonthTicket3      :%6.12s\n"
                   "MonthTicket4      :%6.12s\nMonthTicket5      :%6.12s\nMonthTicket6      :%6.12s\nMonthTicket7      :%6.12s\nTotal_Paid        :%6.12s\n"
                   "PaidClass1        :%6.12s\nPaidClass2        :%6.12s\nPaidClass3        :%6.12s\nPaidClass4        :%6.12s\nPaidClass5        :%6.12s\n"
                   "PaidClass6        :%6.12s\nPaidClass7        :%6.12s\nTotal_PreferPaid  :%6.12s\nPreferPaidClass1  :%6.12s\nPreferPaidClass2  :%6.12s\n"
                   "PreferPaidClass3  :%6.12s\nPreferPaidClass4  :%6.12s\nPreferPaidClass5  :%6.12s\nPreferPaidClass6  :%6.12s\nPreferPaidClass7  :%6.12s\n"
                   "Total_svcPaid     :%6.12s\nsvcPaidClass1     :%6.12s\nsvcPaidClass2     :%6.12s\nsvcPaidClass3     :%6.12s\nsvcPaidClass4     :%6.12s\n"
                   "svcPaidClass5     :%6.12s\nsvcPaidClass6     :%6.12s\nsvcPaidClass7     :%6.12s\nTotal_CreditPaid  :%6.12s\nCreditPaidClass1  :%6.12s\n"
                   "CreditPaidClass2  :%6.12s\nCreditPaidClass3  :%6.12s\nCreditPaidClass4  :%6.12s\nCreditPaidClass5  :%6.12s\nCreditPaidClass6  :%6.12s\n"
                   "CreditPaidClass7  :%6.12s\nOpentime          :%6.10s\ntotal_emergency   :%6.10s\ntotal_official    :%6.10s\nTotal_Traffic     :%6.10s\nTotal_Violation   :%6.10s\n",                
            MsgExitHt->CarInfoContext[0].Kind_Total,
            MsgExitHt->CarInfoContext[0].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[0].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[0].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[0].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[0].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[0].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[0].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[1].Kind_Total,
            MsgExitHt->CarInfoContext[1].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[1].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[1].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[1].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[1].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[1].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[1].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[2].Kind_Total,
            MsgExitHt->CarInfoContext[2].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[2].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[2].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[2].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[2].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[2].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[2].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[3].Kind_Total,
            MsgExitHt->CarInfoContext[3].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[3].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[3].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[3].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[3].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[3].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[3].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[4].Kind_Total,
            MsgExitHt->CarInfoContext[4].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[4].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[4].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[4].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[4].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[4].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[4].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[5].Kind_Total,
            MsgExitHt->CarInfoContext[5].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[5].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[5].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[5].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[5].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[5].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[5].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[6].Kind_Total,
            MsgExitHt->CarInfoContext[6].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[6].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[6].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[6].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[6].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[6].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[6].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[7].Kind_Total,
            MsgExitHt->CarInfoContext[7].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[7].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[7].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[7].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[7].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[7].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[7].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[8].Kind_Total,
            MsgExitHt->CarInfoContext[8].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[8].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[8].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[8].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[8].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[8].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[8].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[9].Kind_Total,
            MsgExitHt->CarInfoContext[9].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[9].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[9].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[9].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[9].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[9].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[9].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[10].Kind_Total,
            MsgExitHt->CarInfoContext[10].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[10].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[10].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[10].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[10].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[10].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[10].CarTypes[6].CarType,
            MsgExitHt->CarInfoContext[11].Kind_Total,
            MsgExitHt->CarInfoContext[11].CarTypes[0].CarType,
            MsgExitHt->CarInfoContext[11].CarTypes[1].CarType,
            MsgExitHt->CarInfoContext[11].CarTypes[2].CarType,
            MsgExitHt->CarInfoContext[11].CarTypes[3].CarType,
            MsgExitHt->CarInfoContext[11].CarTypes[4].CarType,
            MsgExitHt->CarInfoContext[11].CarTypes[5].CarType,
            MsgExitHt->CarInfoContext[11].CarTypes[6].CarType,
            MsgExitHt->Opentime,
            MsgExitHt->total_emergency,
            MsgExitHt->total_official,
            MsgExitHt->Total_Traffic,
            MsgExitHt->Total_Violation);
}

void TrafficHour(void)
{
    struct MSG_HOUR *MsgHour;
    int FilePointer;
    if(!FileExists(FILENAME_SAVE_TrafficHour)) 
    {
        CreateMsgFile(FILENAME_SAVE_TrafficHour,sizeof(struct MSG_HOUR));
    }
    FilePointer=open(FILENAME_SAVE_TrafficHour,O_RDWR);
	MsgHour = (struct MSG_HOUR*)mmap(0,sizeof(struct MSG_HOUR),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);	
    printf("\n");
    fprintf(stderr,"HourTime:%6.10s\ntmGreen :%6.10s\n",MsgHour->HourTime,MsgHour->tmGreen);
}
void ImageHeader(void)
{
    struct MSG_IMAGE *MsgImage;
    int FilePointer;
    if(!FileExists(FILENAME_SAVE_ImageHeader)) 
    {
        CreateMsgFile(FILENAME_SAVE_ImageHeader,sizeof(struct MSG_IMAGE));
    }
    FilePointer=open(FILENAME_SAVE_ImageHeader,O_RDWR);
    MsgImage=(struct MSG_IMAGE*)mmap(0,sizeof(struct MSG_IMAGE),PROT_READ|PROT_WRITE,MAP_SHARED,FilePointer,0);
    printf("\n");
    fprintf(stderr,"NetWork     :%1.2s\nPlaza       :%1.2s\nCollector   :%4.6s\nYear        :%2.4s\nDay         :%2.4s\nYMD         :%6.8s\n"
                   "Hour        :%4.6s\nTime        :%10.14s\nEntryNetwork:%1.2s\nEntryPlaza  :%1.2s\nClass       :%c\nType        :%c\n"
                   "LaneName    :%2.3s\nLaneType    :%c\nPictureNum  :%6.10s\nSubTrans    :%c\nTollFare    :%1.4s\nTrans       :%1.4s\nStatus      :%c\n",
            MsgImage->NetWork,
            MsgImage->Plaza,
            MsgImage->Collector,
            MsgImage->Year,
            MsgImage->Day,
            MsgImage->YMD,
            MsgImage->Hour,
            MsgImage->Time,
            MsgImage->EntryNetwork,
            MsgImage->EntryPlaza,
            MsgImage->Class,
            MsgImage->Type,
            MsgImage->LaneName,
            MsgImage->LaneType,
            MsgImage->PictureNum,
            MsgImage->SubTrans,      
            MsgImage->TollFare,
            MsgImage->Trans,
            MsgImage->Status
            );
}
void ParameterVersion(void)
{
    struct ParameterVersion *PVersion;
    int FilePointer;
    if(!FileExists(FILENAME_SAVE_ParameterVersion)) 
    {
        CreateMsgFile(FILENAME_SAVE_ParameterVersion,sizeof(struct ParameterVersion));
    }
    FilePointer=open(FILENAME_SAVE_ParameterVersion,O_RDWR);
    PVersion=(struct ParameterVersion *)mmap(0,sizeof(struct ParameterVersion),PROT_READ|PROT_WRITE,MAP_SHARED,FilePointer,0);
    printf("\n");
    fprintf(stderr,"Collect:%s\n",PVersion->Collect);
}
void BillNumber(void)
{
    char *BillNumber;
    int FilePointer;
    if(!FileExists(FILENAME_SAVE_BILLNUMBER)) 
    {
        CreateMsgFile(FILENAME_SAVE_BILLNUMBER,sizeof(BillNumber));
    }
    FilePointer=open(FILENAME_SAVE_BILLNUMBER,O_RDWR);
    BillNumber=mmap(0,sizeof(BillNumber),PROT_READ|PROT_WRITE,MAP_SHARED,FilePointer,0);
    printf("\n");
    fprintf(stderr,"BillNumber:%s\n",BillNumber);
}
int main(int argc ,char *argv[])
{
	int i;
    char *s;
	
	for(i=1;i<argc;i++)
	{
        s=argv[i];
       if(i>=1) 
       {
           if(strcmp(s,"ES")==0) 
           {
               printf("\nYou are viewing the table name is ExitEs:\n");
               LsExitEs();
               fprintf(stderr,"\nargv[%d]=%s\n\n",i,argv[i]);
           }
           else 
           if(strcmp(s,"HT")==0) 
           {
               printf("\nYou are viewing the table name is ExitHt:\n");
               LsExitHt();
               fprintf(stderr,"\nargv[%d]=%s\n\n",i,argv[i]);
           }
           else if(strcmp(s,"Hour")==0)
           {
               printf("\nYou are viewing the table name is TrafficHour:\n");
               TrafficHour();
               fprintf(stderr,"\nargv[%d]=%s\n\n",i,argv[i]);
           }
           else if(strcmp(s,"Image")==0)
           {
               printf("\nYou are viewing the table name is ImageHeader:\n");
               ImageHeader();
               fprintf(stderr,"\nargv[%d]=%s\n\n",i,argv[i]);
           }
           else if(strcmp(s,"PV")==0) 
           {
               printf("\nYou are viewing the table name is ParameterVersion:\n");
               ParameterVersion();
               fprintf(stderr,"\nargv[%d]=%s\n\n",i,argv[i]);
           }
           else if(strcmp(s,"BN")==0) 
           {
               printf("\nYou are viewing the table name is BillNumber:\n");
               BillNumber();
               fprintf(stderr,"\nargv[%d]=%s\n\n",i,argv[i]);
           }
           else 
           {
               printf("the parameter is not!\nFor more information:\n	             "
                      "ES:it help you to View ExitEs's information;\n	             "
                      "HT:it help you to View EXITHT's information;\n	             "
                      "BN:it help you to view BillNumber's information;\n	             "
                      "PV:it help you to view PatameterVersion's information;\n	             "
                      "Image:it help you to view ImageHeader's information;\n	             "
                      "Hour:it help you to view TrafficHour's information;\n");
           }
        }
    }
       if(argc==1) 
         {
           printf("Please enter the parameters!\n			    "
                  "ES:it help you to View ExitEs's information;\n			    "
                  "HT:it help you to View EXITHT's information;\n"
                  "			    BN:it help you to view BillNumber's information;\n"
                  "			    PV:it help you to view PatameterVersion's information;\n"
                  "			    Image:it help you to view ImageHeader's information;\n"
                  "			    Hour:it help you to view TrafficHour's information;\n");
         }
	return 0; 
}
