#ifndef _InterFaceStruct_H_
#define _InterFaceStruct_H_



void InitUdp(int Port,int IsBind);
char *Udp_Base_RecvData(char *Buf,int Length,int SocketUDP);
int Udp_Base_SendData(char *Buf,char *SendToIP,int SendToPort);
#endif
