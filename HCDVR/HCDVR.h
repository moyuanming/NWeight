#ifndef _HCDVR_H_
#define _HCDVR_H_

extern "C" int DVR_Open(void);
extern "C" void DVR_Close(void);
extern "C" char * GetCPHM(char *cp);
extern "C" void ClearCPHM(void);
#endif
