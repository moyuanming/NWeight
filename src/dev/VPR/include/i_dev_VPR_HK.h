#ifndef __i_dev_VPR_H__
#define __i_dev_VPR_H__

int VPR_HK_Load(void);
int VPR_HK_UnLoad(void);
int VPR_HK_Open(void);
void VPR_HK_Close(void);
char * VPR_HK_GetCPHM(char *cp);
 void VPR_HK_ClearCPHM(void);
#endif
