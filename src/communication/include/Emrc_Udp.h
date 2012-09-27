#ifndef __Emrc_Udp_H__
#define __Emrc_Udp_H__
#define MAX_DATA_LEN 8192

#define UDP_Send(_socketUDP_,_buf_,_addr_) sendto((_socketUDP_), (_buf_), (strlen((_buf_))),( 0),((struct sockaddr *)&(_addr_)),( sizeof(struct sockaddr)))
#define UDP_Recv(_socketUDP_,_buf_,_addr_,_RecvadLen_) recvfrom((_socketUDP_),(_buf_),sizeof(_buf_),(0),((struct sockaddr *) &(_addr_)),(&(_RecvadLen_)))

int CreateUDP(void);
void SetSendUdp(struct sockaddr_in *InputSockAddr ,int UdpPort,char *UdpIp);
int SetRecvUdp(int FD_Udp,struct sockaddr_in *InputSockAddr ,int UdpPort);

#endif

