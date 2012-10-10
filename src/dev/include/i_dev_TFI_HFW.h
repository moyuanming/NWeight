#ifndef __i_dev_TFI_HFW_H__
#define __i_dev_TFI_HFW_H__
static void TFI_HFW_Init(void);
void TFI_HFW_SoundOuther(char * tmp);
void  TFI_HFW_LedShow (int CarType , int charge );
void TFI_HFW_SetTongXingDeng(BOOL bFlag);
void TFI_HFW_SetHuangShan(BOOL bFlag);
void  TFI_HFW_BaoJia(int CarType, int charge);
int getloc(char *src, char c);
void HFW_SZ(float   value);
#endif
