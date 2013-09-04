#ifndef __i_dev_TFI_STD_H__
#define __i_dev_TFI_STD_H__
void TFI_STD_Init(void);
void TFI_STD_Close(void);
void TFI_STD_BaoJia_ForThread(void);
void TFI_STD_clean(BOOL IsSound);
void  TFI_STD_LedShow(int CarType, int charge);
void TFI_STD_SetTongXingDeng(BOOL bFlag);
void TFI_STD_SetHuangShan(BOOL bFlag);
void  TFI_STD_BaoJia(int CarType, int charge);
void  TFI_STD_BJ(void);
void SendStdCMD(char cmd);
void ShowFullScreenText(char * content);
#endif
