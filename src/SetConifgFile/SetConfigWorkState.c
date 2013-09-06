#include "LocalIncludeFile.h"
char *GetNetNoConfig(void);
static char *GetPlazaNoConfig(void);
static int ChangCodeInt(int nKey)
{
	if (nKey == 11)
	{
		nKey = 0;
	}
	else
	{
		nKey -=1;
	}
	return nKey;
}
static int ChangCodeChar(int nKey)
{
	switch (nKey)
	{
	case VK_0:

		nKey = 48;
		break;
	case VK_UP:
		nKey = 'U';
		break;
	case VK_DOWN:
		nKey = 'D';
		break;
	case VK_LEFT:
		nKey = 'E';
		break;
	case VK_RIGHT:
		nKey = 'X';
		break;
	case VK_GONGWU:
		nKey = '.';
		break;
	default:
		nKey = nKey + 47;
		break;
	}
	return nKey;
}
char NetNo[3];
char *GetNetNoConfig()
{
	strncpy(NetNo,GetLanConfigNetNo(),2);
	NetNo[2] = 0x00;
	return NetNo;
}
char PlazaNo[3];
static char *GetPlazaNoConfig()
{
	strncpy(PlazaNo,GetLanConfigPlazaNo(),2);
	PlazaNo[2] = 0x00;
	return PlazaNo;
}
int EditConfig = 0;
char Input[20];
void initConfig(void)
{
	EditConfig = 0;
	memset(Input,0x00,20);
}
char *ShowInfo20= "提示：\n1：配置车道基本信息\n2：配置车道通讯配置\n3：配置外设串口\n4：收费模式配置\n按【取消】键返回。";
void SetWorkStation_200_SetConfig()
{	
	UI_ShowOperatorInfo("配置车道","请选择配置项");
	Set_WorkStation(200);
	UI_Show_Info(ShowInfo20);
}
void WorkStation_200_SetConfig(int nKey)
{
	switch (nKey)
	{
	case VK_1:
		SetWorkStation_201_SetLanInfo();
		break;
	case VK_2:
		SetWorkStation_202_SetCommunction();
		break;
	case VK_3:
		SetWorkStation_203_SetCommunction();
		break;
	case VK_4:
		SetWorkStation_205_SetMode();
		break;
	case VK_CANCEL:
		Set_WorkStation_30_SelectWorkMod();
		break;
	default:
		echoic("%d",nKey);
		ErrorPressKey();
		break;
	}
}

//=============================================================================================================================================
char *ShowInfo201 = "提示：\n1：路网号<%s>\n2：配置站代码<%s>\n3：车道号<%s>\n4：配置上下行<%c>\n按【确认】键保存\n按【取消】键返回";
//=====================
void SetWorkStation_201_SetLanInfo()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	UI_ShowOperatorInfo("基本信息","请选择配置项");
	SetWorkState(201);
	sprintf(tempinfo,ShowInfo201,GetNetNoConfig(),GetPlazaNoConfig(),GetLanConfigLaneNo(),GetLanConfigLaneType());
	UI_Show_Info(tempinfo);
	initConfig();
}
static void ShowNewInfo201(void)
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	switch (EditConfig)
	{
		case 1:
			sprintf(tempinfo,ShowInfo201,Input,GetPlazaNoConfig(),GetLanConfigLaneNo(),GetLanConfigLaneType());
			break;
		case 2:
			sprintf(tempinfo,ShowInfo201,GetNetNoConfig(),Input,GetLanConfigLaneNo(),GetLanConfigLaneType());
			break;
		case 3:
			sprintf(tempinfo,ShowInfo201,GetNetNoConfig(),GetPlazaNoConfig(),Input,GetLanConfigLaneType());
			break;
		case 4:
			sprintf(tempinfo,ShowInfo201,GetNetNoConfig(),GetPlazaNoConfig(),GetLanConfigLaneNo(),Input[0] ==0 ? ' ':Input[0]);
			break;
	}
		UI_Show_Info(tempinfo);
}
void ShowSelectitem201(void)
{
	switch (EditConfig)
	{
	case 1:
		UI_ShowOperatorInfo("基本信息","路网号");
		break;
	case 2:
		UI_ShowOperatorInfo("基本信息","配置站代码");
		break;
	case 3:
		UI_ShowOperatorInfo("基本信息","车道号");
		break;
	case 4:
		UI_ShowOperatorInfo("基本信息","配置上下行");
		break;
	}
}
void SaveLanInfo201(void)
{
	char *Item ="";
	char SysCommamd[200];
	memset(SysCommamd,0x00,200);
	switch (EditConfig)
	{
	case 1:
		Item = "NetNo";
		break;
	case 2:
		Item = "PlazaNo";
		break;
	case 3:
		Item = "LaneNo";
		break;
	case 4:
		Item = "LaneType";
		break;
	}
	if(0!=EditConfig)
	{
		sprintf(SysCommamd,"sed -i \"s/%s.\\{0,20\\}=.\\{0,20\\}<.\\{0,30\\}>/%s=<%s>/g;\" "LANECONFIGFILENAME_FILE,Item,Item,Input);
		echoic("%s",SysCommamd);
		system(SysCommamd);
		LoadLanConfig();
		SetWorkStation_201_SetLanInfo();
		UI_Show_Help_Info("数据已保存");
	}
}
void WorkStation_201SetLanInfo(int nKey)
{
	switch (nKey)
	{
	case VK_1:
	case VK_2:
	case VK_3:
	case VK_4:
		if (0==EditConfig)
		{
			EditConfig =ChangCodeInt(nKey);
			ShowSelectitem201();
		}
		else
		{
			sprintf(Input+strlen(Input),"%c",ChangCodeChar(nKey));
			ShowNewInfo201();
		}
		break;
	case VK_5:
	case VK_6:
	case VK_7:
	case VK_8:
	case VK_9:
	case VK_0:
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		if (0!=EditConfig)
		{
			sprintf(Input+strlen(Input),"%c",ChangCodeChar(nKey));
			ShowNewInfo201();
		}
		break;
	case VK_RETURN:
		SaveLanInfo201();
		break;
	case VK_CANCEL:
		if(0!=EditConfig)
		{
			if(0==strlen(Input))
			{
				SetWorkStation_201_SetLanInfo();
			}
			else
			{
				Input[strlen(Input)-1] = 0x00;
				ShowNewInfo201();
			}
		}
		else
		{
			SetWorkStation_200_SetConfig();
		}
		break;
	default:
		echoic("%d",nKey);
		ErrorPressKey();
		break;
	}
}
//=================================================================================================================================
char *ShowInfo202 = "提示：\n1: 消息服务器IP<%s>\n2：FTP服务器IP<%s>\n3：校时服务器<%s>\n4：TCO服务器IP<%s>\n按【确认】键保存\n按【取消】键返回";
void SetWorkStation_202_SetCommunction()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);	
	UI_ShowOperatorInfo("通讯配置","请选择配置项");
	SetWorkState(202);
	sprintf(tempinfo,ShowInfo202,GetMagServerIP(),GetFtpServerIP(),GetTimeServerIP(),GetTCOServerIP());
	UI_Show_Info(tempinfo);
	initConfig();
}
void ShowNewInfo202(void)
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	switch (EditConfig)
	{
	case 1:
		sprintf(tempinfo,ShowInfo202,Input,GetFtpServerIP(),GetTimeServerIP(),GetTCOServerIP());
		break;
	case 2:
		sprintf(tempinfo,ShowInfo202,GetMagServerIP(),Input,GetTimeServerIP(),GetTCOServerIP());
		break;
	case 3:
		sprintf(tempinfo,ShowInfo202,GetMagServerIP(),GetFtpServerIP(),Input,GetTCOServerIP());
		break;
	case 4:
		sprintf(tempinfo,ShowInfo202,GetMagServerIP(),GetFtpServerIP(),GetTimeServerIP(),Input);
		break;
	}
	UI_Show_Info(tempinfo);
}
void ShowSelectitem202(void)
{
	switch (EditConfig)
	{
	case 1:
		UI_ShowOperatorInfo("通讯配置","消息服务器IP");
		break;
	case 2:
		UI_ShowOperatorInfo("通讯配置","FTP服务器IP");
		break;
	case 3:
		UI_ShowOperatorInfo("通讯配置","校时服务器IP");
		break;
	case 4:
		UI_ShowOperatorInfo("通讯配置","TCO服务器IP");
		break;
	}
}
void SaveLanInfo202(void)
{
	char *Item="";
	char SysCommamd[200];
	memset(SysCommamd,0x00,200);
	switch (EditConfig)
	{
	case 1:
		Item = "MagServerIP";
		break;
	case 2:
		Item = "FtpServerIP";
		break;
	case 3:
		Item = "TimeServerIP";
		break;
	case 4:
		Item = "TCOServerIP";
		break;
	}
	if(0!=EditConfig)
	{
		sprintf(SysCommamd,"sed -i \"s/%s.\\{0,20\\}=.\\{0,20\\}<.\\{0,30\\}>/%s=<%s>/g;\" "CONFCOMMUNCTION_FILE,Item,Item,Input);
		system(SysCommamd);
		LoadCommunctionConfig();
		SetWorkStation_202_SetCommunction();
		UI_Show_Help_Info("数据已保存");
	}
}

void WorkStation_202_SetCommunction(int nKey)
{
	switch (nKey)
	{
	case VK_1:
	case VK_2:
	case VK_3:
	case VK_4:
		if (0==EditConfig)
		{
			EditConfig =ChangCodeInt(nKey);
			ShowSelectitem202();
		}
		else
		{
			sprintf(Input+strlen(Input),"%c",ChangCodeChar(nKey));
			ShowNewInfo202();
		}
		break;
	case VK_5:
	case VK_6:
	case VK_7:
	case VK_8:
	case VK_9:
	case VK_0:
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_GONGWU:
		if (0!=EditConfig)
		{
			sprintf(Input+strlen(Input),"%c",ChangCodeChar(nKey));
			ShowNewInfo202();
		}
		break;
	case VK_RETURN:
		SaveLanInfo202();
		break;
	case VK_CANCEL:
		if(0!=EditConfig)
		{
			if(0==strlen(Input))
			{
				SetWorkStation_202_SetCommunction();
			}
			else
			{
				Input[strlen(Input)-1] = 0x00;
				ShowNewInfo202();
			}
		}
		else
		{
			SetWorkStation_200_SetConfig();
		}
		break;
	default:
		echoic("%d",nKey);
		ErrorPressKey();
		break;
	}
}
//====================================================================================================================================
char *ShowInfo203 = "提示：\n1: 金额显示器串口<%d>\n2：票据打印机串口<%d>\n3：计重串口<%d>\n4：读卡器串口<%d>\n按【确认】键保存\n按【取消】键返回";
void SetWorkStation_203_SetCommunction()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	UI_ShowOperatorInfo("串口配置","请选择配置项");
	sprintf(tempinfo,ShowInfo203,Get_LEDCOM(),Get_PrintCOM(),Get_WeightCOM(),Get_ICCOM());
	SetWorkState(203);
	UI_Show_Info(tempinfo);
	initConfig();
}
void ShowNewInfo203(void)
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	switch (EditConfig)
	{
	case 1:
			sprintf(tempinfo,ShowInfo203,atoi(Input),Get_PrintCOM(),Get_WeightCOM(),Get_ICCOM());
		break;
	case 2:
			sprintf(tempinfo,ShowInfo203,Get_LEDCOM(),atoi(Input),Get_WeightCOM(),Get_ICCOM());
		break;
	case 3:
			sprintf(tempinfo,ShowInfo203,Get_LEDCOM(),Get_PrintCOM(),atoi(Input),Get_ICCOM());
		break;
	case 4:
			sprintf(tempinfo,ShowInfo203,Get_LEDCOM(),Get_PrintCOM(),Get_WeightCOM(),atoi(Input));
		break;
	}
	UI_Show_Info(tempinfo);
}
void ShowSelectitem203(void)
{
	switch (EditConfig)
	{
	case 1:
		UI_ShowOperatorInfo("串口配置","金额显示器串口");
		break;
	case 2:
		UI_ShowOperatorInfo("串口配置","票据打印机串口");
		break;
	case 3:
		UI_ShowOperatorInfo("串口配置","计重串口");
		break;
	case 4:
		UI_ShowOperatorInfo("串口配置","读卡器串口");
		break;
	}
}
void SaveLanInfo203(void)
{
	char *Item="";
	char SysCommamd[200];
	memset(SysCommamd,0x00,200);
	switch (EditConfig)
	{
	case 1:
		Item = "LEDCOM";
		break;
	case 2:
		Item = "PrintCOM";
		break;
	case 3:
		Item = "WeightCOM";
		break;
	case 4:
		Item = "ICCOM";
		break;
	}
	if(0!=EditConfig)
	{
		sprintf(SysCommamd,"sed -i \"s/%s[ \\t.]\\{0,20\\}=.\\{0,20\\}<.\\{0,30\\}>/%s=<%s>/g;\" "TTYCONFIG_FILE,Item,Item,Input);
		echoic("%s",SysCommamd);
		system(SysCommamd);
		LoadTTyConfig();
		SetWorkStation_203_SetCommunction();
		UI_Show_Help_Info("数据已保存");
	}
}
void WorkStation_203_SetDevConfig(int nKey)
{
	switch (nKey)
	{
	case VK_1:
	case VK_2:
	case VK_3:
	case VK_4:
		if (0==EditConfig)
		{
			EditConfig =ChangCodeInt(nKey);
			ShowSelectitem203();
		}
		else
		{
			sprintf(Input,"%c",ChangCodeChar(nKey));
			ShowNewInfo203();
		}
		break;
		/*if (0!=EditConfig)
		{
			sprintf(Input+strlen(Input),"%c",ChangCodeChar(nKey));
			ShowNewInfo203();
		}
		break;*/
	case VK_RETURN:
		SaveLanInfo203();
		break;
	case VK_CANCEL:
		if(0!=EditConfig)
		{
			if(0==strlen(Input))
			{
				SetWorkStation_203_SetCommunction();
			}
			else
			{
				Input[strlen(Input)-1] = 0x00;
				ShowNewInfo203();
			}
		}
		else
		{
			SetWorkStation_200_SetConfig();
		}
		break;
	default:
		echoic("%d",nKey);
		ErrorPressKey();
		break;
	}
}
char *ShowInfo205 = "提示：\n1: 计重功能模式<%c>\n2：费率计算模式<%c>\n3：票据样式<%c>\n按【确认】键保存\n按【取消】键返回";

void SetWorkStation_205_SetMode()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	UI_ShowOperatorInfo("收费模式配置","请选择配置项");
	sprintf(tempinfo,ShowInfo205,GetWeightFunctions(),GetCalculateFareMode(),GetPrinterMode());
	SetWorkState(205);
	UI_Show_Info(tempinfo);
	initConfig();
}

void ShowNewInfo205(void)
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	switch (EditConfig)
	{
	case 1:
			sprintf(tempinfo,ShowInfo205,Input[0],GetCalculateFareMode(),GetPrinterMode());
		break;
	case 2:
			sprintf(tempinfo,ShowInfo205,GetWeightFunctions(),Input[0],GetPrinterMode());
		break;
	case 3:
			sprintf(tempinfo,ShowInfo205,GetWeightFunctions(),GetCalculateFareMode(),Input[0]);
		break;
	}
	UI_Show_Info(tempinfo);
}
void ShowSelectitem205(void)
{
	switch (EditConfig)
	{
	case 1:
		UI_ShowOperatorInfo("收费模式配置","计重功能模式[0-3]");
		break;
	case 2:
		UI_ShowOperatorInfo("收费模式配置","费率计算模式[0-1]");
		break;
	case 3:
		UI_ShowOperatorInfo("收费模式配置","票据样式[0-3]");
		break;
	}
}
void SaveLanInfo205(void)
{
	char SysCommamd[200];
	memset(SysCommamd,0x00,200);
	switch (EditConfig)
	{
	case 1:
		sprintf(SysCommamd,"sed -i \"s/^G[0-9][0-9][0-9]/G%c%c%c/g;\" %s",Input[0],GetCalculateFareMode(),GetPrinterMode(),PARACONSTANT_FILE);
		break;
	case 2:
		sprintf(SysCommamd,"sed -i \"s/^G[0-9][0-9][0-9]/G%c%c%c/g;\" %s",GetWeightFunctions(),Input[0],GetPrinterMode(),PARACONSTANT_FILE);
		break;
	case 3:
		sprintf(SysCommamd,"sed -i \"s/^G[0-9][0-9][0-9]/G%c%c%c/g;\" %s",GetWeightFunctions(),GetCalculateFareMode(),Input[0],PARACONSTANT_FILE);
		break;
	}
	if(0!=EditConfig)
	{
		echoic("%s",SysCommamd);
		system(SysCommamd);
		LoadConstantRecord(ISLOADFIRST);
		SetWorkStation_205_SetMode();
		UI_Show_Help_Info("数据已保存");
	}
}
void WorkStation_205_SetMode(int nKey)
{
	switch (nKey)
	{
	case VK_1:
	case VK_2:
	case VK_3:
		if (0==EditConfig)
		{
			EditConfig =ChangCodeInt(nKey);
			ShowSelectitem205();
			break;
		}
	case VK_0:
		if (0!=EditConfig)
		{
			if(2==EditConfig&&ChangCodeChar(nKey)>'1')
			{
				break;
			}
			sprintf(Input,"%c",ChangCodeChar(nKey));
			ShowNewInfo205();
		}
		break;
	case VK_RETURN:
		SaveLanInfo205();
		break;
	case VK_CANCEL:
		if(0!=EditConfig)
		{
			if(0==strlen(Input))
			{
				SetWorkStation_205_SetMode();
			}
			else
			{
				Input[strlen(Input)-1] = 0x00;
				ShowNewInfo205();
			}
		}
		else
		{
			SetWorkStation_200_SetConfig();
		}
		break;
	default:
		echoic("%d",nKey);
		ErrorPressKey();
		break;
	}
}
