/************************************************************************/
/* 卡动态库  fuxl 2008.5.30                                             */
/************************************************************************/
#include "LocalIncludeFile.h"
#include "imf.h"
#include "mac.h"
/************************************************************************/
/* 卡初始化 liujl 2008.6.10                                             */
/************************************************************************/
int CardExist = MIF_NoCard;//卡是否存在于天线上
int GetCardExist(void )
{
	return CardExist;
}
unsigned int  RequestcardNum;//整数的卡号码
int MIFHandl;//消息接受体句柄


int I_DEV_IC_Init(HWND pWnd)
{

	int iRet = -1;;
	MIFHandl = pWnd;
	if(MI_OK ==COM_Open(SERIAL_CSC_ID))
	{
		I_DEV_IC_CreateThread();
		iRet= 0;
	}
	return iRet;
}

static pthread_t cscThread;
int I_DEV_IC_CreateThread(void)
{
	int ret;
	//print_emrc("-->卡线程创建 \n");
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&cscThread, &new_attr, (void *)CSC_DLL_IcCheck, NULL);
	pthread_attr_destroy(&new_attr);
	return ret;
}
char hexCardNumber[9];
char * GetHexCardNumber(void)
{
	return hexCardNumber ;
}
/************************************************************************/
/* 卡检查线程                                                           */
/************************************************************************/
char CardData15File[1024];
char *Get15File(void)
{
	return CardData15File;
}
char CardData16File[1024];
char *Get16File(void)
{
	return CardData16File;
}
UINT CSC_DLL_IcCheck(void)
{
	char * HexCard;
	initMIF:

	while (1)
	{

		HexCard = RequestPro();
		if (0!=strlen(HexCard) && CardExist!=MIF_ExistCard  )
		{
			CardExist=MIF_ExistCard;
			memset(hexCardNumber,0x00,9);
			memcpy(hexCardNumber,HexCard,8);
			RequestcardNum= Hex2UINT(HexCard);
			ReadCardInfo("0015",CardData15File);
			ReadCardInfo("0016",CardData16File);
			PostMessage(UI_Get_From_Handl(),MSG_CRADENENT,CSC_CARDENTER,RequestcardNum);
			echoic("卡进入HEX:%s DEC:%010u",hexCardNumber,RequestcardNum);
		}
		else if (0==strlen(HexCard) &&  CardExist!=MIF_NoCard)
		{
			CardExist=MIF_NoCard;
			hexCardNumber[0] = 0x00;
			RequestcardNum=0;
			memset(CardData15File,0x00,1024);
			memset(CardData16File,0x00,1024);
			PostMessage(UI_Get_From_Handl(),MSG_CRADENENT,CSC_CARDEXIT,RequestcardNum);
			echoic("卡离开HEX:%s DEC:%010u",HexCard,RequestcardNum);
		}
		else
		{
			//echoic("状态未改变");
		}


		usleep(3000);//v1.0.0.183
	}
	goto initMIF;
}
/************************************************************************/
/* 关闭天线 liujl 2008.6.10                                             */
/************************************************************************/
void I_DEV_IC_Close(void)
{
	return ;
}


/************************************************************************/
/* 读Block liujl 2008.6.10                                              */
/************************************************************************/
int I_DEV_IC_ReadByBlock(int block,int keyType,char* data)
{
	int iRet;
	iRet=MIFReadCRC(NULL,block,(unsigned char *)data);
	return iRet;
}

/************************************************************************/
/* 写Block liujl 2008.6.10                                              */
/************************************************************************/
int I_DEV_IC_WriteByBlock(int block,int keyType,char* data)
{
	int iRet;
	iRet=MIFWriteCRC(NULL,block,(BYTE *)data);
	return iRet;
}

/************************************************************************/
/* 重置 liujl 2008.6.10                                                 */
/************************************************************************/
int I_DEV_IC_OpenCard(void)
{
	return 0;
}

/************************************************************************/
/* 置 liujl 2008.6.10                                                   */
/************************************************************************/
int I_DEV_IC_CloseCard(void)
{
	return 0;
}





#define USR_Start1          0x55        //开始位第一位
#define USR_Start2          0xAA        //开始位第二位
#define USR_Request         0x01 /*寻卡 防碰撞获得卡号*/
#define USR_Select          0x02 /*选择卡*/
#define USR_PiccRead        0x03 /*读卡*/
#define USR_PiccWrite       0x04 /*写卡*/
#define USR_PiccHalt        0x05 /*挂起*/
#define USR_PcdRfReset      0x06 /*复位M1 卡 + 时间(ms) =2*/
#define USR_LoadKeyE2       0x10 /*下载密钥 到E2 存储器 可掉电存储*/
#define USR_PiccAuthE2      0x11 /*从E2 验证密钥*/
#define USR_BuzzSwitch      0x30 /*蜂鸣器开关1=on 0=off*/


#define  KeyCommandLen 0x9

#define Secteur0 0x00 //第一扇区
#define Secteur1 0x01 //第一扇区
#define Secteur2 0x02 //第一扇区
#define Secteur3 0x03 //第一扇区
#define PICC_AUTHENT1A 0x60
#define PICC_AUTHENT1B 0x61
#define KEYA 0x60
#define KEYB 0x61

#define CommandRequestLength    0x02
#define CommandReadLength       0x04
#define CommandSelecLength      0x05
#define CommandWriteLength      0x14
#define CommandBuzzSwitchLength         0x14
#define     CRC8        0x80




int fd_com;

int MIFSelectEx(void *ArgMifRegPtr,unsigned int ArgCardSN,unsigned char ArgSector,unsigned char ArgKey,unsigned char ArgKeySet)
{

    return 0;
}
int MIFReadCRC(void *ArgMifRegPtr,unsigned char ArgBlock,unsigned char *ArgBuffer)
{

    return 0;
}

int MIFWriteCRC(void *ArgMifRegPtr,int ArgBlock,unsigned char *ArgBuffer)//读卡中文件
{

          return 0;
}
int MIFReset(void *ArgMifRegPtr,unsigned char ResetTime )
{
     return 0;
}


int MIFHalt(void *ArgMifRegPtr )
{
   return 0;
}

const unsigned char Command_BuzzSwitch[]={USR_Start1,USR_Start2,0x03,USR_BuzzSwitch,0x00,0x30};
void CloseBuzzSwitch(void)
{
return;
}

