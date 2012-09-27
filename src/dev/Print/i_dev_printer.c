#include "LocalIncludeFile.h"


void I_DEV_Printer_Init(void)
{
	if(serial_init(Get_PrintCOM(),Get_PrintCOMSpeed())<0)
	{	
		echoic("打印机串口初始化失败！");		
	}
	else
	{
		echoic("打印机串口初始化成功！");		
	}
}

void I_Dev_Printer_PrintBill(struct BILLPARAM *var_billparam)
{
	echoic("run IS");
    if(0==strcmp("TWD",GetPrintDLL()))
	{
		echoic("run IS");
		I_DEV_TWD_Printer_PrintBill(var_billparam);
		echoic("run IS");
	}
	else if(0==strcmp("KK",GetPrintDLL()))
	{
		I_DEV_KK_Printer_PrintBill(var_billparam);
	}
	else if(0==strcmp("303",GetPrintDLL()))
	{
		I_DEV_S303_Printer_PrintBill(var_billparam);
	}
}

void I_DEV_Printer_Close(void)
{
    if(0==strcmp("TWD",GetPrintDLL()))
	{
		I_DEV_TWD_Printer_Close();
	}
	else if(0==strcmp("KK",GetPrintDLL()))
	{
		I_DEV_KK_Printer_Close();
	}
	else if(0==strcmp("303",GetPrintDLL()))
	{
		I_DEV_S303_Printer_Close();
	}
}


BOOL I_Dev_Printer_TestStatus(void)
{
	BOOL printState = F;
	if(0==strcmp("TWD",GetPrintDLL()))
	{
		printState = I_DEV_TWD_Printer_TestStatus();
	}
	else if(0==strcmp("KK",GetPrintDLL()))
	{
		printState = I_DEV_KK_Printer_TestStatus();
	}
	else if(0==strcmp("303",GetPrintDLL()))
	{
		printState = I_DEV_S303_Printer_TestStatus();
	}
	return printState;
}



void I_DEV_Printer_PrintTestBill(void)
{
    if(0==strcmp("TWD",GetPrintDLL()))
	{
		I_DEV_TWD_Printer_PrintTestBill();
	}
	else if(0==strcmp("KK",GetPrintDLL()))
	{
		I_DEV_TWD_Printer_PrintTestBill();
	}
	else if(0==strcmp("303",GetPrintDLL()))
	{
		I_DEV_TWD_Printer_PrintTestBill();
	}
}
