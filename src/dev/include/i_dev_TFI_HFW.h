#ifndef __i_dev_TFI_HFW_H__
#define __i_dev_TFI_HFW_H__
void TFI_HFW_Init(void);
void TFI_HFW_Close(void);
void TFI_HFW_SoundOuther(char *tmp);
void TFI_HFW_BaoJia_ForThread(void);
void TFI_HFW_clean(BOOL IsSound);
void  TFI_HFW_LedShow(int CarType, int charge);
void TFI_HFW_SetTongXingDeng(BOOL bFlag);
void TFI_HFW_SetHuangShan(BOOL bFlag);
void  TFI_HFW_BaoJia(int CarType, int charge);
void  TFI_HFW_BJ(void);
void HFW_SZ(float   value, int soundtype);
#endif
