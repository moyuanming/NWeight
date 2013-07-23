#ifndef __i_dev_VDM_SAT_H__
#define __i_dev_VDM_SAT_H__
void VDM_SAT_Init(void );
BOOL  VDM_SAT_SupportChinese(void);
void VDM_SAT_Clear(void );
int	VDM_SAT_TextOut(char *text,unsigned char l,unsigned char c,unsigned char  len);
void VDM_SAT_SyncTime(void);
void VDM_SAT_SyncTime_T(void);
#endif
