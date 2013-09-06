#ifndef __i_dev_VPR_H__
#define __i_dev_VPR_H__

int VPR_HW_Load(void);
int VPR_HW_UnLoad(void);
int VPR_HW_Open(void);
void VPR_HW_Close(void);
char * VPR_HW_GetCPHM(char *cp);
 void VPR_HW_ClearCPHM(void);
#endif
