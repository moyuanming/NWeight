#ifndef  __FileContext_H__
#define  __FileContext_H__



void SetG_CurrentInfo(char * value);
char *GetG_CurrentInfo(void);
void SetG_CurrentInfoTemp(char  * value);
char *GetG_CurrentInfoTemp(void);

int Getg_AbateType(void);
void Setg_AbateType(int  value);
void SetMaxvolume(int  value);
int GetMaxvolume(void);
void SetMinvolume(int  value);
int GetMinvolume(void);
void  InitfileState(void);
void SetLoadYPKListRecordFlag(int  value);
void SetLoadYHKListRecordFlag(int  value);
void SetLoadCollectRecordFlag(int  value);
void SetLoadYHRateDescriptionRecordFlag(int  value);
void SetLoadFareRecordFlag(int  value);
void SetLoadCarKindRecordFlag(int  value);
int  GetLoadYPKListRecordFlag(void);
int  GetLoadCollectRecordFlag(void);
int  GetFareRecordFlag(void);
int  GetLoadCarKindRecordFlag(void);
int  GetLoadYHKListRecordFlag(void);
int  GetLoadYHRateDescriptionRecordFlag(void);
#endif
