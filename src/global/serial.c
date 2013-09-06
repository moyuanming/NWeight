#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/
#include "serial.h"
#include "LocalIncludeFile.h"
/**
 *@brief  设置串口通信速率
 *@param  fd     类型 int  打开串口的文件句柄
 *@param  speed  类型 int  串口速度
 *@return  void
 */
int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300, B38400,
		B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = { 38400, 19200, 9600, 4800, 2400, 1200, 300, 38400, 19200,
		9600, 4800, 2400, 1200, 300, };
void Serial_Set_Speed(int fd, int speed) {
	int i;
	int status;
	struct termios Opt;
	tcgetattr(fd, &Opt);
	for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++) {
		if (speed == name_arr[i]) {
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&Opt, speed_arr[i]);
			cfsetospeed(&Opt, speed_arr[i]);
			status = tcsetattr(fd, TCSANOW, &Opt);
			if (status != 0) {
				perror("tcsetattr fd");
				return;
			}
			tcflush(fd, TCIOFLUSH);
		}
	}
}

/**
 *@brief   设置串口数据位，停止位和效验位
 *@param  fd     类型  int  打开的串口文件句柄
 *@param  databits 类型  int 数据位   取值 为 7 或者8
 *@param  stopbits 类型  int 停止位   取值为 1 或者2
 *@param  parity  类型  int  效验类型 取值为N,E,O,,S
 */
int Serial_Set_Parity(int fd, int databits, int stopbits, int parity) {
	struct termios options;
	if (tcgetattr(fd, &options) != 0) {
		perror("SetupSerial 1");
		return FALSE;
	}
	options.c_cflag &= ~CSIZE;
	switch (databits) /*设置数据位数*/
	{
	case 7:
		options.c_cflag |= CS7;
		break;
	case 8:
		options.c_cflag |= CS8;
		break;
	default:
		fprintf(stderr, "Unsupported data size\n");
		return FALSE
		;
	}
	switch (parity) {
	case 'n':
	case 'N':
		options.c_cflag &= ~PARENB; /* Clear parity enable */
		options.c_iflag &= ~INPCK; /* Enable parity checking */
		break;
	case 'o':
	case 'O':
		options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
		options.c_iflag |= INPCK; /* Disnable parity checking */
		break;
	case 'e':
	case 'E':
		options.c_cflag |= PARENB; /* Enable parity */
		options.c_cflag &= ~PARODD; /* 转换为偶效验*/
		options.c_iflag |= INPCK; /* Disnable parity checking */
		break;
	case 'S':
	case 's': /*as no parity*/
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		break;
	default:
		fprintf(stderr, "Unsupported parity\n");
		return FALSE
		;
	}
	/* 设置停止位*/
	switch (stopbits) {
	case 1:
		options.c_cflag &= ~CSTOPB;
		break;
	case 2:
		options.c_cflag |= CSTOPB;
		break;
	default:
		fprintf(stderr, "Unsupported stop bits\n");
		return FALSE
		;
	}
	/* Set input parity option */
	if (parity != 'n')
		options.c_iflag |= INPCK;
	tcflush(fd, TCIFLUSH);
	options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
	options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
	if (tcsetattr(fd, TCSANOW, &options) != 0) {
		perror("SetupSerial 3");
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************/
int Serial_Open(unsigned char *dev,int bps) 
{
	//int   status;
	struct termios newtio;
	int WDS_fd=-1;

	WDS_fd = open((char*)dev,O_RDWR/* | O_NOCTTY*/);
	if(WDS_fd < 0)
	{
		
		return -1;		
	}
	/*print_emrc("card_fd_int fd %x!!\n",WDS_fd);*/
	//bzero(&newtio, sizeof(newtio)); /* 清除结构体以放入新的序列埠设定值 */
	tcgetattr(WDS_fd, &newtio);
	/***********************************************************************************************
	*	BAUDRATE: 设定 bps 的速度. 你也可以用 cfsetispeed 及 cfsetospeed 来设定. 
	*	CRTSCTS : 输出资料的硬体流量控制 (只能在具完整线路的缆线下工作  参考 Serial-HOWTO 第七节) 
	*	CS8     : 8n1 (8 位元, 不做同位元检查,1 个终止位元) 
	*	CLOCAL  : 本地连线, 不具数据机控制功能 
	*	CREAD   : 致能接收字元 
	************************************************************************************************/
	newtio.c_cflag = bps | CS8 | CLOCAL | CREAD ;


	/***********************************************************************************************
	*	IGNPAR  : 忽略经同位元检查後, 错误的位元组 
	*	ICRNL   : 比 CR 对应成 NL (否则当输入讯号有 CR 时不会终止输入) 
	*		在不然把装置设定成 raw 模式(没有其它的输入处理)
	************************************************************************************************/
	newtio.c_iflag = 0;//IGNPAR;//IGNPAR | ICRNL;/*HH IGNPAR*/

	/* 	Raw 模式输出. 	*/ 
	newtio.c_oflag = 0;

	/* 	ICANON  : 致能标准输入, 使所有回应机能停用, 并不送出信号以叫用程式 */ 
	newtio.c_lflag = 0;

	/***********************************************************************************************
	*初始化所有的控制特性 
	*预设值可以在 /usr/include/termios.h 找到, 在注解中也有, 
	*但我们在这不需要看它们 	
	************************************************************************************************/

	/*  	现在清除数据机线并启动序列埠的设定 	*/ 
	/**
	* tcflush函数刷清(抛弃)输入缓存(终端驱动程序已接收到，但用户程序尚未读)
	   或输出缓存(用户程序已经写，但尚未发送)。queue参数应是下列三个常数之一：
	* TCIFLUSH刷清输入队列。
	* TCOFLUSH刷清输出队列。 
	* TCIOFLUSH刷清输入、输出队列。
	*/


	//	tcflush(WDS_fd, TCIFLUSH); 
	tcsetattr(WDS_fd,TCSANOW,&newtio);
	return WDS_fd;
}

int Serial_Close(int fd) {
	close(fd);
	return 0;
}

int Serial_Read(int fd, unsigned char *byReadBuf, int nReadLen) {
	int nLen;
	nLen = read(fd, (void *) byReadBuf, nReadLen);
	return nLen;
}

int Serial_Write(int fd, unsigned char *byWriteBuf, int nWriteLen) {
	int nLen;//,i;
	nLen = write(fd, (void *) byWriteBuf, nWriteLen);

	return nLen;
}
