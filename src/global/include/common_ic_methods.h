#ifndef __GLOBAL_IC_METHODS_H__
#define __GLOBAL_IC_METHODS_H__
int G_IC_strDec2Hex(char* sDec,int iDecLen,char* sHex,int iHexLen);//10�����ַ�ת��16�����ַ�
int G_IC_strBin2Hex(char* sDec,int iBinLen,char* sHex,int iHexLen);//2�����ַ�ת��16�����ַ�
int G_IC_strBin2Dec(char* sBin,int iBinLen,char* sDec,int iDecLen);//2�����ַ�ת��10�����ַ�
int G_IC_strHex2Dec(char* sHex,int iHexLen,char* sDec,int iDecLen);//16�����ַ�ת��10�����ַ�
int G_IC_strHex2Bin(char* sHex,int iHexLen,char* sBin,int iBinLen);//16�����ַ�ת��2�����ַ�
int G_IC_strDec2Bin(char* sDec,int iDecLen,char* sBin,int iBinLen);//10�����ַ�ת��2�����ַ�
int G_IC_strTim2Hex(char* sTim,int iTimLen,char* sHex,int iHexLen);//14λʱ���ַ�->16�����ַ�(4byte)
int G_IC_strHex2Tim(char* sHex,int iHexLen,char* sTim,int iTimLen);//16�����ַ�(4byte)->14λʱ���ַ�
void G_IC_strChr2Hex(char* sChr,int iChrLen,char* sHex,int iHexLen);//Ӣ���ַ�(���������ַ�)(1)->16�����ַ�(2)
void G_IC_strHex2Chr(char* sHex,int iHexLen,char* sChr,int iChrLen);//16�����ַ�(2)->Ӣ���ַ�(���������ַ�)(1)
					void G_IC_itoa(unsigned long val,char *buf,unsigned radix);												// 
																	// 
#endif
