
#include "LocalIncludeFile.h"
int SocketUDP;
int SocketUDPToMe;
struct sockaddr_in their_SendTOMe_addr;
struct sockaddr_in their_Send_addr;
struct sockaddr_in their_Recv_addr;
static void RecvUDPMessage(void)
{
	int RecvCount=0;
	unsigned char  RecvBuf[200];
	int SocketRecvLen;
	SocketRecvLen = sizeof(their_Recv_addr);
	while(1)
	{
		memset(RecvBuf,0x00,200);
		RecvCount =UDP_Recv(SocketUDP,RecvBuf,their_Recv_addr,SocketRecvLen);
		RecvBuf[RecvCount] = 0x00;
		RecvMsgDataHandl( RecvBuf);
		echoic("%s",RecvBuf);
	}

}
static pthread_t UDPMessageThread;
static int CreateRecvUDPMessageThread(void)
{
	int ret;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&UDPMessageThread, &new_attr, (void *)RecvUDPMessage, NULL);
	pthread_attr_destroy(&new_attr);
	return ret;
}
void Init_UDP_Socket()
{
	char temp[3];
	strncpy(temp,&GetLanConfigLaneNo()[1],2);
	temp[2]=0x00;
	SocketUDP = CreateUDP();
	SocketUDPToMe = CreateUDP();

	their_Send_addr.sin_family = AF_INET;
	their_Send_addr.sin_port = htons(GetTCOPort()+ atoi(temp)-1);
	their_Send_addr.sin_addr.s_addr =inet_addr(GetTCOServerIP() );
	bzero(&(their_Send_addr.sin_zero), 8);


	their_SendTOMe_addr.sin_family = AF_INET;
	their_SendTOMe_addr.sin_port = htons(12701);
	their_SendTOMe_addr.sin_addr.s_addr =inet_addr("127.0.0.1" );
	bzero(&(their_SendTOMe_addr.sin_zero), 8);

	their_Recv_addr.sin_family = AF_INET;	
	their_Recv_addr.sin_port = htons(GetTCOPort());
	their_Recv_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(their_Recv_addr.sin_zero), 8);
	if (bind(SocketUDP, (struct sockaddr *)&their_Recv_addr, sizeof(struct sockaddr)) == -1)
	{ 
		perror("bind");
		exit(1);
	}
	CreateRecvUDPMessageThread();
}
void SendUdpMessage(char *SendMsgBody)
{
	UDP_Send(SocketUDP,SendMsgBody,their_Send_addr);
}
void SendMsgToSync(const char *SendMsgBody)
{
	echoic("发给同步程序的指令:%s",SendMsgBody);
	UDP_Send(SocketUDPToMe,SendMsgBody,their_SendTOMe_addr);

}


