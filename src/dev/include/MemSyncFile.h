#ifndef _MemSyncFile_H_
#define _MemSyncFile_H_
void LoadMemSyncFile(void);
struct ParameterVersion *GetSyncParameterVersion(void);
struct MSG_EXITES *LoadMsgExitESFromFile(void);
struct MSG_EXITHT *LoadMsgExitHtFromFile(void);
struct MSG_HOUR *GetSyncMsgHour(void);
struct MSG_NewTifficStat *LoadMsgNewCountFromFile(char *FileName);
#endif
