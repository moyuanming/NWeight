#ifndef __UI_InterFace_H__
#define __UI_InterFace_H__
#define DISPPLAY_640_480 640
#define DISPPLAY_800_600 800
#define UI_DISPLAY_RESOLUTION ((GetDisPlay_Resolution())==(640) ? (DISPPLAY_640_480):(DISPPLAY_800_600))

void Draw_MenuCZ_GUI(void);
void UI_InitFrom(HWND hWnd);
void UI_ClearCarKind(void);
void UI_ClearCarType(void);
void UI_Show_Info(char *pszInfo);
void UI_SetCarKind(int imgID );
void UI_SetFromColor(BOOL isLOGIN);
void UI_Set_From_Title( void);
void UI_ShowRightInfo(char  * TempInfor );
void UI_ShowOperatorInfo(char *LeftInfor,char *RightInfo);
void UI_ShowLeftInfo(char *TempInfor );
void UI_ClearCarMoney(void);
void UI_Input_NumberString(int nKey ,char * PutTo);
void UI_SetCarMoney(short money);
void UI_Set_Device_State(int btnindex,BOOL bFlag);
void UI_ShowNowTime(char * szInfo );
void UI_MsgBox(char *strTitle, char *strSubTitle,BOOL good ,char *Format,...);
void UI_Show_Help_Info(char *pszInfo);
void UI_ShowLoginTime(BOOL bEmpty);
void UI_SetCarType(int nKey);
void UI_ShowTruck(void);
void UI_LoadRes(void);
void UI_ClearAbateChargeEditC(void);
HWND  UI_Get_From_Handl(void);
void UI_Set_From_Handl(HWND hwnd);
void UI_ShowMenu(char *menuname,char *title, char *Info);

void UI_Draw_Login_UserNmber(char *Info);
void UI_Draw_Login_UserPwd(char *Info);
void UI_Show_UserNumber_Text(char *Info);
void UI_Show_Login_UserPwd(char *Info);
void UI_Clear_Login_And_Input(void);


void UI_Show_Input_Text(char *Info);
void UI_Draw_Input_Text(char *Title);
void UI_Show_WeightData(void);

void UI_WorkMode1(char *pszInfo);
void UI_WorkMode2(char *pszInfo);
void UI_Out_SetHistory(void);
void UI_Out_ClearHistory(void);

void UI_Show_ZhaoLing(int je);
#endif
