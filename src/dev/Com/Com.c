
#include "LocalIncludeFile.h"
int g_hCOM[8];
int serial_init(int nCOM, int nBaud)
{	
    struct termios newtio;
    char szCOM[20];
    sprintf(szCOM,"%s%d",Get_ComName(),nCOM);
    g_hCOM[nCOM-1] = open(szCOM,O_RDWR | O_NOCTTY | O_NONBLOCK);

    if(g_hCOM[nCOM-1] < 0)
    {	
        return -1;
    }
	//return set_Parity(g_hCOM[nCOM-1],8,1,'N');

    bzero(&newtio, sizeof(newtio));/* 清除结构体以放入新的序列埠设定值 */
/*
BAUDRATE: 设定 bps 的速度. 你也可以用 cfsetispeed 及 cfsetospeed 来设定.
CRTSCTS : 输出资料的硬体流量控制 (只能在具完整线路的缆线下工作  参考 Serial-HOWTO 第七节)
CS8     : 8n1 (8 位元, 不做同位元检查,1 个终止位元)
CLOCAL  : 本地连线, 不具数据机控制功能
CREAD   : 致能接收字元
*/
    newtio.c_cflag = nBaud |  CS8 | CLOCAL | CREAD ;
/*
IGNPAR  : 忽略经同位元检查後, 错误的位元组
ICRNL   : 比 CR 对应成 NL (否则当输入讯号有 CR 时不会终止输入)
            在不然把装置设定成 raw 模式(没有其它的输入处理)
 */

    newtio.c_iflag = IGNPAR ;//| ICRNL;/*HH IGNPAR*/
/*
 Raw 模式输出.
*/
    newtio.c_oflag = 0;

/*
 ICANON  : 致能标准输入, 使所有回应机能停用, 并不送出信号以叫用程式
*/
    newtio.c_lflag = 0;//ICANON; /*HH 0*/




/*
 初始化所有的控制特性
 预设值可以在 /usr/include/termios.h 找到, 在注解中也有,
 但我们在这不需要看它们
*/
    newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
    newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    newtio.c_cc[VERASE]   = 0;     /* del */
    newtio.c_cc[VKILL]    = 0;     /* @ */
    newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
    newtio.c_cc[VTIME]    = 0;     /* 不使用分割字元组的计时器 */
    newtio.c_cc[VMIN]     = 1;     /* 在读取到 1 个字元前先停止 */
    newtio.c_cc[VSWTC]    = 0;     /* '\0' */
    newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
    newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
    newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
    newtio.c_cc[VEOL]     = 0;     /* '\0' */
    newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
    newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
    newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
    newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
    newtio.c_cc[VEOL2]    = 0;     /* '\0' */


/*echoic("RUn is ");
  现在清除数据机线并启动序列埠的设定
*/
    tcflush(g_hCOM[nCOM-1], TCIFLUSH);	
    tcsetattr(g_hCOM[nCOM-1],TCSANOW,&newtio);	
	
    return 0;
}

int serial_close(int nCOM)
{	
    close(g_hCOM[nCOM-1]);	
    return 0;
}

int serial_read(int nCOM,unsigned char *byReadBuf,int nReadLen)
{	
    int nLen;
    nLen = read(g_hCOM[nCOM-1], (void *)byReadBuf, nReadLen);	
    return nLen;
}

int serial_write(int nCOM,unsigned char *byWriteBuf,int nWriteLen)
{	
    int nLen;//,i;
    nLen = write(g_hCOM[nCOM-1], (void *)byWriteBuf, nWriteLen);	

    return nLen;
}
