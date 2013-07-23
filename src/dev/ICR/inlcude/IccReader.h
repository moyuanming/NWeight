// IccReader.h : main header file for the IccReader DLL
//

#ifndef _ICCREADER_H
#define _ICCREADER_H

#include <stdio.h>
#include <stdlib.h>

 
 
#ifndef BYTE
typedef unsigned char BYTE;
#endif
#ifndef UINT
typedef unsigned int UINT;
#endif
#ifndef DWORD
typedef unsigned long DWORD;
#endif

#define MAX_FRAME_SIZE   512

//机具支持的卡类型
#define MIFARE_ONE      0x00			//只支持mifire one 卡
#define MIFARE_PRO      0x01			//只支持mifire pro 卡
#define MIFARE_CARD     0x02			//两种卡均支持
#define DESFIRE_CARD	0x03			//只支持DESFIRE 卡
#define ALL_CARD		0x04			//支持所有卡

//密钥类型
#define KEYA            0x00
#define KEYB            0x04

//传输协议类型
#define PROTOCOL_CHAR	0x00			//面向字符的异步半双工传输协议
#define PROTOCOL_BLOCK	0x01			//面向块的异步半双工传输协议

//卡请求类型
#define REQUEST_IDLE	0x00			//仅请求空闲的
#define REQUEST_ALL		0x01			//请求所有

//卡座标志
#define NO_PSAM         0x00			//不带PSAM卡
#define PSAM1			0x01			//C2的PSAM1卡座
#define PSAM2			0x02			//C2的PSAM2卡座
#define PSAM3                   0x03
#define PSAM4                   0x04
#define PSAM1_C6		0x11			//C6的PSAM1卡座
#define PSAM2_C6		0x12			//C6的PSAM2卡座
#define NO_PRO			0x20			//不使用用户卡座，当由接触式转为非接触式时请选择此标志进行复位
#define PRO1			0x21			//C6等接触式机具用户卡座

//蜂鸣器
#define BEEP_OFF        0x80			//关闭蜂鸣器
#define BEEP_SHORT      0x81			//短鸣两声：D－D
#define BEEP_LASTING    0x82			//长鸣：D......
#define BEEP_TWINKLE    0x83			//隔50ms

#define  NO_CONTROL      0x00
//LED
#define LED_OFF         0x80			//LED关闭
#define LED_LASTING     0x81			//常亮
#define LED_SHORT       0x82			//亮800ms
#define LAMP_TWINKLE    0x83			//闪亮


//串口传输方式
#define TRANSMODE_HEX	0x01			//以十六进制数传输
#define TRANSMODE_ASC	0x02			//以ASC码传输

//数据位
#define DATABIT_EIGHT	0x08			//8个数据位
#define DATABIT_SEVEN	0x07			//7个数据位
#define DATABIT_SIX		0x06		//6个数据位

//停止位
#define STOPBIT_ONE		0x01			//1个停止位
#define STOPBIT_ONE5	0x02			//1.5个停止位
#define STOPBIT_TWO		0x03			//2个停止位

//校验位
#define PARITYS_NONE		0x00			//无奇偶校验
#define PARITYS_EVEN		0x01			//偶校验
#define PARITYS_ODD			0x02			//奇校验

//功率类型
#define T_MAXPOWER			0x02			//接触式方式工作时的最大发射功率
#define U_MINPOWER			0x03			//非接触式方式工作时的最小发射功率

//机具类型
#define READER_C2B			0x02
#define READER_C6			0x03
#define READER_C6B			0x04


/******************************************************************/
//常用函数
/******************************************************************/

int  HexToBin(unsigned char * shex,unsigned char * sbin,int shex_len);
void  BinToHex(unsigned char *sbin,unsigned char *shex,int sbin_len);
DWORD  HexToInt(char *hex);

/******************************************************************/
//机具控制接口
/******************************************************************/

int  Open_Reader(BYTE iComNo,int BaudRate, int cmdtype);
int  Close_Reader(BYTE iComNo);
int  IsReaderOpen(BYTE iComNo);
int  RD_SetBaud(BYTE iComNo,unsigned long baudrate);
unsigned long  RD_GetBaud(BYTE iComNo);
int  RD_SetMMI(BYTE iComNo,int beep,int green,int yellow);
int  GetLastTxFrame(BYTE iComNo,unsigned char *frame);
int  GetLastRxFrame(BYTE iComNo,unsigned char *frame);
//int  RD_SetTransMode(BYTE iComNo, int iReaderType = READER_C2B, int iTransMode = TRANSMODE_HEX, int nDataBits=DATABIT_EIGHT, int nParity=PARITYS_NONE, int nStopBits=STOPBIT_ONE);
int  RD_GetTransMode(BYTE iComNo, int *iReaderType, int *iTransMode, int *nDataBits, int *nParity, int *nStopBits);
int  RD_Test(BYTE iComNo);
int  RD_GetVersion(BYTE iComNo, char *version);


/***********************************************************/
//卡类共用和专用操作函数
/***********************************************************/

int  RF_Reset(BYTE iComNo);
//如果需要在接触式和非接触式PRO卡应用间切换，从接触式切换到非接触式时必需重新用NO_PRO复位
int  CPU_Reset(BYTE iComNo,int cmdtype, char *szATR);
int  Request_Card(BYTE iComNo,int RequestType, char *resdata);
int  Unticoll_Card(BYTE iComNo,char *cardno);
int  Unticoll_CardB(BYTE iComNo,char *cardno);
int  Select_Card(BYTE iComNo,char *cardno,char *resdata);
int  Open_Card(BYTE iComNo,DWORD *dwcardno);
int  Open_CardB(BYTE iComNo,char *cardno, int *len);
int  Get_CardType(BYTE iComNo);
int  Set_CardType(BYTE iComNo,UINT cardtype);
int  SAM_SetBaud(BYTE iComNo,DWORD baudrate);
int  PRO_SetProtocolCmd(BYTE iComNo);
int  DES_SetProtocolCmd(BYTE iComNo);
//在用户卡座有卡片正确插入时，下位机会对用户卡座复位，此函数执行成功将会切换到接触式操作。
int  ICC_Present(BYTE iComNo);
char*  Put_Error(int ret);
char*  ICC_Message(char *SW12);
char*  RD_GetErrInfo(BYTE iComNo, int iErrCode);

/***********************************************************/
//MIFARE ONE卡接口函数
/***********************************************************/
int  MF1_Authenticate(BYTE iComNo,int keytype,int sector,char* cardid );
int  MF1_LoadKeyB(BYTE iComNo,int keytype,int sector,unsigned char *key);
int  MF1_LoadKey(BYTE iComNo,int keytype,int sector,char *key);
int  MF1_AuthenticateBlock(BYTE iComNo,int keytype,int sector,int block);
int  MF1_AuthenticateWithKey(BYTE iComNo,int keytype,int sector,char *key,char *cardidL);
int  MF1_ReadBlock(BYTE iComNo,int block,char *data);
int  MF1_ReadBlockEx(BYTE iComNo,int block,int KeyType,char *KeyValue,char *data);
int  MF1_WriteBlock(BYTE iComNo,int block,char *data);
int  MF1_WriteBlockEx(BYTE iComNo,int block,int KeyType,char *KeyValue,char *data);
int  MF1_Restore(BYTE iComNo,int source,int target);
int  MF1_Value(BYTE iComNo,int block,DWORD value);
int  MF1_Increment(BYTE iComNo,int source,int target,DWORD value);
int  MF1_Decrement(BYTE iComNo,int source,int target,DWORD value);
int  MF1_Halt(BYTE iComNo);
int  MF1_AuthenticateFile(BYTE iComNo,int ifileID,int keyid);
int  MF1_ReadFileB(BYTE iComNo,int ifileID,int keyid,int start,int length,unsigned char *sReply);
int  MF1_ReadFile(BYTE iComNo,int ifileID,int keyID,int start,int length,char *sReply);
int  MF1_WriteFileB(BYTE iComNo,int ifileID,int keyid,int start,int length,unsigned char *sData);
int  MF1_WriteFile(BYTE iComNo,int ifileID,int keyID,int start,int length,char *sData);

/***********************************************************/
//PRO卡TimeCOS指令函数
/***********************************************************/

int  PRO_Command(BYTE iComNo,char *command,char *response);
int  PRO_CommandEx(BYTE iComNo,char* command,char*response,char* sw12);

/***********************************************************/
//SAM卡TimeCOS指令函数
/***********************************************************/

int  SAM_Command(BYTE iComNo,char *command,char *response);
int  SAM_CommandEx(BYTE iComNo,char *command,char *response,char* sw12);

 
#endif
