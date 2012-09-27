#ifndef __DAL_IMF_H__
#define __DAL_IMF_H__
#ifndef TRUE
	#define TRUE 	1 
#endif 
#ifndef FALSE
	#define FALSE 	0
#endif 
#ifndef T
	#define T 	1  
#endif 
#ifndef F
	#define  F 	0
#endif 
#ifndef BOOL 
	#define BOOL   int
#endif 
//#define      USR_Start1   0x55 
//#define       USR_Start2   0xAA 

char * substring( char * src, int lenght);

#define  SUBSTRING(_src_)   substring(_src_,sizeof(_src_))

BOOL COM_Open(char *comname);
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
void Dal_imf_Set_fd_com(int idfcom);
BOOL  USR_SelectSAM(int iSAM) ;

#endif 
