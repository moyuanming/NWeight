// ***************************************************************
//  RecvMessageDataHandl   version:  1.0   ·  date: 12/13/2007
//  -------------------------------------------------------------
//  处理由TCO 发送过来的数据
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
* 执行来自服务器的指令
*/
void ExecTCOCommand(const   char * InputRevbData)
{
	echoic("主程序收到：%s CMD:%s",InputRevbData,SUBSTRING(GetMsgTcoCommand()->CMD));
	if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_RETURNDATETIME,strlen(TCOCMD_RETURNDATETIME)))
	{
		echoic("返回时间");
		SendTCOMsg(MSGTCO_CMD_RETTIME,GetTime(DATETIME_FORMAT_YYYY_MM_DD_HH_MM_SS));    
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_NOWSYNTIME,strlen(TCOCMD_NOWSYNTIME)))
	{
		echoic("同步时间%s",InputRevbData);

		SendMsgToSync(InputRevbData);
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_RETURNPARAMVER,strlen(TCOCMD_RETURNPARAMVER)))
	{
		echoic("返回版本号%s",   (char*)GetMsgRevision());  
		SendTCOMsg(MSGTCO_CMD_PARAMVER, (char*)GetMsgRevision());   
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_NOWUPDATEPARAM,strlen(TCOCMD_NOWUPDATEPARAM)))
	{
		echoic("同步参数表");
		SyncToDo("SYNCREMOTE");
		SendMsgToSync(InputRevbData);
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,TCOCMD_TCOSTARTED ,strlen(TCOCMD_TCOSTARTED)))
	{
		SendLaneInfo_default();  
		SendMsgInfo("联机消息","","已联机"); 
		echoic("联机");

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
		SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"所有参数表已确认更新成功!");
		SendMsgInfo("参数表消息","","参数表更新成功");
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"PARAMERROR",strlen("SYNCRETURN")))
	{
		SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"参数表更新失败!");
		SendMsgInfo("参数表消息","","参数表更新失败!");
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
	}
	else if (0==strncmp((char*)&GetMsgTcoCommand()->CMD,"SYNCRETURN",strlen("SYNCRETURN")))
	{
		echoic("正在处理数据...%s",(char*)&GetMsgTcoCommand()->Param);
		if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"PARAMSISOK",strlen("PARAMSISOK")))
		{
			int x=0;
			echoic("正在加载参数表！");
			LoadGetParameterFileList();
			x = LoadParameter(ISLOADFIRST);
			LoadAppFunction();
			LoadLanConfig();
			LedClare(T);
			if (x==1)
			{
				SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"参数表更新并加载成功!");
				SendMsgInfo("参数表","","参数下发成功!");
			}
			else
			{
				SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"参数表已更新,但加载失败!");
				SendMsgInfo("参数表消息","","参数表出错!");
			}
			SendTCOMsg(MSGTCO_CMD_PARAMVER, (char*)GetMsgRevision());   
		}
		else if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"PARAMERROR",strlen("PARAMERROR")))
		{
			SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"传送参数表时遇到网络或FTP故障!");
			SendMsgInfo("参数表消息","","参数表出错!");
		}
		else if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"REMOTEPMOK",strlen("REMOTEPMOK")))
		{
			int xxx=0;

			/*xxx=LoadParameter_CARDInfo(ISLOADFIRST);
			LoadLanKey();
			if (xxx==1)
			{
			SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"远程IC卡信息更新成功!");
			SendMsgInfo("参数表消息","","IC卡信息已经升级!");
			}
			else
			{
			SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"远程IC卡信息更新成功,但为正确加载!");
			SendMsgInfo("参数表消息","","远程参数表未能加载!");

			}*/
			//
		}
		else if (0==strncmp((char*)&GetMsgTcoCommand()->Param,"REMOTEPMNO",strlen("REMOTEPMNO")))
		{
			///*SendTCOMsg(MSGTCO_CMD_PARAMUPDATE,"远程IC卡信息更新失败!车道暂不能刷卡");
			//SendMsg*/Info("参数表消息","","远程参数表错误,IC卡将不可用!");

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



