#include "LocalIncludeFile.h"


#define _DEBUG_PRINTRT_


/******************************************************************************************************
*��ӡ��ͨѶ״̬
******************************************************************************************************/
int DevCStatePrinterState = BPLA_OK;
int DevCStatePrinterSendFlag = 1;
int GetDevCStatePrinterState()
{	
	return DevCStatePrinterState;
}
	char DevCStatePrinterState_char[4];
char *GetDevCStatePrinterState_Str()
{	
	memset(DevCStatePrinterState_char,'\0',4);	
	sprintf(DevCStatePrinterState_char,"%4d",GetDevCStatePrinterState());	
	return  DevCStatePrinterState_char;
}

void  SetDevCStatePrinterState (int InputDevCStatePrinterState)
{	
	if(BPLA_NOCHECK != InputDevCStatePrinterState)
	{	
		if( DevCStatePrinterState!=InputDevCStatePrinterState)
		{	
			DevCStatePrinterSendFlag=1;
			DevCStatePrinterState= InputDevCStatePrinterState;
			ShowDevCStatePrinterState();	

		}
	}
}

void ShowDevCStatePrinterState()
{	

	switch(DevCStatePrinterState)
	{	
		case BPLA_OK:
			//SendMsgEI( Ʊ�ݴ�ӡ��ͨ�Żָ�");	
			UI_Show_Help_Info("Ʊ�ݴ�ӡ��ͨ�Żָ�");	
			break;
		case BPLA_COMERROR:
			SendMsgEI(MSGEI_PRINTER_ERROR,MSGEI_STATUS_ERROR_OCCURRED, "Ʊ�ݴ�ӡ��ͨ�Ź���");	
			UI_Show_Help_Info("Ʊ�ݴ�ӡ��ͨ�Ź���");	
			break;
		case BPLA_NOPAPER:

			//SendMsgEvent(EVENT_TYPE_ALARM,ID_DEV_DCP,ID_STATUS_DCP_BLANK,"Ʊ�ݴ�ӡ��ȱֽ��ͨ������");	
			UI_Show_Help_Info("Ʊ�ݴ�ӡ��ȱֽ");	
			break;
	}
}
 
void RePrintBill(void)
{
	SendMsgEI(MSGEI_REPRINTBILL,MSGEI_STATUS_MSGINFO,"�ش�Ʊ��");////lzp  �ش�Ʊ�� MSGEI �¼�����
	if (!postPrinter(F))
	{
		SendMsgEI(MSGEI_PRINTER_ERROR ,MSGEI_STATUS_MSGINFO,"��ӡ������");	//lzp// ��ӡ������   MSGEI �¼�����
		UI_Show_Help_Info("��ӡ�����ϣ�");
	}
	
}
int billCount =0;
void SetbillCount(int inputbillCount)
{	
	billCount=inputbillCount;
}
int GetbillCount(void)
{	
	return billCount;
}
void createBillNumber()
{
    SetbillCount(GetbillCount()+1);	
    SetbillCount( GetbillCount()%10000);	
    writeBillNumber();	
}
void writeBillNumber()
{
    char BillNumber[10];
    FILE *fp;
    memset(BillNumber,0x00,10);	
    sprintf(BillNumber,"%04d",GetbillCount());	
    if((fp=fopen(FILENAME_SAVE_BILLNUMBER,"wt+"))==NULL)
    {
        printf("Cannot open file strike any key exit!");	
    }
    fputs(BillNumber,fp);	
    fclose(fp);	
	echoprint("%s",BillNumber);
    SendTCOMsg(MSGTCO_CMD_BILLNUMBER,BillNumber);	//������������Ʊ�ݺ���
}
void ReadBillNumber()
{
    char BillNumber[10];
    int fbillNumber;
    fbillNumber=open(FILENAME_SAVE_BILLNUMBER,O_RDONLY);	
    if(fbillNumber<0)
    {
    #ifdef SYS_LOG
        writelog(logfd,"system config file not find!\n");	
    #endif
      //createBillNumber();	
    }
	memset(BillNumber,0x00,10);
    lseek(fbillNumber,SEEK_SET,0);	
    if(read(fbillNumber,BillNumber,10)<0)
    {
        #ifdef SYS_LOG
        writelog(logfd,"system config file is emp!\n");	
        #endif
        close(fbillNumber);	
    }
  
    close(fbillNumber);	
	echoprint("%s",BillNumber);
    SetbillCount(atoi(BillNumber));	
}

BOOL _CanTestPrinter=TRUE;
BOOL GetCanTestPrinter(void )
{
	return _CanTestPrinter ;
}
char tempbillNumber_str[9];
char * GetbillNumber_str(void)
{	
	memset(tempbillNumber_str,'0',sizeof(tempbillNumber_str));	
	tempbillNumber_str[8]=0x00;
	sprintf(tempbillNumber_str,"%08d",GetbillCount());	
	return tempbillNumber_str;
}

static void SetBillAbateStly(void)
{
	if (0==strncmp(Getg_CurrentCarKindExplain(),"�Żݿ���",4) )
	{
		echoic("xxx");
		memset(g_currentPrint.Charge,0x00,10);
		sprintf(g_currentPrint.Charge,"   %3.0f",Get_G_Current_Actual_pay());
		memset(g_currentPrint.carType,0x00,10);
		sprintf(g_currentPrint.carType,"%sY",Get_Current_Car_Type());
	}
	else
	{
		memset(g_currentPrint.Charge,0x00,10);
		sprintf(g_currentPrint.Charge,"%5.0f",Get_G_Current_Actual_pay());
		memset(g_currentPrint.carType,0x00,10);
		strcpy(g_currentPrint.carType,Get_Current_Car_Type());
	}
}


BOOL postPrinter(BOOL newNillNumber)
{
	BOOL ret = T;
	TestPrintState();
	SetBillAbateStly();
	if (Getg_bPrint())
	{
		echoic("��Ʊ���%d",atoi(g_currentPrint.Charge));
		if (0!=atoi(g_currentPrint.Charge))
		{
			if (newNillNumber)
			{
				createBillNumber();
				strcpy(g_currentPrint.billNumber,GetbillNumber_str());
			}
			if (EnabledPrinter())
			{
				_CanTestPrinter=FALSE;
				
				printBill(&g_currentPrint);
				_CanTestPrinter=TRUE;
			}
		}
	}
	else
	{
		ret = F;
	}
	return ret;
}


void printBill(struct BILLPARAM *var_billparam)
{
    I_Dev_Printer_PrintBill(var_billparam);
}
void TestprintBill()
{
    I_DEV_Printer_PrintTestBill();
}
void   TestPrintState(void)
{   
	BOOL printState ;
	printState=Getg_bPrint();
	if (EnabledPrinter())
	{
		printState=I_Dev_Printer_TestStatus();
	}
	else
	{
		printState = T;
	}
	if ( printState!=Getg_bPrint())
	{
		Setg_bPrint(printState);
		
		if (Getg_bPrint())
		{
			G_CurrentSystemDevStatus.PrintStatus = 1;
		}
		else
		{
			G_CurrentSystemDevStatus.PrintStatus = 0;
		}
		SendLaneInfo_default();
	}
}

