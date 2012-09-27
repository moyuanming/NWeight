#ifndef __LINUX_INCLUDE_H__
#define __LINUX_INCLUDE_H__

/*��������ͷ�ļ�*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/timeb.h>
/*@-skipposixheaders@*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <malloc.h>
#include <stdarg.h>
#include <sys/mman.h>
#include <ctype.h> 
#include <dirent.h>

int g_hCOM[5];


/*���ڴ��ڱ��*/
#include <fcntl.h>
#include <termios.h>

/*���ڴ�����*/
#include <errno.h>

/*�����߳�*/
#include <pthread.h>

/*�����ź���*/
#include <semaphore.h>
#include <signal.h>

/*�����������*/
#include <linux/soundcard.h>


/*����socket*/


//#include <setjmp.h>
//#include <limits.h>
//#include <unistd.h>
//
//#include <sys/wait.h>
///*@-skipposixheaders@*/
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netinet/tcp.h>



/*MiniGUI����ͷ�ļ�*/
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mgext.h>

/*libxml*/
//#include <libxml/xmlmemory.h>
//#include <libxml/parser.h>

/*�Լ����*/
extern int dprintf (int __fd, __const char *__restrict __fmt, ...)
     __THROW __attribute__ ((__format__ (__printf__, 2, 3)));


#endif
