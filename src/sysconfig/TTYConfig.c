#include "LocalIncludeFile.h"


  int BPS(int bps)
{
	int ret = B9600;
	switch( bps )
	{
		case 1200:
			ret = B1200;
			break;
		case 2400:
			ret = B2400;
			break;
		case 4800:
			ret = B4800;		
			break;
		case 9600:
			ret = B9600;
			break;
		case 19200:
			ret = B19200;
			break;
		case 38400:
			ret = B38400;
			break;
		case 115200:
			ret = B115200;
			break;
	}
	return ret;
}

  int Back_BPS(int bps)
{
	int ret = 9600;
	switch( bps )
	{
		case B1200:
			ret = 1200;
			break;
		case B2400:
			ret = 2400;
			break;
		case B4800:
			ret = 4800;		
			break;
		case B9600:
			ret = 9600;
			break;
		case B19200:
			ret = 19200;
			break;
		case B38400:
			ret = 38400;
			break;
		case B115200:
			ret = 115200;
			break;
	}
	return ret;
}
char ComName[50];
char *Get_ComName()
{
	return ComName;
}
int PrintCOM;
int Get_PrintCOM()
{
	return PrintCOM;
}
int PrintCOMSpeed;
int Get_PrintCOMSpeed()
{
	return BPS(PrintCOMSpeed);
}
int LEDCOM =0;
int Get_LEDCOM()
{
	return LEDCOM;
}
int LEDCOMSpeed =0;
int Get_LEDCOMSpeed()
{
	return BPS(LEDCOMSpeed);
}
int WeightCOM =0;
int Get_WeightCOM()
{
	return WeightCOM;
}
int WeightCOMSpeed =0;
int Get_WeightCOMSpeed()
{
	return BPS(WeightCOMSpeed);
}
int ICCOM =0;
int Get_ICCOM()
{
	return ICCOM;
}
int ICCOMSpeed =0;
int Get_ICCOMSpeed()
{
	return BPS(ICCOMSpeed);
}

int VDMCOM =0;
int Get_VDMCOM(void)
{
	return VDMCOM;
}
int VDMCOMSpeed =0;
int Get_VDMCOMSpeed(void)
{
	return BPS(VDMCOMSpeed);
}

int IOBoardCOM =0;
int Get_IOBoardCOM(void)
{
	return IOBoardCOM;
}
int IOBoardCOMSpeed =0;
int Get_IOBoardCOMSpeed(void)
{
	return BPS(IOBoardCOMSpeed);
}

void LoadTTyConfig()
{   
	memset(ComName,0x00,50);
	echoic("ÕýÔÚ×°ÔØLoadTTyConfig...");
	LoadIniFile(TTYCONFIG_FILE);   
	strcpy(ComName,readItemInIniFile("ComName"));
	PrintCOM		=atoi(readItemInIniFile("PrintCOM"));
	PrintCOMSpeed   =atoi(readItemInIniFile("PrintCOMSpeed"));
	LEDCOM          =atoi(readItemInIniFile("LEDCOM"));
	LEDCOMSpeed     =atoi(readItemInIniFile("LEDCOMSpeed"));
	WeightCOM       =atoi(readItemInIniFile("WeightCOM"));
	WeightCOMSpeed  =atoi(readItemInIniFile("WeightCOMSpeed"));	
	ICCOM       =atoi(readItemInIniFile("ICCOM"));
	ICCOMSpeed  =atoi(readItemInIniFile("ICCOMSpeed"));	
	VDMCOM       =atoi(readItemInIniFile("VDMCOM"));
	VDMCOMSpeed  =atoi(readItemInIniFile("VDMCOMSpeed"));
	IOBoardCOM       =atoi(readItemInIniFile("IOBoardCOM"));
	IOBoardCOMSpeed  =atoi(readItemInIniFile("IOBoardCOMSpeed"));

}

