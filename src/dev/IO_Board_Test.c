#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<strings.h>		/* for convenience */

#include<time.h>

#include	"IO_Board.h"

/********定义输出字符的颜色***********/
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

/*********金额显示器的命令***********/
 char Tfi_10yuan[23]  = {0xFF,0xDC,0x17,0x44,0xCD,0x02,0xBD,0xF0,0xB6,0xEE,0xA3,0xBA,0x31,0x30,0xD4,0xAA,0x20,0x20,0x20,0x20,0x20,0x20,0xCC};
 char Tfi_chexing1[23]= {0xFF,0xDC,0x17,0x44,0xCD,0x01,0xB3,0xB5,0xD0,0xCD,0xA3,0xBA,0x31,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xAF};
unsigned char testusar[1024];
static char in_test=0;

/*分析IO输入变化 此函数传入IO_Board_Init 作为回调函数*/
void Analyse_Gpio_in(unsigned int stat)
{
	if(in_test != 1)
		return;

	fprintf(stderr,"%s检测到输入变化：%s0x%08X\n",GCor,PCor,stat);
	switch(stat)
	{
		case GuangShanUp:
			fprintf(stderr,"%s光栅到达%s\n",GCor,PCor);
			break;
		case GuangShanDown:
			fprintf(stderr,"%s光栅离开%s\n",GCor,PCor);
			break;
		case LineZhaPaiUp:

			break;			fprintf(stderr,"%s抓拍线圈到达%s\n",GCor,PCor);
		case LineZhaPaiDown:
			fprintf(stderr,"%s抓拍线圈离开%s\n",GCor,PCor);
			break;
		case LinePassUp:
			fprintf(stderr,"%s通过线圈到达%s\n",GCor,PCor);
			break;
		case LinePassDown:
			fprintf(stderr,"%s通过线圈离开%s\n",GCor,PCor);
			break;
		case ConnError:
			fprintf(stderr,"%s通信错误%s\n",GCor,PCor);
			break;
	}
	
	
}
void UseHelp(char *help)
{
	fprintf(stderr,"%s\n使用方法: %s [tfi] [out] [in] [vdm]\n",GCor,help);
	fprintf(stderr,"%s请输入正确的参数! \n",RCor);
	fprintf(stderr,"%s tfi = 测试金额显示器\n",DEFCor);
	fprintf(stderr,"%s out = 测试IO板输出\n",DEFCor);
	fprintf(stderr,"%s in  = 测试IO板输入\n",DEFCor);
	fprintf(stderr,"%s vmd = 测试字符叠加\n\n",DEFCor);
}
int main(int argc, char *argv[])
{
	int i;
	time_t timep;
	struct tm *p;

	 char VMD_buf[25]="2012/12/30 18:30:31    ";//19

	time(&timep);
	p=localtime(&timep); /*取得当地时间*/

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
		fprintf(stderr,"\n\n\n%s IO板初始化错误 !\n\n\n\n",RCor);
		return -1;
	}
	if(strcmp("tfi",argv[1])==0)
	{
		#if 1
		/*测试金额显示器*/
		fprintf(stderr,"%s\n测试金额显示器(请观察显示器的现实是否正常)!\n\n",DGCor);
		if(IO_Usart_Tx(Tfi_10yuan,40) < 0)
			fprintf(stderr,"%s发生数据失败(请检查IO板或连接线)!\n",RCor);
		else
			fprintf(stderr,"%s显示(10元)\n",GCor);
		if(IO_Usart_Tx(Tfi_chexing1,40) < 0)
			fprintf(stderr,"%s发生数据失败(请检查IO板或连接线)!\n",RCor);
		else
			fprintf(stderr,"%s显示(车型1)\n",GCor);
		fprintf(stderr,"\n%s金额显示器测试结束!\n\n",DGCor);

		#else
		IO_Usart_Tx(testusar,1024);
		#endif
	}else if(strcmp("out",argv[1])==0)
	{
		/*测试IO板输出*/
		fprintf(stderr,"%s\n输出测试：所有通道(开启->0.2秒->关闭)!\n\n",DGCor);
		for(i=0;i<20;i++)
		{
			fprintf(stderr,"%s第 %02d 次: ",DEFCor,i+1);
			if(IO_Board_Out(0xffff,0) < 0)
			{
				fprintf(stderr,"%s失败(请检查IO板或连接线)!\n",RCor);
				continue;
			}
			sleep(1);
			if(IO_Board_Out(0,0xffff) < 0)
			{
				fprintf(stderr,"%s失败(请检查IO板或连接线)!\n",RCor);
				continue;
			}
			sleep(1);
			fprintf(stderr,"%s成功!\n",GCor);
		}
		fprintf(stderr,"\n%s输出测试结束!\n\n",DGCor);
	}else if(strcmp("in",argv[1])==0)
	{
		/*测试IO板输入*/
		in_test = 1;
		fprintf(stderr,"%s\n输入测试:请改变输入状态并观察打印结果（测试时间60秒）!\n\n",DGCor);
		sleep(60);
		fprintf(stderr,"\n%s输入测试结束!\n\n",DGCor);
	}else if(strcmp("vdm",argv[1])==0)
	{
		/*测试字符叠加*/
		fprintf(stderr,"%s\n字符叠加:请观察显示器视频窗口的变化(测试5次)!\n\n",DGCor);
		for(i=0;i<5;i++)
		{
			fprintf(stderr,"%s第 %02d 次: ",DEFCor,i+1);
			if(Vdm_line(0,0,24,"                                  ") < 0)
			{
				fprintf(stderr,"%s失败(请检查IO板或连接线)!\n",RCor);
				continue;
			}
			if(Vdm_line(1,0,24,"                                  ") < 0)
			{
				fprintf(stderr,"%s失败(请检查IO板或连接线)!\n",RCor);
				continue;
			}
			sleep(1);
			if(Vdm_line(0,0,24,"TEST VDM..............!!!!!!!!!!!!!!") < 0)
			{
				fprintf(stderr,"%s失败(请检查IO板或连接线)!\n",RCor);
				continue;
			}
			if(Vdm_line(1,0,24,"0123456789ABCDEFGabcdefghijhijk") < 0)
			{
				fprintf(stderr,"%s失败(请检查IO板或连接线)!\n",RCor);
				continue;
			}
			sleep(1);
			fprintf(stderr,"%s发送成功!\n",GCor);
		}
		fprintf(stderr,"\n%s字符叠加测试结束!\n\n",DGCor);
	}else
	{
		
		UseHelp(argv[0]);
	}
	return 0;
}

