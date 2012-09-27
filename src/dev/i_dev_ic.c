/************************************************************************/
/* ����̬��  fuxl 2008.5.30                                             */
/************************************************************************/
#include "LocalIncludeFile.h"
#include "imf.h"
#include "mac.h"
/************************************************************************/
/* ����ʼ�� liujl 2008.6.10                                             */
/************************************************************************/
int CardExist = MIF_NoCard;//���Ƿ������������
int GetCardExist(void )
{
	return CardExist;
}
unsigned int  RequestcardNum;//�����Ŀ�����
int MIFHandl;//��Ϣ��������


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
	//print_emrc("-->���̴߳��� \n");
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
/* ������߳�                                                           */
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
			echoic("������HEX:%s DEC:%010u",hexCardNumber,RequestcardNum);
		}
		else if (0==strlen(HexCard) &&  CardExist!=MIF_NoCard)
		{
			CardExist=MIF_NoCard;
			hexCardNumber[0] = 0x00;
			RequestcardNum=0;
			memset(CardData15File,0x00,1024);
			memset(CardData16File,0x00,1024);
			PostMessage(UI_Get_From_Handl(),MSG_CRADENENT,CSC_CARDEXIT,RequestcardNum);
			echoic("���뿪HEX:%s DEC:%010u",HexCard,RequestcardNum);
		}
		else
		{
			//echoic("״̬δ�ı�");
		}


		usleep(3000);//v1.0.0.183
	}
	goto initMIF;
}
/************************************************************************/
/* �ر����� liujl 2008.6.10                                             */
/************************************************************************/
void I_DEV_IC_Close(void)
{
	return ;
}


/************************************************************************/
/* ��Block liujl 2008.6.10                                              */
/************************************************************************/
int I_DEV_IC_ReadByBlock(int block,int keyType,char* data)
{
	int iRet;
	iRet=MIFReadCRC(NULL,block,(unsigned char *)data);
	return iRet;
}

/************************************************************************/
/* дBlock liujl 2008.6.10                                              */
/************************************************************************/
int I_DEV_IC_WriteByBlock(int block,int keyType,char* data)
{
	int iRet;
	iRet=MIFWriteCRC(NULL,block,(BYTE *)data);
	return iRet;
}

/************************************************************************/
/* ���� liujl 2008.6.10                                                 */
/************************************************************************/
int I_DEV_IC_OpenCard(void)
{
	return 0;
}

/************************************************************************/
/* �� liujl 2008.6.10                                                   */
/************************************************************************/
int I_DEV_IC_CloseCard(void)
{
	return 0;
}





#define USR_Start1          0x55        //��ʼλ��һλ
#define USR_Start2          0xAA        //��ʼλ�ڶ�λ
#define USR_Request         0x01 /*Ѱ�� ����ײ��ÿ���*/
#define USR_Select          0x02 /*ѡ��*/
#define USR_PiccRead        0x03 /*����*/
#define USR_PiccWrite       0x04 /*д��*/
#define USR_PiccHalt        0x05 /*����*/
#define USR_PcdRfReset      0x06 /*��λM1 �� + ʱ��(ms) =2*/
#define USR_LoadKeyE2       0x10 /*������Կ ��E2 �洢�� �ɵ���洢*/
#define USR_PiccAuthE2      0x11 /*��E2 ��֤��Կ*/
#define USR_BuzzSwitch      0x30 /*����������1=on 0=off*/


#define  KeyCommandLen 0x9

#define Secteur0 0x00 //��һ����
#define Secteur1 0x01 //��һ����
#define Secteur2 0x02 //��һ����
#define Secteur3 0x03 //��һ����
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

int MIFWriteCRC(void *ArgMifRegPtr,int ArgBlock,unsigned char *ArgBuffer)//�������ļ�
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

