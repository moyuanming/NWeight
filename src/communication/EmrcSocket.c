// ***************************************************************
//  EmrcSocket   version:  1.0   ·  date: 11/30/2007
//  -------------------------------------------------------------
//
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"



static int CliSocket = 0;
static volatile int ConnectFlag = 0;
static volatile int HeartWatchDog = 0;
static volatile int MessageWatchDog = 0;
static volatile sem_t HandSocketSync;
static volatile sem_t AcceptDataSync;

/****************************************************************************************
* 初始化Socket
*****************************************************************************************/
  long TestSocketCount = 0;
  void InitSocket(void)
{
    int flags;
    sem_init((sem_t *)&HandSocketSync,0,0);
    sem_init((sem_t *)&AcceptDataSync,0,0);
    CreateRecvThread();
con:
    CliSocket = socket(AF_INET,SOCK_STREAM,0);
    if ((flags = fcntl(CliSocket, F_GETFL, 0)) < 0)
    {
        close(CliSocket);
        goto con;
    }
    if(connect_socket_timeout(CliSocket,(char *)GetMagServerIP(),GetMsgServerProt(),3) ==-1)
    {
        sleep(1);
        close(CliSocket);
        goto con;
    }
    if (fcntl(CliSocket, F_SETFL, flags ) < 0)
    {

    }
    EmrcSocketConnect();
    sem_post((sem_t *)&HandSocketSync);
    if(-1==SocketSend((char *)GetRegMessage()))
    {
        goto con;
    }
    sem_post((sem_t *)&AcceptDataSync);
     SendLaneInfo_default();
     HeartWatchDog=0;
     MessageWatchDog=0;
    while(1)
    {
        if( !ConnectFlag)
        {
            break;
        }
        if(HeartWatchDog)
        {
            if(-1 ==SocketSend(HEART_MSG))
            {
                DisConnect();
                break;
            }
            if(++MessageWatchDog>5)
            {

                DisConnect();
               break;
            }
        }
        else
        {
            HeartWatchDog = 1;
        }
        MessageWatchDog = 1;    //喂狗

        sleep(1);
    }
    goto con;

}
/****************************************************************************************
* Socket 发送字符串
*****************************************************************************************/
  long SendIndex = 0;
  int  SocketSend(char *InputSendData)
{
    int ret =-1;
    char Temp[MAXMSGBODYLENGTH +2 ] = {0};
	char ptemp[20];
    sem_wait((sem_t *)&HandSocketSync);
    if(1==ConnectFlag)
    {
        sprintf(Temp,"%s%s",InputSendData,"\r\n");
		strncpy(ptemp,Temp,19);
		ptemp[19] = 0x00;
        ret = send(CliSocket,Temp, strlen(Temp),0)  ;
        if(-1== ret)
        {
            DisConnect();
        }
        else
        {
            sem_post((sem_t *)&HandSocketSync);
        }
    }
    return ret;
}
/****************************************************************************************
 * 设置Socket的连接状态
 * Socket 连接成功 EmrcSocketConnect
 * Socket 连接失败 DisConnect
 *****************************************************************************************/
   BOOL REGESTED = F;
  void EmrcSocketConnect(void)
{
    ConnectFlag = 1;
    SetDevCStatePlazaServerState(ConnectFlag);
}
  void DisConnect(void)
{
    ConnectFlag = 0;
	REGESTED = FALSE;
	SetDevCStatePlazaServerState(DEVCOMSTATE_DISCONNECT);
    close(CliSocket);
}
/****************************************************************************************
 * 处理接受的数据
 * 根据返回值来判断 下一步操作
 ****************************************************************************************/
 
  void HandRecvData( char *InputRecvData)
{
	char *MessageData;
	HeartWatchDog = 0;
    if(0 == strncmp(InputRecvData,ACK_MSG,3))
    {
		if( DeleteSendedMessageFromMessageQueue(InputRecvData+3))
	   {
			usleep(1000);
			MessageData = GetCurrentMessage();
			if(NULL!=MessageData)
			{
				SocketSend(MessageData);
			}
	   }
    }
	else if(0 == strncmp(InputRecvData,ACK_REG,3))
	{
		REGESTED = TRUE;
		MessageData = GetCurrentMessage();
		if(REGESTED && NULL!=MessageData)
		{
			SocketSend(MessageData);
		}
	}
    else if(0 == strncmp(InputRecvData,HEART_MSG,3)  || 0 == strncmp(InputRecvData,NAK_MSG,3))
    {
		
        MessageData = GetCurrentMessage();
        if(REGESTED && NULL!=MessageData)
        {
            SocketSend(MessageData);
        }

    }
	else if(0 == strncmp(InputRecvData,BCCERROR_MSG,3))
	{
		CheckMessageBCC();
	}
    else if(0 == strncmp(InputRecvData,NAK_REG,3))
    {
        DisConnect();
	}
    else
    {
        RecvMsgDataHandl((unsigned char *)InputRecvData);
    }
    //处理接受数据！
}

/****************************************************************************************
* 根据消息中 的 \r 与 \n来拆分消息
****************************************************************************************/
  void SplitRecvData(char * InputRecvData)
{

    int Index = 0;
	char Recvtemp[20];
	int Len = strlen(InputRecvData);
    int  i;
	echo("RecvData:%s",InputRecvData);
    for (i=0;i<Len;i++)
    {

        if('\n'!=InputRecvData[i])
        {
			Recvtemp[Index++] = InputRecvData[i];
        }
        else
        {
			Recvtemp[Index-1] = 0x00;
            Index = 0;
			HandRecvData(Recvtemp);
        }
    }
	memset(InputRecvData,0x00,200);
	if(0!=Index)
	{

		strncpy(InputRecvData,Recvtemp,Index);
		InputRecvData[Index] = 0x00;
	}

}
/****************************************************************************************
* 接受数据的线程
* 使用了阻塞的 只有有数据才唤醒
****************************************************************************************/
void RecvData(void)
{
    char strRecv[100];
	char ReadBuff[200];
    int RecvLen = 0;
    memset(strRecv,0x00,100);
	memset(ReadBuff,0x00,200);
    sem_wait((sem_t *)&AcceptDataSync);
    while(1)
    {
        if(ConnectFlag)
        {
			memset(strRecv,0x00,100);
            RecvLen =read(CliSocket,strRecv,100);
            if(RecvLen >0)
            {

                strRecv[RecvLen] = '\0';
				sprintf(ReadBuff,"%s%s",ReadBuff,strRecv);
                SplitRecvData(ReadBuff);
            }
            else
            {
                DisConnect();

            }
        }
        else
        {
            sem_wait((sem_t *)&AcceptDataSync);
        }
        usleep(3000);
    }

}

static pthread_t MessageThread;
int Init_TCP_Socket()
{

    int ret;
    pthread_attr_t new_attr;
    pthread_attr_init(&new_attr);
    pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&MessageThread, &new_attr, (void *)InitSocket, NULL);
    pthread_attr_destroy(&new_attr);
    return ret;
}
static pthread_t RecvThread;
int CreateRecvThread()
{

    int ret;
    pthread_attr_t new_attr;
    pthread_attr_init(&new_attr);
    pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&RecvThread, &new_attr, (void *)RecvData, NULL);
    pthread_attr_destroy(&new_attr);
    LogCAppLog("启动接受数据线程");
    return ret;
}

  int connect_socket_timeout(int sockfd,char *dest_host, int port, int timeout)
{
    struct sockaddr_in address;
    int  err, noblock=1 , connect_ok=0, begin_time=time(NULL);

    address.sin_addr.s_addr =inet_addr(dest_host);

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    /* Take the first IP address associated with this hostname */
    ioctl(sockfd,FIONBIO,&noblock);

    /** connect until timeout */
    /*
    EINPROGRESS                A nonblocking socket connection cannot be completed immediately.
    EALREADY                The socket is nonblocking and a        previous connection attempt has not been completed.
    EISCONN                        The socket is already connected.
    */
    if (connect(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0)
    {
        err = errno;
        if (err != EINPROGRESS)
        {
        }
        else
        {
            while (1) /* is noblocking connect, check it until ok or timeout */
            {
                connect(sockfd, (struct sockaddr *) &address, sizeof(address));
                err = errno;
                switch (err)
                {
                    case EISCONN:   /* connect ok */
                        connect_ok = 1;
                        break;
                    case EALREADY:  /* is connecting, need to check again */
                        //                                                        log_info("connect again return EALREADY check again...\n");
                        usleep(50000);
                        break;
                        //13779038135
                        //                                                default:   /* failed, retry again ? */
                        //fprintf(stderr,"connect fail err=%d \n",err);
                        //                                                        connect_ok = -1;
                        //                                                        break;
                }
                if (connect_ok==1)
                {
                    //                                            log_info ("connect ok try time =%d \n", (time(NULL) - begin_time) );
                    break;
                }
                if (connect_ok==-1)
                {
                    fprintf(stderr,"connect failed try time =%ld", (time(NULL) - begin_time) );
                    break;
                }
                if ( (timeout>0) && ((time(NULL) - begin_time)>timeout) )
                {
                    //fprintf(stderr,"connect failed, timeout %d seconds\n", (time(NULL) - begin_time));
                    break;
                }
            }
        }
    }
    else        /* Connect successful immediately        */
    {
        //                    log_info("connect immediate success to host %s\n", dest_host);
        connect_ok = 1;
    }
    /** end of try connect */
    return ((connect_ok==1)?sockfd:-1);
}
