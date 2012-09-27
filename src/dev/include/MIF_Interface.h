/********************************************************************
	created:	2008/06/12
	created:	12:6:2008   10:38
	filename: 	d:\LnTc\trunk\src\Lane\src\dev\include\MIF_Interface.h
	file path:	d:\LnTc\trunk\src\Lane\src\dev\include
	file base:	MIF_Interface
	file ext:	h
	author:		MYM
	
	purpose:	天线接口头文件
	Version:    $Id: MIF_Interface.h 5481 2008-06-13 05:18:05Z mym $
*********************************************************************/



#ifndef __MIF_Interface_H__
#define __MIF_Interface_H__
#define PICC_REQIDL 0x26
#define PICC_REQALL 0x52
#define MIF_succeed             0 
#define MIF_ExistCard          1 
#define MIF_NoCard              2 
#define MIF_ExistCardNONum     3 
#define MI_OK				0
#define MI_CHK_OK			0
#define MI_CRC_ZERO			0
#define MI_CRC_NOTZERO		1
#define MI_NOTAGERR			-1
#define OpenErr				-1
#define MI_CHK_FAILED		-1
#define MI_CRCERR			-2
#define MI_CHK_COMPERR		-2
#define MI_EMPTY			-3
#define MI_AUTHERR			-4
#define MI_PARITYERR		-5
#define MI_CODEERR			-6
#define MI_SERNRERR			-8
#define MI_KEYERR			-9
#define MI_NOTAUTHERR		-10
#define MI_BITCOUNTERR		-11
#define MI_BYTECOUNTERR		-12
#define MI_IDLE				-13
#define MI_TRANSERR			-14
#define MI_WRITEERR			-15
#define MI_INCRERR			-16
#define MI_DECRERR			-17
#define MI_READERR			-18
#define MI_OVFLERR			-19
#define MI_POLLING			-20
#define MI_FRAMINGERR		-21
#define MI_ACCESSERR		-22
#define MI_UNKNOWN_COMMAND	-23
#define MI_COLLERR			-24
#define MI_RESETERR			-25/*复位错误 IC 没有正确响应*/
#define MI_INITERR			-25
#define MI_INTERFACEERR		-26
#define MI_ACCESSTIMEOUT	-27
#define MI_NOBITWISEANTICOLL -28
#define MI_QUIT -30
#define MI_RECBUF_OVERFLOW	-50
#define MI_SENDBYTENR		-51
#define MI_SENDBUF_OVERFLOW			-53
#define MI_BAUDRATE_NOT_SUPPORTED	-54
#define MI_SAME_BAUDRATE_REQUIRED	-55
#define MI_WRONG_PARAMETER_VALUE	-60
 int MIFSelectEx(void *ArgMifRegPtr,unsigned int ArgCardSN,unsigned char ArgSector,unsigned char ArgKey,unsigned char ArgKeySet);
int MIFReadCRC(void *ArgMifRegPtr,unsigned char ArgBlock,unsigned char *ArgBuffer);
int MIFWriteCRC(void *ArgMifRegPtr,int ArgBlock,unsigned char *ArgBuffer);
int MIFHalt(void *ArgMifRegPtr );
int MIFReset(void *ArgMifRegPtr,unsigned char ResetTime );
void CloseBuzzSwitch(void);
#endif


