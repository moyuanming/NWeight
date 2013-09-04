#include "LocalIncludeFile.h"
BOOL VDM_SAT_IsInit=F;
BOOL  VDM_SAT_IsSync=F;
sem_t VDM_SAT_Semt;
#define  USLEEPVDM usleep(1000*180)
void VDM_SAT_Init(void )
{
	if (VDM_SAT_IsInit==F )
	{
		serial_init(Get_VDMCOM(),Get_VDMCOMSpeed());
		VDM_SAT_IsInit=T;
		VDM_SAT_IsSync=F ;
		sem_init(&VDM_SAT_Semt, 0, 1);
	}
}
BOOL  VDM_SAT_SupportChinese(void)
{
	return TRUE;
}
void VDM_SAT_Clear(void )
{
	sem_wait(&VDM_SAT_Semt);
	{
		unsigned char  temp[24]={0x0a,0x00,0x46,0x0d}; //校准时间
		serial_write(Get_VDMCOM(),(unsigned char * )&temp,4);	
		USLEEPVDM;
	}
	VDM_SAT_IsSync=F ;
	sem_post(&VDM_SAT_Semt);
}


int	VDM_SAT_TextOut(char *text,unsigned char l,unsigned char c,unsigned char  len)
{
	sem_wait(&VDM_SAT_Semt);
	{
		unsigned char  temp[60]={0x0a,0x00,c,l}; 
		unsigned char  tempstr[50];
		memset(tempstr,' ',sizeof(tempstr));
		sprintf((char*)&tempstr,"%s",text);
		memcpy(&temp[4],tempstr,48);
		temp[52]=0x0d;
		if (l <=0x0b && c <0x17)
		{
			serial_write(Get_VDMCOM(),(unsigned char * )&temp,53);	
			USLEEPVDM;
		}
	}
	sem_post(&VDM_SAT_Semt);
	return T;
}
int   VDM_SAT_IsSync_counter=0;
static pthread_t __VDM_SAT_SyncTime_T;
void VDM_SAT_SyncTime_T()
{
	sem_wait(&VDM_SAT_Semt);
	{ ////////////////////////////////////  c列  l行 0xb是12 
		unsigned char  temp[30]={0x0a,0x00,0x00,0x00,'D','W','T','0'}; //校准时间
		unsigned char  setdate[9]={0x0a,0x00,0x00,0x00,'D','D','D','1',0x0d}; 
		unsigned char  settime[9]={0x0a,0x00,0x0c,0x00,'T','T','T','1',0x0d}; 
		unsigned char  setweek[9]={0x0a,0x00,0x00,0x0C,'W','W','W','0',0x0d}; 
		memcpy(&temp[8],GetFormatTime(DATETIME_FORMAT_YYYYMMDDWHHMMSS,time(NULL)),15);
		temp[8+15]=0x0d;
		serial_write(Get_VDMCOM(),(unsigned char * )&temp,24);	
		USLEEPVDM;
		serial_write(Get_VDMCOM(),(unsigned char * )&setdate,9);	
	USLEEPVDM;
		serial_write(Get_VDMCOM(),(unsigned char * )&settime,9);	
		USLEEPVDM;
		serial_write(Get_VDMCOM(),(unsigned char * )&setweek,9);	
		USLEEPVDM;
	}
	sem_post(&VDM_SAT_Semt);
}

void VDM_SAT_SyncTime(void)
{
	if (!VDM_SAT_IsSync) 
	{
		pthread_attr_t new_attr;
		pthread_attr_init(&new_attr);
		pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
		pthread_create(&__VDM_SAT_SyncTime_T, &new_attr, (void *)VDM_SAT_SyncTime_T, NULL);
		pthread_attr_destroy(&new_attr);
		VDM_SAT_IsSync=T ;
	}
	if (VDM_SAT_IsSync)
	{
		VDM_SAT_IsSync_counter++;
		if (VDM_SAT_IsSync_counter>=60*30)//30分钟校准一次。
		{
			VDM_SAT_IsSync_counter=0;
			VDM_SAT_IsSync=F ;
		}
	}
}