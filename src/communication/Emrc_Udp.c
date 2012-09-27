#include "LocalIncludeFile.h"


int CreateUDP(void)
{
	return socket(AF_INET, SOCK_DGRAM, 0);
}
void SetSendUdp(struct sockaddr_in *InputSockAddr ,int UdpPort,char *UdpIp)
{
	InputSockAddr->sin_family = AF_INET;
	InputSockAddr->sin_port = htons(UdpPort);
	InputSockAddr->sin_addr.s_addr =inet_addr(UdpIp);
	bzero(&(InputSockAddr->sin_zero), 8);
}
int SetRecvUdp(int FD_Udp,struct sockaddr_in *InputSockAddr ,int UdpPort)
{
	int ret = 0;
	InputSockAddr->sin_family = AF_INET;
	InputSockAddr->sin_port = htons(UdpPort);
	InputSockAddr->sin_addr.s_addr = INADDR_ANY;
	bzero(&(InputSockAddr->sin_zero), 8);
	ret = bind(FD_Udp, (struct sockaddr *)InputSockAddr, sizeof(struct sockaddr));
	return ret;
}
