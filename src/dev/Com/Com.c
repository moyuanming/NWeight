
#include "LocalIncludeFile.h"
int g_hCOM[20];
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
    bzero(&newtio, sizeof(newtio));/* 清除结构体以放入新的序列埠设定值 */
    newtio.c_cflag = nBaud |  CS8 | CLOCAL | CREAD ;
    newtio.c_iflag = IGNPAR ;//| ICRNL;/*HH IGNPAR*/
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;//ICANON; /*HH 0*/
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
    tcflush(g_hCOM[nCOM-1], TCIFLUSH);	
    tcsetattr(g_hCOM[nCOM-1],TCSANOW,&newtio);	
    return 0;
}
int serial_initbit7_JI(int nCOM, int nBaud)
{
 
	char szCOM[20];
	memset(szCOM,0x00,20);
	sprintf(szCOM,"/dev/COM%d",nCOM);	
	g_hCOM[nCOM-1] = open(szCOM,O_RDWR | O_NOCTTY | O_NONBLOCK);
	if(g_hCOM[nCOM-1] < 0)
	{	
		printf("Open Error!");
		return -1;
	}
	return set_Parity(g_hCOM[nCOM-1],7,1,'O');
}
int set_Parity(int fd,int databits,int stopbits,int parity)
{ 
	printf("set_Parity In");
	struct termios options; 
	if  ( tcgetattr( fd,&options)  !=  0) { 
		perror("SetupSerial 1");     
		return(FALSE);  
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
		fprintf(stderr,"Unsupported data size\n"); return (FALSE);  
	}
	switch (parity) 
	{   
	case 'n':
	case 'N':    
		options.c_cflag &= ~PARENB;   /* Clear parity enable */
		options.c_iflag &= ~INPCK;     /* Enable parity checking */ 
		break;  
	case 'o':   
	case 'O':     
		options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/  
		options.c_iflag |= INPCK;             /* Disnable parity checking */ 
		break;  
	case 'e':  
	case 'E':   
		options.c_cflag |= PARENB;     /* Enable parity */    
		options.c_cflag &= ~PARODD;   /* 转换为偶效验*/     
		options.c_iflag |= INPCK;       /* Disnable parity checking */
		break;
	case 'S': 
	case 's':  /*as no parity*/   
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;break;  
	default:   
		fprintf(stderr,"Unsupported parity\n");    
		return (FALSE);  
	}  
	/* 设置停止位*/  
	switch (stopbits)
	{   
	case 1:    
		options.c_cflag &= ~CSTOPB;  
		break;  
	case 2:    
		options.c_cflag |= CSTOPB;  
		break;
	default:    
		fprintf(stderr,"Unsupported stop bits\n");  
		return (FALSE); 
	} 
	/* Set input parity option */ 
	if (parity != 'n')   
		options.c_iflag |= INPCK; 
	tcflush(fd,TCIFLUSH);
	//options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/   
	//options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
	if (tcsetattr(fd,TCSANOW,&options) != 0)   
	{ 
		perror("SetupSerial 3");   
		return (FALSE);  
	} 
	printf("set_Parity Out");
	return (TRUE);  
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
