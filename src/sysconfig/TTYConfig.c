#include "LocalIncludeFile.h"


static int BPS(int bps)
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
}

