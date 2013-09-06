#include "LocalIncludeFile.h"
#ifndef __From800_600_H__
#define __From800_600_H__

//界面对象
UI_Object * gui_title ;
UI_Object * gui_car_title ;
UI_Object * gui_carType_title ;
UI_Object * gui_PassCharge_title ;
UI_Object * gui_Payment_title ;
UI_Object * gui_EquipmentState_title ;
UI_Object * gui_car ;
UI_Object * gui_carType ;
UI_Object * gui_carTypeBJ ;
UI_Object * gui_PassCharge ;
UI_Object * gui_Payment ;
UI_Object * gui_EquipmentState ;
UI_Object * gui_Baojing ;
UI_Object * gui_Jiaotong ;
UI_Object * gui_Langan ;
UI_Object * gui_ZhuaPaiXianQuan_title ;
UI_Object * gui_TongGuoXianQuan_title ;
UI_Object * gui_ZhuaPaiXianQuan ;
UI_Object * gui_TongGuoXianQuan ;
UI_Object * gui_CarNoInfo ;
UI_Object * gui_RorwardEnterInfo ;
UI_Object * gui_ForwardChargeInfo ;
UI_Object * gui_ForwardPaymentInfo ;
UI_Object * gui_PassCarNum ;
UI_Object * gui_AutoLanganState ;
UI_Object * gui_WeightInfo ;
UI_Object * gui_OperateInfo ;
UI_Object * gui_WorkMode1 ;
UI_Object * gui_WorkMode2 ;
UI_Object * gui_CurrentWeightInfo ;
UI_Object * gui_Information ;
UI_Object * gui_Video ;
UI_Object * gui_InputDataArea ;
UI_Object * gui_ArrivedCarWeightInfo ;
UI_Object * gui_CardBoxInfo ;
UI_Object * gui_Yupeng ;
UI_Object * gui_Print ;
UI_Object * gui_Event_title ;
UI_Object * gui_Event ;
UI_Object * gui_CurrentTime ;
UI_Object * gui_LoginTime ;
UI_Object * gui_NowTime ;

UI_Object * gui_Login_USR_Panel ;
UI_Object * gui_Login_USR ;
UI_Object * gui_Login_PWD_Panel ;
UI_Object * gui_Login_PWD ;

UI_Object * gui_QK_QKD_Panel ;
UI_Object * gui_QK_QKD ;
UI_Object * gui_QK_QK_Panel ;
UI_Object * gui_QK_QK ;

UI_Object * gui_YH_Panel ;
UI_Object * gui_YH_YHK ;
//计重
UI_Object * gui_JZ_Panel ;
UI_Object * gui_ShiShou ;
UI_Object * gui_ZhaoLing ;
//称重菜单
#define CZMenu 10
//UI_Object * gui_CZMenu[CZMenu];

#define MenuItemItem 15
//菜单
UI_Object * gui_MenuFrom ;
//菜单项
#define MaxMenu 10
UI_Object * gui_Menu[MaxMenu];
//模拟
#define MaxMenuMoni 5
//UI_Object * gui_MenuMoni[MaxMenuMoni];

void UI_Out_800_600_InitFrom(HWND hWnd);
void UI_Out_800_600_LoadRes(void);
void UI_Out_800_600_ShowLoginTime_MMI( char *szInfo);
void UI_Out_800_600_ShowTime_MMI(char * szInfo );
void UI_Out_800_600_ShowDeviceState_MMI(int btnindex,BOOL flag);
void UI_Out_800_600_ClearAbateChargeEditC(void);
void UI_Out_800_600_SetMainFromColor(int nBkColor);
void UI_Out_800_600_Show_BigFont(int nEditAt, short sVal,BOOL Flag);
void UI_Out_800_600_Show_Image(int  nEditAt ,int index);
void UI_Out_800_600_Show_Edit(int nEditAt, char *pszInfo);
void UI_Out_800_600_Show_Info_ByColor(char *pszInfo, unsigned int  bc,unsigned int  tc);
void UI_Out_800_600_Show_Info(char *pszInfo);
void UI_Out_800_600_Set_Help_Info(char *pszInfo);
void UI_Out_800_600_Set_From_Title(char* szTitle);
void UI_Out_800_600_Show_Input(char * Type);
void UI_Out_800_600_ShowOperatorInfo(char *pszInfo);
//主窗口句柄
void UI_Out_800_600_Set_From_Handl(HWND hwnd);
HWND  UI_Out_800_600_Get_From_Handl(void);

void UI_Out_800_600_Draw_LoginFrom_GUI ( void );
void UI_Out_800_600_Set_Pwd(char *UserNumber);
void UI_Out_800_600_Set_UserNumber(char *UserNumber);
void UI_Out_800_600_Show_Input_Text(char * Text);
void Draw_InputDataArea_GUI ( void );


void Draw_MenuFrom_GUI ( char *menuName , UI_Object ** Menu,int length);
void Draw_MenuHide(void);
void Draw_MenuMoni_GUI(void);
void Set_MenuMoni_Enable(int index,int flag);
void Set_MenuMoni_Check(int index,int flag);


void Set_MenuCZ_Enable(int index,int flag);
int Get_MenuCZ_Enable(int index);
void Set_MenuCZ_Check(int index,int flag);
int Get_MenuCZ_Check(int index);


void Draw_MenuForArray(char *menuName , char ** Menu,int length);
void Draw_MenuHide(void);
void Set_JZData(int Axles,float TotalWeight,float WeightLimit,int Speed,float OverloadWeight,float FareWeight,float OverLoadRate);
void Draw_JZFrom_GUI(void);

void UI_Out_800_600_SetHistory(void);
void UI_Out_800_600_ClearHistory(void);

void UI_Out_800_600_Set_ShiShou(char *temp);
void UI_Out_800_600_Set_ZaoLing(char *temp);
#endif 

