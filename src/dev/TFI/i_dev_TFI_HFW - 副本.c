#include "LocalIncludeFile.h"
#define HFW_FULL_MaxCommandLen 68
#define HFW_DATALen 64
#define HTF_NUMBER {64,65,66,67,68,69,70,71,72,73}

typedef unsigned char byte;
int is_Led_HFW_init = 0;
sem_t HFW_Semt;
 void TFI_HFW_Init(void)
{
	if (is_Led_HFW_init == 0)
	{
		echoic("111");
		sem_init(&HFW_Semt, 0, 1);
				echoic("��ʼ��HFW_Semt");
		TFI_HFW_clean(T);
		echoic("111");
		is_Led_HFW_init = 1;
		
		
	 
	}
}
void TFI_HFW_Close(void)
{
	sem_destroy(&HFW_Semt);
}

char tmp_command[HFW_FULL_MaxCommandLen];
static pthread_t HFW_T;
void TFI_HFW_SoundOuther(char *tmp)
{
	int ret;
	   pthread_attr_t new_attr;
	memset(tmp_command, 0x00, HFW_FULL_MaxCommandLen);
	strncpy(tmp_command, tmp, strlen(tmp));
  
    pthread_attr_init(&new_attr);
    pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&HFW_T, &new_attr, (void *)TFI_HFW_SoundOuther_EXXX, NULL);
    pthread_attr_destroy(&new_attr);

}
void TFI_HFW_SoundOuther_EXXX(void)
{
		echoic("waitHFW_Semt");
	sem_wait(&HFW_Semt);
	{
		byte command1[strlen(tmp_command) + 1 + 1];
		memset(command1, 0x0d, strlen(tmp_command) + 1 + 1);
		command1[0] = 'V';
		memcpy((char *)&command1[1], tmp_command, strlen(tmp_command));
		serial_write(LED_COM, command1, strlen(tmp_command) + 1 + 1);
		echoic("TFI_HFW_SoundOuther:%s|%s", command1, tmp_command);
	}
		echoic("post HFW_Semt");
	sem_post(&HFW_Semt);
		echoic("postendHFW_Semt");

}
void TFI_HFW_clean(BOOL IsSound)
{
	unsigned char strCharge[5];
	int ret;

	byte command[HFW_FULL_MaxCommandLen];
	byte str1[255];
 
		echoic("waitHFW_Semt");
	sem_wait(& HFW_Semt);
	{
		echoic("111");
		sprintf(str1, " ���˸���              ��ӭ����  �����շ�              �����У�");
		memset(command, 0x00, HFW_FULL_MaxCommandLen);
		command[0] = 'D'; //0x44(D)
		command[1] = '2'; //���״̬ 0 ������
		command[2] = '1'; //���״̬ 0 ������
		echoic("111");
		memcpy((char *)&command[3], str1, HFW_DATALen);
		command[HFW_FULL_MaxCommandLen - 1] = 0x0d;
		serial_write(LED_COM, command, HFW_FULL_MaxCommandLen);
	}
		echoic("endpost");
	sem_post(& HFW_Semt);
	if (IsSound)
	{
		//TFI_HFW_SoundOuther("1");
	}
}
int getloc(char *src, char c)
{
	int i;
	for (i = 0; i < strlen(src); i++)
	{
		if (src[i] == c)
		{
			break;
		}
	}
	return i;
}
void HFW_SZ(float   value,int soundtype)
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
	echoic("value=%f  soundtype=%d", value,soundtype);
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
					sprintf(str1, "%d", 64 + (int)tmp1[i - s] - 48); //����λ�������ʱΪԪ
				}
				else
				{
					cmdL += 2;
					sprintf(str1, "%d+%d", 64 + (int)tmp1[i - s] - 48, i == 0 ? 165 :  76 - i + 1); //����λ�������ʱΪԪ

				}
			}
			echoic("%s::%d %d %d", str1, i, s, dot);
			sprintf(tmpcmd, "%s%s%s", tmpcmd, strlen(tmpcmd) == 0 ? "" : "+", str1);
			if (cmdL >= 6)
			{
				TFI_HFW_SoundOuther(tmpcmd);
			 
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
 
void  TFI_HFW_BaoJia(int CarType, int charge)
{
	 
	float weight;
	weight = GetFareContext_CarWeight();
	TFI_HFW_SoundOuther("141");
	if(CarType>0&&CarType<6)
	{
		byte str1[255];
		memset(str1, 0x00, 255);
		sprintf(str1, "%d", 40 + CarType - 1);
		TFI_HFW_SoundOuther(str1);
		 
	}
	if (WeightCarClassBUS != GetWeightCarClass() && WeightCarClassTruckISNotUseWeight != GetWeightCarClass() && weight > 0)
	{
		HFW_SZ(weight, 1);
		 

	}
	if (charge > 0 && charge < 50000)
	{
		HFW_SZ(charge, 2);
	}
}

void  TFI_HFW_LedShow(int CarType, int charge)
{ 
	byte command[HFW_FULL_MaxCommandLen];
	byte str1[255];
	memset(str1, ' ', 255);
	memset(command, 0x00, HFW_FULL_MaxCommandLen);
	command[0] = 'D'; //0x44(D)
	command[1] = '0'; //���״̬ 0 ������
	command[2] = '0'; //���״̬ 0 ������
	sprintf(str1, "��    ��:%4s%1d�ͽ�    ��:%5dԪ���ر�׼:%5.0f�ֳ�������:%5.0f��",
			GetWeightCarClass()== WeightCarClassBUS ? "��" : "��",
			CarType,
			charge,
			GetWeightContext_WeightLimit_ByTon(),
			GetFareContext_CarWeight());
	memcpy((char *)&command[3], str1, HFW_DATALen);
	command[HFW_FULL_MaxCommandLen - 1] = 0x0d;
	serial_write(LED_COM, command, HFW_FULL_MaxCommandLen);
	echoic("��������:%s",str1);
	TFI_HFW_BaoJia(CarType, charge);

}
void TFI_HFW_SetTongXingDeng(BOOL bFlag)
{
	byte command[5];
	memset(command, 0x00, 5);
	command[0] = 'K'; //0x44(D)
	command[1] = bFlag == T ? '1' : '2'; //���״̬ 0 ������
	command[2] = bFlag == T ? '2' : '1'; //�̵�״̬ 0 ������
	command[3] = '0'; //������
	command[4] = 0x0d;
	serial_write(LED_COM, command, 5);
	echoic("TFI_HFW_SetTongXingDeng %s", command);
}
void TFI_HFW_SetHuangShan(BOOL bFlag)
{
	byte command[5];
	memset(command, 0x00, 5);
	command[0] = 'K'; //0x44(D)
	command[1] = '0'; //���״̬ 0 ������
	command[2] = '0'; //�̵�״̬ 0 ������
	command[3] =  bFlag == T ? '2' : '1';; //������
	command[4] = 0x0d;
	serial_write(LED_COM, command, 5);
}
