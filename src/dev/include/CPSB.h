#ifndef __CPSB_H__
#define __CPSB_H__

int CPSB_Load(void);
int CPSB_UnLoad(void);
int DVR_Open(void);
void DVR_Close(void);
char * GetCPHM(char *cp);
 void ClearCPHM(void);
#endif
