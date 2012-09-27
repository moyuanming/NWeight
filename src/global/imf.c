

#include "3des.h"
#include "mac.h"
#include "imf.h"
#include <math.h>
#include "LocalIncludeFile.h"
static sem_t IMF_SYNC;
/// <summary>
/// CPU��Ƭִ�н������
/// </summary>
typedef struct 
{
	/// <summary>
	/// PRO���������ִ�н�����Ǹ���PROSW12�Ľ���Ƿ�Ϊ 9000���жϵ�
	/// </summary>
	BOOL PROResult;
	/// <summary>
	/// ������ִ�н�������ֵΪ55AA01XX�� ��ʾ����ִ��ʧ�ܡ� 
	/// </summary>
	BOOL RADResult;
	/// <summary>
	/// ������������󷵻ص�ֵ
	/// </summary>
	char  PROResponse[512];
	/// <summary>
	/// ִ�н���� ���� 9000 Ϊ�ɹ�
	/// </summary>
	char PROSW12[5];

} CPUResult;
typedef struct 
{
	/// <summary>
	/// ������������󷵻ص�ֵ
	/// </summary>
	char * Response;
	/// <summary>
	/// ִ�н���� ���� 9000 Ϊ�ɹ�
	/// </summary>
	char * SW12;
} PSAMResult;


unsigned int Hex2UINT(char * hexvalue)
{
	unsigned char temp[strlen(hexvalue)/2];Hex2Bin(hexvalue,temp);
	unsigned int   j;                          
	memcpy((char *)&j,temp,strlen(hexvalue)/2);
	return j;
}
BOOL  EndsWith(char* src,char *endwith)
{
	int ret;
	ret=strncmp((char*)&src[strlen(src)-strlen(endwith)],endwith,strlen(endwith));
	return((ret==0)?T:F); 
}
BOOL  StartsWith(char* src,char *startwith)
{
	int ret;
	ret=strncmp(src,startwith,strlen(startwith));
	return((ret==0)?T:F); 
}


BOOL COM_ISOpen=F;//�����Ƿ��
BOOL isready = F;//�Ƿ�׼�����������Զ�д��Ƭ��
int fd_com;//���ڷ��ʾ��
int  COM_Open(char *comname)
{
	struct termios newtio;
	if (COM_ISOpen==F)
	{
		sem_init ((sem_t *)&IMF_SYNC,0,0);
		echoic("���ߴ��ں�:%s",comname);
		fd_com = open(comname,O_RDWR | O_NOCTTY	/*| O_NONBLOCK*/);
		echoic("���ھ��Ϊfd_com=%d",fd_com);
		if (fd_com < 0)
		{
			echoic("��Ч�Ĵ��ھ�����򿪴���ʧ��\n");
			close(fd_com);
			fd_com = open(comname,O_RDWR | O_NOCTTY	/*| O_NONBLOCK*/);
			if (fd_com < 0)
			{
				echoic("�رմ��ں󣬵ڶ��γ��Դ���Ȼʧ��!!\n");
				return -1;
			}
		}
		COM_ISOpen=T;
		
		
		echoic("���մ��ھ��%x",fd_com);
		bzero(&newtio, sizeof(newtio));/* ����ṹ���Է����µ����в��趨ֵ */
		newtio.c_cflag = B115200| CS8 | CLOCAL | CREAD ;//���ò����ʣ�Ĭ��Ϊ115200
		newtio.c_iflag = IGNPAR;//IGNPAR | ICRNL;/*HH IGNPAR*/
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;//ICANON; /*HH 0*/
		newtio.c_cc[VINTR]    = 0;	   /* Ctrl-c */  
		newtio.c_cc[VQUIT]    = 0;	   /* Ctrl-\ */ 
		newtio.c_cc[VERASE]   = 0;	   /* del */ 
		newtio.c_cc[VKILL]    = 0;	   /* @ */ 
		newtio.c_cc[VEOF]     = 4;	   /* Ctrl-d */ 
		newtio.c_cc[VTIME]    = 0;	   /* ��ʹ�÷ָ���Ԫ��ļ�ʱ�� */ 
		newtio.c_cc[VMIN]     = 1;	   /* �ڶ�ȡ�� 1 ����Ԫǰ��ֹͣ */ 
		newtio.c_cc[VSWTC]    = 0;	   /* '\0' */ 
		newtio.c_cc[VSTART]   = 0;	   /* Ctrl-q */  
		newtio.c_cc[VSTOP]    = 0;	   /* Ctrl-s */ 
		newtio.c_cc[VSUSP]    = 0;	   /* Ctrl-z */ 
		newtio.c_cc[VEOL]     = 0;	   /* '\0' */ 
		newtio.c_cc[VREPRINT] = 0;	   /* Ctrl-r */ 
		newtio.c_cc[VDISCARD] = 0;	   /* Ctrl-u */ 
		newtio.c_cc[VWERASE]  = 0;	   /* Ctrl-w */ 
		newtio.c_cc[VLNEXT]   = 0;	   /* Ctrl-v */ 
		newtio.c_cc[VEOL2]    = 0;	   /* '\0' */ 

		/*  
		����������ݻ��߲��������в����趨 
		*/ 
		tcflush(fd_com, TCIFLUSH);
		tcsetattr(fd_com,TCSANOW,&newtio);
		sem_post((sem_t *)&IMF_SYNC);
	}
	return 0;
}
void COM_Close(void)
{
	close(fd_com);
	COM_ISOpen=F;
}
//�Ƿ������ݿ��Զ�ȡ
int BytesToRead(void)
{
	int nLen=0,i;
	for (i=0;i<10000;i++)
	{
		ioctl(fd_com,FIONREAD,&nLen);
		if (nLen>=3)
		{			
			return nLen;
		}
	}
	return -1;
	
}
//������뻺��
void DiscardInBuffer(int  fd)
{
	unsigned  char rb[64];                                                                                           
	while ((BytesToRead() > 0))
	{
		read(fd_com,rb,   64);		
	}
}
char ICRecvData[2049];
char *  SendCommand( unsigned char *hexbuffer )                                 
{
	
	int wRet=0;    
	int loc = 0; 
	char cmdbins[strlen(hexbuffer)/2+1];
	unsigned  char    result[1024];//����1024���ֽڵĽ������  	
	//echoic("SendCommand=%s,Len = %d \n",hexbuffer,strlen(hexbuffer));
	memset(result,0x00,1024);	
	Hex2Bin(hexbuffer,cmdbins);
	DiscardInBuffer(fd_com);
	wRet=write(fd_com, cmdbins, strlen(hexbuffer)/2);
	usleep(20000);
	loc = read(fd_com,result,   1024); 
	Bin2Hex(result,loc,ICRecvData);	
	ICRecvData[loc*2+1] = 0x00;
	//echoic("ICRecvData=%s\n",ICRecvData);
	return ICRecvData;                                                                                                   
}


//�ж��ǲ���PRO��������ǣ���ָ��λ��Ӧ���� 08
BOOL IsProCard(char* rex)                            
{
	unsigned char	temp[3];
	return EndsWith(Substring(rex,6, 2,temp) , "08");                              
}   
char HexCard[9];
char * _RequestPro(void)                                           
{

	char * rex ;
	ResetPro();
	rex = SendCommand("55AA020152"); 
	memset(HexCard,0x00,9);
	if (strlen(rex) != 0 && IsProCard(rex)==T)
	{                                                 
		memcpy(HexCard, (char*)&rex[strlen(rex) - 2 * 4], 2 * 4);     
	}	
	return HexCard;                                                   
}   
char * RequestPro(void)
{
	char *temp;
	sem_wait((sem_t *)&IMF_SYNC);
	temp  = _RequestPro();
	sem_post((sem_t *)&IMF_SYNC);
	return temp;
}
BOOL  SelectPro_____=F;
BOOL SelectPro(char * card)                                     
{
	char * rex ;
	char tmp[20];
	memset(tmp,0x00,20);		
	sprintf(tmp,"55AA0502%s",card);
	echoic("SelectPro = %s ,%s\n",tmp,card);
	rex=SendCommand(tmp) ;
	echoic("ѡ��%s�����Ϊ%s",  card , rex);  
	SelectPro_____=  EndsWith(rex,"00");        
	return SelectPro_____;
}                                                                 

BOOL ___resetpro;
BOOL ResetPro(void)                                               
{	
	char * rex =  SendCommand("55AA02060A");  	
	___resetpro= EndsWith(rex,"00");	                                 
	return   ___resetpro;                                   
}                                                                    

char * __RATS;                                           
char * RATS(void)                                                 
{
	__RATS =  SendCommand("55AA0690040105E070");	                      
	return __RATS;                                                      

}                                                     

//��Ҫ����������״̬��־���û�ִ������ʱ�任�ؼ���Ϣ
BOOL cmdstate = T;                                                                                                       
char * _______ExcCPUCmd;                                                                                            
char* ExcCPUCmd(char * command)                                                                               
{
	char  hexcmd[1024];
	memset(hexcmd,0x00,1024);	
	sprintf(hexcmd,"%02X%02X%02X%02X%02X%02X%02X%02X%02X%s", USR_Start1, USR_Start2, strlen(command) / 2 + 6, 0x90, strlen(command)/ 2 + 4, 0x01, 0x06, (int)((cmdstate == T )? 0x0a : 0x0b), 0x00, command);                                                              
	_______ExcCPUCmd = SendCommand( hexcmd);                                                                         
	cmdstate =( cmdstate==T)?F:T ; 	                                                                                        
	return _______ExcCPUCmd;                                                                                                        

}                                                                                                                    

CPUResult  ____CPUResult;
CPUResult * CPU_CommandEx(char * command)                                                             
{
	char * strTemp = ExcCPUCmd(command);                                             
	memset(&____CPUResult,0x00,sizeof(  CPUResult));
	if ( strTemp!=NULL && strlen(strTemp)>0)
	{
		if (StartsWith(strTemp,"55AA01")==T)
		{
			if (StartsWith(strTemp , "55AA010")==F)
			{
				                                                                         
				____CPUResult.RADResult = T;                                                                  
			}
			else
			{
				____CPUResult.RADResult = T;                                                                   
			}                                                                                              
		}
		else //���ش���һ���ֽڣ� ����ֵ������Σ����������ֽڡ�                                           
		{
			unsigned char subtemp[3];
			unsigned  char rlen[1];  
			Hex2Bin(Substring(strTemp,4, 2,subtemp),rlen);                                                                                                      
			if ((int)(rlen[0]) > 1)
			{
				int tt ;                     
				char crc[5];
				char tempsubstring[512];
				memset(tempsubstring,0x00,512);				                                                               
				____CPUResult.RADResult = T;
				sprintf(tempsubstring,"%s",Substring(strTemp,strlen(strTemp) - 8, 4,crc));
				memset(crc,0x00,5); 
				memcpy((char*)& ____CPUResult.PROSW12[0],tempsubstring ,4);
				tt = strlen(strTemp); 
				____CPUResult.PROResult = StartsWith(____CPUResult.PROSW12 , "9000");//���� �ĳɹ�����ֵΪ 9000                 
				Substring(strTemp,strlen(strTemp) - 4,4,crc);    
				memset(tempsubstring,0x00,512);
				Substring(strTemp,0, tt- 8,tempsubstring);                                
				Substring(tempsubstring,6 + 6,tt-8-(6+6),(char*)&____CPUResult.PROResponse[0]);;//����ֵ
			}
		}                                                                                                  
	}
	return &____CPUResult;//��Ƭ�����Ƿ�ִ�гɹ�                                                                   
}
//ȡ��һ��8λ�������
char * GET_CHALLENGE(void)
{
	return GET_CHALLENGE_n(8);
}

char  ___GET_CHALLENGE_n[17];
//ȡ��ָ�����ȵ������
char * GET_CHALLENGE_n(int len)
{
	char tempx[32];
	if (len < 4) len = 8;	
	memset(tempx,0x00,32);
	sprintf(tempx,"00840000%02X",len);
	CPUResult *cr = CPU_CommandEx(tempx); //ȡ8�ֽ������
	if (cr->PROResult==T)
	{
		memset(___GET_CHALLENGE_n,0x00,17);
		memcpy(___GET_CHALLENGE_n, cr->PROResponse,16);
	}
	echoic("ȡ�������%s", ___GET_CHALLENGE_n );
	return ___GET_CHALLENGE_n;
}
//ʹ��ָ������Կ�����ⲿ��֤
BOOL EXTERNAL_AUTHENTICATE(void)
{
	char * initkey = Get_EXTERNAL_AUTHENTICATE_KEY();
	return EXTERNAL_AUTHENTICATE_key(initkey);
}
//ʹ��ָ������Կ�����ⲿ��֤
BOOL EXTERNAL_AUTHENTICATE_key(char * initkey)
{
	// initkey = initkey.Replace(" ", "");
	char * sRand = GET_CHALLENGE();
	if (sRand != NULL && strlen(sRand)==16)
	{
		char * endparam=sRand ;
		char cmdtemp[32];
		CPUResult *cr;
		memset(cmdtemp,0x00,32);
		endparam=enc3des16(initkey, endparam);
		echoic("��Կ %s�����%s��֤����  %s",initkey,sRand,endparam);
		sprintf(cmdtemp,"0082000008%s",endparam);
		cr= CPU_CommandEx(cmdtemp);
		return cr->PROResult;
	}
	else
	{
		echoic("δȡ�����ʵ������");
		return F;
	}

}                                                                                                          
//ѡ���ļ������ļ���
BOOL SELECT(char * fileid)
{
	char cmdtemp[32];
	CPUResult *cr;	
	memset(cmdtemp,0x00,32);
	sprintf(cmdtemp,"00A4000C02%s",fileid);
	cr = CPU_CommandEx(cmdtemp ); 
	return cr->PROResult;
}


char _______INITIALIZE_FOR_PURCHASE[8024];
char * INITIALIZE_FOR_PURCHASE(void)
{
	CPUResult *cr;  
	char MAC1[17];
	memset(MAC1,0x00,17);
	if (SELECT("1001"))
	{
		char cmdtemp1[100];
		char  guochengmiyao[64];
		unsigned char subtemp[9];
		memset(cmdtemp1,0x00,100);
		sprintf(cmdtemp1,"805001020B%s%s%s%s" , "01" , "00000000" , "010203040506" , "0F");
		cr = CPU_CommandEx(cmdtemp1);//���ѳ�ʼ��

		memset(guochengmiyao,0x00,64);
		sprintf(guochengmiyao,"%s00043344", Substring(cr->PROResponse,22, 8,subtemp));
		enc3des16("01202020202020202020202020202020", guochengmiyao);
		if (strlen(guochengmiyao)== 16)
		{
			//string tt = cr.PROResponse.Substring(22, 8);
			char *tmpdsjk="000000000601020304050620100423111933";
			char *tmpxxx= MAC8(tmpdsjk,strlen(tmpdsjk), "0000000000000000", guochengmiyao);
			memcpy(MAC1,tmpxxx,16);
		}
		else if (strlen(guochengmiyao)> 16)
		{
			char *tempcmdxx="000000100600000000000020100423111933";
			char * tempsdfjk= MAC(tempcmdxx ,strlen(tempcmdxx), "0000000000000000", guochengmiyao);
			memcpy(MAC1 ,tempsdfjk,16);
		}
		if (cr->PROResult==T)
		{
			char cmdtmp[100];
			memset(cmdtmp,0x00,100);
			sprintf(cmdtmp, "805401000F%s%s%s","1122334420100423111933" , MAC1 , "08");
			cr = CPU_CommandEx(cmdtmp);//����ָ��
		}
	}

	memset(_______INITIALIZE_FOR_PURCHASE,0x00,8024);
	memcpy(_______INITIALIZE_FOR_PURCHASE, cr->PROResponse ,sizeof( cr->PROResponse)+1);
	return _______INITIALIZE_FOR_PURCHASE;
}

char ___read[2048];
/*��ȡָ���ֶε�ָ���ֽ�ָ�����ȵ�ʮ�������ַ���
ע�⣬ ���ֽڣ� ����ʮ�����Ƶĳ���*/
char * Read(char * tempinfo,int loc ,int len)
{
	
	memset(___read,0x00,len+1);
	memcpy(___read,(char*)&tempinfo[(loc-1)*2],len*2);
	return ___read;
}
/*��ÿ�����*/
int GetProType(char* tmpinfo)
{
   return atoi( Read(tmpinfo,9,1));
}
char *  Write(char * info,char *tmpvalue,int loc ,int len)
{
	memcpy((char*)&info[(loc-1)*2],tmpvalue,len*2);
	echoic("info:%s", info);
	return info;
}

char * ReadCardInfo(char * fileid,char *_ReadCardInfo)
{
	if(WF_IC_WriteBase())
	{
		if (strncmp(fileid,"0015",4)==0)
		{
			if (SELECT("1001")==F)
			{
				fileid=NULL;
			}
		}
		if (fileid!=NULL && SELECT(fileid )==T)
		{
			CPUResult *cr;
			cr = CPU_CommandEx("00B0000000");
			memset(_ReadCardInfo,0x00,512);
			
			sprintf(_ReadCardInfo,"%s",SUBSTRING(cr->PROResponse));
			echoic("_ReadCardInfo = %s\n",_ReadCardInfo);
		}
		else
		{
			
			memset(_ReadCardInfo,0x00,512);
		}
	}
	else
	{
		_ReadCardInfo[0] = 0x00;
	}	
	return _ReadCardInfo;
}

BOOL IMFVERIFY(char * param)
{
	CPUResult *cr;
	char cmdtemp[32];
	memset(cmdtemp,0x00,32);
	sprintf(cmdtemp,"0020000003%s",param);
	echoic("IMFVERIFY===%s",cmdtemp);
	cr = CPU_CommandEx(cmdtemp);
	if (strncmp(cr->PROSW12,  "63C0",4)==0)
	{
		echoic("���Ѿ�����");
	}
	echoic("��֤����:%d,PROSW12 = %s\n", cr->PROResult,cr->PROSW12);
	return cr->PROResult;
}

BOOL WriteCardInfo(char *cardinformation)
{
	BOOL result=F;
	if(2==GetCardExist())
	{
		return result;
	}
	sem_wait((sem_t *)&IMF_SYNC);
	if (WF_IC_WriteBase() &&  SELECT("1001") && SELECT("0015") && IMFVERIFY("123456"))//
	{
		char* rnd = GET_CHALLENGE_n(4);
		echoic("�����%s",rnd);
		if (rnd !=NULL && strlen(rnd)!=0)
		{
			char cmdtemp[1024];
			CPUResult *cr;
			char*  mac;
			memset(cmdtemp,0x00,1024);
			sprintf(cmdtemp,"04D600002F%s" ,cardinformation);
			echoic("...");
			mac = MAC(cmdtemp, strlen(cmdtemp), rnd, Get_WRITE_KEY());
			echoic("mac=%s",mac);
			memset(cmdtemp,0x00,1024);
			sprintf(cmdtemp, "04D60000%s%s%s" , "2F",cardinformation , mac);
			 cr= CPU_CommandEx(cmdtemp);
			echoic("result %s",SUBSTRING(cr->PROSW12));
			result=cr->PROResult;
		}
	}
	else
	{
		echoic("�������");
	}
	sem_post((sem_t *)&IMF_SYNC);
	return result;
}


// ʹ�ÿ��������˲����������󿨣� ѡ�񿨣�������ATS,��ȷ��������ʹ������

BOOL ReadyCard(char * procard)
{
	char * tempcard;
	BOOL result = F;	
	tempcard = _RequestPro();
	if ( 8==strlen(tempcard) &&  SelectPro(tempcard)==T)
	{
		char *ats =NULL;
		echoic("ѡ���ɹ�");
		ats = RATS();
		echoic("ATS:%s" ,ats);
		if (ats != NULL && strlen(ats)>0)
		{
			cmdstate = T;
			result = T;
		}
	}
	else
	{
		echoic("��Ƭ�����쳣");
	}

	return result;
}


