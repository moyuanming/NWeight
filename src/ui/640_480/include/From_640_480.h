#ifndef __From640_480_H__
#define __From640_480_H__

void UI_Out_640_480_InitFrom(HWND hWnd);
void UI_Out_640_480_LoadRes(void);
void UI_Out_640_480_ShowLoginTime_MMI( char *szInfo);
void UI_Out_640_480_ShowTime_MMI(char * szInfo );
void UI_Out_640_480_ShowDeviceState_MMI(int btnindex,BOOL flag);
void UI_Out_640_480_ClearAbateChargeEditC(void);
void UI_Out_640_480_SetMainFromColor(int nBkColor);
void UI_Out_640_480_Show_BigFont(int nEditAt, short sVal,BOOL Flag);
void UI_Out_640_480_Show_Image(int  nEditAt ,int index);
void UI_Out_640_480_Show_Edit(int nEditAt, char *pszInfo);
void UI_Out_640_480_Show_Info_ByColor(char *pszInfo, unsigned int  bc,unsigned int  tc);
void UI_Out_640_480_Show_Info(char *pszInfo);
void UI_Out_640_480_Set_Help_Info(char *pszInfo);
void UI_Out_640_480_Set_From_Title(HWND hWnd, char* szTitle);
//Ö÷´°¿Ú¾ä±ú
void UI_Out_640_480_Set_From_Handl(HWND hwnd);
HWND  UI_Out_640_480_Get_From_Handl(void);
#endif 

