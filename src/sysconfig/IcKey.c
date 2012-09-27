#include "LocalIncludeFile.h"

char EXTERNAL_AUTHENTICATE_KEY[33];
void Set_EXTERNAL_AUTHENTICATE_KEY(char *InPut)
{
	strncpy(EXTERNAL_AUTHENTICATE_KEY,InPut,32);
	EXTERNAL_AUTHENTICATE_KEY[32] = 0x00;
}
char *Get_EXTERNAL_AUTHENTICATE_KEY(void)
{
	return EXTERNAL_AUTHENTICATE_KEY;
}
char WRITE_KEY[33];
void Set_WRITE_KEY(char *InPut)
{
	strncpy(WRITE_KEY,InPut,32);
	WRITE_KEY[32] = 0x00;
}
char *Get_WRITE_KEY(void)
{
	return "20202020202020202020202020202020";//WRITE_KEY;
}
char KEYVER[3];
void Set_KeyVer(char *InPut)
{
	strncpy(KEYVER,InPut,2);
	KEYVER[2] = 0x00;
}
char *Get_KEYVER (void)
{
	return KEYVER;
}

void LoadLanKey(void)
{
	if(GetEnableIC())
	{
		LoadIniFile(ICKEY_FILE);
		Set_EXTERNAL_AUTHENTICATE_KEY(readItemInIniFile("EXTERNAL_AUTHENTICATE_KEY"));
		Set_WRITE_KEY(readItemInIniFile("WRITE_KEY"));
		Set_KeyVer(readItemInIniFile("KEYVER"));
	}
}

