// ***************************************************************
//  ParameterTable   version:  1.0   ��  date: 12/09/2007
//  -------------------------------------------------------------
//  ���������ӿڣ�
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"
struct ParameterVersion *CurrentUseParameterVersionNumber;

void LoadCurrentUseParameterVersionNumber(void)
{
  CurrentUseParameterVersionNumber = GetSyncParameterVersion();
}

int IsUpdate = 0;

int CompareVersion(int InputParameterIndex,char* InputVersion)
{
    int ret=0;
    if(NULL!=strstr(CurrentUseParameterVersionNumber->Collect,InputVersion))
    {
        ret= 0;
    }
    else
    {
        strncpy(CurrentUseParameterVersionNumber->Collect,InputVersion,2);
        if(msync((void *)CurrentUseParameterVersionNumber,sizeof(struct ParameterVersion),MS_SYNC)<0)
        {
            LogCAppLog("Msync Faile!");
        }
        ret= 1;
    }
    return ret;
}


/******************************************************************************************************
* ����������ͷ��ʱ���ж� �Ƿ�����˲���
* δ��ʹ�ò�������Ϣ ��ʱ��������
******************************************************************************************************/
int  ParseHead(char *HeadStr,struct  PARAM_HEAD *Head ,int InputParameterIndex)
{
    char tempVerNo[3];
    memset(tempVerNo,0x00,3);
    memset((char*)Head,0x00,sizeof(struct PARAM_HEAD));
    strncpy((char*)Head,HeadStr,sizeof(struct PARAM_HEAD));
    Head->Type[0] = HeadStr[0];
    Head->Type[1] = HeadStr[1];
    strncpy(Head->DateCreate,&HeadStr[2],12);
    strncpy(Head->DateApply,&HeadStr[14],12);
    Head->NetNo[0] = HeadStr[26];
    Head->NetNo[1] = HeadStr[27];
    Head->PlazaNo[0] = HeadStr[28];
    Head->PlazaNo[1] = HeadStr[29];
    Head->VerNo[0] = HeadStr[30];
    Head->VerNo[1] = HeadStr[31];
    strncpy(Head->Recordcount,&HeadStr[32],6);
    strncpy(tempVerNo,Head->VerNo,sizeof(Head->VerNo));
    return CompareVersion(InputParameterIndex,tempVerNo);
}

  void ReadWithoutCLRF(int FileFd)
{
    char Temp[2];
    read(FileFd,Temp,1);
    if( '\n' ==Temp[0] || '\r' ==Temp[0] )
    {
        ReadWithoutCLRF(FileFd);
    }
}


/******************************************************************************************************
* ���ر�����
* ���н���
******************************************************************************************************/
int LoadRecord(char *FileName,struct PARAM_HEAD *Head,int RecordStrLenrth,int (*ParseRecord)(char *RecordStr,int Rowindex),int InputParameterIndex,int IsFirst )
{

	char HeadStr[PAEAMHEAD_LENGTH+1];
	char RecordStr[1024];
	int FileSet;
	int i;
    int FileFd;
	FileFd =open(FileName,O_RDONLY);
	if(FileFd<0)
	{
        LogCParameter(LOG_ERROR,"������ %s δ�ҵ�",FileName);
        return 0;
    }
    lseek(FileFd,0,SEEK_SET);
    read(FileFd,HeadStr,PAEAMHEAD_LENGTH);
    HeadStr[39] = 0x00;
	echoic("HeadStr=<%s>",HeadStr);
    if(ParseHead(HeadStr,Head,InputParameterIndex) || IsFirst)
    {
        for(i=0;i<atol(Head->Recordcount);i++)
        {
            ReadWithoutCLRF(FileFd);
            FileSet = lseek(FileFd,0,SEEK_CUR);
            FileSet--;
            lseek(FileFd,FileSet,SEEK_SET);
            read(FileFd,RecordStr,RecordStrLenrth);
            RecordStr[RecordStrLenrth] = 0x00;
            ParseRecord(RecordStr,i);
        }
        LogCParameter(LOG_INFOR,"��������� %s ",FileName);
    }
    close(FileFd);
    return 1;
}


/******************************************************************************************************
*  �����������������ļ����ڴ���
*  �Ժ����ӳ���ʱ��ֻҪ�޸�parmeterTable.h�е�MAXCARKINDCOUNT
******************************************************************************************************/
int LoadCarKind(char *FileName,int RecordStrLenrth,int (*ParseRecord)(char *RecordStr,int Rowindex) )
{

    int FileFd;
   char HeadStr[PAEAMHEAD_LENGTH+1];
   char RecordStr[1024];
    int FileSet;
    int i;
    FileFd=open(FileName,O_RDONLY);
    if(FileFd<0)
    {
		LogCParameter(LOG_ERROR,"������ %s δ�ҵ�",FileName);
        return 0;
    }
    lseek(FileFd,0,SEEK_SET);
    read(FileFd,HeadStr,PAEAMHEAD_LENGTH);

    HeadStr[39] = 0x00;

        for(i=0;i<MAXCARKINDCOUNT;i++)
        {
            ReadWithoutCLRF(FileFd);
            FileSet = lseek(FileFd,0,SEEK_CUR);
            FileSet--;
            lseek(FileFd,FileSet,SEEK_SET);
            read(FileFd,RecordStr,RecordStrLenrth);
            RecordStr[RecordStrLenrth] = 0x00;
            ParseRecord(RecordStr,i);
			SetG_Lane_carKindCount(i+1);
        }
        LogCParameter(LOG_INFOR,"��������� %s ",FileName);
    close(FileFd);
    return 1;
}
int p1,p2,p3,p4,p5,p6,p7,p8;
/******************************************************************************************************
* ���ز������ڴ�
******************************************************************************************************/
/**
 *
 *
 * @param IsFirst
 * @param ret
 */
int  LoadParameter_CARDInfo(int IsFirst)
{
	 int ret=0;
	if (TRUE==GetEnableIC())
	{
		if (LoadSVRListRecord(IsFirst))
		{
			ret=1;
			p7=0;
		}
		else
		{
			if ( p7==0)
			{
				p7=1;
				SendMsgInfo("���������","","IC����Ϣ��");
			}
		}
		if (LoadJOUListRecord(IsFirst))
		{
			ret=1;
			p8=0;
		}
		else
		{
			if (p8==0)
			{
				p8=1;
				SendMsgInfo("���������","","�ó̱�");
			}
		}
	}
	else
	{
		ret = 1;
	}
	return ret;

}
int  LoadParameter(int IsFirst)
{
    int ret = 0;
    IsUpdate = 0;

	 if(LoadYPKListRecord(IsFirst))
	{
		ret = 1;
		p1=0;
	}
	else
	{
		SetLoadYPKListRecordFlag(0);//���ز��ɹ�ʱ����messageHandl.c������̨����Ϣ��
		SetG_weiZhangType(4);
		if (p1==0)
		{
			p1=1;
			SendMsgInfo("���������","","��Ʊ��");
		}
	 }
     if(LoadYHKListRecord(IsFirst))
     {
         ret=1;
		 p2=0;
     }
	 else
	 {
		 SetLoadYHKListRecordFlag(0);
         SetG_weiZhangType(4);
		if (p2==0)
		{
			p2=1;
			SendMsgInfo("���������","","�Żݿ�");
		}
	 }

     if (LoadYHRateDescriptionRecord(IsFirst))
     {
         ret=1;
		 p3=0;
     }
	 else
	 {
		 SetLoadYHRateDescriptionRecordFlag(0);
         //SetG_BillPrintFlag(4);
		 SetG_weiZhangType(4);
		if (p3==0)
		{
			p3=1;
			SendMsgInfo("���������","","�Ż�������");
		}
	 }

     if(LoadFareRecord(IsFirst))
     {
         ret=1;
		 p4=0;
     }
	 else
	 {
		 SetLoadFareRecordFlag(0);
		//SetG_BillPrintFlag(4);
		SetG_weiZhangType(4);
		if (p4==0)
		{
			p4=1;
			SendMsgInfo("���������","","���ʱ�");
		}
	 }

     if (LoadCollectRecord(IsFirst))
    {
          ret = 1;
		  p5=0;
    }
	 else
	 {

		 SetLoadCollectRecordFlag(0);
		 SetG_weiZhangType(4);
		if (p5==0)
		{
			p5=1;
			SendMsgInfo("���������","","ְԱ��");
		}
	 }
	 if (!LoadFreeCarListRecord(IsFirst))
	 {		
		SendMsgInfo("���������","","������Ϣ��");		
	 }

	 if(IsUpdate)
	 {

        //Send  REVISION TABLES
	 }
	//ÿ�ζ�Ҫ���س��������ļ���
	if( LoadCarKindRecord(IsFirst))
	{
		ret=1;
		p6=0;
	}
	else
	{
			SetLoadCarKindRecordFlag(0);
			SetG_weiZhangType(4);
			if (p6==0)
			{
				p6=1;
				SendMsgInfo("���������","","���ֱ�");
			}
	}


	ret=LoadParameter_CARDInfo(IsFirst);
	LoadConstantRecord(IsFirst);
	return ret;
}
