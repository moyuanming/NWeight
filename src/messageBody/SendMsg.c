// ***************************************************************
//  MsgEvent   version:  1.0   ��  date: 12/11/2007
//  -------------------------------------------------------------
//  �����¼���Ϣ
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"

//���ã�����MSGEI��Ϣ����������¼�
//������: ��Ǳ�

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
*���ã�����MSGAK  �ļ�ȷ������   ��Ϣ����������¼�
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
				FileType="�·�ְԱ��" ;
				break;
			case  '2':
				FileType="�·���Ʊ��";
				break;
			case  '3':
				FileType="�·��Żݿ�";
				break;
			case  '4':
				FileType="�·����ʱ� ";
				break;
			case  '5':
				FileType="�·��Ż���������";
				break;
			default:
				FileType="����������";
				break;
	}
	SetG_weiZhangType(4);
	SendMsgInfo("�������·���Ϣ","",FileType);	   //qq
    SendMessageToQueue(ID_MSGAK);
}

/*******************************************************************************************************
*���ã�����MSGEM   ���������ݱ�  ��Ϣ����������¼�
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
*���ã�����MSGGR  ���������  ��Ϣ����������¼�
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
*���ã�����MSGOF   ���񳵶�����  ��Ϣ����������¼�
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
//���ͼ����Ϣ
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
		echoic("���͸����:%s",MsgContext);
	}
}

/***************************************************************
* ��ʼ��
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
* �����̵�ʱ��
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
* ����
****************************************************************/
void LoadMsgHour()
{
    MsgHour = GetSyncMsgHour();
}

char *  tmpClientMsg="";

/*----------------------------------------------------------------------------------------------------------------------------------------------------------
�������ƣ�   void SendLaneInfo(void)
���ã�          Ϊ��̨����ṩ����״̬��Ϣ������س��������б������ʾ��ʵʱ����Ϣ
������
����ֵ��        ��
�������ڣ�      2008.7
������:         lzp
----------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SendLaneInfo_default(void )
{
    if(0== 1 && GetDevCStatePlazaServerState())
    {
        return;
    }
    sprintf(GetMsgLaneInfo()->LaneNo,"%3.3s",GetLanConfigLaneNo());
    sprintf(GetMsgLaneInfo()->CollName,"%32.32s",Getg_szName());
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
�������ƣ�   void SendLaneInfo(void)
���ã�          Ϊ��̨����ṩ������Ϣ������س��������б������ʾ����Ӧ����Ϣ
������           ��Ϣ���� / ���ʽ  /�쳣���   /��ʾ��Ϣ
����ֵ��        ��
�������ڣ�      2008.7
������:         lzp
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
            Receipt="��ҪƱ��";
            break;
        case 1:
            Receipt="����";
            break;
        case 2:
            Receipt="������˺Ʊ";
            break;
        case 3:
            Receipt="�ش�Ʊ��";
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
            WeiZhangType="����";
            break;
        case 2:
            WeiZhangType="����";
            break;
        case 3:
            WeiZhangType="�󱨾�";
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
		sprintf(GetMsgMsgInfo()->CarKind ,"%16.9s","������");
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
			strcpy(InputPayType,"δ����");
			break;
		case 'D':
			strcpy(InputPayType,"Ƿ��");
			break;
		case '1':
			strcpy(InputPayType,"�ֽ�");
			break;
		case '2':
			strcpy(InputPayType,"��ֵ��");
			sprintf(devstate , "%s",GetCardContext_CardNumber());
			break;
		case '3':
			strcpy(InputPayType,"����");
			break;
		case '4':
			strcpy(InputPayType,"��Ʊ��");
			sprintf(devstate  ,"%s",GetCardContext_CardNumber());
			break;
		case '5':
			strcpy(InputPayType,"���˿�");
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
	if (NULL==strstr(InputMsgType,"����" ))
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

