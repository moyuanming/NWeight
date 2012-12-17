// ***************************************************************
//  RecvMessageDataHandl   version:  1.0   ��  date: 12/13/2007
//  -------------------------------------------------------------
//  ������TCO ���͹���������
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************

#include "LocalIncludeFile.h"
#define DEBUGRECVDATA


struct MSG_TCOCMD  MsgTCOCommand;
struct MSG_TCOCMD *GetMsgTcoCommand(void)
{	
    return &MsgTCOCommand;
}
void InitMsgTcoCommand(void)
{	
    memset((char*)&MsgTCOCommand,' ',sizeof(struct MSG_TCOCMD));	
}
/**
 * ִ�����Է�������ָ��
 */
void ExecTCOCommand(const   char * InputRevbData)
{
	 echoic("�������յ���%s CMD:%s",InputRevbData,SUBSTRING(GetMsgTcoCommand()->CMD));
	if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_RETURNDATETIME,strlen(TCOCMD_RETURNDATETIME)))
	{
		echoic("����ʱ��");
		SendTCOMsg(MSGTCO_CMD_RETTIME,GetTime(DATETIME_FORMAT_YYYY_MM_DD_HH_MM_SS));    
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_NOWSYNTIME,strlen(TCOCMD_NOWSYNTIME)))
	{
		echoic("ͬ��ʱ��%s",InputRevbData);
	
		SendMsgToSync(InputRevbData);
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_RETURNPARAMVER,strlen(TCOCMD_RETURNPARAMVER)))
	{
		echoic("���ذ汾��%s",   (char*)GetMsgRevision());  
		SendTCOMsg(MSGTCO_CMD_PARAMVER, (char*)GetMsgRevision());   
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_NOWUPDATEPARAM,strlen(TCOCMD_NOWUPDATEPARAM)))
	{
		echoic("ͬ��������");
		SyncToDo("SYNCREMOTE");
		SendMsgToSync(InputRevbData);
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_TCOSTARTED ,strlen(TCOCMD_TCOSTARTED)))
	{
	 	SendLaneInfo_default();  
		SendMsgInfo("������Ϣ","","������"); 
	//echox("������Ϣ");
			echoic("����");
 
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"TCOCOMMADN",strlen("TCOCOMMADN")))
	{
		SendMsgToSync(InputRevbData);

	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"MD5SUMFILE",strlen("MD5SUMFILE")))
	{
		SendTCOMsg(MSGTCO_CMD_MD5SUMFILE,(char*)&GetMsgTcoCommand()->Param);

	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"TIMESYNCED",strlen("SYNCRETURN")))
	{
		SendTCOMsg(MSGTCO_CMD_TIMESYNC,SUBSTRING(GetMsgTcoCommand()->Param));
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"PARAMSISOK",strlen("SYNCRETURN")))
	{
		SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"���в�������ȷ�ϸ��³ɹ�!");
		SendMsgInfo("��������Ϣ","","��������³ɹ�");
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"PARAMERROR",strlen("SYNCRETURN")))
	{
		SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"���������ʧ��!");
		SendMsgInfo("��������Ϣ","","���������ʧ��!");
	}
	else if(0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_REMOTCOMD,strlen(TCOCMD_REMOTCOMD)))
	{
		char temp[11];
		int message;
		WPARAM wParam;
		LPARAM lParam;
		memset(temp,0x0,11);
		strncpy(temp,GetMsgTcoCommand()->Param,10);
		message = atoi(temp);
		
		memset(temp,0x0,11);
		strncpy(temp,GetMsgTcoCommand()->Param+10,10);
		wParam = atoi(temp);

		memset(temp,0x0,11);
		strncpy(temp,GetMsgTcoCommand()->Param+20,10);
		lParam = atoi(temp);
		echoic("message %d wparam %d lparam %d",message,wParam,lParam);
		PostMessage(UI_Get_From_Handl(),message,wParam,lParam);
		//strncpy(temp,GetMsgTcoCommand()->Param,3);
		//temp[3] = 0x00;
		//WorkStation(atoi(temp));
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"SYNCRETURN",strlen("SYNCRETURN")))
	{
		echoic("���ڴ�������...%s",(char*)&GetMsgTcoCommand()->Param);
		if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"PARAMSISOK",strlen("PARAMSISOK")))
		{
			int x=0;
			echoic("���ڼ��ز�����");
			LoadGetParameterFileList();
			x = LoadParameter(ISLOADFIRST);
			LoadAppFunction();
			LoadLanConfig();
			LedClare(T);
			if (x==1)
			{
				SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"��������²����سɹ�!");
				SendMsgInfo("������","","�����·��ɹ�!");
			}
			else
			{
				SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"�������Ѹ���,������ʧ��!");
				SendMsgInfo("��������Ϣ","","���������!");
			}
			SendTCOMsg(MSGTCO_CMD_PARAMVER, (char*)GetMsgRevision());   
		}
		else if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"PARAMERROR",strlen("PARAMERROR")))
		{
			SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"���Ͳ�����ʱ���������FTP����!");
			SendMsgInfo("��������Ϣ","","���������!");
		}
		else if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"REMOTEPMOK",strlen("REMOTEPMOK")))
		{
			int xxx=0;

			xxx=LoadParameter_CARDInfo(ISLOADFIRST);
			LoadLanKey();
			if (xxx==1)
			{
				SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"Զ��IC����Ϣ���³ɹ�!");
					SendMsgInfo("��������Ϣ","","IC����Ϣ�Ѿ�����!");
			}
			else
			{
				SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"Զ��IC����Ϣ���³ɹ�,��Ϊ��ȷ����!");
				SendMsgInfo("��������Ϣ","","Զ�̲�����δ�ܼ���!");

			}
			//
		}
		else if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"REMOTEPMNO",strlen("REMOTEPMNO")))
		{
			SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"Զ��IC����Ϣ����ʧ��!�����ݲ���ˢ��");
			SendMsgInfo("��������Ϣ","","Զ�̲��������,IC����������!");
			
		}
		else
		{
			SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,SUBSTRING(GetMsgTcoCommand()->Param));
		}
	}
}
void RecvMsgDataHandl(unsigned char * InputRevbData)
{   
	InitMsgTcoCommand();    
	char temp[200];
	memset(temp,0x00,200);
	memcpy(temp,InputRevbData,sizeof(struct MSG_TCOCMD)); 
	//echoic("UDPMSG %s",temp);
	memcpy(GetMsgTcoCommand(),InputRevbData,sizeof(struct MSG_TCOCMD)); 
	if (0==strncmp(GetMsgTcoCommand()->TCOType,TCOTYPE_TCOCMD,2))
	{
		ExecTCOCommand(InputRevbData);
	}
	else if (0==strncmp(GetMsgTcoCommand()->TCOType,TCOTYPE_TCORET,2))
	{
		echoic("MSG=%s",GetMsgTcoCommand()->CMD);
		WorkStation(atoi(GetMsgTcoCommand()->CMD));
	}
}
 
void DeleteImages(void)
{
	struct MSG_TCOCMD  tmpx111;
	memset((char*)&tmpx111,' ',sizeof(struct MSG_TCOCMD ));
	strncpy(tmpx111.CMD,"DELETEIMGS",10);
	SendMsgToSync((char*)&tmpx111);
	echoic("DeleteImages:%s",(char*)&tmpx111);
}



/*SyncToDo("SYNCREMOTE");*/
void SyncToDo(char *command)
{
	struct MSG_TCOCMD  tmpx111;
	memset((char*)&tmpx111,' ',sizeof(struct MSG_TCOCMD ));
	strncpy(tmpx111.CMD,command,10);
	SendMsgToSync((char*)&tmpx111);
	echoic("SyncToDo:%s",(char*)&tmpx111);
}

 

