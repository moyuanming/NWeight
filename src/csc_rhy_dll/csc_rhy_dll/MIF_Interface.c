    /********************************************************************
	created:	2008/06/12
	created:	12:6:2008   10:29
	filename: 	d:\LnTc\trunk\src\Lane\src\dev\MIFInterface.c
	file path:	d:\LnTc\trunk\src\Lane\src\dev
	file base:	MIFInterface
	file ext:	c
	author:		MYM
	
	purpose:	天线接口
	Version:    $Id: MIFInterface.c 5480 2008-06-13 05:16:33Z mym $
*********************************************************************/
//#include "../include/linux_include.h"
//#include "include/MIF_Interface.h"
#include "LocalIncludeFile.h"
//#include "st_main.h"
//#include "include/CRC.h"

#define USR_Start1			0x55		//开始位第一位
#define USR_Start2			0xAA		//开始位第二位
#define USR_Request			0x01 /*寻卡 防碰撞获得卡号*/
#define USR_Select			0x02 /*选择卡*/
#define USR_PiccRead		0x03 /*读卡*/
#define USR_PiccWrite		0x04 /*写卡*/
#define USR_PiccHalt		0x05 /*挂起*/
#define USR_PcdRfReset		0x06 /*复位M1 卡 + 时间(ms) =2*/
#define USR_LoadKeyE2		0x10 /*下载密钥 到E2 存储器 可掉电存储*/
#define USR_PiccAuthE2		0x11 /*从E2 验证密钥*/
#define USR_BuzzSwitch		0x30 /*蜂鸣器开关1=on 0=off*/


#define  KeyCommandLen 0x9

#define Secteur0 0x00 //第一扇区
#define Secteur1 0x01 //第一扇区
#define Secteur2 0x02 //第一扇区
#define Secteur3 0x03 //第一扇区
#define PICC_AUTHENT1A 0x60
#define PICC_AUTHENT1B 0x61
#define KEYA 0x60		
#define KEYB 0x61

#define CommandRequestLength 	0x02
#define CommandReadLength 		0x04
#define CommandSelecLength 		0x05
#define CommandWriteLength 		0x14
#define CommandBuzzSwitchLength 		0x14
#define		CRC8		0x80


uint getcrc(uint ninit_checksum, uint ncrc_type, unsigned char *cdata, uint nlength)
{
	uint	i;
	uint	j;
	uint	flag;
	uint	current;
	uint	nchecksum;

	nchecksum = ninit_checksum;
	for(i = 0; i < nlength; i++)
	{
		// As the data in byte, so the current only infect low byte
		current = (nchecksum ^ cdata[i]) & 0xFF;
		for(j = 0; j < 8; j++)
		{
			// Check from bit0 to bit8, only use for right Cyclic
			flag = current & 0x01;
			current = current >> 1;
			if(flag != 0)
			{
				// Xor the crc type
				// the type code may be 0x8c, 0xA001, 0x8408, 0xEDB88320
				current = current ^ ncrc_type;
			}
			// Watch the middle value
			////print_emrc("%08X\t", current);
		}
		// Checksum xor the new data's crc data
		nchecksum = (nchecksum >> 8) ^ current;
	}

	return nchecksum;
}
uint getcrc8(unsigned char *cdata, uint nlength)
{
	uint	nchecksum;

	nchecksum = getcrc(0x00, CRC8, cdata, nlength);

	return nchecksum;
}


/************************************************************************
*      Name：	初始化天线
* Parameter：	ProtNumber 串口号
*				Bdps 破特率
*				ArgMsg 有卡时发送的消息号
*				ArgWindowsHandl 窗体句柄
*	  Return:   0 Sucess				
*	 Example:	MIFInitManager("/dev/ttyS1",B115200,124,1)
************************************************************************/
int fd_com;
int MIFMessage;
int MIFHandl;



int MIFInitManager(void **ArgMifRegPtr,char *ProtNumber,int Bdps,int ArgMsg,int ArgWindowsHandl)
{	
	struct termios newtio;
	//print_emrc("-->天线串口号：%s \n",ProtNumber);
	fd_com = open(ProtNumber,O_RDWR | O_NOCTTY /*| O_NONBLOCK*/);
	////print_emrc("-->MIFInitManager fd_com=%d  \n",fd_com);
	if(fd_com < 0){
//		//print_emrc("card_fd_int Failed!!\n");
		return -1;
	}
	close(fd_com);
	fd_com = open(ProtNumber,O_RDWR | O_NOCTTY /*| O_NONBLOCK*/);
	if(fd_com < 0){
//		//print_emrc("card_fd_int Failed!!\n");
		return -1;
	}
	////print_emrc("card_fd_int fd %x!!\n",fd_com);
	bzero(&newtio, sizeof(newtio)); /* 清除结构体以放入新的序列埠设定值 */
	/*   
	BAUDRATE: 设定 bps 的速度. 你也可以用 cfsetispeed 及 cfsetospeed 来设定. 
	CRTSCTS : 输出资料的硬体流量控制 (只能在具完整线路的缆线下工作  参考 Serial-HOWTO 第七节) 
	CS8     : 8n1 (8 位元, 不做同位元检查,1 个终止位元) 
	CLOCAL  : 本地连线, 不具数据机控制功能 
	CREAD   : 致能接收字元 
	*/ 
	//newtio.c_cflag = Bdps | CS8 | CLOCAL | CREAD ;
	switch( Bdps )
	{
	case 2400:
		newtio.c_cflag = B2400 | CS8 | CLOCAL | CREAD ;
		break;
	case 4800:
		newtio.c_cflag = B4800| CS8 | CLOCAL | CREAD ;
		break;
	case 9600:
		newtio.c_cflag = B9600| CS8 | CLOCAL | CREAD ;
		break;
	case 115200:
		newtio.c_cflag = B115200| CS8 | CLOCAL | CREAD ;
		break;
	default:
		newtio.c_cflag = B9600| CS8 | CLOCAL | CREAD ;
		break;
	}
	/*
	IGNPAR  : 忽略经同位元检查後, 错误的位元组 
	ICRNL   : 比 CR 对应成 NL (否则当输入讯号有 CR 时不会终止输入) 
	在不然把装置设定成 raw 模式(没有其它的输入处理)
	*/

	newtio.c_iflag = IGNPAR;//IGNPAR | ICRNL;/*HH IGNPAR*/
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

	/*  
	现在清除数据机线并启动序列埠的设定 
	*/ 
	tcflush(fd_com, TCIFLUSH); 
	MIFMessage = ArgMsg;
	MIFHandl = ArgWindowsHandl;
//	//print_emrc("ArgWindowsHandl:%d ,ArgMsg:%d\n",ArgWindowsHandl,ArgMsg);
	tcsetattr(fd_com,TCSANOW,&newtio);
	
	Dal_imf_Set_fd_com(fd_com);//add by fuxl for pro 2010-08-09 设置DAL_IMF 的 串口设备号

	return 0;
}
/************************************************************************
*      Name:	串口读写数据
* Parameter:	SendCommand 写入串口的数据
*				SendCommand 数据长度
*	  Return:
*	 Example:
*	  Author:	MYM
*CreateDate:	2008/06/12 13:24
************************************************************************/
unsigned  char RecvData[64];
int InterFaceprintfenable = 1;
static int WriteData(unsigned char *SendCommand,int CommandLength)
{
	int ret =0,i;
	int ReadLength =0;	
	char ReadBuf[64];	
	int RecvDataLength = 0;
	if(InterFaceprintfenable>0)
	{	
		printf("write Data :" );
		for(i =0;i<CommandLength+3  ;i++)
		{
			printf(" %02x", SendCommand[i]);
		}
		printf("\n" );
	}
	////print_emrc("-->WriteData fd_com=%d, CommandLength=%d \n",fd_com, CommandLength);
	if(CommandLength+3 != write(fd_com,SendCommand,CommandLength+3))
	{
		ret =  MI_NOTAGERR;
	}
	else
	{
		int nLen=0,i;
		usleep(20000);
		
		for(i=0;i<10000;i++)
		{
			ioctl(fd_com,FIONREAD,&nLen);
			if(nLen>=3)
			{
				break;
			}		
		}
		if(i==10000) 
		{
			//print_cpucscrhy("Read Not Data \n" );
			
			return MI_NOTAGERR;
		}
		ReadLength = read(fd_com,ReadBuf,64);
		if(InterFaceprintfenable>0)
		{	
			printf("Read Data :" );
			for(i =0;i<ReadLength;i++)
			{
				printf(" %02x", ReadBuf[i]);
			}
			printf("\n" );
		}
		if(ReadLength>= 4 && USR_Start1 ==ReadBuf[0] && USR_Start2 ==ReadBuf[1])
		{

			RecvDataLength = ReadBuf[2];
			ret = ReadBuf[3];
			if(RecvDataLength>1)
			{
				memset(RecvData,0x00,64);
				memcpy(RecvData,&ReadBuf[4],RecvDataLength-1);
			}
		}
		else if(	ReadLength>= 4	
					&&  USR_Start1 ==ReadBuf[4] 
					&&  USR_Start2 ==ReadBuf[5]
					&&  MI_OK ==ReadBuf[7] )
		{
			ret = MI_OK;
		}
		else
		{
			ret = MI_NOTAGERR;
		}
	}
	if(InterFaceprintfenable>0)
	{
		//print_cpucscrhy(" ret = %d\n",ret );
	}
	else
	{
		InterFaceprintfenable =0;
	}
	//InterFaceprintfenable--;
	return ret;
}

/************************************************************************
       Name:	加载密钥
  Parameter:	ArgSector 扇区号
				ArgKeySet 保留
				ArgBufKeyA A密钥
				ArgBufKeyB B密钥
				
	  Return:   MI_OK 成功				
	 Example:
	  Author:	MYM
  CreateDate:	2008/06/12 13:48
************************************************************************/
 unsigned  char  KEY_LOAD[]	={USR_Start1,USR_Start2,KeyCommandLen,USR_LoadKeyE2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int MIFLoadKey(void *ArgMifRegPtr,unsigned char  ArgSector,unsigned char ArgKeySet ,unsigned char *ArgBufKeyA,unsigned char *ArgBufKeyB)
{
	/*InterFaceprintfenable = 2;*/
	KEY_LOAD[4]=KEYA;
	KEY_LOAD[5]=ArgSector;
	memcpy((char *)&KEY_LOAD[6],ArgBufKeyA,6);
	if(MI_OK!= WriteData(KEY_LOAD,KeyCommandLen) )
	{
		return MI_KEYERR;
	}
	KEY_LOAD[4]=KEYB;
	KEY_LOAD[5]=ArgSector;
	memcpy((char *)&KEY_LOAD[6],ArgBufKeyB,6);
	if(MI_OK!= WriteData(KEY_LOAD,KeyCommandLen) )
	{
		return MI_KEYERR;
	}
	return MI_OK;
}
unsigned int  RequestcardNum;
unsigned  char CommandRequest[]={USR_Start1,USR_Start2,CommandRequestLength,USR_Request,PICC_REQIDL,0X00};
int CardType = 0; //0 未知，4 M1卡， 8 Pro卡
int MIFGetCardType(void )
{
    return CardType;
}

static int _MIFRequest(unsigned int  *cardNum,unsigned char ArgMode)
{
	int ret = 0;
	CommandRequest[4] = ArgMode;
	
	ret = WriteData(CommandRequest,CommandRequestLength);
//	//print_emrc("WriteData:%d\n",ret);
	if(	MI_OK ==ret)
	{		
		return MIF_NoCard;
	}
	else if(4==ret)
	{
		
		memcpy((char *)cardNum,RecvData,4);
		////print_emrc("MIFEexistCard %02x,%02x,%02x,%02x,%u,%u\n",RecvData[0],RecvData[1],RecvData[2],RecvData[3],*cardNum,RequestcardNum);
		CardType = 4;
		return MIF_EexistCard;	
	}else if(8==ret)
	{

		memcpy((char *)cardNum,RecvData,4);
		////print_emrc("MIFEexistCard %02x,%02x,%02x,%02x,%u,%u\n",RecvData[0],RecvData[1],RecvData[2],RecvData[3],*cardNum,RequestcardNum);
		CardType = 8;
		return MIF_EexistCard;	
		 
	}
	else return -1;
}

/************************************************************************
        Name:	读卡请求
   Parameter:	ArgMode PICC_REQIDL 指令是连续性的读卡指令
						PICC_REQALL 指令是非连续性的读卡指令
	  Return:
	 Example:
	  Author:	MYM
  CreateDate:	2008/06/12 10:37
************************************************************************/
static int CardEexist = MIF_NoCard;

char DDL_strCardNo[11];
unsigned int  DDL_cardNum;
unsigned int MIFGetCardNo(char * sCardNo )
{
   strncpy(sCardNo,DDL_strCardNo,10);
   return DDL_cardNum;
}

int MIFRequest(void *ArgMifRegPtr,unsigned char ArgMode)
{	
	char chTemp[11];
	int ret = 	_MIFRequest(&RequestcardNum,ArgMode);
	memset(chTemp,0x00,sizeof(chTemp));
	printf("_MIFRequest %d,%d\n",ret,CardEexist);
	if(MIF_EexistCard==ret &&  CardEexist!=MIF_EexistCard)
	{
		//print_emrcCSC("MIF_EexistCard %d,%d\n",MIFHandl,MIFMessage);
//		//print_emrc("MIF_EexistCard %d,%d\n",MIFHandl,MIFMessage);
		CardEexist = MIF_EexistCard;

		sprintf(chTemp,"%010u",RequestcardNum);
		memset(DDL_strCardNo,' ',sizeof(DDL_strCardNo));
		strncpy(DDL_strCardNo,chTemp,10); 

		DDL_cardNum = RequestcardNum;
		printf("-->MIFRequest DDL_cardNum=%d \n",DDL_cardNum);
		if ( CardType == 4 )//M1卡
		{
			//LogCDev("MIF_NoCard Msg=1201 ,%d,%d\n",getHWND(),MIFMessage);//v1.0.184
			
			SendNotifyMessage(MIFHandl,MIFMessage,1201,RequestcardNum);
		}else if ( CardType == 8 )//Pro卡
		{
                        printf("-->SendNotifyMessage before 1203  MIFHandl=%d,MIFMessage=%d\n",MIFHandl,MIFMessage);
			I_DEV_CSC_DLL_ProIcCheck();//add by fuxl for pro 2010-08-09

			//LogCDev("MIF_NoCard Msg=1203 ,%d,%d\n",getHWND(),MIFMessage);//v1.0.227
			SendNotifyMessage(MIFHandl,MIFMessage,1203,RequestcardNum);
			printf("-->SendNotifyMessage after 1203 \n");
		}
		
	}
	else if(MIF_NoCard==ret &&  CardEexist!=MIF_NoCard)
	{
		CardEexist = MIF_NoCard;
		memset(DDL_strCardNo,0,10);
		DDL_cardNum = -1;
//		//print_emrc("MIF_NoCard %d,%d\n",getHWND(),MIFMessage);
		//print_emrcCSC("MIF_NoCard %d,%d\n",getHWND(),MIFMessage);
		if ( CardType == 4 )//M1卡
		{
			//LogCDev("MIF_NoCard Msg=1202 ,%d,%d\n",getHWND(),MIFMessage);//v1.0.184
			SendNotifyMessage(MIFHandl,MIFMessage,1202,RequestcardNum);	
		}else if ( CardType == 8 )//Pro卡
		{
			I_DEV_CSC_DLL_ProIcCheck();//add by fuxl for pro 2010-08-09                      
			//LogCDev("MIF_NoCard Msg=1204 ,%d,%d\n",getHWND(),MIFMessage);//v1.0.227
			SendNotifyMessage(MIFHandl,MIFMessage,1204,RequestcardNum);	
		}

		CardType = 0;
	}
	return ret;
}

/************************************************************************
       Name:	选择需要读写的卡
  Parameter:	ArgCardSN 卡号
				ArgSector 扇区
				ArgKey 保留
				ArgKeySet baoliu
				
	  Return:	MI_OK 成功	
	 Example:
	  Author:	MYM
  CreateDate:	2008/06/12 13:52
************************************************************************/
int SelectSector =1;
unsigned  char CommandSelect[] =	{	USR_Start1,USR_Start2,CommandSelecLength,USR_Select,0xff,0xff,0xff,0xff,0x00};
int MIFSelectEx(void *ArgMifRegPtr,unsigned int ArgCardSN,unsigned char ArgSector,unsigned char ArgKey,unsigned char ArgKeySet)
{
	int Temp =0,ret =MI_NOTAGERR;	
	SelectSector = ArgSector;
	/*InterFaceprintfenable = 2;*/
	
	if(MIF_EexistCard ==_MIFRequest(&Temp,PICC_REQIDL) && ArgCardSN == Temp)
	{		
//		//print_emrc("Temp %u ,ArgCardSN %u ,RequestcardNum %u \n",	Temp,ArgCardSN,RequestcardNum);
//		//print_emrc("=================%u\n",ArgCardSN);
		memcpy(&CommandSelect[4],(char *)&ArgCardSN,4);

		ret = WriteData(CommandSelect,CommandSelecLength);
	}
	return ret;
}
/************************************************************************
       Name:	读卡中的内容
  Parameter:	ArgBlock 块号
				ArgBuffer 读卡的数据
	  Return:
	 Example:
	  Author:	MYM
  CreateDate:	2008/06/12 14:27
************************************************************************/
unsigned  char CommandRead[] = {	USR_Start1,USR_Start2,CommandReadLength,USR_PiccRead,
									0xff,0xff,PICC_AUTHENT1B,0x00
								};
int MIFReadCRC(void *ArgMifRegPtr,unsigned char ArgBlock,unsigned char *ArgBuffer)
{
	int ret ;
	CommandRead[4] = SelectSector;
	CommandRead[5] = ArgBlock;
	//ret = MIFSelectEx(NULL,RequestcardNum,SelectSector,0,0);
	ret = MI_OK;
	if(MI_OK== ret)
	{
		
		
		ret = WriteData(CommandRead,CommandReadLength);
		////print_emrc("MIFUserRead section :%d  nBlock:%d,ret=%d  \n", SelectSector,CommandRead[5],ret);

	}
	if(MI_OK==ret)
	{
		sprintf(ArgBuffer,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
			RecvData[0],RecvData[1],RecvData[2],RecvData[3],RecvData[4],RecvData[5],
			RecvData[6],RecvData[7],RecvData[8],RecvData[9],RecvData[10],RecvData[11],
			RecvData[12],RecvData[13],RecvData[14],RecvData[15]);
//		//print_emrc("MIFUserRead val = %s\n",ArgBuffer);
		//print_emrcCSC("MIFUserRead val = %s\n",ArgBuffer);
	}
	return ret;
}
/************************************************************************
       Name:	写入数据
  Parameter:	ArgBlock 块号
				ArgBuffer 写入卡的数据
	  Return:	MI_OK 成功	
	 Example:
	  Author:	MYM
  CreateDate:	2008/06/12 14:46
************************************************************************/
unsigned  char CommandWrite[] = {USR_Start1,USR_Start2,CommandWriteLength,USR_PiccWrite,0xff,0xff,PICC_AUTHENT1B,
									0xff,0xff,0xff,0xff,
									0xff,0xff,0xff,0xff,
									0xff,0xff,0xff,0xff,
									0xff,0xff,0xff,0xff, 0x00};
int MIFWriteCRC(void *ArgMifRegPtr,int ArgBlock,unsigned char *ArgBuffer)//读卡中文件
{

	char Temp[3],TempBlock[16];
	int i,j;
	unsigned char crc;		
	CommandWrite[4] = SelectSector;
	CommandWrite[5] = ArgBlock;
	Temp[2]=0;
	j=7;
	/*InterFaceprintfenable = 3;*/
	////print_emrc("MIFUserWrite Block =%s \n" ,ArgBlock);
	for(i=0;i<30;i++)
	{
		//把待发的数据分割为两个字符的串然后转化为两个16进制的串，存入write_temp数组
		Temp[0]=ArgBuffer[i++];
		Temp[1]=ArgBuffer[i];
		CommandWrite[j++]=strtoul(Temp,NULL,16);

	}
	memcpy(TempBlock,&CommandWrite[7],15);
	crc=getcrc8(TempBlock,15);
	CommandWrite[22]=crc;
	////print_emrc("MIFUserWrite \n" );
	/*if(	MI_OK ==MIFSelectEx(NULL,RequestcardNum,SelectSector,0,0) && 
		MI_OK == WriteData(CommandWrite,CommandWriteLength))*/
	if(	MI_OK == WriteData(CommandWrite,CommandWriteLength))
	{
		return MI_OK;
	}
	else 
	{
		return MI_NOTAGERR;
	}
}
/************************************************************************
       Name:	复位
  Parameter:	ResetTime 复位时间 （不求知是啥意思）
				
	  Return:
	 Example:
	  Author:	MYM
  CreateDate:	2008/06/12 15:08
************************************************************************/
unsigned  char Command_Reset[] = {USR_Start1,USR_Start2,0x02,USR_PcdRfReset,0x00,0x00};
int MIFReset(void *ArgMifRegPtr,unsigned char ResetTime )
{
	Command_Reset[4]=ResetTime;
	return WriteData(Command_Reset,0x02);
}


/************************************************************************
	     Name:	挂机
	Parameter:	

	   Return:	MI_OK 成功	
	  Example:
	   Author:	MYM
	CreateDate:	2008/06/12 15:08
************************************************************************/
unsigned  char Command_Halt[] = {USR_Start1,USR_Start2,0x01,USR_PiccHalt,0x00};
int MIFHalt(void *ArgMifRegPtr )
{
	return WriteData(Command_Halt,0x01);
}

const unsigned char Command_BuzzSwitch[]={USR_Start1,USR_Start2,0x03,USR_BuzzSwitch,0x00,0x30};  
void CloseBuzzSwitch(void)
{
	write(fd_com,Command_BuzzSwitch,6);
}

                                           
  

///////////////////////////////////////////////////
// 0 成功; -1 SELECTSAM失败, -2 RESETSAM失败
///////////////////////////////////////////////////
char * __SelectSAM;
int  MIFPRO_ResetSAM(int iSAM)                                                 
{
	char selectSAM[15];
	if ( iSAM >= 10 || iSAM < 1 || iSAM == NULL ) iSAM  = 1;

	memset(selectSAM,0x00,sizeof(selectSAM));
	sprintf(selectSAM,"55AA02800%d",iSAM);

	__SelectSAM =  SendCommand(selectSAM);	 

	if (StartsWith(__SelectSAM,"55AA0100")!=T)
	{
		return -1;
	}

	//SAM复位 
	memset(selectSAM,0x00,sizeof(selectSAM));
	sprintf(selectSAM,"55aa0182");
	__SelectSAM = SendCommand(selectSAM );

	printf("-->SAM复位   rsp=%s\n", __SelectSAM );

	if (StartsWith(__SelectSAM,"55AA1100")==T)
	{
		return 0;
	}
	return -2;                                                      

}   
/////////////////////////////////////////////////////////////////////////////////////////////////////
// PRO卡通用指令函数
// command	指令帧（以'\0'结尾的16进制字符串或常量字符串），
// sw12	响应状态码SW1和SW2的字符串显示，如"9000" （以'\0'结尾的16进制字符串或常量字符串）等； 
// response	响应帧（以'\0'结尾的16进制字符串或常量字符串，含SW1和SW2）
// 0 成功; -1  失败, -2 RESETSAM失败
////////////////////////////////////////////////////////////////////////////////////////////////////
char * __ProCmndRsp;
int MIFPRO_Command( char *command,char *response,char *sw12)
{
   __ProCmndRsp = ( char *)ExcCPUCmd(command );
   printf("--> MIFPRO_Command __ProCmndRsp=%s \n",__ProCmndRsp);
   if (StartsWith(__ProCmndRsp,"55AA")==T)
  {
      //printf("--> StartsWith 55AA \n");
      if (StartsWith(__ProCmndRsp + 6,"00")==T)
      {
      	   //printf("--> StartsWith 00 \n");
      	   if ( strlen(__ProCmndRsp) > 12   ) // 55AAXX000A00------
      	   {
      	   	//printf("--> strlen >12 \n");
      	   	sprintf(response,"%s",__ProCmndRsp + 12 ) ;
      	   	strncpy(sw12, __ProCmndRsp+ strlen(__ProCmndRsp) - 8 , 4);
      	   }else
      	   {
      	   	strncpy(sw12, __ProCmndRsp+ strlen(__ProCmndRsp) - 8 , 4);
      	   }
	   return 0;
       }
  }
  
  return -1;	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// PRO卡选卡函数
//cardno	输入参数：4字节的物理卡号,即长度为8的16进制字符串
// 0 成功; -1  失败
///////////////////////////////////////////////////////////////////////////////////////////////////

int MIFPRO_SelectCard( char *cardno)
{
    if( ReadyCard(GetHexCardNumber()) == T ) 
    {
    	return 0;
    }
    
    return -1;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// PRO卡指文件信息函数
// fileID	文件的ID（以'\0'结尾的16进制字符串或常量字符串），
// sw12	响应状态码SW1和SW2的字符串显示，如"9000" （以'\0'结尾的16进制字符串或常量字符串）等； 
// response	响应帧（以'\0'结尾的16进制字符串或常量字符串，含SW1和SW2）
// 0 成功; -1  失败
////////////////////////////////////////////////////////////////////////////////////////////////////
char * __ProCmndRsp;
int MIFPRO_GetFileInfo( char *fileid,char *response,char *sw12)
{
      int ret;
      char command[50];
      memset(command,0x00,sizeof(command));
      
   	if( strncmp(fileid,"0015",4)==0 )
	{ 
		sprintf(command,"00B095002B"); 
 
	}else if( strncmp(fileid,"0016",4)==0 )
	{
		sprintf(command,"00B0960037");  
	}else if( strncmp(fileid,"0019",4)==0 )
	{
		sprintf(command,"00B201CC2B");  
	} 
	else
	{

		memset(response,0x00,10);
		return -1;
	}
	
	return MIFPRO_Command(  command, response, sw12);  
  	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// PRO SAM卡通用指令函数
// command	指令帧（以'\0'结尾的16进制字符串或常量字符串），
// sw12	响应状态码SW1和SW2的字符串显示，如"9000" （以'\0'结尾的16进制字符串或常量字符串）等； 
// response	响应帧（以'\0'结尾的16进制字符串或常量字符串，含SW1和SW2）
// 0 成功; -1  失败, -2 RESETSAM失败
////////////////////////////////////////////////////////////////////////////////////////////////////
char * __ProCmndSAMRsp;
int MIFPRO_CommandSAM( char *command,char *response,char *sw12)
{
   __ProCmndSAMRsp = ( char *)ExcSAMCmd(command );
   printf("--> MIFPRO_CommandSAM __ProCmndSAMRsp=%s \n",__ProCmndSAMRsp);
   if (StartsWith(__ProCmndSAMRsp,"55AA")==T)
  {
      //printf("--> StartsWith 55AA \n");
      if (StartsWith(__ProCmndSAMRsp + 6,"00")==T)
      {
      	   //printf("--> StartsWith 00 \n");
      	   if ( strlen(__ProCmndSAMRsp) > 8   ) // 55AAXX000A00------
      	   {
      	   	//printf("--> strlen >8 \n");
      	   	sprintf(response,"%s",__ProCmndSAMRsp + 8 ) ;
      	   	strncpy(sw12, __ProCmndSAMRsp+ strlen(__ProCmndSAMRsp) - 4 , 4);
      	   }else
      	   {
      	   	strncpy(sw12, __ProCmndSAMRsp+ strlen(__ProCmndSAMRsp) - 4 , 4);
      	   }
	   return 0;
       }
  }
  
  return -1;	
}
