#ifndef __i_dev_TFI_RHY_H__
#define __i_dev_TFI_RHY_H__
void TFI_RHY_Init(void);
void TFI_RHY_clean(BOOL IsSound);
void  TFI_RHY_LedShow(int CarType, int charge);
void TFI_RHY_SetTongXingDeng(BOOL bFlag);
void TFI_RHY_SetHuangShan(BOOL bFlag);
void  TFI_RHY_BaoJia(int CarType, int charge);
#endif
