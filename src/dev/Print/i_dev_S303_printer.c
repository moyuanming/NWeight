#include "LocalIncludeFile.h"


unsigned char S303_printfCommand_B[3]={0x1b,0x45,0x00};
unsigned char S303_printfCommand_double[3]={0x1b,0x21,0x00};
unsigned char S303_printfCommand_Rstart[2]={0x1b,0x40};
unsigned char S303_printfCommand_cut[3]={0x1d,0x56,0x01};
unsigned char S303_printfCommand_GetPrinterState[3]={0x10,0x04,0x01};
unsigned char S303_printfCommand_LF = 0x0a;
unsigned char S303_printfCommand_LFSp[2] ={' ', 0x0a};
unsigned char S303_printfCommand_LineSp[3] ={0x1B,0x33,100};



void I_DEV_S303_Printer_PrintBill(struct BILLPARAM *var_billparam)
{
	char printContent[80];
	struct tm *rtc_time;
	time_t t = time(NULL);	
	rtc_time = localtime(&t);	
	serial_write(PRINTER_COM,S303_printfCommand_LineSp,3);	
	memset(printContent,'\0',80);	
	sprintf(printContent,"%s%c",GetBillTitle(),10);	
	echoic("printContent %s",printContent);
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	memset(printContent,'\0',40);	
	sprintf(printContent,"             Test通行费收据%c",10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	serial_write(PRINTER_COM,S303_printfCommand_Rstart,2);	
	serial_write(PRINTER_COM,S303_printfCommand_B,3);	

	serial_write(PRINTER_COM,S303_printfCommand_LineSp,3);	

	memset(printContent,'\0',40);	

	sprintf(printContent,"   站名         金额（元）       车型%c",10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	


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

	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	


	memset(printContent,'\0',40);	
	sprintf(printContent," 收费员            时间          收据号%c",10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	


	memset(printContent,'\0',40);	
	sprintf(printContent,"  %s     %02d-%02d-%02d %02d:%02d     %s%c",GetG_Number(),rtc_time->tm_year-100, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min,var_billparam->billNumber,10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	


	serial_write(PRINTER_COM,(unsigned char * )&S303_printfCommand_LF,1);	
	serial_write(PRINTER_COM,(unsigned char * )&S303_printfCommand_LF,1);	
	serial_write(PRINTER_COM,(unsigned char * )&S303_printfCommand_LF,1);	
	serial_write(PRINTER_COM,S303_printfCommand_Rstart,2);	
	serial_write(PRINTER_COM,S303_printfCommand_cut,3);	
}

void I_DEV_S303_Printer_Close(void)
{
	serial_close(PRINTER_COM);	
}


BOOL I_DEV_S303_Printer_TestStatus(void)
{
	BOOL printState ;
	int count;
	unsigned getPrintState[3];
	unsigned char S303_printfCommand_GetPrinterState[3]={0x10,0x04,0x01};
	serial_write(PRINTER_COM,S303_printfCommand_GetPrinterState,3);
	memset(getPrintState,0x00,3);
	count = serial_read(PRINTER_COM,(unsigned char * )getPrintState,3);	
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



void I_DEV_S303_Printer_PrintTestBill(void)
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
	serial_write(PRINTER_COM,S303_printfCommand_B,3);	
	serial_write(PRINTER_COM,S303_printfCommand_double,3);	
	serial_write(PRINTER_COM,S303_printfCommand_LineSp,3);	
#ifdef SYS_DEBUG
	fprintf(stderr,"printNode->billNumber=%s\n",printNode->billNumber);	
	fprintf(stderr,"carTem=%d\n",carTem);	

#endif
	serial_write(PRINTER_COM,S303_printfCommand_B,3);	
	serial_write(PRINTER_COM,S303_printfCommand_double,3);	
	serial_write(PRINTER_COM,S303_printfCommand_LineSp,3);	
	memset(printContent,'\0',40);	
	sprintf(printContent,"        新疆维吾尔自治区公路车辆%c",10);	
	//sprintf(printContent,"               通行费收据%c",10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	memset(printContent,'\0',40);	
	sprintf(printContent,"               通行费收据%c",10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	//serial_write(PRINTER_COM,(char *)&S303_printfCommand_LF,1);	
	serial_write(PRINTER_COM,S303_printfCommand_Rstart,2);	
	serial_write(PRINTER_COM,S303_printfCommand_B,3);	
	serial_write(PRINTER_COM,S303_printfCommand_LineSp,3);	
	memset(printContent,'\0',40);	
	sprintf(printContent,"   站名         金额（元）       吨位%c",10);
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	memset(printContent,'\0',40);	
	sprintf(printContent,"   %s         %s            %s%c",GetLanConfigPlazaDesc(),printNode->Charge,printNode->carType,10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	memset(printContent,'\0',40);	
	sprintf(printContent,"  收费员          时间          收据号%c",10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	memset(printContent,'\0',40);	
	sprintf(printContent,"  %s  %02d-%02d-%02d %02d:%02d %s%c",GetG_Number(),rtc_time->tm_year-100, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min,printNode->billNumber,10);	
	serial_write(PRINTER_COM,(unsigned char * )printContent,strlen(printContent));	
	serial_write(PRINTER_COM,(unsigned char * )&S303_printfCommand_LF,1);	
	serial_write(PRINTER_COM,(unsigned char * )&S303_printfCommand_LF,1);	
	serial_write(PRINTER_COM,(unsigned char * )&S303_printfCommand_LF,1);	
	serial_write(PRINTER_COM,S303_printfCommand_Rstart,2);	
	serial_write(PRINTER_COM,S303_printfCommand_cut,3);	
}
