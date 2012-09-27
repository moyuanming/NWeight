     /************************************************************************/
/* ����̬��  fuxl 2008.5.30                                             */
/************************************************************************/
#include "LocalIncludeFile.h" 

/************************************************************************/
/* ����ʼ�� liujl 2008.6.10                                             */
/************************************************************************/
static int CardExist = MIF_NoCard;//���Ƿ������������
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
	//if(MI_OK ==COM_Open(SERIAL_CSC_ID))
	//{
	//	I_DEV_IC_CreateThread();
	//	iRet= 0;
	//}
	return iRet;
}

static pthread_t cscThread;
int I_DEV_IC_CreateThread(void)
{
	int ret;
	////print_emrc("-->���̴߳��� \n");
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);	
	ret = pthread_create(&cscThread, &new_attr, (void *)I_DEV_CSC_DLL_IcCheck, NULL);
	pthread_attr_destroy(&new_attr);		
	return ret;
}
char hexCardNumber[9];
char * GetHexCardNumber(void)
{
	return hexCardNumber;
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

char CardData19File[1024];
char *Get19File(void)
{
	return CardData19File;
}

char CardData08File[1024];
char *Get08File(void)
{
	return CardData08File;
}

static char DataTimeStr[20];

void testTrans( void ) //���Ը�������
{
	 
	int ret = -1, transMoney =0 ;
	char rsp[1024],szRandom[1024],command[1024],resp[1024],TerminalNo[20],cpuID[20],DateTime[15];

	char m_szproserial[17]  ,m_sn[17] ,szSn[1024],szDesData[100],icRand[100],transNo[10],calcID[3],keyVerID[3];

	char TAC[10],MAC2[20],MAC1[20],offlineTransNo[10];

	DWORD  dwcardno;

	time_t Currenttime = time(NULL);    

	char* temp;
	struct tm *rtc_time;      

	rtc_time = localtime(&Currenttime);        

	sprintf(DataTimeStr, "%04d%02d%02d%02d%02d%02d%c",rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec,'\0');  


	printf("----��Ӯ��д�� LINUX ���ֽ�֧���������� ����---------\n"); 

	 

	//ret = Open_Card(iComno, &dwcardno);
	//printf("-->Open_Card ret =%d \n",ret );
     

	memset(rsp,0,sizeof(rsp));  
	ret = USR_SelectSAM( 1 );
	printf("-->SAM��λ��ѡ��SAM%d ret=%d, rsp=%s \n",1,ret, rsp ); 
	if(ret!= T )
	{
		printf("\n Error on USR_SelectSAM!\n");
		return;
	}
 
	//SAM��λ 
	sprintf(command,"55aa0182");
	sprintf(rsp,"%s",(char *)SendCommand(command ));
 
	printf("-->SAM��λ ret=%d,  rsp=%s\n",ret ,rsp );

	//��0015�ļ���ȡ���� ��������ʶ��(4�ֽڷ����������*2)

	memset(rsp,0,sizeof(rsp)); 
	ReadCardInfo("0015",CardData15File);
    sprintf(rsp,"%s",CardData15File);
	//ret = CPU_Get0015(m_szproserial,rsp,m_sn); 
	sprintf(m_sn,"%.16s",rsp);
	printf("-->��0015�ļ� ret=%d,m_sn=%s, rsp=%s \n",ret,m_sn, rsp );  

	//ѡ��Ŀ¼1001 
	sprintf(command,"00A40000021001");
	sprintf(rsp,"%s",(char *)ExcCPUCmd(command ));

	memset(cpuID,0,sizeof(cpuID));
	sprintf(cpuID,"%.16s",rsp + 68 + 12 );
	printf("-->ѡ��Ŀ¼1001 ret=%d,cpuID =%s, rsp=%s\n",ret, cpuID,rsp );

	 
	//��0019�ļ�
	//00b0�Ƕ��������ļ�.
	//0019�ļ��Ǳ䳤��¼�ļ���������Ҫʹ��00b2����.
	//00B2  01  CC2B
	//���01���Ǽ�¼��.

	memset(rsp,0,sizeof(rsp));
	sprintf(command,"00B201CC2B");
	sprintf(rsp,"%s",(char *) ExcCPUCmd(command ));

	printf("-->��0019�ļ� ��¼1 ret=%d, rsp=%s\n",ret, rsp );


	//memset(rsp,0,sizeof(rsp));
	//ret=PRO_GetBallance(iComno,2,rsp,sizeof(rsp),resp);

	memset(rsp,0,sizeof(rsp));
	sprintf(command,"805C000204");
	sprintf(rsp,"%s", (char *)ExcCPUCmd(command ));


	printf("-->��ȡ��� ret=%d, rsp=%s \n",ret, rsp ); 



	/*memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"0084000004\0");
	ret = SAM_Command(iComno,command,rsp);
	sprintf(TerminalNo,"%s",rsp);
	printf("-->��ȡSAM������� ret=%d, rsp=%s \n",ret, rsp );  
	*/
    
	memset(rsp,0,sizeof(rsp)); 
	memset(TerminalNo,0,sizeof(TerminalNo));
	memset(command,0x00,sizeof(command)); 
	sprintf(command,"00B0960006");
	command[10] = 0x00;
 
	sprintf(rsp,"%s", (char *)ExcSAMCmd(command ));
 
	sprintf(TerminalNo,"%.18s",rsp + 8);
	printf("-->��ȡSAM���ն˺� ret=%d, TerminalNo=%s,rsp=%s \n",ret,TerminalNo, rsp ); 

	transMoney = 1 ; //���ѽ��

	if( 0 == 0 )
	{
		memset(rsp,0x00,sizeof(rsp));
		memset(icRand,0x00,sizeof(icRand));
		memset(transNo,0x00,sizeof(transNo));
		memset(keyVerID,0x00,sizeof(keyVerID));
		memset(calcID,0x00,sizeof(calcID));
		sprintf(command,"805003020B01%.8x%.12s",transMoney ,TerminalNo);
		//ret = PRO_Command(iComno,command,rsp);
		ret = 0;
		sprintf(rsp,"%s", (char *)ExcCPUCmd(command ) + 12 );


		if(ret == 0 )
		{		
			sprintf(transNo, "%.4s",rsp+8);  
			sprintf(icRand, "%.8s",rsp+22); 
			sprintf(keyVerID, "%.2s",rsp+18);
			sprintf(calcID, "%.2s",rsp+20); 
		}
		printf("-->���Ͻ��׳�ʼ�� ���� ��ȡ����� ret=%d, rsp=%s ,icRand=%s,transNo=%s,keyVerID=%s,calcID=%s\n",ret, rsp ,icRand,transNo,keyVerID,calcID);
	}

	//���ѳ�ʼ���ɹ���->д0019->����MAC1->����->У��MAC2

	//д0019�ļ�
	memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"80DCAAC82BAA2900%.80s","000500467B4ABDC4BA010300000000000000000000100003C9F24332333034380000000000000000");
	//ret = PRO_Command(iComno,command,rsp); 
	sprintf(rsp,"%s", (char *)ExcCPUCmd(command ));
	printf("-->д0019�ļ� ret=%d, rsp=%s \n",ret, rsp );  

	//ѡ��SAM�� df01Ŀ¼.
	memset(rsp,0,sizeof(rsp));  
	sprintf(command,"00a4000002df01"); 
	sprintf(rsp,"%s", (char *)ExcSAMCmd(command ));
	printf("-->ѡ��SAM�� df01Ŀ¼ command=%s,ret=%d, rsp=%s \n",command,ret, rsp ); 
	if(ret!=0)
	{
		printf("\n Error on CPU_reset!\n");
	}

	//����MAC1
	memset(rsp,0,sizeof(rsp)); 
	memset(DateTime,0,sizeof(DateTime)); 
	sprintf(DateTime, "%.14s",DataTimeStr );
	//���������� 8�ֽ�Ӧ�ÿ���+(4�ֽڷ����������*2)
	sprintf(command,"8070000024%.8s%.4s%.8x09%.14s%.2s%.2s%.16s%.8s%.8s",icRand,transNo,transMoney ,DateTime,keyVerID,calcID,cpuID,m_sn,m_sn);
	printf("-->����MAC1 command=%s \n",command ); 
	 
	sprintf(rsp,"%s", (char *) ExcSAMCmd(command ) + 8);
	memset(MAC1,0,sizeof(MAC1)); 
	memset(offlineTransNo,0,sizeof(offlineTransNo)); 
	sprintf(offlineTransNo, "%.8s",rsp   );
	sprintf(MAC1, "%.8s",rsp + 8 ); 
	printf("-->����MAC1 ret=%d,offlineTransNo=%s,MAC1 =%s, rsp=%s \n",ret,offlineTransNo,MAC1, rsp );  



	//����
	memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"805401000F%.8s%.14s%.8s",offlineTransNo,DateTime, MAC1);
	sprintf(rsp,"%s",(char *) ExcCPUCmd(command )  );
	printf("-->���� command=%s \n",command );
	memset(TAC,0,sizeof(TAC)); 
	memset(MAC2,0,sizeof(MAC2));  
	sprintf(TAC, "%.8s",rsp +12  );
	sprintf(MAC2, "%.8s",rsp + 8  + 12 ); 
	printf("-->���� ret=%d, TAC=%s,MAC2=%s ,rsp=%s \n",ret,TAC,MAC2, rsp );  

	//У��MAC2
	memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"8072000004%.8s",MAC2);
	sprintf(rsp,"%s",(char *) ExcSAMCmd(command ));
	printf("-->У��MAC2 command=%s \n",command ); 
	printf("-->У��MAC2 ret=%d,   rsp=%s \n",ret,  rsp );  

	memset(rsp,0,sizeof(rsp));
	sprintf(command,"805C000204");
	sprintf(rsp,"%s", (char *)ExcCPUCmd(command ));


	printf("-->��ȡ��� ret=%d, rsp=%s \n",ret, rsp ); 


}


UINT I_DEV_CSC_DLL_IcCheck(void)
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
			ReadCardInfo("0019",CardData19File);
			//ReadCardInfo("0008",CardData08File);
			//PostMessage(getHWND(),MSG_CRADENENT,CSC_CARDENTER,RequestcardNum);
			echoic("CardData15File:%s  ",CardData15File );
			echoic("CardData16File:%s  ",CardData16File );
			echoic("CardData19File:%s  ",CardData19File );
			//echoic("CardData08File:%s  ",CardData08File );
			echoic("������HEX:%s DEC:%010u",hexCardNumber,RequestcardNum);

		}
		else if (0==strlen(HexCard) &&  CardExist!=MIF_NoCard)
		{
			CardExist=MIF_NoCard;
			hexCardNumber[0] = 0x00;
			RequestcardNum=0;
			memset(CardData15File,0x00,1024);
			memset(CardData16File,0x00,1024);
			//PostMessage(getHWND(),MSG_CRADENENT,CSC_CARDEXIT,RequestcardNum);  
			echoic("���뿪HEX:%s DEC:%010u",HexCard,RequestcardNum);
		}
		else
		{
			//echoic("״̬δ�ı�");
		}
	
		sleep(1);
		usleep(3000);//v1.0.0.183
	}
	goto initMIF;
}

UINT I_DEV_CSC_DLL_ProIcCheck(void)
{
	char * HexCard;

 	HexCard = RequestPro();
		if (0!=strlen(HexCard) && CardExist!=MIF_ExistCard  )
		{
			CardExist=MIF_ExistCard;
			memset(hexCardNumber,0x00,9);
			memcpy(hexCardNumber,HexCard,8);
			RequestcardNum= Hex2UINT(HexCard);	
			//testTrans();
			//ReadCardInfo("0015",CardData15File);
			//ReadCardInfo("0016",CardData16File);
			//ReadCardInfo("0019",CardData19File);
			//ReadCardInfo("0008",CardData08File);
			//PostMessage(getHWND(),MSG_CRADENENT,CSC_CARDENTER,RequestcardNum);
			//echoic("CardData15File:%s  ",CardData15File );
			//echoic("CardData16File:%s  ",CardData16File );
			//echoic("CardData19File:%s  ",CardData19File );
			//echoic("CardData08File:%s  ",CardData08File );
			echoic("������HEX:%s DEC:%010u",hexCardNumber,RequestcardNum);

		}
		else if (0==strlen(HexCard) &&  CardExist!=MIF_NoCard)
		{
			CardExist=MIF_NoCard;
			hexCardNumber[0] = 0x00;
			RequestcardNum=0;
			memset(CardData15File,0x00,1024);
			memset(CardData16File,0x00,1024);
			memset(CardData19File,0x00,1024);
			//PostMessage(getHWND(),MSG_CRADENENT,CSC_CARDEXIT,RequestcardNum);  
			echoic("���뿪HEX:%s DEC:%010u",HexCard,RequestcardNum);
		}
		else
		{
			//echoic("״̬δ�ı�");
		}
	ResetPro();
 
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
 
 
                                                                                                                                           
                                                                                                                                           
                                                                                                                                           
//#define USR_Start1          0x55        //��ʼλ��һλ                                                                                     
//#define USR_Start2          0xAA        //��ʼλ�ڶ�λ                                                                                     
//#define USR_Request         0x01 /*Ѱ�� ����ײ��ÿ���*/                                                                                   
//#define USR_Select          0x02 /*ѡ��*/                                                                                                
//#define USR_PiccRead        0x03 /*����*/                                                                                                  
//#define USR_PiccWrite       0x04 /*д��*/                                                                                                  
//#define USR_PiccHalt        0x05 /*����*/                                                                                                  
//#define USR_PcdRfReset      0x06 /*��λM1 �� + ʱ��(ms) =2*/                                                                               
//#define USR_LoadKeyE2       0x10 /*������Կ ��E2 �洢�� �ɵ���洢*/                                                                       
//#define USR_PiccAuthE2      0x11 /*��E2 ��֤��Կ*/                                                                                         
//#define USR_BuzzSwitch      0x30 /*����������1=on 0=off*/                                                                                  
//                                                                                                                                           
//                                                                                                                                           
//#define  KeyCommandLen 0x9                                                                                                                 
//                                                                                                                                           
//#define Secteur0 0x00 //��һ����                                                                                                           
//#define Secteur1 0x01 //��һ����                                                                                                           
//#define Secteur2 0x02 //��һ����                                                                                                           
//#define Secteur3 0x03 //��һ����                                                                                                           
//#define PICC_AUTHENT1A 0x60                                                                                                                
//#define PICC_AUTHENT1B 0x61                                                                                                                
//#define KEYA 0x60                                                                                                                          
//#define KEYB 0x61                                                                                                                          
//                                                                                                                                           
//#define CommandRequestLength    0x02                                                                                                       
//#define CommandReadLength       0x04                                                                                                       
//#define CommandSelecLength      0x05                                                                                                       
//#define CommandWriteLength      0x14                                                                                                       
//#define CommandBuzzSwitchLength         0x14                                                                                               
//#define     CRC8        0x80                                                                                                               
//                                                                                                                                           
//                                                                                                                                            
//                                                                                                                                           
//                                                             
//int fd_com;                                                                                                                                
//    
//int MIFSelectEx(void *ArgMifRegPtr,unsigned int ArgCardSN,unsigned char ArgSector,unsigned char ArgKey,unsigned char ArgKeySet)            
//{                                                                                                                                          
//                                                                                                                                     
//    return 0;                                                                                                                            
//} 
//int MIFReadCRC(void *ArgMifRegPtr,unsigned char ArgBlock,unsigned char *ArgBuffer)                                                         
//{                                                                                                                                          
//                                                                                                                                     
//    return 0;                                                                                                                            
//}                                                                                                                                          
//                                                                       
//int MIFWriteCRC(void *ArgMifRegPtr,int ArgBlock,unsigned char *ArgBuffer)//�������ļ�                                                      
//{                                                                                                                                          
//                                                                                                                                           
//          return 0;                                                                                                                  
//}
//int MIFReset(void *ArgMifRegPtr,unsigned char ResetTime )                                                                                  
//{                                                                                                                                          
//     return 0;                                                                                                 
//}                                                                                                                                          
//                                                                                                                                           
//                                                               
//int MIFHalt(void *ArgMifRegPtr )                                                                                                           
//{                                                                                                                                          
//   return 0;                                                                                     
//}                                                                                                                                          
//                                                                                                                                           
//const unsigned char Command_BuzzSwitch[]={USR_Start1,USR_Start2,0x03,USR_BuzzSwitch,0x00,0x30};                                            
//void CloseBuzzSwitch(void)                                                                                                                 
//{                                                                                                                                          
//return;                                                                                                 
//}                                                                                                                                          
 
