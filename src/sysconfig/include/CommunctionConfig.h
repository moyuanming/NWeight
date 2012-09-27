#ifndef _CommunctionConfig_H_
#define _CommunctionConfig_H_

char *GetMagServerIP(void);
int GetMsgServerProt(void);
char *GetFtpServerIP(void);
int GetFtpServerProt(void);
char *GetFtpUserName(void);
char *GetFtpPwd(void);
char *GetTimeServerIP(void);

void LoadCommunctionConfig(void);
char *GetNtpDateCommand(void);
char *GetTCOServerIP(void);
int GetTCOPort(void);
char *GetSVRCARDLIST(void);
char *GetJOUCODE(void);
char *GetKEYFILE(void);
#endif

