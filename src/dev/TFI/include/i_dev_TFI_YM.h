#ifndef __i_dev_TFI_YM_H__
#define __i_dev_TFI_YM_H__
void TFI_YM_Init(void);
void TFI_YM_Close(void);
void TFI_YM_SoundOuther(char *tmp);
void TFI_YM_BaoJia_ForThread(void);
void TFI_YM_clean(BOOL IsSound);
void  TFI_YM_LedShow(int CarType, int charge);
void TFI_YM_SetTongXingDeng(BOOL bFlag);
void TFI_YM_SetHuangShan(BOOL bFlag);
void  TFI_YM_BaoJia(int CarType, int charge);
void  TFI_YM_BJ(void);
void YM_SZ(float   value, int soundtype);
#endif
