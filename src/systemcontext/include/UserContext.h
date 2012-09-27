#ifndef __UserContext_H__
#define __UserContext_H__
#define  COLLECTORTYPE_CONLLECTOR '1'//收费员
#define  COLLECTORTYPE_VINDICATOR  '2'// 维护员


void InitCancelCount(void);
void AddCancelCount(void);
int GetCancelCount(void);
void SetInput_Number_Count(int var);
void InitInput_Number_Count(void);
void AddInput_Number_Count(void);
int GetInput_Number_Count(void);
void AddInput_Password_Count(void);
int GetInput_Password_Count(void);
void AddInputLen(void);
int GetInputLen(void);
void SetG_User_Index(int value);
void SetG_NumberByChar(char _C);
void SetInputLen(int value);
int GetG_User_Index(void);
void SetG_Number(char *value);
char *GetG_Number(void);
void IntiG_Password(void);
void SetG_Password(char *value);
void SetG_PasswordByChar(char _C);
void InitInput_Password_Count(void);
char *GetG_Password(void);
void SetsecondLogin(BOOL  value);
BOOL GetsecondLogin(void);
void Setg_szName(char *value);
char *Getg_szName(void);
void Setg_carboxNo(char * value);
char * Getg_carboxNo(void);
void SetG_collectType(char *value);
char GetG_collectType(void);
char * GetG_collectTypeStr(void);
void Setg_workStatus(char value);
char Getg_workStatus(void);
char * Getg_workStatus_str(void);
void Setg_szNum(char  *value);
char *Getg_szNum(void);
void Setg_szCode(char  *value);
char *Getg_szCode(void);
void Setg_sUserNum(char  value);
char Getg_sUserNum(void);
void InitG_Number(void);
void Initg_szName(void);
#endif

