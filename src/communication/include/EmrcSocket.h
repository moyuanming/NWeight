#ifndef __EmrcSocket_H__
#define __EmrcSocket_H__



#define MAX_LANE		60           //一个站内最大车道数
#define MSG_SERVER		0         //本进程工作在Socket Server模式下
#define MSG_CLIENT		1         //本进程工作在Socket Client模式下

#define MSG_START		"~@"
#define MSG_AT_START	"~`"
#define MSG_END			"~$"
#define ACK_MSG			"!!!"
#define NAK_MSG			"!?!"
#define ACK_REG			"!*!"
#define NAK_REG			"!^!"
#define HEART_MSG		"!@!"
#define BCCERROR_MSG	"!#!"
#define LEN_CLIENTNO	15
#define LEN_MSGHEAD		40

#define SVR_PORT	8000
#define BUFFER_SIZE 1024
int Init_TCP_Socket(void);
extern in_addr_t inet_addr (__const char *__cp) __THROW;

  void InitSocket(void);	 
  void RecvData(void); 
  int CreateRecvThread(void); 
    int  SocketSend(char *InputSendData);	 
  int connect_socket_timeout(int sockfd,char *dest_host, int port, int timeout);	 
  void DisConnect(void); 
  void EmrcSocketConnect(void);	
#endif


