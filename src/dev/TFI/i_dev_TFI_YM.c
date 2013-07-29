#include "LocalIncludeFile.h"
#include "i_dev_TFI_YM.h"
#define YM_FULL_MaxCommandLen 68
#define YM_DATALen 64

typedef unsigned char byte;
int is_Led_YM_init = 0;
sem_t YM_Semt;
void TFI_YM_Init(void)
{
	if (is_Led_YM_init == 0)
	{
		echoic("初始化mc32d费显红绿灯黄闪一体设备");
		sem_init(&YM_Semt, 0, 1);
		TFI_YM_clean(T);
		is_Led_YM_init = 1;
	}
}
void TFI_YM_Close(void)
{
	sem_destroy(&YM_Semt);
}

char tmp_command[YM_FULL_MaxCommandLen];
void TFI_YM_SoundOuther(char *tmp)
{

	sem_wait(&YM_Semt);
	{
		/*memset(tmp_command, 0x00, YM_FULL_MaxCommandLen);
		strncpy(tmp_command, tmp, strlen(tmp));
		echoic("恒富威播放指令:%s",tmp);
		byte command1[strlen(tmp_command) + 1 + 1];
		memset(command1, 0x0d, strlen(tmp_command) + 1 + 1);
		command1[0] = 'V';
		memcpy((char *)&command1[1], tmp_command, strlen(tmp_command));
		serial_write(LED_COM, command1, strlen(tmp_command) + 1 + 1);*/
	}
	sem_post(&YM_Semt);
}
void TFI_YM_clean(BOOL IsSound)
{
	sem_wait(&YM_Semt);
	{
		byte command[YM_FULL_MaxCommandLen];
		byte str1[255];
		memset(str1, ' ', 255);
		sprintf((  char * )str1, "%64s", GetTFIText(0));
		memset(command, 0x00, YM_FULL_MaxCommandLen);
		command[0] = 'D'; //0x44(D)
		command[1] = 255; //255 亮度
		command[2] = 0; //全屏显示
		memcpy((char *)&command[3], str1, YM_DATALen);
		command[YM_FULL_MaxCommandLen - 1] = 0x0d;
		serial_write(LED_COM, command, YM_FULL_MaxCommandLen);
		echoic("重置指令:%s",command );
	}
	sem_post(&YM_Semt);
	if (IsSound)
	{
		//TFI_YM_SoundOuther("1");
	}
}
 
void YM_SZ(float   value, int soundtype)
{
	char tempnum[255];
	char tmp1[255];
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
	if (soundtype == 2)
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
				TFI_YM_SoundOuther(tmpcmd);
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
			TFI_YM_SoundOuther(tmpcmd);
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
			TFI_YM_SoundOuther(tmpcmd);
			memset(tmpcmd, 0x00, 255);
			cmdL = 0;
		}
		sprintf(tmpcmd, "%s%s%s", tmpcmd, strlen(tmpcmd) == 0 ? "" : "+", "77");
		cmdL += 1;
	}
	if (cmdL  > 0)
	{
		TFI_YM_SoundOuther(tmpcmd);
	}
}
int __CarType;
int __charge;
static pthread_t YM_T;
void  TFI_YM_BaoJia(int CarType, int charge)
{
	__CarType = CarType;
	__charge = charge;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	 pthread_create(&YM_T, &new_attr, (void *)TFI_YM_BaoJia_ForThread, NULL);
	pthread_attr_destroy(&new_attr);

}
void TFI_YM_BaoJia_ForThread(void)
{
	float weight;
	int CarType =	__CarType;
	int charge = __charge;
	weight = GetFareContext_CarWeight();
	TFI_YM_SoundOuther("141");
	if (CarType > 0 && CarType < 6)
	{
		char str1[255];
		memset(str1, 0x00, 255);
		sprintf(str1, "%d", 40 + CarType - 1);
		TFI_YM_SoundOuther(str1);
		sleep(1);
	}
	if (WeightCarClassBUS != GetWeightCarClass() 
		&& WeightCarClassTruckISNotUseWeight != GetWeightCarClass() 
		&& weight > 0)
	{
		YM_SZ(weight, 1);
		sleep(1);
	}
	if (charge > 0 && charge < 50000)
	{
		YM_SZ(charge, 2);
	}
}

void  TFI_YM_LedShow(int CarType, int charge)
{
	sem_wait(&YM_Semt);
	{
		byte command[19];
		byte str1[255];
		memset(str1, ' ', 255);
		memset(command, 0x00, 19);
		command[0] = 'D'; //0x44(D)
		command[1] = 255; // 
		command[2] = 0; // 
		/*sprintf((  char * )str1, "车  型： %1d",				getweightcarclass() == weightcarclassbus ? "客" : "货",
		cartype,
		charge,
		getweightcontext_weightlimit_byton(),
		getfarecontext_carweight());*/
		sprintf((  char * )str1, "车  型：     %1d",		CarType);
		memcpy((char *)&command[3], str1, 19);
		command[19] = 0x0d;
		serial_write(LED_COM, command, 19);
		usleep(1000*60);


		memset(str1, ' ', 255);
		memset(command, 0x00, 19);
		command[0] = 'D'; //0x44(D)
		command[1] = 255; // 
		command[2] = 0; // 
		sprintf((  char * )str1, "总重量： %5.0f吨",		GetFareContext_CarWeight());
		memcpy((char *)&command[3], str1, 19);
		command[19] = 0x0d;
		serial_write(LED_COM, command, 19);
		usleep(1000*60);

		memset(str1, ' ', 255);
		memset(command, 0x00, 19);
		command[0] = 'D'; //0x44(D)
		command[1] = 255; // 
		command[2] = 0; // 
		sprintf((  char * )str1, "超载率： %5.0f%",		GetWeightContext_WeightLimit_ByTon());
		memcpy((char *)&command[3], str1, 19);
		command[19] = 0x0d;
		serial_write(LED_COM, command, 19);
		usleep(1000*60);


		memset(str1, ' ', 255);
		memset(command, 0x00, 19);
		command[0] = 'D'; //0x44(D)
		command[1] = 255; // 
		command[2] = 0; // 
		sprintf((  char * )str1, "金  额： %d元",		charge);
		memcpy((char *)&command[3], str1, 19);
		command[19] = 0x0d;
		serial_write(LED_COM, command, 19);
		usleep(1000*60);

		echoic("费显内容:%s", str1);

	}
	sem_post(&YM_Semt);
	TFI_YM_BaoJia(CarType, charge);

}
void TFI_YM_SetTongXingDeng(BOOL bFlag)
{
	byte command[2];
	memset(command, 0x00, 2);
	command[0] = 'B';
	command[1] = bFlag == T ? 0x01 : 0x02; //红灯状态 0 不处理，
	serial_write(LED_COM, command, 2);
	echoic("通行灯指令:%s", command);
}

void TFI_YM_SetHuangShan(BOOL bFlag)
{ 
	byte command[5];
	memset(command, 0x00, 5);
	command[0] = 'B'; //0x44(D)
	command[1] =  bFlag == T ? 0x04 :0x08;; //不处理，
	serial_write(LED_COM, command, 5);
	echoic("黄闪指令:%s", command);
}
