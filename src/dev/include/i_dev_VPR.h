#ifndef __i_dev_VPR__
#define __i_dev_VPR__

int CPSB_Load(void);
int CPSB_UnLoad(void);
int DVR_Open(void);
void DVR_Close(void);
char * GetCPHM(char *cp);
 void ClearCPHM(void);
#endif
