#include "LocalIncludeFile.h"
#define HFW_FULL_MaxCommandLen 68
#define HFW_DATALen 64

typedef unsigned char byte;
int is_Led_HFW_init = 0;
sem_t HFW_Semt;
void TFI_HFW_Init(void)
{
	if (is_Led_HFW_init == 0)
	{
		echoic("初始化恒富威费显红绿灯黄闪一体设备");
		sem_init(&HFW_Semt, 0, 1);
		TFI_HFW_clean(T);
		is_Led_HFW_init = 1;
	}
}
void TFI_HFW_Close(void)
{
	sem_destroy(&HFW_Semt);
}

char tmp_command[HFW_FULL_MaxCommandLen];
void TFI_HFW_SoundOuther(char *tmp)
{

	sem_wait(&HFW_Semt);
	{
		memset(tmp_command, 0x00, HFW_FULL_MaxCommandLen);
		strncpy(tmp_command, tmp, strlen(tmp));
		echoic("恒富威播放指令:%s",tmp);
		byte command1[strlen(tmp_command) + 1 + 1];
		memset(command1, 0x0d, strlen(tmp_command) + 1 + 1);
		command1[0] = 'V';
		memcpy((char *)&command1[1], tmp_command, strlen(tmp_command));
		serial_write(LED_COM, command1, strlen(tmp_command) + 1 + 1);
	}
	sem_post(&HFW_Semt);
}
void TFI_HFW_clean(BOOL IsSound)
{
	sem_wait(&HFW_Semt);
	{
		unsigned char strCharge[5];
		int ret;

		byte command[HFW_FULL_MaxCommandLen];
		byte str1[255];
		memset(str1, ' ', 255);
		sprintf(str1, "%64s", GetTFIText(0));
		memset(command, 0x00, HFW_FULL_MaxCommandLen);
		command[0] = 'D'; //0x44(D)
		command[1] = '2'; //红灯状态 0 不处理，
		command[2] = '1'; //红灯状态 0 不处理，
		echoic("111");
		memcpy((char *)&command[3], str1, HFW_DATALen);
		command[HFW_FULL_MaxCommandLen - 1] = 0x0d;
		serial_write(LED_COM, command, HFW_FULL_MaxCommandLen);
		echoic("重置指令:%s",command );
	}
	sem_post(&HFW_Semt);
	if (IsSound)
	{
		//TFI_HFW_SoundOuther("1");
	}
}
 
void HFW_SZ(float   value, int soundtype)
{
	char tempnum[255];
	char tmp1[255];
	char str1[255];
	char str2[255];
	int i;
	int s = 0;
	int  dot;
	char  lastchar = '\n';
	int len;
	char tmpcmd[255];
	int cmdL;
	memset(tmpcmd, 0x00, 255);
	memset(tempnum, 0x00, 255);
	memset(tmp1, 0x00, 255);
	sprintf(tmp1, "%5.2f", value);
	echoic("朗读值=%f  末位单位:=%d", value, soundtype);
	dot =  strchr(tmp1, '.') - tmp1;
	if (dot > 5)
	{
		s = 0;
	}
	else if (dot < 5)
	{
		s = 5 - dot;
	}
	len = 5;
	cmdL = 0;
	if (soundtype = 2)
	{
		sprintf(tmpcmd, "%s", "156");
		cmdL += 1;
	}
	for (i = s; i < len; i++)
	{
		if (tmp1[i - s] != ' ')
		{
			char str1[255];
			memset(str1, 0x00, 255);
			if (tmp1[i - s] == '0')
			{
				if (i < 4)
				{
					if (lastchar != '0')
					{
						cmdL += 1;
						sprintf(str1, "%d", 64);
					}
				}
			}
			else
			{
				if (i == len - 1)
				{
					cmdL += 1;
					sprintf(str1, "%d", 64 + (int)tmp1[i - s] - 48); //第五位是万，相等时为元
				}
				else
				{
					cmdL += 2;
					sprintf(str1, "%d+%d", 64 + (int)tmp1[i - s] - 48, i == 0 ? 165 :  76 - i + 1); //第五位是万，相等时为元
				}
			}
			sprintf(tmpcmd, "%s%s%s", tmpcmd, strlen(tmpcmd) != 0 ?  (strlen(str1) == 0  ? "" : "+") : "", str1);
			if (cmdL >= 6)
			{
				TFI_HFW_SoundOuther(tmpcmd);
				sleep(1);
				memset(tmpcmd, 0x00, 255);
				cmdL = 0;
			}
			lastchar = tmp1[i - s];
		}
	}
	if (soundtype == 1)
	{
		if (cmdL + 1 >= 8)
		{
			TFI_HFW_SoundOuther(tmpcmd);
			//sleep(1);
			memset(tmpcmd, 0x00, 255);
			cmdL = 0;
		}
		sprintf(tmpcmd, "%s%s%s", tmpcmd, strlen(tmpcmd) == 0 ? "" : "+", "138");
		cmdL += 1;
	}
	if (soundtype == 2)
	{
		if (cmdL + 1 >= 8)
		{
			TFI_HFW_SoundOuther(tmpcmd);
			//sleep(1);
			memset(tmpcmd, 0x00, 255);
			cmdL = 0;
		}
		sprintf(tmpcmd, "%s%s%s", tmpcmd, strlen(tmpcmd) == 0 ? "" : "+", "77");
		cmdL += 1;
	}
	if (cmdL  > 0)
	{
		TFI_HFW_SoundOuther(tmpcmd);
	}
}
int __CarType;
int __charge;
static pthread_t HFW_T;
void  TFI_HFW_BaoJia(int CarType, int charge)
{
	int ret;
	__CarType = CarType;
	__charge = charge;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&HFW_T, &new_attr, (void *)TFI_HFW_BaoJia_ForThread, NULL);
	pthread_attr_destroy(&new_attr);

}
void TFI_HFW_BaoJia_ForThread(void)
{
	float weight;
	int CarType =	__CarType;
	int charge = __charge;
	weight = GetFareContext_CarWeight();
	TFI_HFW_SoundOuther("141");
	if (CarType > 0 && CarType < 6)
	{
		byte str1[255];
		memset(str1, 0x00, 255);
		sprintf(str1, "%d", 40 + CarType - 1);
		TFI_HFW_SoundOuther(str1);
		sleep(1);
	}
	if (WeightCarClassBUS != GetWeightCarClass() 
		&& WeightCarClassTruckISNotUseWeight != GetWeightCarClass() 
		&& weight > 0)
	{
		HFW_SZ(weight, 1);
		sleep(1);
	}
	if (charge > 0 && charge < 50000)
	{
		HFW_SZ(charge, 2);
	}
}

void  TFI_HFW_LedShow(int CarType, int charge)
{
	sem_wait(&HFW_Semt);
	{
		byte command[HFW_FULL_MaxCommandLen];
		byte str1[255];
		memset(str1, ' ', 255);
		memset(command, 0x00, HFW_FULL_MaxCommandLen);
		command[0] = 'D'; //0x44(D)
		command[1] = '0'; //红灯状态 0 不处理，
		command[2] = '0'; //红灯状态 0 不处理，
		if (NotUseWeight != GetWeightFunctions())
		{
			sprintf(str1, "车    型:%4s%1d型金    额:%5d元承载标准:%5.0f吨车货总重:%5.0f吨",
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
		memcpy((char *)&command[3], str1, HFW_DATALen);
		command[HFW_FULL_MaxCommandLen - 1] = 0x0d;
		serial_write(LED_COM, command, HFW_FULL_MaxCommandLen);
		echoic("费显内容:%s", str1);

	}
	sem_post(&HFW_Semt);
	TFI_HFW_BaoJia(CarType, charge);

}
void TFI_HFW_SetTongXingDeng(BOOL bFlag)
{
	byte command[5];
	memset(command, 0x00, 5);
	command[0] = 'K'; //0x44(D)
	command[1] = bFlag == T ? '1' : '2'; //红灯状态 0 不处理，
	command[2] = bFlag == T ? '2' : '1'; //绿灯状态 0 不处理，
	command[3] = '0'; //不处理，
	command[4] = 0x0d;
	serial_write(LED_COM, command, 5);
	echoic("通行灯指令:%s", command);
}

void TFI_HFW_SetHuangShan(BOOL bFlag)
{ 
	byte command[5];
	memset(command, 0x00, 5);
	command[0] = 'K'; //0x44(D)
	command[1] = '0'; //红灯状态 0 不处理，
	command[2] = '0'; //绿灯状态 0 不处理，
	command[3] =  bFlag == T ? '2' : '1';; //不处理，
	command[4] = 0x0d;
	serial_write(LED_COM, command, 5);
	echoic("黄闪指令:%s", command);
}
