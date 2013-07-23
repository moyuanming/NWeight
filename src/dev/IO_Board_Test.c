#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<strings.h>		/* for convenience */

#include<time.h>

#include	"IO_Board.h"

/********��������ַ�����ɫ***********/
char RCor[]="\033[0;31;1m";
char GCor[]="\033[0;32;1m";
char YCor[]="\033[0;33;1m";
char BCor[]="\033[0;34;1m";
char PCor[]="\033[0;35;1m";
char DGCor[]="\033[0;36;1m";
char RCorF[]="\033[05;31;1m";
char GCorF[]="\033[05;32;1m";
char YCorF[]="\033[05;33;1m";
char BCorF[]="\033[05;34;1m";
char PCorF[]="\033[05;35;1m";
char DGCorF[]="\033[05;36;1m";
char DEFCor[]="\033[0m";

/*********�����ʾ��������***********/
 char Tfi_10yuan[23]  = {0xFF,0xDC,0x17,0x44,0xCD,0x02,0xBD,0xF0,0xB6,0xEE,0xA3,0xBA,0x31,0x30,0xD4,0xAA,0x20,0x20,0x20,0x20,0x20,0x20,0xCC};
 char Tfi_chexing1[23]= {0xFF,0xDC,0x17,0x44,0xCD,0x01,0xB3,0xB5,0xD0,0xCD,0xA3,0xBA,0x31,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xAF};
unsigned char testusar[1024];
static char in_test=0;

/*����IO����仯 �˺�������IO_Board_Init ��Ϊ�ص�����*/
void Analyse_Gpio_in(unsigned int stat)
{
	if(in_test != 1)
		return;

	fprintf(stderr,"%s��⵽����仯��%s0x%08X\n",GCor,PCor,stat);
	switch(stat)
	{
		case GuangShanUp:
			fprintf(stderr,"%s��դ����%s\n",GCor,PCor);
			break;

		case GuangShanDown:
			fprintf(stderr,"%s��դ�뿪%s\n",GCor,PCor);
			break;
		case LineZhaPaiUp:

			break;			fprintf(stderr,"%sץ����Ȧ����%s\n",GCor,PCor);

		case LineZhaPaiDown:
			fprintf(stderr,"%sץ����Ȧ�뿪%s\n",GCor,PCor);
			break;
		case LinePassUp:
			fprintf(stderr,"%sͨ����Ȧ����%s\n",GCor,PCor);
			break;

		case LinePassDown:
			fprintf(stderr,"%sͨ����Ȧ�뿪%s\n",GCor,PCor);
			break;
		case ConnError:
			fprintf(stderr,"%sͨ�Ŵ���%s\n",GCor,PCor);
			break;
	}
	
	
}
void UseHelp(char *help)
{
	fprintf(stderr,"%s\nʹ�÷���: %s [tfi] [out] [in] [vdm]\n",GCor,help);
	fprintf(stderr,"%s��������ȷ�Ĳ���! \n",RCor);
	fprintf(stderr,"%s tfi = ���Խ����ʾ��\n",DEFCor);
	fprintf(stderr,"%s out = ����IO�����\n",DEFCor);
	fprintf(stderr,"%s in  = ����IO������\n",DEFCor);
	fprintf(stderr,"%s vmd = �����ַ�����\n\n",DEFCor);
}
int main(int argc, char *argv[])
{
	int i;
	time_t timep;
	struct tm *p;

	 char VMD_buf[25]="2012/12/30 18:30:31    ";//19

	time(&timep);
	p=localtime(&timep); /*ȡ�õ���ʱ��*/

	sprintf(VMD_buf,"%04d/%02d/%02d %02d:%02d:%02d",(1900+p->tm_year),( 1+p->tm_mon), p->tm_mday,
		p->tm_hour, p->tm_min, p->tm_sec);
	Vdm_line(1 ,2,19,VMD_buf);

	printf("Vdm_line-->%s\n",VMD_buf);
	
	if(argc  <= 1 )
	{
		UseHelp(argv[0]);
		return -1;
	}

	for(i=0;i<1024;i++)
		testusar[i]=i;
	
	if(IO_Board_Init(Analyse_Gpio_in) <0)
	{
		fprintf(stderr,"\n\n\n%s IO���ʼ������ !\n\n\n\n",RCor);
		return -1;
	}
	if(strcmp("tfi",argv[1])==0)
	{
		#if 1
		/*���Խ����ʾ��*/
		fprintf(stderr,"%s\n���Խ����ʾ��(��۲���ʾ������ʵ�Ƿ�����)!\n\n",DGCor);
		if(IO_Usart_Tx(Tfi_10yuan,40) < 0)
			fprintf(stderr,"%s��������ʧ��(����IO���������)!\n",RCor);
		else
			fprintf(stderr,"%s��ʾ(10Ԫ)\n",GCor);
		if(IO_Usart_Tx(Tfi_chexing1,40) < 0)
			fprintf(stderr,"%s��������ʧ��(����IO���������)!\n",RCor);
		else
			fprintf(stderr,"%s��ʾ(����1)\n",GCor);
		fprintf(stderr,"\n%s�����ʾ�����Խ���!\n\n",DGCor);

		#else
		IO_Usart_Tx(testusar,1024);
		#endif
	}else if(strcmp("out",argv[1])==0)
	{
		/*����IO�����*/
		fprintf(stderr,"%s\n������ԣ�����ͨ��(����->0.2��->�ر�)!\n\n",DGCor);
		for(i=0;i<20;i++)
		{
			fprintf(stderr,"%s�� %02d ��: ",DEFCor,i+1);
			if(IO_Board_Out(0xffff,0) < 0)
			{
				fprintf(stderr,"%sʧ��(����IO���������)!\n",RCor);
				continue;
			}
			sleep(1);
			if(IO_Board_Out(0,0xffff) < 0)
			{
				fprintf(stderr,"%sʧ��(����IO���������)!\n",RCor);
				continue;
			}
			sleep(1);
			fprintf(stderr,"%s�ɹ�!\n",GCor);
		}
		fprintf(stderr,"\n%s������Խ���!\n\n",DGCor);
	}else if(strcmp("in",argv[1])==0)
	{
		/*����IO������*/
		in_test = 1;
		fprintf(stderr,"%s\n�������:��ı�����״̬���۲��ӡ���������ʱ��60�룩!\n\n",DGCor);
		sleep(60);
		fprintf(stderr,"\n%s������Խ���!\n\n",DGCor);
	}else if(strcmp("vdm",argv[1])==0)
	{
		/*�����ַ�����*/
		fprintf(stderr,"%s\n�ַ�����:��۲���ʾ����Ƶ���ڵı仯(����5��)!\n\n",DGCor);
		for(i=0;i<5;i++)
		{
			fprintf(stderr,"%s�� %02d ��: ",DEFCor,i+1);
			if(Vdm_line(0,0,24,"                                  ") < 0)
			{
				fprintf(stderr,"%sʧ��(����IO���������)!\n",RCor);
				continue;
			}
			if(Vdm_line(1,0,24,"                                  ") < 0)
			{
				fprintf(stderr,"%sʧ��(����IO���������)!\n",RCor);
				continue;
			}
			sleep(1);
			if(Vdm_line(0,0,24,"TEST VDM..............!!!!!!!!!!!!!!") < 0)
			{
				fprintf(stderr,"%sʧ��(����IO���������)!\n",RCor);
				continue;
			}
			if(Vdm_line(1,0,24,"0123456789ABCDEFGabcdefghijhijk") < 0)
			{
				fprintf(stderr,"%sʧ��(����IO���������)!\n",RCor);
				continue;
			}
			sleep(1);
			fprintf(stderr,"%s���ͳɹ�!\n",GCor);
		}
		fprintf(stderr,"\n%s�ַ����Ӳ��Խ���!\n\n",DGCor);
	}else
	{
		
		UseHelp(argv[0]);
	}
	return 0;
}

