// ***************************************************************
//  commonality   version:  1.0   ·  date: 12/09/2007
//  -------------------------------------------------------------
//  公共函数处理部分！
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"

#define MAXSYSINI 4096

 /////////////////////////////////////////////////////////////////////////
// 将字符串转为整数 fuxl 2008.06.12
//////////////////////////////////////////////////////////////////////////
int GlobalFunc_atoi(char *str, int len)
{
	char strTemp[21];
	memset(strTemp,0X00, sizeof( strTemp));
	if( len > sizeof(strTemp) ) len = 20; //如果超过20个长，只取前20个	
	strncpy(strTemp, str, len);
	strTemp[len ] = 0x00;
	return atoi( strTemp);
}

 /***********************************************************************
* 描述		:   min函数
* 函数名	:   getmin()
* 输入参数  :   a,b 两个整型值
* 调用实例  :        
* 作者      ：  fuxl
************************************************************************/
int getmin(int a,int b) 
{
	return a>b?b:a;

}

  
/****************************************************************************************
* 获取 格式化 指定时间的日期
*****************************************************************************************/
char DataTimeStr[20];
char *GetFormatTime(char *Format,time_t FormatTime)
{	
    struct tm *rtc_time;
    rtc_time = localtime(&FormatTime);	
    if(!strncmp(Format,DATETIME_FORMAT_MMDD,strlen(DATETIME_FORMAT_MMDD)))
    {	
        sprintf(DataTimeStr, "%02d%02d%c",rtc_time->tm_mon+1, rtc_time->tm_mday,'\0');	
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
* 获取 格式化 字符串 日期
*****************************************************************************************/
char *GetTime(char *Format)
{	
        time_t Currenttime = time(NULL);	
        return GetFormatTime(Format,Currenttime);	
}
/****************************************************************************************
* 获取 格式化 字符串 日期 按要求加减日期！
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
* 装载Ini文件到字符串中
*****************************************************************************************/

int LoadIniFile(char *InputIniFileName)
{	
    int ret=-1;
    ret=LoadFile(InputIniFileName,read_ini_String,MAXSYSINI);	
    return ret;

}
/****************************************************************************************
 * 在装载的Ini字符串中读取指定内容的值
 *****************************************************************************************/
char ItemValue[100];
char  *readItemInIniFile(char *ItemName)
{	
    char *ini_addr_ptr;
    int len;
     memset(ItemValue,0x00,sizeof(ItemValue));
    ini_addr_ptr = strstr(read_ini_String,ItemName);	
    ini_addr_ptr = strchr(ini_addr_ptr,'<')+1;
    len=strchr(ini_addr_ptr,'>')-ini_addr_ptr;
    strncpy(ItemValue,ini_addr_ptr,len);	
    ItemValue[len] = 0x00;
    return ItemValue;
}
/****************************************************************************************
* 将字符串的日期还原到 日期结构 中
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
* 计算两个字符串 日期的 时间间隔 返回的是分钟数
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
* 计算指定时间与当前时间的间隔 返回结果是 分钟
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
* 由职员号前5位计算职员号的第6
*****************************************************************************************/
int GetLunKey(char *userID,char *lunKey )
{	
    int total =0 ,i=0;//记录合计值
    int temp=0 ;//记录中间结果
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
        if ( i%2 == 0) //如果是奇数位上的数 ＊2
        {	
            temp = atoi(chNum) * 2  ;


            if ( temp > 9 ) //如果结果为两位数，则这两位上的数字分别相加
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
        else // 偶数位上的数直接加到总值中
        {	
            total += atoi(chNum) ;
        }
    }


    //itoa(90 - total,chValue,10);	 //90 - 总值， 实际是找总值最邻近的整数与其相减
    sprintf(chValue,"%d\\0",90 - total);	
    //最后只是取其个位上的数字，因为五位数字的这种
    //算法最大总值为45所以用90与其相减即可
    *lunKey = chValue[1];

    return total;
}
/****************************************************************************************
* 查找字符在十六进制中的位置
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
* 十六进制转Asscii码 （意思不准确）
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
* 卡中16进制时间转字符串时间
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
* 日期转卡格式日期
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
* 给字符串加一
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
* 给字段值加一个特定的值
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
* 设置某个字段的值
**************************************************************************************/
void SetFieldAtValue(char *InputField,int FieldLength,int InputAddFieldValue)
{	
    char Temp[20];
    sprintf(Temp,"%014d",InputAddFieldValue);	
    strncpy(InputField,&Temp[14-FieldLength],FieldLength);	
}

//将一个指定长度的字符串转换为数字。 
int charstoint(char * chars,int charslenght)
{
	char  charsx[20];
	memset(charsx,0x00,sizeof(charsx));
	strncpy(charsx,chars ,charslenght);
	//echoic(":::%s ===%s >>> %d ",chars,charsx,atoi(charsx));
	return atoi(charsx);
}
/***********************************************************************
* 描述		:   trim函数
* 函数名	:   alltrim()
* 输入参数  :   irl=1是左补充，irl=2是右补充;isumlen是总长度,inlen输入字符串长度，stype为要填充的字符
* 调用实例  :   如果tmp1="asdfas   " ,调用直接用 alltrim(tmp1);返回结果"asdfas"     
* 作者      ：  hgy
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
* 描述		:   right函数
* 函数名	:   rightStr()
* 输入参数  :   ilen是字符串总长度，iright是
* 调用实例  :   如果tmp1="asdfas   " ,调用直接用 alltrim(tmp1);返回结果"asdfas"     
* 作者      ：  hgy
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
//取指定字符串的指定长度返回
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

//去除空格
char * trim(char * src)
{	
	int i = 0;
	char *begin = src;
	while(src[i] != '\0')
	{	
		if(src[i] != ' ')
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
		if(src[i] != ' ')
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


