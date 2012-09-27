#ifndef __DeviceContext_H__
#define __DeviceContext_H__

void SetroadCridState(char value);
char GetroadCridState(void);
void SetconnectState(BOOL  value);
BOOL  GetconnectState(void);
void SetConnectCount(int  value);
int GetConnectCount(void);
void SetenabledConnect(BOOL value);
BOOL  GetenabledConnect(void);
void SetmessageThreadSleeped(BOOL value);
BOOL  GetmessageThreadSleeped(void);
void SetG_AbateNumber(char *value);
char *GetG_AbateNumber(void);
void SetG_AbateNumber_Index(int  value);
int GetG_AbateNumber_Index(void);
void Setg_SocketState(BOOL  value);
BOOL  Getg_SocketState(void);
void Setg_SocketTimeOut(int value);
int Getg_SocketTimeOut(void);
void Setg_SocketUseTimeCount(int  value);
int Getg_SocketUseTimeCount(void);
void  InitG_AbateNumber(void);
void  SETG_AbateNumber_end(int  value);
void SetG_SerialCommandDev(unsigned  char value);
char GetG_SerialCommandDev(void);
void SetG_SerialCommandDev_or(unsigned char value);
void SetG_SerialCommandDev_and(unsigned char value);
char * GetCardNOByString(void);
unsigned int GetCardNO(void);
void SetCardNO( unsigned int inputequestcardNum );
BOOL IsCardExist(void);
void SetCardExist(BOOL ice);
void SetCardInReader(BOOL ice);
BOOL IsCardInReader(void);

void  InitG_CarAxlesNum(void);
char *GetG_CarAxlesNum(void);

void SetG_WeightMenuStues(int value);
int GetG_WeightMenuStues(void);

void  InitG_ZhaoLing(void);
char *GetG_ZhaoLing(void);
#endif

