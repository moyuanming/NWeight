// ***************************************************************
//  MsgEvent   version:  1.0   ·  date: 12/11/2007
//  -------------------------------------------------------------
//  车道事件消息
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"

//作用：发送MSGEI消息，处理各种事件
//创建人: 麦壳饼

void SendMsgEI(char* InputEquipment,char InputStatus,char* InputMemo)
{
    InitMsgMsgEI();
    SetMsgEIMsgEquipment(InputEquipment);
    SetMsgEIMsgMARK('0');
    SetMsgEIMsgMemo(InputMemo);
    SetMsgEIMsgStatus(InputStatus);
    SendMessageToQueue(ID_MSGEI);
}
/*******************************************************************************************************
*作用：发送MSGAK  文件确认数据   消息，处理各种事件
Author:  LZP
Date: 15/5/2008
********************************************************************************************************/
void SendMsgAK(char InputFileType,char InputRecStatus)
{
	char  *FileType;
    InitMsgMsgAK();
    SetMsgAKMsgFileType(InputFileType);
    SetMsgAKMsgRecStatus(InputRecStatus);
    SetMsgAKMsgMARK('0');

	switch(InputFileType)
	{
			case  '1':
				FileType="下发职员表" ;
				break;
			case  '2':
				FileType="下发月票卡";
				break;
			case  '3':
				FileType="下发优惠卡";
				break;
			case  '4':
				FileType="下发费率表 ";
				break;
			case  '5':
				FileType="下发优惠率描述表";
				break;
			default:
				FileType="其它参数表";
				break;
	}
	SetG_weiZhangType(4);
	SendMsgInfo("参数表下发消息","",FileType);	   //qq
    SendMessageToQueue(ID_MSGAK);
}

/*******************************************************************************************************
*作用：发送MSGEM   紧急车数据表  消息，处理各种事件
Author:  LZP
Date: 15/5/2008
********************************************************************************************************/
void SendMsgEM(char InputDetectorError)
{
    InitMsgMsgEM();
    SetMsgEMMsgDetectorError(InputDetectorError);
    SetMsgEMMsgMARK('0');
    SendMessageToQueue(ID_MSGEM);
}

/*******************************************************************************************************
*作用：发送MSGGR  顶棚灯数据  消息，处理各种事件
Author:  LZP
Date: 15/5/2008
********************************************************************************************************/
void SendMsgGR(char InputCanopy)
{
    //InitMsgMsgGR();
    SetMsgGRMsgCanopy(InputCanopy);
    SetMsgGRMsgMARK( '0');
    SendMessageToQueue(ID_MSGGR);
}

/*******************************************************************************************************
*作用：发送MSGOF   公务车队数据  消息，处理各种事件
Author:  LZP
Date: 15/5/2008
********************************************************************************************************/
void SendMsgOF(char InputFLAG,char* InputVehicleCount)
{
    InitMsgMsgOF();
    SetMsgOFMsgFLAG(InputFLAG);
    SetMsgOFMsgVehicleCount(InputVehicleCount);
    SetMsgOFMsgMARK( '0');
    SendMessageToQueue(ID_MSGOF);
}
//发送监控消息
void SendTCOMsg(char MsgType,char*MsgContext)
{
    if(0== 1 && GetDevCStatePlazaServerState())
    {
        return;
    }
    InitMsgTCO();
    memcpy(GetMsgTCO()->MsgContext,MsgContext,strlen(MsgContext));
    GetMsgTCO()->MsgType =MsgType ;
    SendMessageToQueue(ID_TCOMSG );
	if (0!=strncmp(MsgContext,"OK",2))
	{
		echoic("发送给监控:%s",MsgContext);
	}
}

/***************************************************************
* 初始化
****************************************************************/
void InitMsgHour()
{
    memset((char *)MsgHour,'0',sizeof(struct MSG_HOUR));
    strncpy(MsgHour->HourTime,GetTime(DATETIME_FORMAT_YYYYMMDDHHMM),sizeof(MsgHour->HourTime));
    if (msync((void *)MsgHour,sizeof(struct MSG_HOUR),MS_SYNC)<0)
    {
        LogCAppLog("Msync Faile!");
    }
}
/***************************************************************
* 车道绿灯时间
****************************************************************/
void AddMsgHourtmGreene()
{
    AddField(MsgHour->tmGreen,sizeof(MsgHour->tmGreen));
    if(msync((void *)MsgHour,sizeof(struct MSG_HOUR),MS_SYNC)<0)
    {
        LogCAppLog("Msync Faile!");
    }
}
/***************************************************************
* 加载
****************************************************************/
void LoadMsgHour()
{
    MsgHour = GetSyncMsgHour();
}

char *  tmpClientMsg="";

/*----------------------------------------------------------------------------------------------------------------------------------------------------------
函数名称：   void SendLaneInfo(void)
作用：          为后台监控提供车道状态信息，即监控程序上面列表框中显示的实时的信息
参数：
返回值：        无
创建日期：      2008.7
创建人:         lzp
----------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SendLaneInfo_default(void )
{
    if(0== 1 && GetDevCStatePlazaServerState())
    {
        return;
    }
    sprintf(GetMsgLaneInfo()->LaneNo,"%3.3s",GetLanConfigLaneNo());
    sprintf(GetMsgLaneInfo()->CollName,"%16.16s",Getg_szName());
    sprintf(GetMsgLaneInfo()->CollNo,"%10.10s",GetG_Number());
    sprintf(GetMsgLaneInfo()->ClientMsg,"%32.32s",tmpClientMsg);
    sprintf(GetMsgLaneInfo()->CarType,"%5.5s",Get_Current_Car_Type());
    if (Get_G_Current_Actual_pay()>0)
    {
        sprintf(GetMsgLaneInfo()->Money,"%10d",(int)Get_G_Current_Actual_pay());
    }
    else
    {
        sprintf(GetMsgLaneInfo()->Money,"%10.10s"," ");
    }
    sprintf(GetMsgLaneInfo()->CarKind,"%16.16s",Getg_CurrentCarKindExplain());
    sprintf(GetMsgLaneInfo()->WrokMode,"%16.16s",Getg_workStatus_str());
    sprintf(GetMsgLaneInfo()->JobBeginTime,"%32.32s",GetOnJobDateTime());
     GetMsgLaneInfo()->YuPengDeng = Getg_bYuPeng()|0x30;
     GetMsgLaneInfo()->JiaoTongDeng=Getg_bJiaoTong()|0x30;
     GetMsgLaneInfo()->LanGan =Getg_bLanGan()|0x30;
     GetMsgLaneInfo()->Printer=Getg_bPrint()|0x30;
     GetMsgLaneInfo()->Network='1';
     SendMessageToQueue(ID_LANEINFO);
	 InitMsgLaneInfo();
}

void SendLaneInfo(char *InputClientMsg)
{
    tmpClientMsg=InputClientMsg;
    SendLaneInfo_default();
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------
函数名称：   void SendLaneInfo(void)
作用：          为后台监控提供过车信息，即监控程序下面列表框中显示的相应的信息
参数：           消息类型 / 付款方式  /异常情况   /提示信息
返回值：        无
创建日期：      2008.7
创建人:         lzp
----------------------------------------------------------------------------------------------------------------------------------------------------------*/

void SendMsgInfo(char* InputMsgType,char* InputException,char* InputPromptMsg)
{
    char  * Receipt;
    char  *WeiZhangType;
	char tempWzCarType[2];
	char devstate[20];
    char   date[4];
    char   time[6];
	memset(devstate,0x00,20);
    if(0== 1 && GetDevCStatePlazaServerState())
    {
        return;
    }
	memset(tempWzCarType,0x00,2);
    strncpy(date,GetMsgHead()->Day,sizeof(date));
    strncpy(time,GetMsgHead()->Hour,sizeof(time));
    switch (GetG_BillPrintFlag())
    {
        case 0:
            Receipt="不要票据";
            break;
        case 1:
            Receipt="正常";
            break;
        case 2:
            Receipt="备用手撕票";
            break;
        case 3:
            Receipt="重打票据";
            break;
        default:
            Receipt="";
            break;
    }
    switch (GetG_weiZhangType())
    {
        case 0:
            WeiZhangType="	";
            break;
		case 1:
            WeiZhangType="闯道";
            break;
        case 2:
            WeiZhangType="倒车";
            break;
        case 3:
            WeiZhangType="误报警";
            break;
        default:
            WeiZhangType="";
            break;
    }
    InitMsgMsgInfo();
    sprintf(GetMsgMsgInfo()->LaneNo,"%3.3s",GetLanConfigLaneNo());
    sprintf(GetMsgMsgInfo()->MsgType ,"%10.10s",InputMsgType);
    sprintf(GetMsgMsgInfo()->OccDate,"%14.4s",date);
    sprintf(GetMsgMsgInfo()->OccTime,"%14.6s",time);
    sprintf(GetMsgMsgInfo()->CollNo,"%10.6s",GetG_Number());
	if(1==GetG_weiZhangType())
	{
		sprintf(tempWzCarType,"%d",wzCarType);
		sprintf(GetMsgMsgInfo()->CarKind ,"%16.9s","闯道车");
		sprintf(GetMsgMsgInfo()->CarType,"%5.4s",tempWzCarType);
		SetG_weiZhangType(4);
	}
	else
	{
		sprintf(GetMsgMsgInfo()->CarKind ,"%16.9s",Getg_CurrentCarKindExplain());
		sprintf(GetMsgMsgInfo()->CarType,"%5.4s",Get_Current_Car_Type());
	}
	char InputPayType[20];
	memset(InputPayType,0x00,20);
	echoic("GetMsgExitTR()->Method_Pay=%c",GetMsgExitTR()->Method_Pay);
	switch (GetMsgExitTR()->Method_Pay)
	{
		default:
			strcpy(InputPayType,"");
			break;
		case 'E':
			strcpy(InputPayType,"未付款");
			break;
		case 'D':
			strcpy(InputPayType,"欠款");
			break;
		case '1':
			strcpy(InputPayType,"人民币");
			break;
		case '2':
			strcpy(InputPayType,"储值卡");
			sprintf(devstate , "%s",GetCardContext_CardNumber());
			break;
		case '3':
			strcpy(InputPayType,"公务卡");
			break;
		case '4':
			strcpy(InputPayType,"月票卡");
			sprintf(devstate  ,"%s",GetCardContext_CardNumber());
			break;
		case '5':
			strcpy(InputPayType,"记账卡");
			sprintf(devstate , "%s",GetCardContext_CardNumber());
			break;
	}
    sprintf(GetMsgMsgInfo()->PayType ,"%16.16s",InputPayType);
    if (Get_G_Current_Actual_pay()>0)
    {
        sprintf(GetMsgMsgInfo()->Cash,"%16d",(int)Get_G_Current_Actual_pay());
    }
    else
    {
        sprintf(GetMsgMsgInfo()->Cash,"%16.16s"," ");
    }
    sprintf(GetMsgMsgInfo()->Receipt ,"%16.16s",Receipt);
    sprintf(GetMsgMsgInfo()->Exception,"%32.32s",InputException);
	sprintf(GetMsgMsgInfo()->Peccancy ,"%32.32s",WeiZhangType);
	sprintf(GetMsgMsgInfo()->DevStatus,"%32.32s",devstate);
	sprintf(GetMsgMsgInfo()->PromptMsg ,"%64.64s",InputPromptMsg);
	if (NULL==strstr(InputMsgType,"过车" ))
	{
		sprintf(GetMsgMsgInfo()->CarKind ,"%16.9s"," ");

		sprintf(GetMsgMsgInfo()->CarType,"%5.4s", " ");
		sprintf(GetMsgMsgInfo()->PayType ,"%16.16s","");
		sprintf(GetMsgMsgInfo()->Cash,"%16.16s"," ");
	}
	else
	{
		char   tmp[32];
		memset(tmp,0x00,32);
		sprintf(tmp,"%32s",GetYCQK());
		strncpy((char*)&GetMsgMsgInfo()->Exception,tmp,32);
		echoic("Exception:%s %s  ",SUBSTRING(GetMsgMsgInfo()->Exception),tmp);
		InitYCQK();
	}
	SendMessageToQueue(ID_MSGVIEW);
}

//#define  DEBUGSAVEMSG
#define print_Socket(_Format_,args...)  //printf("CARD DEGUG  [%s:%d]: " _Format_ "\n", __FILE__, __LINE__ , ## args)

#define LogCAppError(_Format_,args...)
#define print_ReadMsgFile(_Format_,args...)

