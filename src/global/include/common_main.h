#ifndef _commonality_H_
#define _commonality_H_

#define U32 unsigned int
#define U16 unsigned short
#define S32 int
#define S16 short int
#define U8  unsigned char
#define	S8  char

#define UINT16 U16
#define UINT32 U32
#define UINT8  U8

#define TRUE 	1   
#define FALSE 	0

#define TRUE_C 	'1'   
#define FALSE_C '0'
#define BOOL   int
#define VOID   void

#define BYTE   S8
#define WORD   S16
#define DWORD  S32


struct GRADATE {
	unsigned int sec:6;
	unsigned int min:6;
	unsigned int hour:5;
	unsigned int day:5;
	unsigned int month:4;
	unsigned int year:6;
};


#define DATETIME_FORMAT_YYYYMMDDHHMMSS          "1yyyyMMddhhmmss1"
#define DATETIME_FORMAT_YYYYMMDDWHHMMSS          "1yyyyMMddwhhmmss1"
#define DATETIME_FORMAT_YYYYMMDDHHOOOO          "1yyyyMMddhhoooo1"
#define DATETIME_FORMAT_YYYYMMDDHHMM            "2yyyyMMddhhmm2"
#define DATETIME_FORMAT_YYYYMMDDHH              "3yyyyMMddhh3"
#define DATETIME_FORMAT_YYYYMMDDHHM				"4yyyyMMddhh4"
#define DATETIME_FORMAT_YYYY_MM_DD_HH_MM_SS     "5yyyy-MM-dd hh:mm:ss5"
#define DATETIME_FORMAT_HH_MM_SS_5			    "5hh:mm:ss5"
#define DATETIME_FORMAT_YYYY_MM_DD_5			"5yyyy-MM-dd5"
#define DATETIME_FORMAT_YYYYMMDD                "6yyyyMMDD6"
#define DATETIME_FORMAT_HHMMSS                  "7HHMMSS7"
#define DATETIME_FORMAT_HHOOOO                  "7HHOOOO7"
#define DATETIME_FORMAT_YYYY                    "8YYYY8"
#define DATETIME_FORMAT_MMDD                    "9MMDD9"
#define DATETIME_FORMAT_YYYY_MM_DD				"10yyyy-MM-dd01"

#define ADDTIME_TYPE_DAY    'D'
#define ADDTIME_TYPE_HOUR   'H'
#define ADDTIME_TYPE_MIN    'M'
#define ADDTIME_TYPE_SEC    'S'

#include "linux_include.h"

char *GetFormatTime(char *Format,time_t FormatTime);
char *GetTime(char *Format);
char *GetTimeAddTime(char *Format,int InputAddValues,char InputTimeType);
int LoadFile(char *InputFileName,char *LoadInFileStr,int FilrStrLength);
int LoadIniFile(char *InputIniFileName);
char  *readItemInIniFile(char *ItemName);
int DiffDataTime(char *InputStarttTime,char *InputEndTime);
int DiffCurrentDataTime(char *InputTime);
void GEA2Time(char* Dest, int DestLen, const char* Src, int SrcLen);
int GetLunKey(char *userID, char *lunKey);
unsigned char Find(unsigned char InputChar);
void EMRC2GEATime(char* Dest, int DestLen, const char* Src, int SrcLen, BOOL IsLongFormat);
void AddField(char *InputField,int FieldLength);
void AddFieldAtValue(char *InputField,int FieldLength,int InputAddFieldValue);
void SetFieldAtValue(char *InputField,int FieldLength,int InputAddFieldValue);
char* Int2String(int value);
char* Int2String_Ex(int value,char* format);
char* float2String_Ex(int value,char* format);
int charstoint(char * chars,int charslenght);
char * trim(char * src);
char * trim_ex(char * src,char c);
char * rightStr(char * instr,int ilen,int iright) ;
int alltrim(char* str);
#define  SUBSTRING(_src_)   substring(_src_,sizeof(_src_))
#define  STRING2FLOAT(_TO_)    atof(SUBSTRING(_TO_))

char * substring( char * src, int lenght);

char * PadLeft(char bychar,char *str,char *_padleft ,int len );
char * FormatDate(char *datetimestring);
void CopyFile(char *sFile ,char * dFile);
void DeleteImages(void);
void SyncToDo(char *command);
void SetTm(char *InputFirstTime, struct tm *rtc_time);
char* InitAndCPYStr(char *A, int lengthA, char *B, int lengthB, int b0);
#define InitAndCPYStrEx(A,B) InitAndCPYStr(A,sizeof(A),  (char *)&B,sizeof(B),1)
#define InitAndCPYStrEx2(A,B) InitAndCPYStr( (char *)&A,sizeof(A),B,strlen(B),0)
#define AddFieldAtValueEX(_InputField_, _InputAddFieldValue_)  AddFieldAtValue(_InputField_,sizeof(_InputField_),_InputAddFieldValue_)
#define AddFieldEX(_InputField_)  AddField(_InputField_,sizeof(_InputField_))
#endif


