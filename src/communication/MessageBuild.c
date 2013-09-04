// ***************************************************************
//  MessageBuild   version:  1.0   ·  date: 12/26/2007
//  -------------------------------------------------------------
//  构建消息
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"


char MsgHeader[33];
static struct MSG_HEAD mHead;
static struct MSG_SubHead *mSubHead;
static struct TCOMSG  MsgTCO;
void InitMsgHead(void )
{	
    memset((char *)&mHead,'0',sizeof(struct MSG_HEAD));	
}
void InitMsgTCO(void )
{	
    memset((char *)&MsgTCO,' ',sizeof(struct TCOMSG));	
}
struct MSG_HEAD  *GetMsgHead(void)
{	
    return &mHead;
}
struct TCOMSG  *GetMsgTCO(void)
{	
    return &MsgTCO;
}
struct MSG_SubHead  *GetMsgSubHead(void)
{	
    return mSubHead;
}
struct MSG_SubHead  *GetSystemInfor(void)
{	
    return mSubHead;
}
char IDTemp[18];
int IDIndex = 0;
static char * CreateMessageID(void)
{	
	unsigned int msc ;
	char Temp[20];
	struct tm *rtc_time;
	time_t t = time(NULL);	
	rtc_time = localtime(&t);
	strncpy(IDTemp,GetLanConfigStationNo(),4);
	strncpy(IDTemp+4,GetLanConfigLaneNo(),3);
	IDIndex = ++IDIndex >=1000 ? 1:IDIndex;
	msc = (unsigned int)t;
	sprintf(Temp,"%08X%03d",msc,IDIndex);
	strncpy(IDTemp+7,Temp,11);
	return IDTemp;
}



/*************************************************************************************
* 构建消息头
**************************************************************************************/
 char *GetMessageHead(char MsgType)
{	
    time_t Currenttime = time(NULL);	
    mHead.MsgType=MsgType;
    mHead.LaneMode=Getg_workStatus();
	memcpy(mHead.ID,CreateMessageID(),sizeof(mHead.ID));
    memcpy(mHead.Year,GetFormatTime(DATETIME_FORMAT_YYYY,Currenttime),sizeof(mHead.Year));	
    memcpy(mHead.Day,GetFormatTime(DATETIME_FORMAT_MMDD,Currenttime),sizeof(mHead.Day));	
    memcpy(mHead.YYYYMMDD,GetFormatTime(DATETIME_FORMAT_YYYYMMDD,Currenttime),sizeof(mHead.YYYYMMDD ));	
	memcpy(mHead.Hour,GetFormatTime(DATETIME_FORMAT_HHMMSS,Currenttime),sizeof(mHead.Hour));	
	memcpy(mHead.YYYYMMDDHHMMSS,GetFormatTime(DATETIME_FORMAT_YYYYMMDDHHMMSS,Currenttime),sizeof(mHead.YYYYMMDDHHMMSS));	
    memcpy(mHead.Collector,GetG_Number(),sizeof(mHead.Collector));	
    return(char *)&mHead;
}
 char * msgh ;
 struct MSG_EXITTR * exittr;
/*************************************************************************************
* 将指定消息添加到消息队列
**************************************************************************************/

 
void SendMessageToQueue(char  InputMsgCode)
{	
    char MessageBody[MAXMSGBODYLENGTH];
    int MsgLen = 0;
    int i;
    int IsLog = 1;
	char tempBillNumber[9];
	tempBillNumber[8]=0x00;
    memset(MessageBody,'0',MAXMSGBODYLENGTH);	
    if ( InputMsgCode==ID_MSG2N)
    {	
        MsgLen =  LaneConfig_LENGHT;
        memcpy(MessageBody,GetCurrentLanConfig(),LaneConfig_LENGHT);	
    }
    /*************************************************************************************
   * 上班消息
   **************************************************************************************/
    else if (InputMsgCode ==ID_MSGEXITBS)
    {	
        memcpy(MessageBody,GetMessageHead(ID_MSGEXITBS),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgExitBS(),LENGHT_MSG_EXITBS);	//
        MsgLen =LENGHT_MSG_EXITBS;
    }
    else if (InputMsgCode==ID_MSGEXITHT)//小时交通量
    {	
		SendHT(MessageBody);	
        MsgLen =LENGHT_MSG_EXITHT;
    }
    else if (InputMsgCode==ID_MSGEXITES)//下班消息
    {	
        char tempBsYmd[15];
        char tempExitEsYmd[15];
        memset(tempBsYmd,' ',sizeof(tempBsYmd));	
        memset(tempExitEsYmd,' ',sizeof(tempExitEsYmd));	
        strncpy(tempBsYmd,GetMsgExitES()->BS_YMDHM,sizeof(GetMsgExitES()->BS_YMDHM));			
        strncpy(tempExitEsYmd,GetMsgExitES()->EXITES_HEAD.YYYYMMDDHHMMSS,sizeof(GetMsgExitES()->EXITES_HEAD.YYYYMMDDHHMMSS));	
        SetExitESMsgWorkTime(GetEixtEsWorkTime(tempBsYmd,tempExitEsYmd));	
        memcpy(MessageBody,(char *)GetMsgExitES(),LENGHT_MSG_EXITES);	
        MsgLen  =LENGHT_MSG_EXITES;		
    }
    else if (InputMsgCode==ID_MSGEXITTR )//过车消息
    {	
		char tempSubTra[2];
		char tempReprint[2];

		tempSubTra[1]=0x00;
        SetExitTRMsgCanopyStatus(Getg_bYuPeng());	
		//if(0==Getg_DisputeType())
		//{	
		//	SetExitTRMsgDisputeType('0');	
		//}
		//if(0==Getg_Violation())
		//{	
		//	SetExitTRMsgViolation('0');	
		//}
		//else
		//{	
		//	SetExitTRMsgViolation('1');	
		//}//测试这段代码
		if(1==GetSubTransNo())
		{	
			SetExitTRMsgsubtranNo('2');	
		}
		if(1==GetG_IsTuoche())
		{	
			SetExitTRMsgsubtranNo('1');	
			AddSubTransNo();	
		}
		if(GetG_reprintbillnum()>0)
		{	
			sprintf(tempReprint,"%d",GetG_reprintbillnum());	
			SetExitTRMsgReceipt(tempReprint[0]);	
		}
		SetExitTRMsgFareTblVer(GetFareVersion());	
        SetExitTRMsgEntryDirection('X');	
        SetExitTRMsgExitDirection('X');	
		SetMsg_TR_WeightInfo();
        msgh=GetMessageHead(ID_MSGEXITTR );	
		SetImageMsgID(msgh);
        memcpy(MessageBody,msgh,MSG_HEAD_LENGTH);	
        exittr=GetMsgExitTR();			
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)exittr,LENGHT_MSG_EXITTR);			
        BuildImageFiles( msgh,exittr);	
		InitMsgImage();
        MsgLen =LENGHT_MSG_EXITTR;
		
    }
    else if (InputMsgCode==ID_MSGEXITVI )//违章记录
    {	
        MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_EXITVI;
        memcpy(MessageBody,GetMessageHead(ID_MSGEXITVI ),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgExitVI (),LENGHT_MSG_EXITVI);	
    }
	else if (InputMsgCode==ID_MSGEXITEI )//例外记录
	{	
		MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_EXITEI;
		memcpy(MessageBody,GetMessageHead(ID_MSGEXITEI ),MSG_HEAD_LENGTH);	
		memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgExitEI (),LENGHT_MSG_EXITEI);	
	}
    else if (InputMsgCode==ID_MSGEM )//紧急车
    {	
        MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_MSGEM;
        memcpy(MessageBody,GetMessageHead(ID_MSGEM ),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgMsgEM (),LENGHT_MSG_MSGEM);	
    }
    else if (InputMsgCode==ID_MSGEI )//例外信息
    {	
        MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_MSGEI;
        memcpy(MessageBody,GetMessageHead(ID_MSGEI ),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgMsgEI(),LENGHT_MSG_MSGEI);	
    }
    else if (InputMsgCode==ID_MSGGR ) //顶棚灯
    {	
        MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_MSGGR;
        memcpy(MessageBody,GetMessageHead(ID_MSGGR ),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgMsgGR(),LENGHT_MSG_MSGGR);	
    }
    else if (InputMsgCode==ID_MSGOF ) //公务车
    {	
        MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_MSGOF;
        memcpy(MessageBody,GetMessageHead(ID_MSGOF ),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgMsgOF(),LENGHT_MSG_MSGOF);	
    }
    else if (InputMsgCode==ID_MSGAK ) //文件确认
    {	
        MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_MSGAK;
        memcpy(MessageBody,GetMessageHead(ID_MSGAK ),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgMsgAK(),LENGHT_MSG_MSGAK);	
    }
    else if (InputMsgCode==ID_SETEXCEPTION ) //设备异常
    {	

    }
        else if (InputMsgCode==ID_SETEXCEPTION ) //设备异常
    {	

    }
    else if (InputMsgCode==ID_TCOMSG  ) ///TCO消息
    {	
        MsgLen =MSG_HEAD_LENGTH +TCOMSG_LENGHT;
        memcpy(MessageBody,GetMessageHead(ID_TCOMSG),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgTCO(),TCOMSG_LENGHT);	
    }
        else if (InputMsgCode==ID_MSGVIEW  ) ///底部信息
    {	
		MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_MSGINFO;
        memcpy(MessageBody,GetMessageHead(ID_MSGVIEW),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgMsgInfo(),LENGHT_MSG_MSGINFO);	
    }
     else if (InputMsgCode==ID_LANEINFO  ) ///T车道信息
    {	
        MsgLen =MSG_HEAD_LENGTH +LENGHT_MSG_LANEINFO;
        memcpy(MessageBody,GetMessageHead(ID_LANEINFO),MSG_HEAD_LENGTH);	
        memcpy(&MessageBody[MSG_HEAD_LENGTH],(char *)GetMsgLaneInfo(),LENGHT_MSG_LANEINFO);	
    }

    /*************************************************************************************
    * 参数版本信息
    **************************************************************************************/
    else if( InputMsgCode=='V')
    {	


    }
	
    for(i=0;i<MsgLen;i++)
    {	
        if(0==MessageBody[i])
        {	
            MessageBody[i] = '0';
        }
    }
    MessageBody[MsgLen] = 0x00;
    if(IsLog)
    {	
        LogCAppLog("发送消息：%s",MessageBody);	
    }
    if(MsgLen>0 )
    {	
		if(InputMsgCode==ID_TCOMSG || ID_LANEINFO == InputMsgCode || ID_MSGVIEW == InputMsgCode)
		{
			SendUdpMessage(MessageBody);
		}
		else
		{
			MsgLen = SetBCC(MessageBody,MsgLen);
			DB_AddMessage(MessageBody);
			MsgLen -=1;
			MessageBody[MsgLen] = 0x00;
			if (InputMsgCode==ID_MSGEXITTR)
			{
				if (GetIs_CardContext_MonthCard_Paid()  ||  GetIs_CardContext_SVCCard_Paid()  )
				{
					struct MSG_HEAD tmph;
					strncpy( (char*)&tmph,MessageBody,sizeof( struct MSG_HEAD ));
					tmph.MsgType='K';
					memcpy(MessageBody,(char*)&tmph,MSG_HEAD_LENGTH);
					MsgLen = SetBCC(MessageBody,MsgLen);
					DB_AddMessage(MessageBody);
				}
			}
			else if (InputMsgCode==ID_MSGEXITES)
			{
				struct MSG_HEAD tmph;
				MsgLen = LENGHT_MSG_NEWEXITES;
				for(i=0;i<MsgLen;i++)
				{	
					if(0==MessageBody[i])
					{	
						MessageBody[i] = '0';
					}
				}
				MessageBody[MsgLen] = 0x00;
				strncpy( (char*)&tmph,MessageBody,sizeof( struct MSG_HEAD ));
				tmph.MsgType=ID_MSGNEWEXITES;
				memcpy(MessageBody,(char*)&tmph,MSG_HEAD_LENGTH);
				memcpy((char*)&MessageBody[LENGHT_MSG_NEWEXITES-LENGHT_MSG_EXITESEND],
					(char*)&MessageBody[LENGHT_MSG_EXITES -LENGHT_MSG_EXITESEND],LENGHT_MSG_EXITESEND);
				memcpy((char*)&MessageBody[LENGHT_MSG_EXITESHEAD],(char*)GetMsgNewExitES(),MSG_NewTifficStatLenght);
				MsgLen = SetBCC(MessageBody,MsgLen);
				DB_AddMessage(MessageBody);


			}
			else if (InputMsgCode==ID_MSGEXITHT)
			{
				
				struct MSG_HEAD tmph;
				MsgLen = LENGHT_MSG_NEWEXITHT;
				for(i=0;i<MsgLen;i++)
				{	
					if(0==MessageBody[i])
					{	
						MessageBody[i] = '0';
					}
				}
				MessageBody[MsgLen] = 0x00;
				strncpy( (char*)&tmph,MessageBody,sizeof( struct MSG_HEAD ));
				tmph.MsgType=ID_MSGNEWEXITHT;
				memcpy(MessageBody,(char*)&tmph,MSG_HEAD_LENGTH);
				memcpy((char*)&MessageBody[LENGHT_MSG_NEWEXITHT-LENGHT_MSG_EXITHTEND],
					(char*)&MessageBody[LENGHT_MSG_EXITES -LENGHT_MSG_EXITHTEND],LENGHT_MSG_EXITHTEND);
				memcpy((char*)&MessageBody[LENGHT_MSG_EXITHTHEAD],(char*)GetMsgNewExitES(),MSG_NewTifficStatLenght);
				MsgLen = SetBCC(MessageBody,MsgLen);
				DB_AddMessage(MessageBody);
			}
		}
    }
}


