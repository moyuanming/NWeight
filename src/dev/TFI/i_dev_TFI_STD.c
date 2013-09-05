#include "LocalIncludeFile.h"
#include "i_dev_TFI_STD.h"
#define STD_FULL_MaxCommandLen 71
#define STD_DATALen 64

typedef unsigned char byte;
int is_Led_STD_init = 0;
sem_t STD_Semt;
void TFI_STD_Init(void)
{
	if (is_Led_STD_init == 0)
	{
		//echoic("初始化恒富威费显红绿灯黄闪一体设备");
		sem_init(&STD_Semt, 0, 1);
		serial_init(LED_COM,Get_LEDCOMSpeed());
		TFI_STD_clean(T);
		is_Led_STD_init = 1;
	}
}
void TFI_STD_Close(void)
{
	sem_destroy(&STD_Semt);
}

char tmp_command[STD_FULL_MaxCommandLen];
 
void TFI_STD_clean(BOOL IsSound)
{
	ShowFullScreenText(GetTFIText(0));
}

 
int __CarType;
int __charge;
static pthread_t STD_T;
void  TFI_STD_BaoJia(int CarType, int charge)
{
	__CarType = CarType;
	__charge = charge;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	 pthread_create(&STD_T, &new_attr, (void *)TFI_STD_BaoJia_ForThread, NULL);
	pthread_attr_destroy(&new_attr);

}
void TFI_STD_BaoJia_ForThread(void)
{
	char fivecmd[20];
	float weight;
	int CarType =	__CarType;
	int charge = __charge;
	sem_wait(&STD_Semt);
	{
		weight = GetFareContext_CarWeight();
		memset(fivecmd,0x00,sizeof(fivecmd));
		if (charge==0)
		{
			char tmpcharge[10];

			fivecmd[0]=0xFF;
			fivecmd[1]=0xDC;
			fivecmd[2]=8;
			fivecmd[3]='S';
			fivecmd[4]=0x32;//双语
			fivecmd[5]=0x37;
			fivecmd[6]= 0x33;//免费车
			SetBCC(fivecmd,7);
		}
		else if (NotUseWeight != GetWeightFunctions() && weight> 0)
		{
			char tmpcharge[10];
			char tmpw[10];
			memset(tmpcharge,0x00,sizeof(tmpcharge));
			memset(tmpw,0x00,sizeof(tmpw));
			fivecmd[0]=0xFF;
			fivecmd[1]=0xDC;
			fivecmd[2]=17;
			fivecmd[3]='S';
			fivecmd[4]=0x32;//双语
			fivecmd[5]=0x37;
			fivecmd[6]=__CarType+0x30;
			sprintf(tmpw,"%03.2f",weight);//999.99
			sprintf(tmpcharge,"%04d",tmpcharge);
			strncpy(&fivecmd[7],tmpw ,3);
			strncpy(&fivecmd[10],&tmpw[4] ,2);
			strncpy(&fivecmd[12],tmpcharge ,4);
			SetBCC(fivecmd,16); 
		}
		else
		{
			char tmpcharge[10];
			memset(tmpcharge,0x00,sizeof(tmpcharge));
			fivecmd[0]=0xFF;
			fivecmd[1]=0xDC;
			fivecmd[2]=12;
			fivecmd[3]='S';
			fivecmd[4]=0x32;//双语
			fivecmd[5]=0x37;
			fivecmd[6]=__CarType+0x30;
			sprintf(tmpcharge,"%04d",charge);
			strncpy(&fivecmd[7],tmpcharge ,4);
			SetBCC(fivecmd,11);
		}
		serial_write(LED_COM, (unsigned  char*)fivecmd, fivecmd[2]);
	}
	sem_post(&STD_Semt);
}

void  TFI_STD_LedShow(int CarType, int charge)
{
	char str1[255];
	memset(str1, ' ', 255);
	if (NotUseWeight != GetWeightFunctions())
	{
		sprintf( str1, "车    型:%4s%1d型金    额:%5d元承载标准:%5.0f吨车货总重:%5.0f吨",
			GetWeightCarClass() == WeightCarClassBUS ? "客" : "货",
			CarType,
			charge,
			GetWeightContext_WeightLimit_ByTon(),
			GetFareContext_CarWeight());
	}
	else
	{
		sprintf(str1, "车    型:    %1d型金    额:%5d元",
			CarType,
			charge);
	}
	ShowFullScreenText(str1);
	echoic("费显内容:%s", str1);
	TFI_STD_BaoJia(CarType, charge);

}
void TFI_STD_SetTongXingDeng(BOOL bFlag)
{
	 SendStdCMD(bFlag == T ? 'E' : 'F');
}

void TFI_STD_SetHuangShan(BOOL bFlag)
{ 
	SendStdCMD(bFlag == T ? 'J' : 'K');
}
//发送短命令
void SendStdCMD(char cmd)
{
	sem_wait(&STD_Semt);
	{
		byte command[5];
		memset(command, 0x00, 5);
		command[0] =0xFF; //0x44(D) 
		command[1] =0xDC;
		command[2] = 5; //不处理，
		command[3] = cmd;
		SetBCC((char*)command,4);
		serial_write(LED_COM, command, 5);
	}
	sem_post(&STD_Semt);
}
//发送全屏显示命令
void ShowFullScreenText(char * content)
{
	sem_wait(&STD_Semt);
	{
		byte command[STD_FULL_MaxCommandLen];
		byte str1[255];
		memset(str1, ' ', 255);
		sprintf((  char * )str1, "%64s",content);
		memset(command, 0x00, STD_FULL_MaxCommandLen);
		command[0] = 0xFF ; //0x44(D)
		command[1] = 0xDC;  
		command[2] = 71;  
		command[3] = 'D';
		command[4] = 255;
		command[5] = 0;
		memcpy((char *)&command[6], str1, STD_DATALen);
		SetBCC((char*)command,STD_FULL_MaxCommandLen - 1);
		serial_write(LED_COM, command, STD_FULL_MaxCommandLen);
		echoic("重置指令:%s",command );
	}
	sem_post(&STD_Semt);
}