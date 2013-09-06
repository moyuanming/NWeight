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
char *ShowInfo20= "��ʾ��\n1�����ó���������Ϣ\n2�����ó���ͨѶ����\n3���������贮��\n4���շ�ģʽ����\n����ȡ���������ء�";
void SetWorkStation_200_SetConfig()
{	
	UI_ShowOperatorInfo("���ó���","��ѡ��������");
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
char *ShowInfo201 = "��ʾ��\n1��·����<%s>\n2������վ����<%s>\n3��������<%s>\n4������������<%c>\n����ȷ�ϡ�������\n����ȡ����������";
//=====================
void SetWorkStation_201_SetLanInfo()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	UI_ShowOperatorInfo("������Ϣ","��ѡ��������");
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
		UI_ShowOperatorInfo("������Ϣ","·����");
		break;
	case 2:
		UI_ShowOperatorInfo("������Ϣ","����վ����");
		break;
	case 3:
		UI_ShowOperatorInfo("������Ϣ","������");
		break;
	case 4:
		UI_ShowOperatorInfo("������Ϣ","����������");
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
		UI_Show_Help_Info("�����ѱ���");
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
char *ShowInfo202 = "��ʾ��\n1: ��Ϣ������IP<%s>\n2��FTP������IP<%s>\n3��Уʱ������<%s>\n4��TCO������IP<%s>\n����ȷ�ϡ�������\n����ȡ����������";
void SetWorkStation_202_SetCommunction()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);	
	UI_ShowOperatorInfo("ͨѶ����","��ѡ��������");
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
		UI_ShowOperatorInfo("ͨѶ����","��Ϣ������IP");
		break;
	case 2:
		UI_ShowOperatorInfo("ͨѶ����","FTP������IP");
		break;
	case 3:
		UI_ShowOperatorInfo("ͨѶ����","Уʱ������IP");
		break;
	case 4:
		UI_ShowOperatorInfo("ͨѶ����","TCO������IP");
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
		UI_Show_Help_Info("�����ѱ���");
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
char *ShowInfo203 = "��ʾ��\n1: �����ʾ������<%d>\n2��Ʊ�ݴ�ӡ������<%d>\n3�����ش���<%d>\n4������������<%d>\n����ȷ�ϡ�������\n����ȡ����������";
void SetWorkStation_203_SetCommunction()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	UI_ShowOperatorInfo("��������","��ѡ��������");
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
		UI_ShowOperatorInfo("��������","�����ʾ������");
		break;
	case 2:
		UI_ShowOperatorInfo("��������","Ʊ�ݴ�ӡ������");
		break;
	case 3:
		UI_ShowOperatorInfo("��������","���ش���");
		break;
	case 4:
		UI_ShowOperatorInfo("��������","����������");
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
		UI_Show_Help_Info("�����ѱ���");
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
char *ShowInfo205 = "��ʾ��\n1: ���ع���ģʽ<%c>\n2�����ʼ���ģʽ<%c>\n3��Ʊ����ʽ<%c>\n����ȷ�ϡ�������\n����ȡ����������";

void SetWorkStation_205_SetMode()
{
	char tempinfo[200];
	memset(tempinfo,0x00,200);
	UI_ShowOperatorInfo("�շ�ģʽ����","��ѡ��������");
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
		UI_ShowOperatorInfo("�շ�ģʽ����","���ع���ģʽ[0-3]");
		break;
	case 2:
		UI_ShowOperatorInfo("�շ�ģʽ����","���ʼ���ģʽ[0-1]");
		break;
	case 3:
		UI_ShowOperatorInfo("�շ�ģʽ����","Ʊ����ʽ[0-3]");
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
		UI_Show_Help_Info("�����ѱ���");
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
