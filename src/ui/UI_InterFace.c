
#include "LocalIncludeFile.h"
#include "From_640_480.h"
#include "From_800_600.h"
#include "Version.h"
/*******************************************************************************************/
//窗体句柄
/*******************************************************************************************/
HWND  UI_Get_From_Handl(void)
{
	if (DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		return UI_Out_640_480_Get_From_Handl();

	}
	else
	{
		return UI_Out_800_600_Get_From_Handl();
	}
}
void UI_Set_From_Handl(HWND hwnd)
{	
	UI_Out_640_480_Set_From_Handl(hwnd);
}

/*******************************************************************************************/
//窗体初始化
//系统资源载入
//窗体标题
/*******************************************************************************************/
void UI_InitFrom(HWND hWnd)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_InitFrom(hWnd);
		UI_Set_From_Title();
		UI_Show_Info("提示：\n上班请按【上班】键。");  
	}
	else
	{
		UI_Out_800_600_InitFrom(hWnd);
		UI_Set_From_Title();
		UI_Show_Info("提示：\n上班请按【上班】键。");
		UI_WorkMode1("关闭");
		UI_WorkMode2("关闭");
	}
}
void UI_WorkMode1(char *pszInfo)
{
	if(DISPPLAY_640_480 != UI_DISPLAY_RESOLUTION)
	{
		set_Text ( gui_WorkMode1 , pszInfo ) ;
	}
}
void UI_WorkMode2(char *pszInfo)
{
	if(DISPPLAY_640_480 != UI_DISPLAY_RESOLUTION)
	{
		set_Text ( gui_WorkMode2 , pszInfo ) ;
	}
}
void UI_Out_SetHistory(void)
{
	if(DISPPLAY_640_480 != UI_DISPLAY_RESOLUTION)
	{
		UI_Out_800_600_SetHistory();
	}
}
void UI_Out_ClearHistory(void)
{
	if(DISPPLAY_640_480 != UI_DISPLAY_RESOLUTION)
	{
		UI_Out_800_600_ClearHistory();
	}
}
void UI_LoadRes()
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_LoadRes();
	}
	else
	{
		UI_Out_800_600_LoadRes();
	}
}
void UI_Set_From_Title( void)
{
	char title[200];
	char cname[20];
	if (strlen(trim(Getg_szName()))!=0)
	{
		sprintf(cname,"%s",trim(Getg_szName()));
	}
	else
	{
		sprintf(cname,"%s","无");
	}
	sprintf(title,"%s-车道%s-操作员:%s-工作模式:%s %s [%02d]",GetLanConfigPlazaDesc(),GetLanConfigLaneNo(),trim(Getg_szName()),Getg_workStatus_str(),PROVER,GetWorkState());
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Set_From_Title(UI_Get_From_Handl(), title);
	}
	else
	{
		UI_Out_800_600_Set_From_Title(title);
	}
}

/*******************************************************************************************/
//车型、车种、金额
/*******************************************************************************************/
static void UI_In_showInputDateToFace(int nKey,int showControlIndex,char *storDataVar)
{	
	char szTmp[2] = "";
	nKey = KeyChangCode(nKey);	
	sprintf(szTmp, "%c%c", nKey,'\0');	
	if(Getg_carTypeLen()==1 )
	{
		strncpy(storDataVar, szTmp,2);	
	}
	else
	{
		strncat(storDataVar, szTmp,2);
	}
	//strncpy(storDataVar, szTmp,2);		
	InitCancelCount();	
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{			
		UI_Out_640_480_Show_BigFont(showControlIndex, atoi(storDataVar),F);			
	}
	else
	{
		UI_Out_800_600_Show_Edit(showControlIndex, storDataVar);
	}

}
void UI_SetMethodPay(int carKindIndex )
{
	if(DISPPLAY_640_480 != UI_DISPLAY_RESOLUTION)	
	{		
		UI_Out_800_600_Show_Edit(3,GetMethodPayText(GetCarKindChar(carKindIndex)));
	}
}
void UI_SetCarKind(int carKindIndex )
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Image(1,atoi(SUBSTRING(CarKindRecord[carKindIndex].imageIndex)));
		
	}
	else
	{		
		UI_Out_800_600_Show_Edit(1,GetCarKindNameByIndex(carKindIndex));
		UI_SetMethodPay(carKindIndex);
	}
}
void UI_ClearCarKind(void)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(0, "");
	}
	else
	{
		UI_Out_800_600_Show_Edit(0, "？");
		UI_Out_800_600_Show_Edit(3, "");
	}

}
void UI_ClearCarType(void)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(1, "");
	}
	else
	{
		UI_Out_800_600_Show_Edit(1, "");
	}
}

void UI_SetCarType(int nKey)
{
	UI_In_showInputDateToFace(nKey, 0,Get_Current_Car_Type());
	I_DEV_VDM_CarType(Get_Current_Car_Type());
}
void UI_ShowTruck()
{
	if(GetWeightCarClass()==WeightCarClassBUS?F:T)
	{
		char temp[10];
		memset(temp,0x00,10);
		sprintf(temp,"货%s",Get_Current_Car_Type());
		UI_Out_800_600_Show_Edit(0,temp);
	}
	else
	{
		UI_Out_800_600_Show_Edit(0,Get_Current_Car_Type());
	}
}
void UI_ClearCarMoney(void)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(2, "");
	}
	else
	{
		UI_Out_800_600_Show_Edit(2, "");
	}
}
void UI_SetCarMoney(short money)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_BigFont(2, money ,T);
	}
	else
	{
		UI_Out_800_600_Show_BigFont(2, money ,T);
	}
}
/*******************************************************************************************/
//设置左、右提示框的信息
/*******************************************************************************************/
void UI_ShowOperatorInfo(char *LeftInfor,char *RightInfo)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(3,LeftInfor);
		UI_Out_640_480_Show_Edit(4,RightInfo);
	}
	else
	{
		UI_Out_800_600_ShowOperatorInfo(LeftInfor);
	}
}
void UI_ShowLeftInfo (char *TempInfor )
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(3,TempInfor);
	}
	else
	{
		UI_Out_800_600_Show_Edit(3,TempInfor);
	}
}
void UI_ShowRightInfo(char *TempInfor )
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(4,TempInfor);
	}
	else
	{
		UI_Out_800_600_Show_Edit(4,TempInfor);
	}
}

void UI_ShowMenu(char *menuname,char *title, char *Info)
{
	char *Menu[10];
	int i=0;
	char *split = "\n";
	char *resu;
	char str[500];
	char temp[200];
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		sprintf(temp, title, Info);
		UI_Show_Info(temp);
	}
	else
	{
		sprintf(temp, title,"\n");
		UI_Show_Info(temp);
		strcpy(str,Info);
		resu = strtok(str,split);
		while(resu!=NULL)
		{
			Menu[i++] = resu;
			resu = strtok(NULL,split);
		}
		Draw_MenuForArray(menuname, Menu, i);
	}
}
/*******************************************************************************************
信息输入窗口
*******************************************************************************************/

void UI_Draw_Input_Text(char *Title)
{
	
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(3,Title);
	}
	else
	{
		UI_Out_800_600_Show_Input(Title);
	}
}
void UI_Show_Input_Text(char *Info)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(4,Info);
	}
	else
	{
		UI_Out_800_600_Show_Input_Text(Info);
	}
}

/*******************************************************************************************
用户登录
*******************************************************************************************/
void UI_Draw_Login_UserNmber(char *Info)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(3,Info);
		UI_Out_640_480_Show_Edit(4,"");
	}
	else
	{
		UI_Out_800_600_Draw_LoginFrom_GUI();
	}
}
void UI_Draw_Login_UserPwd(char *Info)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(3,Info);
		UI_Out_640_480_Show_Edit(4,"");
	}
}
void UI_Show_UserNumber_Text(char *Info)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(4,Info);
	}
	else
	{
		UI_Out_800_600_Set_UserNumber(Info);
	}
}
void UI_Show_Login_UserPwd(char *Info)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Edit(4,Info);
	}
	else
	{
		UI_Out_800_600_Set_Pwd(Info);
	}
}
void UI_Clear_Login_And_Input()
{
	if(DISPPLAY_800_600 == UI_DISPLAY_RESOLUTION)
	{	
		Draw_InputDataArea_GUI ( ) ;		
	}
}
/*******************************************************************************************
系统提示信息
系统帮助信息
*******************************************************************************************/
void UI_Show_Info(char *pszInfo)
{
	strcpy(GetG_CurrentInfo(),pszInfo); 
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Show_Info(pszInfo);
	}
	else
	{
		UI_Out_800_600_Show_Info(pszInfo);
	}
}
void UI_Show_Help_Info(char *pszInfo)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_Set_Help_Info(pszInfo);
	}
	else
	{
		UI_Out_800_600_Set_Help_Info(pszInfo);
	}
	g_nHelpTimer = 1;
}
void UI_MsgBox(char *strTitle, char *strSubTitle,BOOL good, char *Format,...)
{
	if (strTitle!=NULL)
	{
		UI_ShowLeftInfo( strTitle);
	}
	if (strSubTitle!=NULL)
	{
		UI_ShowRightInfo(strSubTitle);
	}
	if (Format!=NULL)
	{
		if (good)
		{
			UI_Show_Info(Format);
		}
		else
		{
			strcpy(GetG_CurrentInfo(),Format); 
			if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
			{
				UI_Out_640_480_Show_Info_ByColor(Format,TISHI_BACK_COLOR,RGB(250, 40, 40));
			}
			else
			{
				UI_Out_800_600_Show_Info_ByColor(Format,TISHI_BACK_COLOR,RGB(250, 40, 40));
			}
		}
	}
}
void UI_ClearAbateChargeEditC()
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_ClearAbateChargeEditC();
	}
	else
	{
		UI_Out_800_600_ClearAbateChargeEditC();
	}
}

/*******************************************************************************************/
//设置窗体颜色
/*******************************************************************************************/
void UI_SetFromColor(BOOL isLOGIN)
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_SetMainFromColor(isLOGIN?GLOAB_BACK_COLOR:WND_BACK_COLOR);
	}
	else
	{
		UI_Out_800_600_SetMainFromColor(isLOGIN?GLOAB_BACK_COLOR:WND_BACK_COLOR);
	}
}
/*******************************************************************************************/
//设置上班时间、系统当前时间
/*******************************************************************************************/
void UI_ShowNowTime(char * szInfo )
{
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		UI_Out_640_480_ShowTime_MMI(szInfo);
	}
	else
	{
		UI_Out_800_600_ShowTime_MMI(szInfo);
	}
}
void UI_ShowLoginTime(BOOL bEmpty)
{
	char *szInfo ;
	szInfo=GetUpdatedLoginTime(bEmpty);
	if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
	{
		
		UI_Out_640_480_ShowLoginTime_MMI( szInfo);
	}
	else
	{
		UI_Out_800_600_ShowLoginTime_MMI( szInfo);
	}

}
/*******************************************************************************************/
//控制界面上外设状态
/*******************************************************************************************/
void UI_Set_Device_State(int btnindex,BOOL bFlag)
{
	if (0==btnindex)
	{
		if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
		{
			UI_Out_640_480_ShowDeviceState_MMI(1,bFlag);
			UI_Out_640_480_ShowDeviceState_MMI(2,bFlag);
			UI_Out_640_480_ShowDeviceState_MMI(3,bFlag);
			UI_Out_640_480_ShowDeviceState_MMI(4,bFlag);
			UI_Out_640_480_ShowDeviceState_MMI(5,bFlag);
			UI_Out_640_480_ShowDeviceState_MMI(6,bFlag);
		}
		else
		{
			UI_Out_800_600_ShowDeviceState_MMI(1,bFlag);
			UI_Out_800_600_ShowDeviceState_MMI(2,bFlag);
			UI_Out_800_600_ShowDeviceState_MMI(3,bFlag);
			UI_Out_800_600_ShowDeviceState_MMI(4,bFlag);
			UI_Out_800_600_ShowDeviceState_MMI(5,bFlag);
			UI_Out_800_600_ShowDeviceState_MMI(6,bFlag);
			UI_Out_640_480_ShowDeviceState_MMI(7,bFlag);
		}
	}
	else
	{
		if(DISPPLAY_640_480 == UI_DISPLAY_RESOLUTION)
		{
			UI_Out_640_480_ShowDeviceState_MMI(btnindex,bFlag);
		}
		else
		{
			UI_Out_800_600_ShowDeviceState_MMI(btnindex,bFlag);
		}
	}
}
void UI_Show_WeightData()
{
	float Weight;
	Weight= GetWeightContext_DevWeight();
	echoic("Weight = <%f>",Weight);
	if(NotUseWeight != GetWeightFunctions())
	{
		Set_JZData
			(
			
			GetFareContext_CarAxleNumber(),
			GetWeightContext_DevWeight(),
			GetWeightContext_WeightLimit_ByTon(),
			GetWeightContext_Speed(),
			GetWeightContext_OverLoadWeight(),
			GetFareContext_CarWeight(),
			GetWeightContext_OverLoadWeightRate()
			
			
			);
		Draw_JZFrom_GUI();
	}
}
void UI_Show_ZhaoLing(int je)
{
	char temp[50];
	sprintf(temp,"实收：%4d",je);
	UI_Out_800_600_Set_ShiShou(temp);
	sprintf(temp,"找零：%4.2f",je-Get_G_Current_Actual_pay());
	UI_Out_800_600_Set_ZaoLing(temp);

}
