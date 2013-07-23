#include "LocalIncludeFile.h"
char  iComNo;
HWND  MIFHwnd;
int HaveCard;
unsigned long SaveCardNomber;
int isInit;
void ICR_JY2_Init(char *ProtNumber, int Bdps)
{
	char tmp[10];
	int i ;
	memset(tmp,0x00,10);
	sprintf(tmp,"%c",ProtNumber[strlen(ProtNumber)-1]);
	MIFHwnd=UI_Get_From_Handl();
	iComNo=atoi(tmp);
	i =Open_Reader(iComNo,Bdps,0);
	echoic("金溢读卡器打开机具返回值为%d ,串口号%d 波特率 %d",i,iComNo,Bdps);
}
void ICR_JY2_MIFRequest(void)
{
	DWORD  dwcardno;
	int i =Open_Card(iComNo,&dwcardno);
	if (i==0)
	{
		if (dwcardno!=SaveCardNomber || SaveCardNomber==0)
		{
			if (HaveCard==FALSE)
			{
				HaveCard=TRUE;
				SaveCardNomber=dwcardno;
				RD_SetMMI(iComNo,BEEP_OFF,LED_LASTING,LED_OFF);
				SendNotifyMessage(MIFHwnd, MSG_CRADENENT, 1201, dwcardno);
				RD_SetMMI(iComNo,BEEP_OFF,LED_OFF,LED_OFF);
			}
		}

	}
	if (HaveCard==TRUE)
	{
		if (dwcardno==0 &&  SaveCardNomber!=0)
		{

			SendNotifyMessage(MIFHwnd, MSG_CRADENENT, 1202, SaveCardNomber);
			SaveCardNomber=0;
			HaveCard=FALSE;
			

		}  
	}
}
char key[12];
int ICR_JY2_ReadBlock(int blockid,char* buffer)
{
	int i=-1;
	memcpy(key,"FFFFFFFFFFFF",12);	
	RD_SetMMI(iComNo,BEEP_OFF,LED_LASTING,LED_LASTING);
	if (MF1_AuthenticateWithKey(iComNo,0,blockid/4,key,NULL)==0)
	{
		i= MF1_ReadBlock(iComNo,blockid,buffer);
	}
	return i ;
}
int ICR_JY2_WriteBlock(int blockid,char* buffer)
{
	int i=-1;
		RD_SetMMI(iComNo,BEEP_OFF,LED_LASTING,LED_LASTING);
	if (MF1_AuthenticateWithKey(iComNo,0,blockid/4,key,NULL)==0)
	{
		i = MF1_WriteBlock(iComNo,blockid,buffer);
	}
	return i ;
}

