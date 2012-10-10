#include "LocalIncludeFile.h"
#define HFW_FULL_MaxCommandLen 68
#define HFW_DATALen 64
#define HTF_NUMBER {64,65,66,67,68,69,70,71,72,73}

typedef unsigned char byte;
int is_Led_HFW_init = 0;
static void TFI_HFW_Init(void)
{
	if (is_Led_HFW_init == 0)
	{
		echoic("111");
		TFI_HFW_clean(T);
		echoic("111");
		is_Led_HFW_init = 1;
	}
}
 
void TFI_HFW_SoundOuther(char *tmp)
{
	byte command1[strlen(tmp) + 1+1];
	memset(command1, 0x0d, strlen(tmp) + 1+1);
	command1[0]='V';
	memcpy((char *)&command1[1], tmp, strlen(tmp));
	serial_write(LED_COM, command1, strlen(tmp) + 1+1);
	echoic("TFI_HFW_SoundOuther:%s|%s",command1,tmp);
 
}
void TFI_HFW_clean(BOOL IsSound)
{
	unsigned char strCharge[5];
	int ret;

	byte command[HFW_FULL_MaxCommandLen];
	byte str1[255];
	echoic("111");
	sprintf(str1, " 奎克高速              欢迎您！  计重收费              试运行！");
	memset(command, 0x00, HFW_FULL_MaxCommandLen);
	command[0] = 'D'; //0x44(D)
	command[1] = '2'; //红灯状态 0 不处理，
	command[2] = '1'; //红灯状态 0 不处理，
	echoic("111");
	memcpy((char *)&command[3], str1, HFW_DATALen);
	command[HFW_FULL_MaxCommandLen - 1] = 0x0d;
	serial_write(LED_COM, command, HFW_FULL_MaxCommandLen);
	if (IsSound)
	{
		TFI_HFW_SoundOuther("141");
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
void HFW_SZ(float   value)
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
	memset(tempnum, 0x00, 255);
	memset(tmp1, 0x00, 255);
	sprintf(tmp1, "%5.2f", value);
	echoic("tmp1=%s",tmp1);
	dot =  strchr(tmp1,'.')-tmp1;
	if (dot > 5)
	{
		s = 0;
	}
	else if (dot < 5)
	{
		s = 5 - dot;
	}
	len=5;
	for (i = s; i <len ; i++)
	{
		 if (tmp1[i - s] != ' ' )
		{
			char str1[255];
			memset(str1, 0x00, 255);
			if (tmp1[i - s] == '0' )
			{
				 if (i <4)
				 {
					if (lastchar != '0')
					{

						sprintf(str1, "%d", 64);
					}
				 }
			}
			else
			{
				if (i == len - 1)
				{
					sprintf(str1, "%d", 64 + (int)tmp1[i - s] - 48); //第五位是万，相等时为元
				}
				else
				{
					sprintf(str1, "%d+%d", 64 + (int)tmp1[i - s] - 48, i == 0 ? 165 :  76 - i + 1); //第五位是万，相等时为元

				}
			}
			echoic("%s::%d %d %d", str1, i, s, dot);
			TFI_HFW_SoundOuther(str1);
			sleep(1);
			lastchar = tmp1[i - s];
		}
	}
}


void  TFI_HFW_BaoJia(int CarType, int charge)
{ 
	float weight;
 	weight =GetFareContext_CarWeight();
	TFI_HFW_SoundOuther("V141");
	if(CarType>0&&CarType<6)
	{
		byte str1[255];
		memset(str1, 0x00, 255);
		sprintf(str1, "%d",40+CarType-1);
		TFI_HFW_SoundOuther(str1);
	 sleep(1);
	}
	if(WeightCarClassBUS!=GetWeightCarClass()&&WeightCarClassTruckISNotUseWeight!=GetWeightCarClass()&&weight>0)
	{
    	HFW_SZ(weight);
		TFI_HFW_SoundOuther("138");
		sleep(1);
	}
	if (charge > 0 && charge < 50000)
	{
		TFI_HFW_SoundOuther("156");
		HFW_SZ(charge);
		TFI_HFW_SoundOuther("77");
		sleep(1);
		TFI_HFW_SoundOuther("1");
		sleep(1);

	}
}

void  TFI_HFW_LedShow(int CarType, int charge)
{ 
	byte command[HFW_FULL_MaxCommandLen];
	byte str1[255];
	memset(str1, ' ', 255);
	memset(command, 0x00, HFW_FULL_MaxCommandLen);
	command[0] = 'D'; //0x44(D)
	command[1] = '0'; //红灯状态 0 不处理，
	command[2] = '0'; //红灯状态 0 不处理，
	sprintf(str1, "车    型:%4s%1d型金    额:%5d元承载标准:%5.0f吨车货总重:%5.0f吨",
			GetWeightCarClass()== WeightCarClassBUS ? "客" : "货",
			CarType,
			charge,
			GetWeightContext_WeightLimit_ByTon(),
			GetFareContext_CarWeight());
	memcpy((char *)&command[3], str1, HFW_DATALen);
	command[HFW_FULL_MaxCommandLen - 1] = 0x0d;
	serial_write(LED_COM, command, HFW_FULL_MaxCommandLen);
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
}

void TFI_HFW_SetHuangShan(BOOL bFlag)
{
	byte command[5];
	memset(command, 0x00, 5);
	command[0] = 'K'; //0x44(D)
	command[1] = '0'; //红灯状态 0 不处理，
	command[2] = '0'; //绿灯状态 0 不处理，
	command[3] =  bFlag == T ? '2' : '1'; ; //不处理，
	command[4] = 0x0d;
	 serial_write(LED_COM, command, 5);
}