
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

    bzero(&newtio, sizeof(newtio));/* ����ṹ���Է����µ����в��趨ֵ */
/*
BAUDRATE: �趨 bps ���ٶ�. ��Ҳ������ cfsetispeed �� cfsetospeed ���趨.
CRTSCTS : ������ϵ�Ӳ���������� (ֻ���ھ�������·�������¹���  �ο� Serial-HOWTO ���߽�)
CS8     : 8n1 (8 λԪ, ����ͬλԪ���,1 ����ֹλԪ)
CLOCAL  : ��������, �������ݻ����ƹ���
CREAD   : ���ܽ�����Ԫ
*/
    newtio.c_cflag = nBaud |  CS8 | CLOCAL | CREAD ;
/*
IGNPAR  : ���Ծ�ͬλԪ�����, �����λԪ��
ICRNL   : �� CR ��Ӧ�� NL (��������Ѷ���� CR ʱ������ֹ����)
            �ڲ�Ȼ��װ���趨�� raw ģʽ(û�����������봦��)
 */

    newtio.c_iflag = IGNPAR ;//| ICRNL;/*HH IGNPAR*/
/*
 Raw ģʽ���.
*/
    newtio.c_oflag = 0;

/*
 ICANON  : ���ܱ�׼����, ʹ���л�Ӧ����ͣ��, �����ͳ��ź��Խ��ó�ʽ
*/
    newtio.c_lflag = 0;//ICANON; /*HH 0*/




/*
 ��ʼ�����еĿ�������
 Ԥ��ֵ������ /usr/include/termios.h �ҵ�, ��ע����Ҳ��,
 ���������ⲻ��Ҫ������
*/
    newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
    newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    newtio.c_cc[VERASE]   = 0;     /* del */
    newtio.c_cc[VKILL]    = 0;     /* @ */
    newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
    newtio.c_cc[VTIME]    = 0;     /* ��ʹ�÷ָ���Ԫ��ļ�ʱ�� */
    newtio.c_cc[VMIN]     = 1;     /* �ڶ�ȡ�� 1 ����Ԫǰ��ֹͣ */
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
  ����������ݻ��߲��������в����趨
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
