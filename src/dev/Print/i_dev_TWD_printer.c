#include "LocalIncludeFile.h"


unsigned char TWD_printfCommand_B[3]={0x1b,0x45,0x00}; 
unsigned char TWD_printfCommand_double[3]={0x1b,0x21,0x00};
unsigned char TWD_printfCommand_Rstart[2]={0x1b,0x40}; //1B 45 
unsigned char TWD_printfCommand_cut[3]={0x1d,0x56,0x01}; // 1B 64 00
unsigned char TWD_printfCommand_GetPrinterState[3]={0x1B,0x06,0x01}; //1b 06 01 == 23 06 {00|28}
unsigned char TWD_printfCommand_LF = 0x0a;
unsigned char TWD_printfCommand_LFSp[2] ={' ', 0x0a};
unsigned char TWD_printfCommand_LineSp[3] ={0x1B,0x33,100};
#define  TWD_UNDELINEHEAD "\x1B-1\x1C-1"
#define   TWD_UNDELINEEND "\x1C-0\x1B-0"

void I_DEV_TWD_Printer_Init(void)
{
	
	if(serial_init(PRINTER_COM,B9600)<0)
	{
        echoic("打印机串口初始化失败！");		
    }
	else
	{
		echoic("打印机串口初始化成功！");		
	}
}

void I_DEV_TWD_Printer_PrintBill_OLDPrintStyle(struct BILLPARAM *var_billparam)
{
	char printContent[80];
    struct tm *rtc_time;
    time_t t = time(NULL);	
    rtc_time = localtime(&t);	
    serial_write(PRINTER_COM,TWD_printfCommand_LineSp,3);	
    memset(printContent,'\0',80);	
    sprintf(printContent,"%s%c",GetBillTitle(),10);	
	echoic("printContent %s",printContent);
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    memset(printContent,'\0',40);	
    sprintf(printContent,"               通行费收据%c",10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    serial_write(PRINTER_COM,TWD_printfCommand_Rstart,2);	
    serial_write(PRINTER_COM,TWD_printfCommand_B,3);	
    serial_write(PRINTER_COM,TWD_printfCommand_LineSp,3);	
    memset(printContent,'\0',40);	
    sprintf(printContent,"   站名         金额（元）       车型%c",10);	
	serial_write(PRINTER_COM,printContent,strlen(printContent));
    memset(printContent,'\0',40);	
	//fprintf(stderr,"strlen(printNode->Charge) = %c %c %c \n",printNode->Charge[2],printNode->Charge[3],printNode->Charge[1]);	
	if(var_billparam->Charge[3]=='/')
	{
		sprintf(printContent,"  %s        %s            %s%c",GetLanConfigPlazaDesc(),var_billparam->Charge,var_billparam->carType,10);	
	}
	else
	{
		sprintf(printContent,"  %s        %s              %s%c",GetLanConfigPlazaDesc(),var_billparam->Charge,var_billparam->carType,10);	
	}
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    memset(printContent,'\0',40);	
    sprintf(printContent," 收费员            时间          收据号%c",10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    memset(printContent,'\0',40);	
    sprintf(printContent,"  %s     %02d-%02d-%02d %02d:%02d     %s%c",GetG_Number(),rtc_time->tm_year-100, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min,var_billparam->billNumber,10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));
    serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
    serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
    serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
    serial_write(PRINTER_COM,TWD_printfCommand_Rstart,2);	
    serial_write(PRINTER_COM,TWD_printfCommand_cut,3);	
}
static void BillHead(char  *SubTitle)
{
	char printContent[80];
	serial_write(PRINTER_COM,TWD_printfCommand_LineSp,3);	
	memset(printContent,'\0',80);	
	sprintf(printContent,"        新疆维吾尔自治区政府还贷公路%c",10);
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));
	sprintf(printContent,"            车辆通行费专用票据%c",10);
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));

	memset(printContent,'\0',80);	
	sprintf(printContent,SubTitle,10);	
	echoic("printContent %s",printContent);
	//serial_write(PRINTER_COM,printContent,strlen(printContent));
	memset(printContent,'\0',80);	
	sprintf(printContent,"   收费站名称:"TWD_UNDELINEHEAD"%-24s"TWD_UNDELINEEND"%c",GetLanConfigPlazaDesc(),10);		
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));	

}

 // "TWD_UNDELINEEND"
static void BillEnd(struct BILLPARAM *var_billparam)
{
	char printContent[80];
	struct tm *rtc_time;
	time_t t = time(NULL);	
	rtc_time = localtime(&t);	
	memset(printContent,'\0',80);	
	sprintf(printContent,"   收费员号:"TWD_UNDELINEHEAD"  %-6s  "TWD_UNDELINEEND" 时间:"TWD_UNDELINEHEAD"%02d-%02d-%02d %02d:%02d"TWD_UNDELINEEND"%c",GetG_Number(),rtc_time->tm_year-100, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min,10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));
	memset(printContent,'\0',80);	
	sprintf(printContent,"   NO:"TWD_UNDELINEHEAD"   %-14s"TWD_UNDELINEEND"%c",var_billparam->billNumber,10);	
	echoic("printContent %s",printContent);

	serial_write(PRINTER_COM,printContent,strlen(printContent));
	serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
	serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
	serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
	serial_write(PRINTER_COM,TWD_printfCommand_Rstart,2);	
	serial_write(PRINTER_COM,TWD_printfCommand_cut,3);	
}


void I_DEV_TWD_Printer_PrintBill_Weight_CarType_BUS_rintStyle(struct BILLPARAM *var_billparam)
{
	char printContent[200];
		
	BillHead("              作报销凭证(客车)%c");
	memset(printContent,'\0',200);	
	sprintf(printContent,"   收费金额:"TWD_UNDELINEHEAD"  %-6d"TWD_UNDELINEEND"元 车型:"TWD_UNDELINEHEAD" %d"TWD_UNDELINEEND""TWD_UNDELINEHEAD"至"TWD_UNDELINEEND""TWD_UNDELINEHEAD"%d  "TWD_UNDELINEEND"座位%c",atoi(var_billparam->Charge),(atoi(var_billparam->carType)-1)*10+1,atoi(var_billparam->carType)*10,10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));	
	BillEnd(var_billparam);
	
}

void I_DEV_TWD_Printer_PrintBill_Weight_CarType_rintStyle(struct BILLPARAM *var_billparam)
{
	char printContent[80];
		
	BillHead("            作报销凭证(按车型分类)%c");	
	memset(printContent,'\0',80);	
	sprintf(printContent,"   收费金额:"TWD_UNDELINEHEAD"  %-6d"TWD_UNDELINEEND"元 车型:"TWD_UNDELINEHEAD" %5d   "TWD_UNDELINEEND"型%c",atoi(var_billparam->Charge),atoi(var_billparam->carType),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));	
	BillEnd(var_billparam);
	
}

void I_DEV_TWD_Printer_PrintBill_NewPrintStyle(struct BILLPARAM *var_billparam)
{
	char printContent[80];
   	 	
    BillHead("             作报销凭证(货车)%c");
    memset(printContent,'\0',80);	
    sprintf(printContent,"   车型:"TWD_UNDELINEHEAD"      %s     "TWD_UNDELINEEND"型 承载标准:"TWD_UNDELINEHEAD"%5.0f"TWD_UNDELINEEND"吨%c",var_billparam->carType,GetWeightContext_WeightLimit_ByTon(),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));	

    memset(printContent,'\0',80);	
    sprintf(printContent,"   收费金额:"TWD_UNDELINEHEAD"  %-6d"TWD_UNDELINEEND"元 超载:"TWD_UNDELINEHEAD" %5.0f   "TWD_UNDELINEEND"吨%c",atoi(var_billparam->Charge),(float)GetWeightContext_OverLoadWeight(),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));	

	memset(printContent,'\0',80);	
	sprintf(printContent,"   超载比率:"TWD_UNDELINEHEAD"%5.0f   "TWD_UNDELINEEND"％%c",GetWeightContext_OverLoadWeightRate(),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));
	BillEnd(var_billparam);
   
}
void I_DEV_TWD_Printer_PrintBill_PromptPrintStyle(struct BILLPARAM *var_billparam)
{
	char printContent[80];
     	
	BillHead("           不作报销凭证(货车)%c");
	memset(printContent,'\0',80);	
	sprintf(printContent,"   车型:"TWD_UNDELINEHEAD"      %s     "TWD_UNDELINEEND"型 承载标准:"TWD_UNDELINEHEAD"%5.0f"TWD_UNDELINEEND"吨%c",var_billparam->carType,GetWeightContext_WeightLimit_ByTon(),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));

	memset(printContent,'\0',80);	
	sprintf(printContent,"   收费金额:"TWD_UNDELINEHEAD"  %-6d"TWD_UNDELINEEND"元 超载:"TWD_UNDELINEHEAD" %5.0f   "TWD_UNDELINEEND"吨%c",atoi(var_billparam->Charge),GetWeightContext_OverLoadWeight(),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));	

	memset(printContent,'\0',80);	
	sprintf(printContent,"   超载比率:"TWD_UNDELINEHEAD"%5.0f   "TWD_UNDELINEEND"％%c",GetWeightContext_OverLoadWeightRate(),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,printContent,strlen(printContent));
	BillEnd(var_billparam);
}
void I_DEV_TWD_Printer_PrintBill_BothNewandPromptPrintStyl(struct BILLPARAM *var_billparam)
{
	I_DEV_TWD_Printer_PrintBill_NewPrintStyle(var_billparam);
	I_DEV_TWD_Printer_PrintBill_PromptPrintStyle(var_billparam);
}
void I_DEV_TWD_Printer_PrintBill(struct BILLPARAM *var_billparam)
{
    switch(GetPrinterMode())
	{
	case OLDPrintStyle:
		I_DEV_TWD_Printer_PrintBill_OLDPrintStyle(var_billparam);
		break;
	case NewPrintStyle:
		if(GetWeightCarClass() == WeightCarClassBUS)
		{
			I_DEV_TWD_Printer_PrintBill_Weight_CarType_BUS_rintStyle(var_billparam);
		}
		else if(GetWeightCarClass() == WeightCarClassTruckISNotUseWeight)
		{
			I_DEV_TWD_Printer_PrintBill_Weight_CarType_rintStyle(var_billparam);
		}
		else
		{
			I_DEV_TWD_Printer_PrintBill_NewPrintStyle(var_billparam);
		}
		break;
	case PromptPrintStyle:
		I_DEV_TWD_Printer_PrintBill_PromptPrintStyle(var_billparam);
		break;
	case BothNewandPromptPrintStyl:		
		I_DEV_TWD_Printer_PrintBill_BothNewandPromptPrintStyl(var_billparam);
		break;
	default :
		I_DEV_TWD_Printer_PrintBill_NewPrintStyle(var_billparam);
		break;
	}
}
void I_DEV_TWD_Printer_Close(void)
{
    serial_close(PRINTER_COM);	
}


BOOL I_DEV_TWD_Printer_TestStatus(void)
{
	BOOL printState ;
	int count;
	char getPrintState[3];
	unsigned char TWD_printfCommand_GetPrinterState[3]={0x10,0x04,0x01};
	serial_write(PRINTER_COM,TWD_printfCommand_GetPrinterState,3);
	usleep(100);
	memset(getPrintState,0x00,3);
	count = serial_read(PRINTER_COM,getPrintState,3);	
	//echoic("count = [%d] getPrintState = [%d]",count,getPrintState[0]);
	if ( -1==count || 22!=getPrintState[0])
	{
		printState = F;
	}
	else
	{
		printState = T;
	}
	return printState;
}



void I_DEV_TWD_Printer_PrintTestBill(void)
{
    char printContent[80];
    struct tm *rtc_time;
     struct  BILLPARAM *printNode;
    struct BILLPARAM Temp;
    time_t t = time(NULL);	
    strcpy(Temp.carType,"1");	
    strcpy(Temp.carKind,"测试");	
    strcpy(Temp.Charge,"888");	
    strcpy(Temp.billNumber,"88888888888888888");	
    printNode = &Temp;
    rtc_time = localtime(&t);	
    serial_write(PRINTER_COM,TWD_printfCommand_B,3);	
    serial_write(PRINTER_COM,TWD_printfCommand_double,3);	
    serial_write(PRINTER_COM,TWD_printfCommand_LineSp,3);	
#ifdef SYS_DEBUG
    fprintf(stderr,"printNode->billNumber=%s\n",printNode->billNumber);	
    fprintf(stderr,"carTem=%d\n",carTem);
#endif
    serial_write(PRINTER_COM,TWD_printfCommand_B,3);	
    serial_write(PRINTER_COM,TWD_printfCommand_double,3);	
    serial_write(PRINTER_COM,TWD_printfCommand_LineSp,3);	
    memset(printContent,'\0',40);	
    sprintf(printContent,"        新疆维吾尔自治区公路车辆%c",10);	
    //sprintf(printContent,"               通行费收据%c",10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    memset(printContent,'\0',40);	
    sprintf(printContent,"               通行费收据%c",10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    //serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
    serial_write(PRINTER_COM,TWD_printfCommand_Rstart,2);	
    serial_write(PRINTER_COM,TWD_printfCommand_B,3);	
    serial_write(PRINTER_COM,TWD_printfCommand_LineSp,3);	
    memset(printContent,'\0',40);	
    sprintf(printContent,"   站名         金额（元）       吨位%c",10);	 serial_write(PRINTER_COM,printContent,strlen(printContent));	
    memset(printContent,'\0',40);	
    sprintf(printContent,"   %s         %s            %s%c",GetLanConfigPlazaDesc(),printNode->Charge,printNode->carType,10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    memset(printContent,'\0',40);	
    sprintf(printContent,"  收费员          时间          收据号%c",10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    memset(printContent,'\0',40);	
    sprintf(printContent,"  %s  %02d-%02d-%02d %02d:%02d %s%c",GetG_Number(),rtc_time->tm_year-100, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min,printNode->billNumber,10);	
    serial_write(PRINTER_COM,printContent,strlen(printContent));	
    serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
    serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
    serial_write(PRINTER_COM,(char *)&TWD_printfCommand_LF,1);	
    serial_write(PRINTER_COM,TWD_printfCommand_Rstart,2);	
    serial_write(PRINTER_COM,TWD_printfCommand_cut,3);	
}
