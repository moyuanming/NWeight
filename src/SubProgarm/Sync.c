// ***************************************************************
//  Sync   version:  1.0   ·  date: 01/07/2008
//  -------------------------------------------------------------
//  同步 参数文件
//  同步 时间
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"
int main(void);
BOOL  sub_SyncParam( char* locfile );
void  SyncParam(void);
void  BadCmd(void);
void RecvMsgDataHandl_Sync(  char * InputRevbData);
int  SyncParams(char * param);
void SyncDate(void);
int SocketUDP_Sync;
struct sockaddr_in their_Send_addr_Sync;
struct sockaddr_in their_Recv_addr_Sync;
static void RecvUDPMessageSync_Sync(void)
{
	int RecvCount=0;
	int RecvBuf[200];
	unsigned int SocketRecvLen;
	SocketRecvLen = sizeof(their_Recv_addr_Sync);
	while(1)
	{
		memset(RecvBuf,0x00,200);
		RecvCount =UDP_Recv(SocketUDP_Sync,RecvBuf,their_Recv_addr_Sync,SocketRecvLen);
		RecvBuf[RecvCount] = 0x00;
		echoic("RecvData:[%s]",(char*)&RecvBuf);
		RecvMsgDataHandl_Sync((char*)&RecvBuf);
		usleep(100);
	}
}
static pthread_t UDPMessageThread_Sync;
static int CreateRecvUDPMessageThread_Sync(void)
{
	int ret;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&UDPMessageThread_Sync, &new_attr, (void *)RecvUDPMessageSync_Sync, NULL);
	pthread_attr_destroy(&new_attr);
	return ret;
}



char ret[3024];
char *DoSysCmd(char * cmdline)
{
    FILE *fp;
    char line[32];
    char cmdtmp[256];
    memset(cmdtmp,0x00,sizeof(cmdtmp));

    sprintf(cmdtmp,"%s  2>&1",cmdline);

    memset(ret,0x00,sizeof(ret));

    fp = popen(cmdtmp, "r");

    while( fgets( line, sizeof(line), fp))
    {
        sprintf(ret ,"%s%s",ret,line);
    }

    pclose(fp);

    return ret;
}


static void InitSoucket_Sync(void)
{
    SocketUDP_Sync = CreateUDP();
	their_Send_addr_Sync.sin_family = AF_INET;
	their_Send_addr_Sync.sin_port = htons(GetTCOPort());
	their_Send_addr_Sync.sin_addr.s_addr =inet_addr("127.0.0.1");

	bzero(&(their_Send_addr_Sync.sin_zero), 8);
	their_Recv_addr_Sync.sin_family = AF_INET;	
	their_Recv_addr_Sync.sin_port = htons(12701);
	their_Recv_addr_Sync.sin_addr.s_addr = INADDR_ANY;
	bzero(&(their_Recv_addr_Sync.sin_zero), 8);
	if (bind(SocketUDP_Sync, (struct sockaddr *)&their_Recv_addr_Sync, sizeof(struct sockaddr)) == -1)
	{ 
		perror("bind");
		exit(1);
	}


	CreateRecvUDPMessageThread_Sync();
}


static void SendUdpMessage_Sync(const char* SendMsgBody)
{
	 UDP_Send(SocketUDP_Sync,SendMsgBody,their_Send_addr_Sync);
	echoic("发送到EMRC%s ",SendMsgBody);
}

struct MSG_TCOCMD tmp_sendtoemrc;
void SendToEmrc(char *msg)
{

	char tmpmsg[51] ;
	memset(tmpmsg,0x00,51);
	memset((char *)&tmp_sendtoemrc,' ',sizeof(struct MSG_TCOCMD));
	sprintf(tmpmsg,"%-50s",msg);
	strncpy(tmp_sendtoemrc.Param,tmpmsg,sizeof(tmp_sendtoemrc.Param));
	strncpy(tmp_sendtoemrc.TCOType,TCOTYPE_TCOCMD,2);
	memcpy(tmp_sendtoemrc.CMD,"SYNCRETURN",sizeof(tmp_sendtoemrc.CMD));
	SendUdpMessage_Sync((char*)&tmp_sendtoemrc);
}
struct MSG_TCOCMD tmp_sendtoemrc_TIME;
void SendToEmrcTIME(char *msg)
{

	char tmpmsg[51] ;
	memset(tmpmsg,0x00,51);
	memset((char *)&tmp_sendtoemrc_TIME,' ',sizeof(struct MSG_TCOCMD));
	sprintf(tmpmsg,"%-50s",msg);
	strncpy(tmp_sendtoemrc_TIME.Param,tmpmsg,sizeof(tmp_sendtoemrc_TIME.Param));
	strncpy(tmp_sendtoemrc_TIME.TCOType,TCOTYPE_TCOCMD,2);
	memcpy(tmp_sendtoemrc_TIME.CMD,"TIMESYNCED",sizeof(tmp_sendtoemrc_TIME.CMD));
	SendUdpMessage_Sync((char*)&tmp_sendtoemrc_TIME);
}


struct MSG_TCOCMD tmp_sendtoemrc_filemd5;
void SendToEmrc_MD5SUMFILE(char *msg)
{

	char tmpmsg[51] ;
	memset(tmpmsg,0x00,51);
	memset((char *)&tmp_sendtoemrc_filemd5,' ',sizeof(struct MSG_TCOCMD));
	sprintf(tmpmsg,"%-50s",msg);
	strncpy(tmp_sendtoemrc_filemd5.Param,tmpmsg,sizeof(tmp_sendtoemrc_filemd5.Param));
	strncpy(tmp_sendtoemrc_filemd5.TCOType,TCOTYPE_TCOCMD,2);
	memcpy(tmp_sendtoemrc_filemd5.CMD,"MD5SUMFILE",sizeof(tmp_sendtoemrc_filemd5.CMD));
	SendUdpMessage_Sync((char*)&tmp_sendtoemrc_filemd5);
}



void SyncDate(void)
{
	char * tmpxx;
	tmpxx= DoSysCmd(GetNtpDateCommand());
	if (NULL!=strstr(tmpxx,"adjust time server"))
	{
		SendToEmrcTIME("时间同步完成！");
	}
	else
	{
		char tmp[50];
		sprintf(tmp,"与时间服务器%s同步失败！",GetTimeServerIP());
		SendToEmrcTIME(tmp);
	}
}
char md5ret[50];
void SyncParam_MD5Sum(char * paramfile)
{

     char md5cmd[200];
     char remotfile[100];
     memset(md5cmd,0x00,200);
     memset(md5ret,0x00,50);
     sprintf(md5cmd,"md5sum %s", paramfile );
     echoic("命令行命令:%s",md5cmd);
     strncpy(md5ret,  DoSysCmd(md5cmd),32);
     echoic("命令执行返回%s",md5ret);
     memset(remotfile,0x00,100);
     strcpy(remotfile,strrchr(paramfile,'/'));
     sprintf(md5ret,"%s%-18s",substring(md5ret,32),remotfile);
     echoic("最终要发送的数据%s\n|||%s",md5ret,remotfile);
     SendToEmrc_MD5SUMFILE(md5ret);

}

/**
 * 同步指定文件
 *
 * @param locfile 需要同步的文件
 *
 * @return 如果ftp命令执行成功则返回真，否则返回T
 */
BOOL  sub_SyncParam( char* locfile )
{
	char tcomsg[100];
	char TempCommand[200];
	char remotfile[100];
	char * tmpret;
	BOOL result=F;
	memset(TempCommand,0x00,200);
	memset(tcomsg,0x00,100);
	memset(remotfile,0x00,100);
	strcpy(remotfile,&locfile[strlen("../PARAMETER/")]);
	echoic("%s %s",locfile,remotfile);
	FTPSYNCCOMMAND(TempCommand,locfile,remotfile);//此函数在 "LocalIncludeFile.h" 中定义
	echoic("执行FTP指令:%s",TempCommand);
	tmpret=DoSysCmd(TempCommand);
	echoic("执行结果:%s",tmpret);
	if (tmpret==NULL  || strlen(tmpret)==0)
	{
		result=T;
	}
	return result;
}


/**
 * 参数同步。
 *
 * @param param  同步参数，决定那些同步那些不同步。
 */
int SyncParams(char *param )
{
	int res=0;
	BOOL result;
	if (NULL!=strstr(param ,"COL=1;"))
	{
		result= sub_SyncParam( PARACOLLECT_FILE  ) ;
		if (result)
		{
			SyncParam_MD5Sum(PARACOLLECT_FILE);
		}
		else
		{
			res++;
			SendToEmrc("收费员表传送失败");
		}
		echoic("dsafasd");
	}
	if (NULL!=strstr(param ,"YHK=1;"))
	{
		result= sub_SyncParam( PARAYHKLIST_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARAYHKLIST_FILE);
		}
		else
		{
			res++;
			SendToEmrc("优惠卡表传送失败");
		}
	}
	if (NULL!=strstr(param ,"FAR=1;"))
	{
		result= sub_SyncParam( PARAFARELIST_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARAFARELIST_FILE);
		}

		else
		{
			res++;
			SendToEmrc("费率表传送失败");
		}
	}
	if (NULL!=strstr(param ,"YHR=1;"))
	{
		result= sub_SyncParam( PARAYHRATE_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARAYHRATE_FILE);
		}
		else
		{
			res++;
			SendToEmrc("优惠率表传送失败");
		}
	}
	if (NULL!=strstr(param ,"YPK=1"))
	{
		result= sub_SyncParam( PARAYPKLIST_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARAYPKLIST_FILE);
		}
		else
		{
			res++;
			SendToEmrc("月票卡表传送失败");
		}
	}
	if (NULL!=strstr(param ,"JOU=1;"))
	{
		result= sub_SyncParam( PARAJOUCODE_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARAJOUCODE_FILE);
		}
		else
		{
			res++;
			SendToEmrc("旅程表传送失败");
		}
	}
	if (NULL!=strstr(param ,"OFI=1;"))
	{
		result= sub_SyncParam( PARFREECARLIST_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARFREECARLIST_FILE);
		}
		else
		{
			res++;
			SendToEmrc("公务车信息传送失败");
		}
	}
	if (NULL!=strstr(param ,"SVR=1;"))
	{
		result= sub_SyncParam( PARASVRCARDLIST_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARASVRCARDLIST_FILE);
		}
		else
		{
			res++;
			SendToEmrc("IC卡表传送失败");
		}
	}
	if (NULL!=strstr(param ,"CKL=1;"))
	{

		result= sub_SyncParam( PARACARKINDLIST_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARACARKINDLIST_FILE);
		}
		else
		{
			res++;
			SendToEmrc("车种表传送失败");
		}
	}
	if (NULL!=strstr(param ,"WGH=1;"))
	{

		result= sub_SyncParam( PARACONSTANT_FILE  );
		if (result)
		{
			SyncParam_MD5Sum(PARACONSTANT_FILE);
		}
		else
		{
			res++;
			SendToEmrc("计重信息常量表传输失败");
		}
	}
	return  res;
}


void RecvMsgDataHandl_Sync(  char * InputRevbData)
{
	struct MSG_TCOCMD  tcocmd;
	memcpy(&tcocmd,InputRevbData,sizeof(struct MSG_TCOCMD));
	echoic("%s",InputRevbData);
	if (0==strncmp(tcocmd.CMD,TCOCMD_RETURNDATETIME,strlen(TCOCMD_RETURNDATETIME)))
	{
		echoic("返回时间");
		SendUdpMessage_Sync(InputRevbData);
	}
	else if (0==strncmp(tcocmd.CMD,TCOCMD_RETURNPARAMVER,strlen(TCOCMD_RETURNPARAMVER)))
	{

		SendUdpMessage_Sync(InputRevbData);
	}
	if (0==strncmp(tcocmd.CMD,TCOCMD_NOWSYNTIME,strlen(TCOCMD_NOWSYNTIME)))
	{
		SyncDate();

	}
	else if (0==strncmp(tcocmd.CMD,TCOCMD_NOWUPDATEPARAM,strlen(TCOCMD_NOWUPDATEPARAM)))
	{
		int res;
		char param[50];
		char tmpx[10];
		memset(tmpx ,0x00,10);
		memset(param,0x00,50);
		strncpy(param,tcocmd.Param,sizeof(tcocmd.Param));
		res=SyncParams(param);
		if (res==0)
		{
			SendToEmrc("PARAMSISOK");
		}
		else
		{
			SendToEmrc("PARAMERROR" );
		}
	}
	else if (0==strncmp(tcocmd.CMD,"TCOCOMMADN",strlen("TCOCOMMADN")))
	{
		char param1[50];
		char *tmt1;
		memset(param1,0x00,50);
		tmt1= DoSysCmd (SUBSTRING(tcocmd.Param));
		sprintf(param1,"%-50s",tmt1);
		echoic("%s\n%s",param1,tmt1);
		SendToEmrc(param1);
	}
	else if (0==strncmp(tcocmd.CMD,"DELETEIMGS",strlen("DELETEIMGS")))
	{
		DoSysCmd("rm "FILENAME_SAVE_ImageUPLOAD"* -f");
		echoic("rm "FILENAME_SAVE_ImageUPLOAD"* -f");
	}
	else 
	{
		echoic("Sync Unknow command%s",SUBSTRING(tcocmd.CMD));
	}

}


int main(void)
{
	LogCGenera("Sync",LOG_INFOR,"启动参数时间同步服务");//
	LoadCommunctionConfig();//
	LoadGetParameterFileList();
	InitSoucket_Sync();
	while (1)
	{

		echoic("10分钟同步时间一次：%s",DoSysCmd(GetNtpDateCommand()));
		sleep(60*10);//

	}
}


