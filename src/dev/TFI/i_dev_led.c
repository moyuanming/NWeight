#include "LocalIncludeFile.h"
#include "i_dev_TFI_RHY.h"
#include "i_dev_TFI_SG.h"
#include "tfi_lib.h"
#include "i_dev_TFI_CJ.h"
#include "i_dev_TFI_HFW.h"
#include "i_dev_TFI_KY.h"
#include "i_dev_TFI_MNS.h"
void I_DEV_LED_Init(void)
{
	//双涝坝等老费县为 9600 吐乌的费显为 1200
	int BTLV = B9600;

	if (0 == strcmp("RHY", GetTFIDLL()))
	{
		TFI_RHY_Init();
	}
	else if (0 == strcmp("HFW", GetTFIDLL()))
	{
		TFI_HFW_Init();
	}
	else if (0 == strcmp("MNSNEW", GetTFIDLL()))
	{
		char szCOM[20];
		sprintf(szCOM, "/dev/COM%d", LED_COM);
		LedTfi_init(szCOM);
	}
	else
	{
		if (0 == strcmp("TWD", GetTFIDLL()))
		{
			BTLV = B1200;
		}

		if (0 == strcmp("KY", GetTFIDLL()))
		{
			BTLV = B1200;
		}
		if (serial_init(LED_COM, BTLV) < 0)
		{
			echo("费显串口初始化失败12！");
		}
		else
		{
			echo("费显串口初始化成功！");
		}
	}

}
void setLed(void)
{
	int kbd_fd;
	unsigned char led;
	kbd_fd = open("/dev/tty0", O_RDWR);
	if (kbd_fd < 0)
	{
		perror("/dev/tty0");
		exit(errno);
	}
	else
	{
		ioctl(kbd_fd, KDGKBLED, &led);
		led &= ~LED_NUM;
		ioctl(kbd_fd, KDSKBLED, led);
		usleep(100);
		led |= LED_NUM;
		ioctl(kbd_fd, KDSKBLED, led);
	}
	close(kbd_fd);

}


void LedSound(int Index)
{

}
void LedClare(BOOL IsSound)
{

	if (0 == strcmp("TWD", GetTFIDLL()))
	{
		if (IsSound && 1 == atoi(sys_ini.LedSoundEnabled))
		{
			serial_write(LED_COM, (unsigned char*)"<Y>", 3);
		}
		else
		{

			serial_write(LED_COM, (unsigned char*)"<D>", 3);
		}
	}
	else if (0 == strcmp("KK", GetTFIDLL()))
	{
		TFI_KK_clean();
	}
	else if (0 == strcmp("303", GetTFIDLL()))
	{
		TFI_303_clean(IsSound);
	}
	else if (0 == strcmp("HN", GetTFIDLL()))
	{
		TFI_HN_clean();
	}
	else if (0 == strcmp("SG", GetTFIDLL()))
	{
		TFI_SG_clean();
	}
	else if (0 == strcmp("CJ", GetTFIDLL()))
	{
		TFI_CJ_clean();
	}
	else if (0 == strcmp("KY", GetTFIDLL()))
	{
		TFI_KY_clean();
	}
	else if (0 == strcmp("MNS", GetTFIDLL()))
	{
		TFI_MNS_clean();
	}
	else if (0 == strcmp("MNSNEW", GetTFIDLL()))
	{
		TFI_MNS_New_clean();
	}
	else if (0 == strcmp("RHY", GetTFIDLL()))
	{
		TFI_RHY_clean(T);
	}
	else if (0 == strcmp("HFW", GetTFIDLL()))
	{
		TFI_HFW_clean(T);
	}
}
void LedVolume(int VolumeValue)
{
	//unsigned char Command[4];
	//Command[0] = 0x0A;
	//Command[1] = 0x46;
	//switch (VolumeValue)
	//{
	//case 0:
	//	Command[2] = 0x22;
	//	break;
	//case 1:
	//	Command[2] = 0x21;
	//	break;
	//case 2:
	//	Command[2] = 0x20;
	//	break;
	//case 3:
	//	Command[2] = 0x19;
	//	break;
	//case 4:
	//	Command[2] = 0x18;
	//	break;
	//case 5:
	//	Command[2] = 0x17;
	//	break;
	//case 6:
	//	Command[2] = 0x16;
	//	break;
	//}

	//Command[3] = 0x00;
	////serial_write(LED_COM,Command,4);
	////sprintf(help,"音量调节为 %d ",Currentvolume);
}
void LedShowCharge(char CarType, int charge)
{
	echo("%s", GetTFIDLL());
	if (0 == strcmp("TWD", GetTFIDLL()))
	{
		echo("TWD %c  %d  %d", CarType, CarType, charge);
		if (' ' != CarType && '0' != CarType)
		{
			TWD_ShowCarType(CarType);
		}
		usleep(10);
		if (0 != charge)
		{
			TWD_Showcharge(charge);
		}
	}
	else if (0 == strcmp("KK", GetTFIDLL()))
	{
		TFI_KK_LedShow((int)CarType - 0x30,  charge);
	}
	else if (0 == strcmp("303", GetTFIDLL()))
	{
		echo("303 %c  %d  %d", CarType, CarType, charge);
		TFI_303_LedShow(CarType, charge);
	}
	else if (0 == strcmp("HN", GetTFIDLL()))
	{
		echo("HN %c  %d  %d", CarType, CarType, charge);
		TFI_HN_LedShow((int)CarType - 0x30,  charge);
	}
	else if (0 == strcmp("SG", GetTFIDLL()))
	{
		echo("SG %c  %d  %d", CarType, CarType, charge);
		TFI_SG_LedShow((int)CarType - 0x30,  charge);
	}
	else if (0 == strcmp("CJ", GetTFIDLL()))
	{
		echo("CJ %c  %d  %d", CarType, CarType, charge);
		TFI_CJ_LedShow((int)CarType - 0x30,  charge);
	}
	else if (0 == strcmp("KY", GetTFIDLL()))
	{
		echo("KY %c  %d  %d", CarType, CarType, charge);
		//TFI_KY_LedShow((int)CarType - 0x30,  charge);
	}
	else if (0 == strcmp("MNS", GetTFIDLL()))
	{
		echo("MNS %c  %d  %d", CarType, CarType, charge);
		TFI_MNS_LedShow(CarType, charge);
	}
	else if (0 == strcmp("MNSNEW", GetTFIDLL()))
	{
		echo("MNS %c  %d  %d", CarType, CarType, charge);
		TFI_MNS_NEW_LedShow(CarType, charge);
	}
	else if (0 == strcmp("RHY", GetTFIDLL()))
	{
		echo("MNS %c  %d  %d", CarType, CarType, charge);
		TFI_RHY_LedShow((int)CarType - 0x30, charge);
	}
	else if (0 == strcmp("HFW", GetTFIDLL()))
	{
		TFI_HFW_LedShow((int)CarType - 0x30, charge);
	}
}

void TWD_ShowCarType(char ct)
{
	unsigned char strCMD[9];
	memset(strCMD, 0x00, 9);
	sprintf((  char * )strCMD, "<V****%c>", ct);
	echo1("指令:%s  车型:%c  端口COM%d", strCMD, ct, LED_COM);
	serial_write(LED_COM, strCMD, sizeof(strCMD));
}
void TWD_Showcharge(int ct)
{
	unsigned char strCMD[9];
	char  tmpx1[10];
	char  tmpx2[10];
	memset(tmpx2, 0x00, 10);
	memset(tmpx1, 0x00, 10);
	memset(strCMD, 0x00, 9);
	sprintf(tmpx1, "%d", ct);
	strncpy(tmpx2, "*****", 5 - strlen(tmpx1));
	sprintf((char*)strCMD, "<M%s%s>", tmpx2, tmpx1);
	echoic("指令:%s  费额:%d", strCMD, ct);
	serial_write(LED_COM, strCMD, sizeof(strCMD));
}


void  LedClear()
{
	if (0 == strcmp("TWD", GetTFIDLL()))
	{
		serial_write(LED_COM, (unsigned char * )"<Y>", 3);
	}

	else if (0 == strcmp("KK", GetTFIDLL()))
	{
		TFI_KK_clean();
	}
	else if (0 == strcmp("303", GetTFIDLL()))
	{
		TFI_303_clean(F);
	}
	else if (0 == strcmp("HN", GetTFIDLL()))
	{
		TFI_HN_clean();
	}
	else if (0 == strcmp("CJ", GetTFIDLL()))
	{
		TFI_CJ_clean();
	}
	else if (0 == strcmp("RHY", GetTFIDLL()))
	{
		TFI_RHY_clean(T);
	}
	else if (0 == strcmp("HFW", GetTFIDLL()))
	{
		TFI_HFW_clean(F);
	}


}

//是否为 一体设备， 比如恒富威的  黄闪 通行灯 费显一体的设备 
BOOL  IsRichTFI(void)
{
	BOOL result = F;
	if (0 == strcmp("HFW", GetTFIDLL()))
	{
		result = T;
	}
	return result;

}

void TFI_SetTongXingDeng(BOOL bFlag)
{
	if (0 == strcmp("HFW", GetTFIDLL()))
	{
		TFI_HFW_SetTongXingDeng(bFlag);
	}
}

void TFI_SetHuangShan(BOOL bFlag)
{
	if (0 == strcmp("HFW", GetTFIDLL()))
	{
		TFI_HFW_SetHuangShan(bFlag);
	}
}
