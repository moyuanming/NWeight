#ifndef __GLOBAL_IC_METHODS_H__
#define __GLOBAL_IC_METHODS_H__
int G_IC_strDec2Hex(char* sDec,int iDecLen,char* sHex,int iHexLen);//10进制字符转成16进制字符
int G_IC_strBin2Hex(char* sDec,int iBinLen,char* sHex,int iHexLen);//2进制字符转成16进制字符
int G_IC_strBin2Dec(char* sBin,int iBinLen,char* sDec,int iDecLen);//2进制字符转成10进制字符
int G_IC_strHex2Dec(char* sHex,int iHexLen,char* sDec,int iDecLen);//16进制字符转成10进制字符
int G_IC_strHex2Bin(char* sHex,int iHexLen,char* sBin,int iBinLen);//16进制字符转成2进制字符
int G_IC_strDec2Bin(char* sDec,int iDecLen,char* sBin,int iBinLen);//10进制字符转成2进制字符
int G_IC_strTim2Hex(char* sTim,int iTimLen,char* sHex,int iHexLen);//14位时间字符->16进制字符(4byte)
int G_IC_strHex2Tim(char* sHex,int iHexLen,char* sTim,int iTimLen);//16进制字符(4byte)->14位时间字符
void G_IC_strChr2Hex(char* sChr,int iChrLen,char* sHex,int iHexLen);//英文字符(包括数字字符)(1)->16进制字符(2)
void G_IC_strHex2Chr(char* sHex,int iHexLen,char* sChr,int iChrLen);//16进制字符(2)->英文字符(包括数字字符)(1)
					void G_IC_itoa(unsigned long val,char *buf,unsigned radix);												// 
																	// 
#endif
