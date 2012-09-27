#include "LocalIncludeFile.h"
/************************************************************************/
/* 10进制字符转成16进制字符 liujl 2008.6.10                             */
/************************************************************************/
int G_IC_strDec2Hex(char* sDec,int iDecLen,char* sHex,int iHexLen)
{
	long c,a,b=16;
	int i=0,j=0;
	char temp[100],d[2],chtemp[100];
	a = atol(sDec);
	do
	{
		c=a%b;
		temp[ i]=c;
		i++;
	}while((a/=b)!=0);
	for(i--;i>=0;i--)
	{
		if(b==16&&(temp[ i]>=10&&temp[ i]<=15))
		{
//			print_emrc("x1%c",temp[ i]+55);
			sprintf(d,"%c",temp[i]+55);
			strncpy(chtemp+j,d,1);
		}
		else
		{
			memset(d,0,sizeof(d));
//			print_emrc("x2%d",temp[ i]);
			sprintf(d,"%d",temp[i]);
//			print_emrc("%s\n",d);
			strncpy(chtemp+j,d,1);
		}
		j = j+1;
	}
	strcpy(sHex,chtemp);
//	print_emrc("%s,%d\n",sHex,strlen(chtemp));

	return 0;
}

/************************************************************************/
/* 2进制字符转成16进制字符 liujl 2008.6.10                              */
/************************************************************************/
int G_IC_strBin2Hex(char* sDec,int iBinLen,char* sHex,int iHexLen)
{
	char chTemp[100];

	memset(chTemp,0x00,sizeof(chTemp));
	G_IC_strBin2Dec(sDec,strlen(sDec),chTemp,10);
	G_IC_strDec2Hex(chTemp,strlen(chTemp),sHex,16);

	return 0;
}

/************************************************************************/
/* 2进制字符转成10进制字符 liujl 2008.6.10                              */
/************************************************************************/
int G_IC_strBin2Dec(char* sBin,int iBinLen,char* sDec,int iDecLen)
{
	int i=0,iSum=0;
	char chTemp[65];

	memset(chTemp,0x00,sizeof(chTemp));
	strcpy(chTemp,sBin);
//	print_emrc("-->%s,%d\n",chTemp,iBinLen);
	for(i=0;i<iBinLen;i++)
	{
		if(chTemp[i]=='1')
		{
			iSum = iSum *2 + 1;
		}
		else
		{
			iSum = iSum*2 + 0;
		}

	}

	sprintf(sDec,"%d",iSum);
//	print_emrc("%s\n",sDec);
	return 0;
}

/************************************************************************/
/* 16进制字符转成10进制字符 liujl 2008.6.10                             */
/************************************************************************/
int G_IC_strHex2Dec(char* sHex,int iHexLen,char* sDec,int iDecLen)
{
	char chTemp[65];
	
	memset(chTemp,0x00,sizeof(chTemp));
	G_IC_strHex2Bin(sHex,iHexLen,chTemp,iDecLen);
	G_IC_strBin2Dec(chTemp,strlen(chTemp),sDec,iDecLen);
	return 0;
}

/************************************************************************/
/* 16进制字符转成2进制字符 liujl 2008.6.10                              */
/************************************************************************/
int G_IC_strHex2Bin(char* sHex,int iHexLen,char* sBin,int iBinLen)
{
	char sSrc[100];
//	char chCardDate[14];
	char chTemp[4];
	int i=0;
	memset(sSrc,0x00,sizeof(sSrc));
	for(i=0;i<iHexLen;i++)
	{
		if('0'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0000",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('1'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0001",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('2'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0010",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('3'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0011",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('4'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0100",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('5'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0101",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('6'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0110",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('7'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"0111",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('8'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1000",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('9'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1001",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('A'==sHex[i] || 'a'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1010",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('B'==sHex[i] || 'b'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1011",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('C'==sHex[i] || 'c'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1100",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('D'==sHex[i] || 'd'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1101",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('E'==sHex[i] || 'e'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1110",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
		else if('F'==sHex[i] || 'f'==sHex[i])
		{
			memset(chTemp,0x00,sizeof(chTemp));
			strncpy(chTemp,"1111",4);
			strncpy(sSrc+i*4,chTemp,4);
		}
	}
	
	strncpy(sBin,sSrc,strlen(sSrc));
//	print_emrc("%s\n",sBin);
	return 0;
}

/************************************************************************/
/* 10进制字符转成2进制字符 liujl 2008.6.10                              */
/************************************************************************/
int G_IC_strDec2Bin(char* sDec,int iDecLen,char* sBin,int iBinLen)
{
	int   number10, a[100],i=0,j=0;   
	char d[2],temp[100];
	long c;
	number10 = atoi(sDec);
	memset(a,0x00,sizeof(a));
	memset(temp,0x00,sizeof(temp));
	do
	{
		c=number10%2;
		a[i]=c;
		i++;
	}while((number10/=2)!=0);

	for(i--;i>=0;i--)
	{
		memset(d,0x00,2);
		sprintf(d,"%d",a[i]);
		temp[j]=d[0];
		j = j+1;
	}

	strncpy(sBin,temp,strlen(temp));

	return 0;
}

/************************************************************************/
/* 14位时间字符->16进制字符(4byte) liujl 2008.6.10                      */
/************************************************************************/
int G_IC_strTim2Hex(char* sTim,int iTimLen,char* sHex,int iHexLen)
{
	return 0;
}

/************************************************************************/
/* 16进制字符(4byte)->14位时间字符 liujl 2008.6.10                      */
/************************************************************************/
int G_IC_strHex2Tim(char* sHex,int iHexLen,char* sTim,int iTimLen)
{
	return 0;
}

/************************************************************************/
/* 英文字符(包括数字字符)(1)->16进制字符(2) liujl 2008.6.10             */
/************************************************************************/
void G_IC_strChr2Hex(char* sChr,int iChrLen,char* sHex,int iHexLen)
{
	int i=0;
	for (i=0;i<iChrLen;i++)
	{
		G_IC_itoa(*(sChr+i),sHex+i*2,16);
	}
}

/************************************************************************/
/* 16进制字符(2)->英文字符(包括数字字符)(1) liujl 2008.6.10             */
/************************************************************************/
void G_IC_strHex2Chr(char* sHex,int iHexLen,char* sChr,int iChrLen)
{
	char chTemp[65];

	memset(chTemp,0x00,sizeof(chTemp));
	G_IC_strHex2Bin(sHex,iHexLen,chTemp,iChrLen);
	G_IC_strBin2Dec(chTemp,strlen(chTemp),sChr,iChrLen);
}
 

/************************************************************************/
/* 时间转换 liujl 2008.6.10                                             */
/************************************************************************/
char chDateTime[15];
char *G_IC_ConvertDateTime(char strCardDate[8])
{
	char y[5],strTemp[10];
	int iYear;
	char chTemp[40];
	char chtye[5];
	char chtmo[5];
	char chtda[5];
	char chtho[5];
	char chtmi[5];
	char chtse[5];
	char chHex[5];
	char chCardDate[9];
//	char chDateTime[14];

	memset(chDateTime,0x00,sizeof(chDateTime));
	memset(chtye,0x00,sizeof(chtye));
	memset(chtmo,0x00,sizeof(chtmo));
	memset(chtda,0x00,sizeof(chtda));
	memset(chtho,0x00,sizeof(chtho));
	memset(chtmi,0x00,sizeof(chtmi));
	memset(chtse,0x00,sizeof(chtse));
	memset(chHex,0x00,sizeof(chHex));
	memset(chCardDate,0,sizeof(chCardDate));
	memset(y,0x00,sizeof(y));

	memset(chTemp,0,sizeof(chTemp));
	strncpy(chCardDate,strCardDate,8);
	if(strlen(strCardDate) < 8)
	{
		G_IC_strHex2Bin(chCardDate,strlen(chCardDate),chTemp,16);
		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp,6);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtye,4);

		//y = chtye;
		iYear = GlobalFunc_atoi(chtye,getmin(strlen(chtye),sizeof(chtye))) + 2000;
		sprintf(y,"%d",iYear);

		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp+6,4);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtmo,2);

		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp+10,5);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtda,2);

		sprintf(chDateTime,"%s%02d%02d",y,atoi(chtmo)%100,atoi(chtda)%100);
		chDateTime[8]=0x00;
		return chDateTime;
	}

	else
	{
		G_IC_strHex2Bin(chCardDate,strlen(chCardDate),chTemp,32);
		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp,6);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtye,4);
		iYear = GlobalFunc_atoi(chtye,getmin(strlen(chtye),sizeof(chtye))) + 2000;
		sprintf(y,"%d",iYear);

		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp+6,4);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtmo,2);

		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp+10,5);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtda,2);

		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp+15,5);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtho,2);

		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp+20,6);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtmi,2);

		memset(strTemp,0x00,sizeof(strTemp));
		strncpy(strTemp,chTemp+26,6);
		G_IC_strBin2Dec(strTemp,strlen(strTemp),chtse,2);

		sprintf(chDateTime,"%s%02d%02d%02d%02d%02d",y,atoi(chtmo)%100,atoi(chtda)%100,atoi(chtho)%100,atoi(chtmi)%100,atoi(chtse) %100);
		chDateTime[14] = 0x00;

		return chDateTime;
	}
}
 
/************************************************************************/
/* 转换时间 liujl 2008.6.12                                             */
/************************************************************************/
char strHex[10]; 
char *G_IC_MakeDateTime(char *strCardDate,int iSize)
{
	int ye,mo,da,ho,mi,se;
	long i=0;
//	char tye[100],tmo[100],tda[100],tho[100],tmi[100],tse[100];
	char sd[50];
	char strDec[15];

	char chTemp[15];
	char chtye[15];
	char chtmo[15];
	char chtda[15];
	char chtho[15];
	char chtmi[15];
	char chtse[15];
	char chHex[15];

	memset(chtye,0,sizeof(chtye));
	memset(chtmo,0,sizeof(chtmo));
	memset(chtda,0,sizeof(chtda));
	memset(chtho,0,sizeof(chtho));
	memset(chtmi,0,sizeof(chtmi));
	memset(chtse,0,sizeof(chtse));
	memset(chHex,0,sizeof(chHex));

	memset(sd,0x00,sizeof(sd));

	memset(chTemp,0,sizeof(chTemp));
	strncpy(chTemp,strCardDate,4);
	ye=GlobalFunc_atoi(chTemp,4);
	if(ye<=2000)
		ye = 0;
	else
		ye=ye - 2000;

	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",ye);

	G_IC_strDec2Bin(strDec,strlen(strDec),chtye,6);
	memset(chTemp,0x00,sizeof(chTemp));
	i = atol(chtye);
	sprintf(chTemp,"%06ld",i);
	strncpy(sd,chTemp,6);

	memset(chTemp,0,sizeof(chTemp));
	strncpy(chTemp,strCardDate+4,2);
	mo=atoi(chTemp);
	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",mo);
	G_IC_strDec2Bin(strDec,strlen(strDec),chtmo,4);
	memset(chTemp,0x00,sizeof(chTemp));
	i = atoi(chtmo);
	sprintf(chTemp,"%04ld",i);
	strncpy(sd+6,chTemp,4);

	memset(chTemp,0,sizeof(chTemp));
	strncpy(chTemp,strCardDate+6,2);
	da=atoi(chTemp);
	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",da);
	G_IC_strDec2Bin(strDec,strlen(strDec),chtda,5);
	memset(chTemp,0x00,sizeof(chTemp));
	i = atol(chtda);
	sprintf(chTemp,"%05ld",i);
	strncpy(sd+10,chTemp,5);

	memset(chTemp,0,sizeof(chTemp));
	strncpy(chTemp,strCardDate+8,2);
	ho=atoi(chTemp);
	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",ho);
	G_IC_strDec2Bin(strDec,strlen(strDec),chtho,5);
	memset(chTemp,0x00,sizeof(chTemp));
	i = atol(chtho);
	sprintf(chTemp,"%05ld",i);
	strncpy(sd+15,chTemp,5);

	memset(chTemp,0,sizeof(chTemp));
	strncpy(chTemp,strCardDate+10,2);
	mi=atoi(chTemp);
	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",mi);
	G_IC_strDec2Bin(strDec,strlen(strDec),chtmi,6);
	memset(chTemp,0x00,sizeof(chTemp));
	i = atol(chtmi);
	sprintf(chTemp,"%06ld",i);
	strncpy(sd+20,chTemp,6);

	memset(chTemp,0,sizeof(chTemp));
	strncpy(chTemp,strCardDate+12,2);
	se=atoi(chTemp);
	if(iSize == 7)
		se = se/15;
	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",se);
	if(iSize == 7)
	{
		G_IC_strDec2Bin(strDec,strlen(strDec),chtse,2);
		memset(chTemp,0x00,sizeof(chTemp));
		i = atoi(chtse);
		sprintf(chTemp,"%02ld",i);
		strncpy(sd+26,chTemp,2);
	}
	else
	{
		G_IC_strDec2Bin(strDec,strlen(strDec),chtse,6);
		memset(chTemp,0x00,sizeof(chTemp));
		i = atol(chtse);
		sprintf(chTemp,"%06ld",i);
		strncpy(sd+26,chTemp,6);
	}
	
	//将二进制转换为十六进制
	//memset(chTemp,0,sizeof(chTemp));
	//strncpy(chTemp,sd,sizeof(chTemp));
	if(iSize == 7)
		G_IC_strBin2Hex(sd,strlen(sd),chHex,7);
	else
		G_IC_strBin2Hex(sd,strlen(sd),chHex,8);
	memset(strHex,0x00,sizeof(strHex));
	strncpy(strHex,chHex,strlen(chHex));
	//messagebox("hex",sd)

	return strHex;
}

/************************************************************************/
/* 转换日期 liujl 2008.6.12                                             */
/************************************************************************/
char strDate[10];
char *G_IC_MakeDate(char *strCardDate)
{
	char chTemp[15];
	char chtye[15];
	char chtmo[15];
	char chtda[15];
	char chHex[15];

	char strDec[15];
	int ye,mo,da;

	char sd[50];

	memset(chtye,0,sizeof(chtye));
	memset(chtmo,0,sizeof(chtmo));
	memset(chtda,0,sizeof(chtda));
	memset(chHex,0,sizeof(chHex));

	memset(sd,0x00,sizeof(sd));	
	memset(chTemp,0x00,sizeof(chTemp));
	strncpy(chTemp,strCardDate,4);
	ye=GlobalFunc_atoi(chTemp,4);

	if (ye<2000)
		ye=0;
	else
		ye=ye - 2000;

	memset(strDec,0,sizeof(strDec));
	sprintf(strDec,"%d",ye);
	G_IC_strDec2Bin(strDec,strlen(strDec),chtye,6);
	strncpy(sd,chtye,6);

	memset(chTemp,0x00,sizeof(chTemp));
	strncpy(chTemp,strCardDate+4,2);
	mo=GlobalFunc_atoi(chTemp,2);
	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",mo);
	G_IC_strDec2Bin(strDec,strlen(strDec),chtmo,4);
	strncpy(sd+6,chtmo,4);

	memset(chTemp,0x00,sizeof(chTemp));
	strncpy(chTemp,strCardDate+6,2);
	da=GlobalFunc_atoi(chTemp,2);
	memset(strDec,0x00,sizeof(strDec));
	sprintf(strDec,"%d",da);
	G_IC_strDec2Bin(strDec,strlen(strDec),chtda,5);
	strncpy(sd+10,chtda,5);

	sd[15]='0';

	//将二进制转换为十六进制
	memset(chTemp,0,sizeof(chTemp));
	strncpy(chTemp,sd,sizeof(chTemp));
	G_IC_strBin2Hex(chTemp,strlen(sd),chHex,4);
	
	memset(strDate,0x00,sizeof(strDate));
	strncpy(strDate ,chHex,sizeof(chHex));
	return strDate;
}

/************************************************************************/
/* 转写车道号 liujl 2008.6.12                                           */
/************************************************************************/
char strLane[5];
char *CSC_DLL_Convert_WriteLaneNO(char *strLaneNo)
{
	char strtemp[15];
	char chLaneNo[15];
	char chTemp[15];
	char chBin[15];
	int iTemp;
	long lTemp;
	memset(chLaneNo,0x00,sizeof(chLaneNo));
	memset(chTemp,0x00,sizeof(chTemp));
	memset(chBin,0x00,sizeof(chBin));
//	print_emrc("%s\n",strLaneNo);
	memset(strtemp,0x00,sizeof(strtemp));
	strncpy(strtemp,strLaneNo+2,1);
	iTemp = strtemp[0];
	memset(strtemp,0x00,sizeof(strtemp));
	sprintf(strtemp,"%d",iTemp);
	strncpy(chTemp,strtemp,strlen(strtemp));
	G_IC_strDec2Bin(chTemp,strlen(chTemp),chBin,8);
	memset(strtemp,0x00,sizeof(strtemp));
	lTemp = atol(chBin);
	sprintf(strtemp,"%08ld",lTemp);
//	print_emrc("%s\n",strtemp);
	memset(chTemp,0x00,sizeof(chTemp));
	G_IC_strBin2Hex(strtemp,8,chTemp,2);
	memset(strLane,0x00,sizeof(strLane));
	strncpy(strLane,chTemp,strlen(chTemp));
	strncpy(strLane+2,strLaneNo+1,2);
	strLane[4]=0x00;
	return strLane;
}

/************************************************************************/
/* 整型转字符串 liujl 2008.6.12                                         */
/************************************************************************/
void G_IC_itoa(unsigned long val,char *buf,unsigned radix)     
{     
	char *p;
	char *firstdig;
	char temp;
	unsigned digval;

	p = buf;
	firstdig = p;

	do {
		digval = (unsigned)(val % radix);
		val /= radix;

		if (digval > 9)     
			*p++ = (char)(digval - 10 + 'a');
		else
			*p++ = (char)(digval + '0');
	} while (val > 0);

	*p-- = '\0';
	do {
		temp = *p;     
		*p = *firstdig;
		*firstdig = temp;
		--p;
		++firstdig;
	} while (firstdig < p);
}

