 
#include<stdio.h> 
#include<stdint.h>
#include<string.h>
#include<ctype.h>
#include "3des.h"
#include "mac.h"
#define echomac(fmt, args...)   fprintf(stderr,"IMF:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
static int strToHex(char * str)
{
	int ret=0;
	switch (tolower(*str))
	{
		case'0' :
			ret=0*16;
			break;
		case'1' :
			ret=1*16;
			break;
		case'2' :
			ret=2*16;
			break;
		case'3' :
			ret=3*16;
			break;
		case'4' :
			ret=4*16;
			break;
		case'5' :
			ret=5*16;
			break;
		case'6' :
			ret=6*16;
			break;
		case'7' :
			ret=7*16;
			break;
		case'8' :
			ret=8*16;
			break;
		case'9' :
			ret=9*16;
			break;
		case'a' :
			ret=10*16;
			break;
		case'b' :
			ret=11*16;
			break;
		case'c' :
			ret=12*16;
			break;
		case'd' :
			ret=13*16;
			break;
		case'e' :
			ret=14*16;
			break;
		case'f' :
			ret=15*16;
			break;

	}



	switch (tolower(*(str+1)))
	{
		case'0':
			ret+=0;
			break;
		case'1':
			ret+=1;
			break;
		case'2':
			ret+=2 ;
			break;
		case'3':
			ret+=3 ;
			break;
		case'4':
			ret+=4 ;
			break;
		case'5':
			ret+=5 ;
			break;
		case'6':
			ret+=6 ;
			break;
		case'7':
			ret+=7 ;
			break;
		case '8':
			ret+=8 ;
			break;
		case '9':
			ret+=9 ;
			break;
		case 'a':
			ret+=10 ;
			break;
		case'b':
			ret+=11 ;
			break;
		case'c':
			ret+=12 ;
			break;
		case'd':
			ret+=13 ;
			break;
		case'e':
			ret+=14 ;
			break;
		case'f':
			ret+=15 ;
			break;

	}
	return ret;
}
/*在右边补充n个字符c*/
char * PadRight(char *strvalue ,int n,char c ,char * ___PadRight )
{
	char ___PadRight1[1024];
	char _______prtmp[255];
	memset (___PadRight1,0x00,1024);
	memset (_______prtmp,c,255);
	sprintf (___PadRight1,"%s%s",strvalue,_______prtmp);		
	memcpy(___PadRight,___PadRight1,n);
	return ___PadRight;
}
;
/*取得字符串value第start开始len个字符的字符串*/
char * Substring(char* value ,int start,int len,char * ____Substring)
{
	memcpy( ____Substring, (char*)&value[start],len);
	____Substring[len]=0;
	return ____Substring;
}


unsigned char* Hex2Bin(char * values,unsigned char* ___Hex2Bin)
{
	int i ;
	unsigned char  temp[3];
	for ( i =0;i<strlen(values )/2;i++)
	{
		___Hex2Bin[i] = (   unsigned char)strToHex(Substring(values,i*2,2,temp));
	}
	return ___Hex2Bin;
}

char * Bin2Hex( unsigned char* values,int len,unsigned char* _____Bin2Hex)
{
	int i ;	
	for (i=0;i<len;i++)
	{
		sprintf((char*)&_____Bin2Hex[i*2],"%02X",((unsigned int)values[i]));
	}
	//printf("Bin2HEX=%s\r\n",_____Bin2Hex);
	return _____Bin2Hex; 
}
;
/*将两个数据异或，从data中输出结果*/
char *   XOR(  char* data,   char* data2,int len,char * _______XOR)
{
	int i ;
	int bLenght=len/2;
	unsigned char b[strlen(data)/2];
	unsigned char b2[strlen(data2)/2];
	Hex2Bin(data,b);
	Hex2Bin(data2,b2);
	for ( i = 0; i < bLenght; i++)
	{
		b[i] =  b[i]  ^  b2[i];
	}
	Bin2Hex(b,bLenght,_______XOR);
	return _______XOR;

}
 
EXPORT  void  MAC_E(char* data,int dataLength, char * ran, char * key16,char * result)
{

	memcpy(	result,MAC(data,dataLength,ran,key16),8);
 
}
char ___MAC[9];
char * MAC(char* data,int dataLength, char * ran, char * key16)
{
	int key16Length =32 ;
	char keya[17];
	char keyb[17];
	char d3[17];
	char d4[17];
	char result[17];
	memcpy( keya ,key16, key16Length / 2);
	memcpy( keyb  , (char*)&key16[key16Length / 2],key16Length / 2);
	keya[16]=0;
	keyb[16]=0;
	memset( d3 ,0x00,sizeof(d3));
	memset( d4 ,0x00,sizeof(d3));
	memset( result,0x00,sizeof(16));
	echomac("bb");
	if (dataLength >= 16)
	{
		unsigned char Ran9[9];
		unsigned char PrTemp[17];
		memcpy(d3, data, 16);
		PrTemp[16] = 0x00;
		d3[16]=0;
		XOR(PadRight(Substring(ran,0,8,Ran9), 16, '0',PrTemp),  d3,16,result);
		echomac("bb");
		if (dataLength % 16 == 0)
		{
			int i ;
			for ( i = 1; i <dataLength / 16; i++)
			{
				unsigned char resultBin[8],keyaBin[8] ;				;
				enc(Hex2Bin(keya,keyaBin), Hex2Bin(result,resultBin));
				Bin2Hex(resultBin,8,result);
				printf( result);
				Substring(data,i * 16, 16,d3);
				XOR(result, d3,16,result);
				memcpy(d4 , (char*)&"8000000000000000",16);
				echomac("bb");
			}
			if (dataLength == 16) 
			{
				memcpy(d4 ,"8000000000000000",16);
			}
			echomac("bb");
			unsigned char temp222[8];Hex2Bin(result,temp222);
			unsigned char keyaXXX[8];Hex2Bin(keya,keyaXXX);
			unsigned char keybXXX[8];Hex2Bin(keyb,keybXXX);
			enc(keyaXXX, temp222);
			Bin2Hex(temp222,8,result);			
			XOR(result, d4,16,result);			
			Hex2Bin(result,temp222);
			enc(keyaXXX, temp222);
			Bin2Hex(temp222,8,result);			
			dec(keybXXX, temp222);
			Bin2Hex(temp222,8,result);			
			enc(keyaXXX, temp222);
			Bin2Hex(temp222,8,result);	
			echomac("bb");
		}
		else
		{
			
			int i ;
			unsigned char keyaXXX1[8];Hex2Bin(keya,keyaXXX1);
			unsigned char keybXXX1[8];Hex2Bin(keyb,keybXXX1);
			echomac("bb");
			for ( i = 1; i < dataLength / 16; i++)
			{
				unsigned char temp4441[8];Hex2Bin(result,temp4441);
				unsigned char temp4442keya[8];Hex2Bin(keya,temp4442keya);
				enc(temp4442keya, temp4441);
				Bin2Hex(temp4441,8,result);
				Substring(data, i * 16, 16,d3);
				XOR(result, d3,16,result);
			}
			Substring(data,dataLength - dataLength % 16, dataLength % 16,d4);
			strcat(d4,"8");//可能有问题
			PadRight(d4,16, '0',d4);
			unsigned char temp555[8];Hex2Bin(result,temp555);
			enc(keyaXXX1, temp555);
			Bin2Hex(temp555,8,result);
			XOR(result,  d4,16,result);
			Hex2Bin(result,temp555);//temp555=Hex2Bin(result);
			enc(keyaXXX1, temp555);
			dec(keybXXX1, temp555);
			enc(keyaXXX1, temp555);
			Bin2Hex(temp555,8,result);
			echomac("bb");
		}
	}
	else
	{
		echomac("bb");
		unsigned char Ran9[9];
		unsigned char temp4442keya[8];Hex2Bin(keya,temp4442keya);
		unsigned char temp4442keyb[8];Hex2Bin(keyb,temp4442keyb);
		sprintf(d3,"%s%s",data,"8");
		PadRight(d3,16, '0',d3);
		PadRight(Substring(ran,0,8,Ran9),16,'0',result);
		XOR( result, d3,16,result);
		unsigned char temp777[8];Hex2Bin(result,temp777);
		enc(temp4442keya, temp777);
		Bin2Hex(temp777,8,result);;
		dec(temp4442keyb, temp777);
		Bin2Hex(temp777,8,result);
		enc(temp4442keya, temp777);
		Bin2Hex(temp777,8,result);
		echomac("bb");
	}
	memset(___MAC,0x00,9);
	memcpy(___MAC,result,8);
	return ___MAC;

}


char ___MAC8[9];
EXPORT char *   MAC8(char * data,int dataLength, char * ran, char * key8)
{
	char result[17] ;
	char d3[17] ;
	char d4[17];
	unsigned char Ran9[9];
	unsigned char Prtwmp[17];
	unsigned char key8aaa[strlen(key8)/2];Hex2Bin(key8,key8aaa);
	if (dataLength >= 16)
	{
		
		Substring(data,0, 16,d3);
		Prtwmp[16] = 0x00;
		XOR(PadRight( Substring(ran,0,8,Ran9),16,'0',Prtwmp),d3,dataLength,result);
		result[16]=0;
		if (dataLength % 16 == 0)
		{
			unsigned char temp777[8];
			int i;
			for (  i = 1; i < dataLength / 16; i++)
			{
				Hex2Bin(result,temp777);//temp777=Hex2Bin(result);
				enc(key8aaa, temp777);
				Bin2Hex(temp777,8,result);
				Substring(data,i * 16, 16,d3);
				XOR(result, d3,16,result);
				memcpy(d4,(char *)"8000000000000000",16);
				d4[16] = 0x00;
			}
			if (dataLength == 16) 
			{
				memcpy(d4,(char*)"8000000000000000",16);
				d4[16] = 0x00;
			}
			Hex2Bin(result,temp777);
			enc(key8aaa, temp777);
			Bin2Hex(temp777,8,result);
			XOR(result, d4,16,result);
			Hex2Bin(result,temp777);
			enc(key8aaa, temp777);
			Bin2Hex(temp777,8,result);

		}
		else
		{
			int i;
			unsigned char tmp999[8];
			char *tmpx99x;
			unsigned char tmp999keya[strlen(key8)/2];Hex2Bin(key8,tmp999keya);
			for ( i= 1; i < dataLength / 16; i++)
			{
				unsigned char tmp888[8];Hex2Bin(result,tmp888);
				enc(key8aaa, tmp888);
				Substring(data,i * 16, 16,d3);
				Bin2Hex(tmp888,8,result);
				XOR(result, d3,16,result);

			}

			Substring(data,dataLength - dataLength % 16, dataLength % 16,d4);			
			strcat(d4,"8");
			PadRight(d4,16, '0',d4);
			Hex2Bin(result,tmp999);
			enc(tmp999keya, tmp999);
			Bin2Hex(tmp999,8,result);
			XOR(result, d4,16,result);
			Hex2Bin(result,tmp999);
			enc(tmp999keya, tmp999);
			Bin2Hex(tmp999,8,result);
		}
	}
	else
	{
		unsigned char tmp888111[8];
		unsigned char PdTemp[17];
		sprintf(d3,"%s%s", data, "8");
		PadRight(d3,16, '0',d3);
		PdTemp[16] = 0;
		XOR(PadRight( Substring(ran,0, 8,Ran9),16, '0',PdTemp), d3,16,result);
		Hex2Bin(result,tmp888111);
		enc(key8aaa, tmp888111);
		Bin2Hex(tmp888111,8,result);
	}
	memset(___MAC8,0x00,9);
	memcpy(___MAC8,result,8);
	return ___MAC8;
}

