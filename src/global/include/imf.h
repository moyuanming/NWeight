#ifndef __IMF_H__
#define __IMF_H__
#define BOOL   int
BOOL COM_Open(char *comname);
#define      USR_Start1   0x55 
#define       USR_Start2   0xAA 
void COM_Close(void);
int BytesToRead(void);
void DiscardInBuffer(int  fd);
char *  SendCommand(unsigned char * buffer );
BOOL  EndsWith(char* src,char *endwith);
BOOL  StartsWith(char* src,char *startwith);
BOOL SelectPro(char * card)  ;
BOOL IsProCard(char * rex)  ;
char * RequestPro(void);
BOOL ResetPro(void)   ;
char * RATS(void)  ;
unsigned int Hex2UINT(char * hexvalue);
BOOL EXTERNAL_AUTHENTICATE(void);
char * GET_CHALLENGE(void);
char * GET_CHALLENGE_n(int len);
BOOL EXTERNAL_AUTHENTICATE_key(char * initkey);
char * ReadCardInfo(char * fileid,char *_ReadCardInfo);
char *  Write(char * info,char *tmpvalue,int loc ,int len);
int GetProType(char* tmpinfo);
char * Read(char * tempinfo,int loc ,int len);
BOOL ReadyCard(char * procard);
char * INITIALIZE_FOR_PURCHASE(void);
BOOL SELECT(char * fileid);
BOOL IMFVERIFY(char * param);
BOOL WriteCardInfo(char *cardinformation);

#endif 
