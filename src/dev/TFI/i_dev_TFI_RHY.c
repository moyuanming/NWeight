#include "LocalIncludeFile.h"
#include "tfi_lib.h"
#define RHY_FULL_MaxCommandLen 68
#define RHY_DATALen 64
#define HTF_NUMBER {64,65,66,67,68,69,70,71,72,73}

typedef unsigned char byte;
int is_Led_RHY_init = 0;
void TFI_RHY_Init(void)
{
	if (is_Led_RHY_init == 0)
	{
		char szCOM[20];
		memset(szCOM, 0x00, 20);
		sprintf(szCOM, "/dev/COM%d", LED_COM);
		echo("TFI_RHY_InitTFI_RHY_InitTFI_RHY_Init:%s", szCOM);
		LedTfi_init(szCOM);
		LedTfi_Clean();
		is_Led_RHY_init = 1;
	}
}

 
void TFI_RHY_clean(BOOL IsSound)
{
	LedTfi_Clean();
	/*LedTfi_Line16(0, "                ");
	LedTfi_Line16(1, "小草湖收费站    ");
	LedTfi_Line16(2, "      欢迎你    ");
	LedTfi_Line16(3, "                ");*/
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
 
//只支持 十位 个位 ， 暂时不支持 100位以上中间带0 ， 比如 101 2002 ，后期加记重时再王维护
void  TFI_RHY_BaoJia(int CarType, int charge)
{
	char  varchartype[1000];
	int num=0;
	memset(varchartype, 0x00, 1000);
	sprintf(varchartype, "T00%1d|QING", CarType);
	num+=2;
	int q = charge / 1000;
	int b = charge / 100;
	int s = charge / 10;
	int g = charge - q * 1000 - b * 100 - s * 10;
	if (q>0)
	{
		sprintf(varchartype, "%s|%04d",varchartype,q*1000);
		num+=1;
	}
	if (b>0)
	{
		sprintf(varchartype, "%s|%04d",varchartype,b*100);
		num+=1;
	}
	if (s>0)
	{
		sprintf(varchartype, "%s|%04d", varchartype, s * 10);
		num += 1;
	}
	if (g > 0)
	{
		sprintf(varchartype, "%s|%04d", varchartype, g);
		num += 1;
	}
	sprintf(varchartype, "%s|YUAN", varchartype);
	num += 1;
	echo("num:%d  varchartype:%s", num, varchartype);
	PlayAudio((unsigned char *)varchartype, num);
}

void  TFI_RHY_LedShow(int CarType, int charge)
{
	char  varcartype[20];
	char  varcharge[20];
	memset(varcartype, 0x00, 20);
	sprintf(varcartype, "车型%2d型", CarType);
	memset(varcharge, 0x00, 20);
	sprintf(varcharge, "金额%2d元", charge);
	LedTfi_Clean();
	//LedTfi_Line32(0, varcartype);
	//LedTfi_Line32(1, varcharge);
	TFI_RHY_BaoJia(CarType, charge);
}
void TFI_RHY_SetTongXingDeng(BOOL bFlag)
{
 	//TFI_Output(2,  bFlag);
}
void TFI_RHY_SetHuangShan(BOOL bFlag)
{
	//TFI_Output(1,  bFlag);
}

