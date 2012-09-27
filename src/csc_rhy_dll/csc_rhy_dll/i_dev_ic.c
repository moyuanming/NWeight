     /************************************************************************/
/* 卡动态库  fuxl 2008.5.30                                             */
/************************************************************************/
#include "LocalIncludeFile.h" 

/************************************************************************/
/* 卡初始化 liujl 2008.6.10                                             */
/************************************************************************/
static int CardExist = MIF_NoCard;//卡是否存在于天线上
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
	////print_emrc("-->卡线程创建 \n");
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

void testTrans( void ) //测试复合消费
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


	printf("----瑞华赢读写器 LINUX 非现金支付复合消费 测试---------\n"); 

	 

	//ret = Open_Card(iComno, &dwcardno);
	//printf("-->Open_Card ret =%d \n",ret );
     

	memset(rsp,0,sizeof(rsp));  
	ret = USR_SelectSAM( 1 );
	printf("-->SAM复位即选择SAM%d ret=%d, rsp=%s \n",1,ret, rsp ); 
	if(ret!= T )
	{
		printf("\n Error on USR_SelectSAM!\n");
		return;
	}
 
	//SAM复位 
	sprintf(command,"55aa0182");
	sprintf(rsp,"%s",(char *)SendCommand(command ));
 
	printf("-->SAM复位 ret=%d,  rsp=%s\n",ret ,rsp );

	//读0015文件，取得区 发卡方标识＝(4字节发行区域代码*2)

	memset(rsp,0,sizeof(rsp)); 
	ReadCardInfo("0015",CardData15File);
    sprintf(rsp,"%s",CardData15File);
	//ret = CPU_Get0015(m_szproserial,rsp,m_sn); 
	sprintf(m_sn,"%.16s",rsp);
	printf("-->读0015文件 ret=%d,m_sn=%s, rsp=%s \n",ret,m_sn, rsp );  

	//选择目录1001 
	sprintf(command,"00A40000021001");
	sprintf(rsp,"%s",(char *)ExcCPUCmd(command ));

	memset(cpuID,0,sizeof(cpuID));
	sprintf(cpuID,"%.16s",rsp + 68 + 12 );
	printf("-->选择目录1001 ret=%d,cpuID =%s, rsp=%s\n",ret, cpuID,rsp );

	 
	//读0019文件
	//00b0是读二进制文件.
	//0019文件是变长记录文件来的所以要使用00b2来读.
	//00B2  01  CC2B
	//这个01就是记录号.

	memset(rsp,0,sizeof(rsp));
	sprintf(command,"00B201CC2B");
	sprintf(rsp,"%s",(char *) ExcCPUCmd(command ));

	printf("-->读0019文件 记录1 ret=%d, rsp=%s\n",ret, rsp );


	//memset(rsp,0,sizeof(rsp));
	//ret=PRO_GetBallance(iComno,2,rsp,sizeof(rsp),resp);

	memset(rsp,0,sizeof(rsp));
	sprintf(command,"805C000204");
	sprintf(rsp,"%s", (char *)ExcCPUCmd(command ));


	printf("-->读取余额 ret=%d, rsp=%s \n",ret, rsp ); 



	/*memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"0084000004\0");
	ret = SAM_Command(iComno,command,rsp);
	sprintf(TerminalNo,"%s",rsp);
	printf("-->读取SAM卡随机数 ret=%d, rsp=%s \n",ret, rsp );  
	*/
    
	memset(rsp,0,sizeof(rsp)); 
	memset(TerminalNo,0,sizeof(TerminalNo));
	memset(command,0x00,sizeof(command)); 
	sprintf(command,"00B0960006");
	command[10] = 0x00;
 
	sprintf(rsp,"%s", (char *)ExcSAMCmd(command ));
 
	sprintf(TerminalNo,"%.18s",rsp + 8);
	printf("-->读取SAM卡终端号 ret=%d, TerminalNo=%s,rsp=%s \n",ret,TerminalNo, rsp ); 

	transMoney = 1 ; //消费金额

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
		printf("-->复合交易初始化 消费 并取得随机 ret=%d, rsp=%s ,icRand=%s,transNo=%s,keyVerID=%s,calcID=%s\n",ret, rsp ,icRand,transNo,keyVerID,calcID);
	}

	//消费初始化成功后->写0019->计算MAC1->消费->校验MAC2

	//写0019文件
	memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"80DCAAC82BAA2900%.80s","000500467B4ABDC4BA010300000000000000000000100003C9F24332333034380000000000000000");
	//ret = PRO_Command(iComno,command,rsp); 
	sprintf(rsp,"%s", (char *)ExcCPUCmd(command ));
	printf("-->写0019文件 ret=%d, rsp=%s \n",ret, rsp );  

	//选择到SAM卡 df01目录.
	memset(rsp,0,sizeof(rsp));  
	sprintf(command,"00a4000002df01"); 
	sprintf(rsp,"%s", (char *)ExcSAMCmd(command ));
	printf("-->选择到SAM卡 df01目录 command=%s,ret=%d, rsp=%s \n",command,ret, rsp ); 
	if(ret!=0)
	{
		printf("\n Error on CPU_reset!\n");
	}

	//计算MAC1
	memset(rsp,0,sizeof(rsp)); 
	memset(DateTime,0,sizeof(DateTime)); 
	sprintf(DateTime, "%.14s",DataTimeStr );
	//命令的最后是 8字节应用卡号+(4字节发行区域代码*2)
	sprintf(command,"8070000024%.8s%.4s%.8x09%.14s%.2s%.2s%.16s%.8s%.8s",icRand,transNo,transMoney ,DateTime,keyVerID,calcID,cpuID,m_sn,m_sn);
	printf("-->计算MAC1 command=%s \n",command ); 
	 
	sprintf(rsp,"%s", (char *) ExcSAMCmd(command ) + 8);
	memset(MAC1,0,sizeof(MAC1)); 
	memset(offlineTransNo,0,sizeof(offlineTransNo)); 
	sprintf(offlineTransNo, "%.8s",rsp   );
	sprintf(MAC1, "%.8s",rsp + 8 ); 
	printf("-->计算MAC1 ret=%d,offlineTransNo=%s,MAC1 =%s, rsp=%s \n",ret,offlineTransNo,MAC1, rsp );  



	//消费
	memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"805401000F%.8s%.14s%.8s",offlineTransNo,DateTime, MAC1);
	sprintf(rsp,"%s",(char *) ExcCPUCmd(command )  );
	printf("-->消费 command=%s \n",command );
	memset(TAC,0,sizeof(TAC)); 
	memset(MAC2,0,sizeof(MAC2));  
	sprintf(TAC, "%.8s",rsp +12  );
	sprintf(MAC2, "%.8s",rsp + 8  + 12 ); 
	printf("-->消费 ret=%d, TAC=%s,MAC2=%s ,rsp=%s \n",ret,TAC,MAC2, rsp );  

	//校验MAC2
	memset(rsp,0,sizeof(rsp)); 
	sprintf(command,"8072000004%.8s",MAC2);
	sprintf(rsp,"%s",(char *) ExcSAMCmd(command ));
	printf("-->校验MAC2 command=%s \n",command ); 
	printf("-->校验MAC2 ret=%d,   rsp=%s \n",ret,  rsp );  

	memset(rsp,0,sizeof(rsp));
	sprintf(command,"805C000204");
	sprintf(rsp,"%s", (char *)ExcCPUCmd(command ));


	printf("-->读取余额 ret=%d, rsp=%s \n",ret, rsp ); 


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
			echoic("卡进入HEX:%s DEC:%010u",hexCardNumber,RequestcardNum);

		}
		else if (0==strlen(HexCard) &&  CardExist!=MIF_NoCard)
		{
			CardExist=MIF_NoCard;
			hexCardNumber[0] = 0x00;
			RequestcardNum=0;
			memset(CardData15File,0x00,1024);
			memset(CardData16File,0x00,1024);
			//PostMessage(getHWND(),MSG_CRADENENT,CSC_CARDEXIT,RequestcardNum);  
			echoic("卡离开HEX:%s DEC:%010u",HexCard,RequestcardNum);
		}
		else
		{
			//echoic("状态未改变");
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
			echoic("卡进入HEX:%s DEC:%010u",hexCardNumber,RequestcardNum);

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
			echoic("卡离开HEX:%s DEC:%010u",HexCard,RequestcardNum);
		}
		else
		{
			//echoic("状态未改变");
		}
	ResetPro();
 
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
 
 
                                                                                                                                           
                                                                                                                                           
                                                                                                                                           
//#define USR_Start1          0x55        //开始位第一位                                                                                     
//#define USR_Start2          0xAA        //开始位第二位                                                                                     
//#define USR_Request         0x01 /*寻卡 防碰撞获得卡号*/                                                                                   
//#define USR_Select          0x02 /*选择卡*/                                                                                                
//#define USR_PiccRead        0x03 /*读卡*/                                                                                                  
//#define USR_PiccWrite       0x04 /*写卡*/                                                                                                  
//#define USR_PiccHalt        0x05 /*挂起*/                                                                                                  
//#define USR_PcdRfReset      0x06 /*复位M1 卡 + 时间(ms) =2*/                                                                               
//#define USR_LoadKeyE2       0x10 /*下载密钥 到E2 存储器 可掉电存储*/                                                                       
//#define USR_PiccAuthE2      0x11 /*从E2 验证密钥*/                                                                                         
//#define USR_BuzzSwitch      0x30 /*蜂鸣器开关1=on 0=off*/                                                                                  
//                                                                                                                                           
//                                                                                                                                           
//#define  KeyCommandLen 0x9                                                                                                                 
//                                                                                                                                           
//#define Secteur0 0x00 //第一扇区                                                                                                           
//#define Secteur1 0x01 //第一扇区                                                                                                           
//#define Secteur2 0x02 //第一扇区                                                                                                           
//#define Secteur3 0x03 //第一扇区                                                                                                           
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
//int MIFWriteCRC(void *ArgMifRegPtr,int ArgBlock,unsigned char *ArgBuffer)//读卡中文件                                                      
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
 
