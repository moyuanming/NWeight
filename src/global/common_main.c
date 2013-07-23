// ***************************************************************
//  commonality   version:  1.0   ��  date: 12/09/2007
//  -------------------------------------------------------------
//  �������������֣�
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"

#define MAXSYSINI 4096

 /////////////////////////////////////////////////////////////////////////
// ���ַ���תΪ���� fuxl 2008.06.12
//////////////////////////////////////////////////////////////////////////
int GlobalFunc_atoi(char *str, int len)
{
	char strTemp[21];
	memset(strTemp,0X00, sizeof( strTemp));
	if( len > sizeof(strTemp) ) len = 20; //�������20������ֻȡǰ20��	
	strncpy(strTemp, str, len);
	strTemp[len ] = 0x00;
	return atoi( strTemp);
}

 /***********************************************************************
* ����		:   min����
* ������	:   getmin()
* �������  :   a,b ��������ֵ
* ����ʵ��  :        
* ����      ��  fuxl
************************************************************************/
int getmin(int a,int b) 
{
	return a>b?b:a;

}

 

  
/****************************************************************************************
* ��ȡ ��ʽ�� ָ��ʱ�������
*****************************************************************************************/
char DataTimeStr[25];
char *GetFormatTime(char *Format,time_t FormatTime)
{	
    struct tm *rtc_time;
	memset(DataTimeStr,0x00,sizeof(DataTimeStr));
    rtc_time = localtime(&FormatTime);	
    if(!strncmp(Format,DATETIME_FORMAT_MMDD,strlen(DATETIME_FORMAT_MMDD)))
    {	
        sprintf(DataTimeStr, "%02d%02d%c",rtc_time->tm_mon+1, rtc_time->tm_mday,'\0');	
    }
	
	else if(!strncmp(Format,DATETIME_FORMAT_YYYYMMDDWHHMMSS,strlen(DATETIME_FORMAT_YYYYMMDDWHHMMSS)))
	{	
		sprintf(DataTimeStr, "%04d%02d%02d%d%02d%02d%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_wday+1, rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec,'\0');	
	}
    else if(!strncmp(Format,DATETIME_FORMAT_YYYYMMDDHHMMSS,strlen(DATETIME_FORMAT_YYYYMMDDHHMMSS)))
    {	
        sprintf(DataTimeStr, "%04d%02d%02d%02d%02d%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec,'\0');	
    }
    else if(!strncmp(Format,DATETIME_FORMAT_YYYYMMDDHHOOOO,strlen(DATETIME_FORMAT_YYYYMMDDHHOOOO)))
    {	
        sprintf(DataTimeStr, "%04d%02d%02d%02d0000%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour,'\0');	
    }
	else if(!strncmp(Format,DATETIME_FORMAT_YYYYMMDDHHMM,strlen(DATETIME_FORMAT_YYYYMMDDHHMM)))
	{	
        sprintf(DataTimeStr, "%04d%02d%02d%02d%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour,rtc_time->tm_min,'\0');	
	}
    else if(!strncmp(Format,DATETIME_FORMAT_YYYYMMDDHH,strlen(DATETIME_FORMAT_YYYYMMDDHH)))
    {	
        sprintf(DataTimeStr, "%04d%02d%02d%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour,'\0');	
    }
	else if(!strncmp(Format,DATETIME_FORMAT_YYYYMMDDHHM,strlen(DATETIME_FORMAT_YYYYMMDDHHM)))
	{	

		sprintf(DataTimeStr, "%04d%02d%02d%02d%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour,rtc_time->tm_min /10,'\0');	
	}
    else if(!strncmp(Format,DATETIME_FORMAT_YYYY_MM_DD_HH_MM_SS,strlen(DATETIME_FORMAT_YYYY_MM_DD_HH_MM_SS)))
    {	
        sprintf(DataTimeStr, "%04d-%02d-%02d %02d:%02d:%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec,'\0');	
    }
	 else if(!strncmp(Format,DATETIME_FORMAT_HH_MM_SS_5,strlen(DATETIME_FORMAT_HH_MM_SS_5)))
    {	
        sprintf(DataTimeStr, "%02d:%02d:%02d%c", rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec,'\0');	
    }
	 else if(!strncmp(Format,DATETIME_FORMAT_YYYY_MM_DD_5,strlen(DATETIME_FORMAT_YYYY_MM_DD_5)))
    {	
        sprintf(DataTimeStr, "%04d-%02d-%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,'\0');	
    }
    else if(!strncmp(Format,DATETIME_FORMAT_YYYYMMDD,strlen(DATETIME_FORMAT_YYYYMMDD)))
    {	
        sprintf(DataTimeStr, "%04d%02d%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,'\0');	
    }
    else if(!strncmp(Format,DATETIME_FORMAT_HHMMSS,strlen(DATETIME_FORMAT_HHMMSS)))
    {	
        sprintf(DataTimeStr, "%02d%02d%02d%c",rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec,'\0');	
    }
    else if(!strncmp(Format,DATETIME_FORMAT_HHOOOO,strlen(DATETIME_FORMAT_HHOOOO)))
	{	
        sprintf(DataTimeStr, "%02d0000%c",rtc_time->tm_hour,'\0');	
	}
    else if(!strncmp(Format,DATETIME_FORMAT_YYYY,strlen(DATETIME_FORMAT_YYYY)))
    {	
        sprintf(DataTimeStr, "%04d%c",rtc_time->tm_year+1900,'\0');	
    }
	else if(!strncmp(Format,DATETIME_FORMAT_YYYY_MM_DD,strlen(DATETIME_FORMAT_YYYY_MM_DD)))
	{	
        sprintf(DataTimeStr, "%04d-%02d-%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,'\0');	
	}
    return DataTimeStr;
}
/****************************************************************************************
* ��ȡ ��ʽ�� �ַ��� ����
*****************************************************************************************/
char *GetTime(char *Format)
{	
        time_t Currenttime = time(NULL);	
        return GetFormatTime(Format,Currenttime);	
}
/****************************************************************************************
* ��ȡ ��ʽ�� �ַ��� ���� ��Ҫ��Ӽ����ڣ�
*****************************************************************************************/
char *GetTimeAddTime(char *Format,int InputAddValues,char InputTimeType)
{	
        time_t Currenttime = time(NULL);	
        switch(InputTimeType)
        {	
            case ADDTIME_TYPE_DAY:
                Currenttime +=  InputAddValues*24*3600;
                break;
            case ADDTIME_TYPE_HOUR:
                Currenttime +=  InputAddValues*3600;
                break;
            case ADDTIME_TYPE_MIN:
                Currenttime +=  InputAddValues*60;
                break;
            default:
                Currenttime +=InputAddValues;
        }
        return GetFormatTime(Format,Currenttime);	
}


char read_ini_String[MAXSYSINI];
int LoadFile(char *InputFileName,char *LoadInFileStr,int FilrStrLength)
{	
    int LoadFinleFd;
    LoadFinleFd=open(InputFileName,O_RDONLY);	
    if(LoadFinleFd<0)
    {	
        printf("opern %s error \n",InputFileName);	
        exit(-1);	
    }
    lseek(LoadFinleFd,SEEK_SET,0);	
    if(read(LoadFinleFd,LoadInFileStr,FilrStrLength)<0)
    {	

        printf("read %s error \n",InputFileName);	
        close(LoadFinleFd);	
        exit(-1);	
    }
    close(LoadFinleFd);	
    return 1;
}

/****************************************************************************************
* װ��Ini�ļ����ַ�����
*****************************************************************************************/

int LoadIniFile(char *InputIniFileName)
{	
    int ret=-1;
    ret=LoadFile(InputIniFileName,read_ini_String,MAXSYSINI);	
    return ret;

}
/****************************************************************************************
 * ��װ�ص�Ini�ַ����ж�ȡָ�����ݵ�ֵ
 *****************************************************************************************/
char ItemValue[100];
char  *readItemInIniFile(char *ItemName)
{	
    char *ini_addr_ptr;
    int len;
     memset(ItemValue,0x00,sizeof(ItemValue));
    ini_addr_ptr = strstr(read_ini_String,ItemName);	
	if(ini_addr_ptr == NULL)
	{
		ItemValue[0] = '0';
		ItemValue[1] = 0x00;
		fprintf(stderr,"Load Config Item Error ItemName =<%s>",ItemName);
		return ItemValue;
	}
    ini_addr_ptr = strchr(ini_addr_ptr,'<')+1;
    len=strchr(ini_addr_ptr,'>')-ini_addr_ptr;
    strncpy(ItemValue,ini_addr_ptr,len);	
    ItemValue[len] = 0x00;
    return ItemValue;
}
/****************************************************************************************
* ���ַ��������ڻ�ԭ�� ���ڽṹ ��
*****************************************************************************************/
void SetTm(char *InputFirstTime, struct tm *rtc_time)
{	
    char Temp[5];
    strncpy(Temp,InputFirstTime,4);	
    Temp[4]=0x00;
    rtc_time->tm_year = atoi(Temp) - 1900;
    Temp[2]=0x00;
    strncpy(Temp,&InputFirstTime[4],2);	
    rtc_time->tm_mon = atoi(Temp) - 1;
    strncpy(Temp,&InputFirstTime[6],2);	
    rtc_time->tm_mday = atoi(Temp) ;
    strncpy(Temp,&InputFirstTime[8],2);	
    rtc_time->tm_hour = atoi(Temp);	
    strncpy(Temp,&InputFirstTime[10],2);	
    rtc_time->tm_min = atoi(Temp);	
    strncpy(Temp,&InputFirstTime[12],2);	
    rtc_time->tm_sec = atoi(Temp);	
}
/****************************************************************************************
* ���������ַ��� ���ڵ� ʱ���� ���ص��Ƿ�����
*****************************************************************************************/
int DiffDataTime(char *InputStarttTime,char *InputEndTime)
{	
    time_t StarttTime, EndTime;
    struct tm rtc_time;
    int Sec;
    SetTm(InputStarttTime,&rtc_time);	
    StarttTime  = mktime(&rtc_time);	
    SetTm(InputEndTime,&rtc_time);	
    EndTime = mktime(&rtc_time);	
    Sec = difftime(EndTime,StarttTime);	
    return Sec/60;
}
/****************************************************************************************
* ����ָ��ʱ���뵱ǰʱ��ļ�� ���ؽ���� ����
*****************************************************************************************/
int DiffCurrentDataTime(char *InputTime)
{	
    time_t StarttTime, EndTime;
    struct tm rtc_time;
    int Sec;
    if(strlen(InputTime)<10)
    {	
        return 0;
    }
    SetTm(InputTime,&rtc_time);	
    StarttTime  = mktime(&rtc_time);	
    EndTime = time(NULL);	
    Sec = difftime(EndTime,StarttTime);	
    return Sec/60;
}
/****************************************************************************************
* ��ְԱ��ǰ5λ����ְԱ�ŵĵ�6
*****************************************************************************************/
int GetLunKey(char *userID,char *lunKey )
{	
    int total =0 ,i=0;//��¼�ϼ�ֵ
    int temp=0 ;//��¼�м���
    char chValue[256];
    char chTemp[256];
    char chNum[2];
    memset(chNum,0,sizeof(chNum));	
    memset(chTemp,0,sizeof(chTemp));	
    memset(chValue,0,sizeof(chValue));	
    strncpy(chTemp ,userID,sizeof(chTemp));	

    for ( i=4; i >=0 ; i--)
    {	
        chNum[0]=chTemp[i];
        if ( i%2 == 0) //���������λ�ϵ��� ��2
        {	
            temp = atoi(chNum) * 2  ;


            if ( temp > 9 ) //������Ϊ��λ����������λ�ϵ����ֱַ����
            {	
                //itoa(temp,chValue,10);	
                sprintf(chValue,"%d\\0",temp);	
                chNum[0]=chValue[0];
                total += atoi(chNum) ;
                chNum[0]=chValue[1];
                total += atoi(chNum) ;
            }
            else
                total +=temp;
        }
        else // ż��λ�ϵ���ֱ�Ӽӵ���ֵ��
        {	
            total += atoi(chNum) ;
        }
    }


    //itoa(90 - total,chValue,10);	 //90 - ��ֵ�� ʵ��������ֵ���ڽ��������������
    sprintf(chValue,"%d\\0",90 - total);	
    //���ֻ��ȡ���λ�ϵ����֣���Ϊ��λ���ֵ�����
    //�㷨�����ֵΪ45������90�����������
    *lunKey = chValue[1];

    return total;
}
/****************************************************************************************
* �����ַ���ʮ�������е�λ��
*****************************************************************************************/
unsigned char Find(unsigned char InputChar)
{	
    int i;
    char *HexString = "0123456789ABCDEF";

    for (i=0;i<16;i++)
    {	
        if(toupper(InputChar) == HexString[i])
        {	
            //printf("i = %d %c %c \n ",i,toupper(InputChar),InputChar);	
            return i;
        }
    }
    return -1;
}
/****************************************************************************************
* ʮ������תAsscii�� ����˼��׼ȷ��
*****************************************************************************************/
static void StrHex2Byte(unsigned char * Dest, int DestLen,const char* Src, int SrcLen)
{	

    int ByteHi =0, ByteLo =0;
    int DestIndex,i;
    for ( i=0; i<SrcLen; i+=2)
    {	
        ByteHi = (int)Find(toupper(Src[i]));	
        ByteLo = (int)Find(toupper(Src[i+1]));	
        DestIndex=DestLen-1-i/2;
        if ((ByteHi>=0) && (ByteLo>=0))
            Dest[DestIndex] = ByteHi*16+ByteLo;
        else
            Dest[DestIndex] = 0;
    }
}
/****************************************************************************************
* ����16����ʱ��ת�ַ���ʱ��
*****************************************************************************************/
void GEA2Time(char* Dest, int DestLen, const char* Src, int SrcLen)
{	
    struct GRADATE ddhm;
    memset(&ddhm,0,sizeof(ddhm));	
    StrHex2Byte((unsigned char *)&ddhm,sizeof(ddhm),Src,SrcLen);	
    snprintf(Dest,DestLen,"%04d%02d%02d%02d%02d%02d",ddhm.year+2000,
        ddhm.month,ddhm.day,ddhm.hour,ddhm.min,ddhm.sec);	
}
/****************************************************************************************
* ����ת����ʽ����
*****************************************************************************************/
void EMRC2GEATime(char* Dest, int DestLen, const char* Src, int SrcLen, BOOL IsLongFormat)
{
    struct GRADATE ddhm;
    unsigned char Temp[5] = {0};
    unsigned char MidTemp;
    /*unsigned*/ char sTemp[30];
		
    memset(sTemp,0x00,30);	
    sprintf(sTemp,"%s",Src);	
    strcat(sTemp,"000000");	
    MidTemp = sTemp[4];
    sTemp[4] = 0x00;
    ddhm.year = atoi(sTemp) - 2000; //20071216211323



    sTemp[4] = MidTemp;
    MidTemp = sTemp[6];
    sTemp[6] = 0x00;
    ddhm.month = atoi(&sTemp[4]);	//12


    sTemp[6] = MidTemp;
    MidTemp = sTemp[8];
    sTemp[8] = 0x00;
    ddhm.day   = atoi(&sTemp[6] );	//16

    sTemp[8] = MidTemp;
    MidTemp = sTemp[10];
    sTemp[10] = 0x00;
    ddhm.hour  = atoi(&sTemp[8]);	//21

    sTemp[10] = MidTemp;
    MidTemp = sTemp[12];
    sTemp[12] = 0x00;
    ddhm.min   = atoi(&sTemp[10]);	 //13


    sTemp[12] = MidTemp;
    MidTemp = sTemp[14];
    sTemp[14] = 0x00;
    ddhm.sec   = atoi(&sTemp[12] );	//23

    memcpy(Temp,&ddhm,sizeof(Temp));	
    Temp[4] = 0x00;

    if(IsLongFormat)
	{

			snprintf(Dest,DestLen,"%02X%02X%02X%02X",Temp[3],Temp[2],Temp[1],Temp[0]);	
	}
    else
    {	
        Temp[2] = Temp[2] & 0xFE;
        snprintf(Dest,DestLen,"%02X%02X",Temp[3],Temp[2]);	
    }
}


 

/****************************************************************************************
* ���ַ�����һ
*****************************************************************************************/
void AddField(char *InputField,int FieldLength)
{	
    char Temp[20];
    int Fieldvalue =0;
    strncpy(Temp,InputField,FieldLength);	
    Temp[FieldLength] = 0x00;
    Fieldvalue = atoi(Temp);	
    sprintf(Temp,"%014d",++Fieldvalue);	
    strncpy(InputField,&Temp[14-FieldLength],FieldLength);	
}

/*************************************************************************************
* ���ֶ�ֵ��һ���ض���ֵ
**************************************************************************************/
void AddFieldAtValue(char *InputField,int FieldLength,int InputAddFieldValue)
{	
    char Temp[20];
    int Fieldvalue =0;
    strncpy(Temp,InputField,FieldLength);	
    Temp[FieldLength] = 0x00;
    Fieldvalue = atoi(Temp);	
    Fieldvalue +=InputAddFieldValue;
    sprintf(Temp,"%014d",Fieldvalue);	
    strncpy(InputField,&Temp[14-FieldLength],FieldLength);	
}

/*************************************************************************************
* ����ĳ���ֶε�ֵ
**************************************************************************************/
void SetFieldAtValue(char *InputField,int FieldLength,int InputAddFieldValue)
{	
    char Temp[20];
    sprintf(Temp,"%014d",InputAddFieldValue);	
    strncpy(InputField,&Temp[14-FieldLength],FieldLength);	
}

//��һ��ָ�����ȵ��ַ���ת��Ϊ���֡� 
int charstoint(char * chars,int charslenght)
{
	char  charsx[20];
	memset(charsx,0x00,sizeof(charsx));
	strncpy(charsx,chars ,charslenght);
	//echoic(":::%s ===%s >>> %d ",chars,charsx,atoi(charsx));
	return atoi(charsx);
}
char _inttochars[20];
char* Int2String(int value)
{
	memset(_inttochars, 0x00, 20);
	sprintf(_inttochars, "%d", value);
	return _inttochars;
}
char __Int2String_Ex[20];
char* Int2String_Ex(int value,char* format)
{
	memset(__Int2String_Ex, 0x00, 20);
	sprintf(__Int2String_Ex,format, value);
	return __Int2String_Ex;
}
char _floattochars[100];
char* floatString(float value)
{
	memset(_floattochars, 0x00, 20);
	sprintf(_floattochars, "%f", value);
	return _floattochars;
}
char __floatString_Ex[255];
char* float2String_Ex(int value,char* format)
{
	memset(__floatString_Ex, 0x00, 255);
	sprintf(__floatString_Ex,format, value);
	return __floatString_Ex;
}
 
/***********************************************************************
* ����		:   trim����
* ������	:   alltrim()
* �������  :   irl=1���󲹳䣬irl=2���Ҳ���;isumlen���ܳ���,inlen�����ַ������ȣ�stypeΪҪ�����ַ�
* ����ʵ��  :   ���tmp1="asdfas   " ,����ֱ���� alltrim(tmp1);���ؽ��"asdfas"     
* ����      ��  hgy
************************************************************************/
int alltrim(char* str)
{

	int nSize=0;
	char *p=str;
	char *p2=p;
	 
	if(str == NULL){
		return -1;
	}
	while( *p2 != '\0'){
		if(*p2 == 10 || *p2 == 13 || *p2 =='\t' || *p2 == ' '){
			p2++;
		}else{
			if(p!=p2){
				*p=*p2; 
			}
			p++;
			p2++;
			nSize++;            
		}
	}
	*p='\0';
	return nSize;
}

/***********************************************************************
* ����		:   right����
* ������	:   rightStr()
* �������  :   ilen���ַ����ܳ��ȣ�iright��
* ����ʵ��  :   ���tmp1="asdfas   " ,����ֱ���� alltrim(tmp1);���ؽ��"asdfas"     
* ����      ��  hgy
************************************************************************/
char _righttmp[100];
char * rightStr(char * instr,int ilen,int iright) 
{
	int i,j,m;
	char tmp[100];
	memset(tmp,0x00,sizeof(tmp));
	if( ilen > 99 ) ilen = 99;
	for(i=0;i<ilen;i++)
		tmp[i]=*instr++;

	memset(_righttmp,0x00,sizeof(_righttmp));
	/*for (i=(ilen-iright),j=0;i<ilen,j<iright;i++,j++ )
	{
		_righttmp[j]=tmp[i];
	}*/
	if(iright > ilen) return _righttmp;

	m = ilen-iright;
	j=0;
	for ( i=m ;i<ilen ;i++ )
	{
		_righttmp[j]=tmp[i];
		j++;
	}
	return _righttmp;

}
char _substring[2048];
//ȡָ���ַ�����ָ�����ȷ���
char * substring( char * src ,int lenght)
{
	
	strncpy(_substring ,src ,lenght);
	_substring[lenght] = 0x00;	
	return _substring;
}
 char * PadLeft(char bychar,char *str,char *_padleft ,int len )
 {
	 char tmpxx[len*2+1];
	
	 
	memset(_padleft,0x00,len+1); 
	memset(tmpxx,0x00,len*2+1);
	memset(tmpxx,bychar,len*2);
	//tmpxx[len*2+1]=0;
	echoic("%s",substring(tmpxx,len*2));
	if (strlen(str)>0)
	{
		memcpy(&tmpxx[len*2-strlen(str)] ,str,strlen(str));
		strncpy(_padleft,(char*)&tmpxx[len],len);  
	}
	else
	{
		strncpy(_padleft,tmpxx,len);
	}
	echoic("SetExitTRMsgServiceCard ||%s||||%s||%s",tmpxx,str,_padleft);
	return _padleft;
}

char formateddate[20];
char * FormatDate(char *datetimestring)
{
	memset(formateddate,0x00,20);
	memcpy((char*)&formateddate[0],(char*)&datetimestring[2],2);
	memcpy((char*)&formateddate[2],"-",1);
	memcpy((char*)&formateddate[3],(char*)&datetimestring[4],2);
	memcpy((char*)&formateddate[5],"-",1);
	memcpy((char*)&formateddate[6],(char*)&datetimestring[6],2);
	memcpy((char*)&formateddate[8]," ",1);
	memcpy((char*)&formateddate[9],(char*)&datetimestring[8],2);
	memcpy((char*)&formateddate[11],":",1);
	memcpy((char*)&formateddate[12],(char*)&datetimestring[10],2);
	return formateddate;
}

void CopyFile(char *sFile ,char * dFile)
{
	char   ch[4];   
	FILE   *sfp,*dfp;   
	if ((sfp=fopen(sFile,"rb"))==NULL)
		return ;
	if ((dfp=fopen(dFile,"wb"))==NULL)
		return ;
	while (1)
	{
		if (fread(ch , 4 ,1,sfp )!=1)
		{
			if (!feof(sfp))
				printf("file read error\n");

			else
				break ;
		}
		if (fwrite(ch,4 ,1 ,dfp )!=1)
			printf("file write error\n");
	}

	fclose(sfp);   
	fclose(dfp);   
	return;   

}
char * trim(char * src)
{
return trim_ex(src ,' ');
}
//ȥ���ո�
char * trim_ex(char * src,char c)
{	
	int i = 0;
	char *begin = src;
	while(src[i] != '\0')
	{	
		if(src[i] !=c)
		{	
			break;
		}
		else
		{	
			begin++;
		}
		i++;
	}
	for(i=strlen(src)-1;i>=0;i--)
	{	
		if(src[i] != c)
		{	
			break;
		}
		else
		{	
			src[i] = '\0';
		}
	}
	return begin;
}




char* InitAndCPYStrBase(char *A, int lengthA, char *B, int lengthB, char def, int b0)
{
	char temp[50];
	char temp2[50];
	char format[50];
	int i =0;
	memset(temp, 0x00, sizeof(temp));
	memset(temp2, 0x00, sizeof(temp2));
	memcpy(temp2,B,lengthB);
	sprintf(format, b0 == 0 ? "%%0%ds" : "%%s", lengthA);
	sprintf(temp, format, temp2);
	if (b0==0)
	{
		for (i=0;i<strlen(temp);i++)
		{
			if (temp[i]==' ')
			{
				temp[i] = '0';
			}
		}
	}
	//  echo_ct("format=%s temp=%s ",format,temp);
	memset(A, def, lengthA);
	memcpy(A,temp,lengthA>strlen(temp)?strlen(temp):lengthA);
	return A;
}
char* InitAndCPYStr(char *A, int lengthA, char *B, int lengthB, int b0)
{
	return InitAndCPYStrBase(A, lengthA, B, lengthB, (char)0x00, b0);
}

