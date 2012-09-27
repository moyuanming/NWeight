#ifndef __MAC_H__
#define __MAC_H__


char * PadRight(char *strvalue ,int n,char c ,char * ___PadRight);
char * Substring(char* value ,int start,int len,char * ____Substring);
unsigned char* Hex2Bin(char * values,unsigned char* ___Hex2Bin);
char * Bin2Hex( unsigned char* values,int len,unsigned char* _____Bin2Hex);
char *   XOR(  char* data,   char* data2,int bLenght,char * _______XOR);

void  MAC_E(char* data,int dataLength, char * ran, char * key16,char * result);
char * MAC(char* data,int dataLength, char * ran, char * key16);
char *   MAC8(char * data,int dataLength, char * ran, char * key8);

#endif 
