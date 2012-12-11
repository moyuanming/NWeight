#ifndef		DEVCE_H
#define		DEVCE_H
 //����ģ�����ӵĴ���
//�����ʾ�����ں�
#define LED_COM         (Get_LEDCOM())

/*Ʊ�ݴ�ӡ�����ں�*/
#define PRINTER_COM		(Get_PrintCOM())
  
int serial_read(int nCOM,unsigned char *byReadBuf,int nReadLen);
int serial_write(int nCOM,unsigned char *byWriteBuf,int nWriteLen);

int serial_init(int nCOM, int nBaud);
 
#define IMG_FIRST  '1' //��һ��ͼƬ
#define IMG_SECOND  '2' //�ڶ���ͼƬ

int OpenLedCom(int nCOM);
int serial_close(int nCOM);
int i_dev_ioboard_IOBoardInit(void);
void i_dev_ioboard_exit(void);
void  ShowLineState(int readLinState);
void I_DEV_IOBoard_CommandSender(int bFlag ,int command1,int command2);
void InLineUP(void);
void InLineDown(void);
void PassLineUP(void);
void PassLineDown(void);
void  LedClear(void);
BOOL  IsRichTFI(void);
void TFI_SetHuangShan(BOOL bFlag);
void TFI_SetTongXingDeng(BOOL bFlag);
int GetMoneyTimer(void);
void SetYuPeng(BOOL  bFlag);
void SetRingVoide(BOOL  bFla);
void SetJiaoTong(BOOL bFlag);
void SetLanGan(BOOL bFlag);
void SetRing(BOOL bFlag);
void SetPassCar(void);
void OpenMoneyBox(void);
void CloseMoneyBox(void);
void SetCloseDev(void);
void I_DEV_IOBoard_Callback(unsigned char Input);
void LedSound(int Index);

void LedShowCharge(char CarType,int charge);
void TWD_ShowCarType(char ct);
void TWD_Showcharge(int ct);
void LedClare(BOOL IsSound);
int getJiaoTongDengState(void);
int getGetPrintState(void);
int getLanGanState(void);
int getTongGuoXianQuan(void);
int getZhuaPaiXianQuan(void);
 
void LedVolume(int VolumeValue );
#define HELLO	1
#define THANKS	2
#define WELCOME	3
#define ITEASY	4
#define PLEGO	5
#define GO		6
#define GOODBYE	7
#define CLEARANDSOUND	8
#define CLEARNOTSOUND	9
char *DoSysCmd(char * cmdline);
void  DataExporter(void);
char  *GetJiaoTongDengState_Str(void);
char  *GetLanGanState_Str(void);
 
 
void setLed(void);

#define FIFO_NAME "/dev/shm/VideoFifo"
void I_DEV_VDM_SyncTime(void);
int  DevSetInit(void);
void I_DEV_VDM_TextOut(char *text,unsigned char x,unsigned char y,unsigned char  len);
void I_DEV_VDM_Reset(void);
void I_DEV_VDM_Cash(int value);
void I_DEV_VDM_CarKind(int CarKind);
void I_DEV_VDM_CarType(char *CarType);
void I_DEV_VDM_CollectNo(char *CollectNo);
void I_DEV_VDM_LaneNO(char *LaneNo);
void I_DEV_VDM_ShowPlaza(char *PlazaNo);
int  I_DEV_IOBoard_Init(void);
void I_DEV_IOBoard_Exit(void);
void I_DEV_IOBoard_Callback(unsigned char Input);
  void ReadDeviceStatus_Loop(int i, char bt, char oldbt);

//����������
#define SERIAL_CSC_ID    GetCSCCOM( )
 
//������������
#define SERIAL_CSC_SPEED  atoi(GetSysConfig( )->CSC_SPEED)
#define MSG_CRADENENT		(MSG_USER+14)
 
#define CSC_CARDENTER					1201  //������������ɶ���Χ
#define CSC_CARDEXIT					1202  //���˳��˶������ɶ���Χ





/******************************************************************************************************
*�����¼�����
******************************************************************************************************/
#define  EVENT_TYPE_NORMAL				'2'		//������ͨ�¼���Ϣ
#define  EVENT_TYPE_ALARM				'1'		//���ͱ����¼���Ϣ
#define  EVENT_TYPE_RESUME				'0'		//���ͱ����ָ��¼���Ϣ
/******************************************************************************************************
*���������� 
******************************************************************************************************/
#define ID_DEV_LCL						"01"  //���������� 
#define ID_STATUS_LCL_COMMERR 			"001"  //01001 ����������:ͨ�Ź���" 
#define ID_STATUS_LCL_INI 				"002"  //01002 ����������:�������ʼ��"
#define ID_STATUS_LCL_DISKFULL 	 		"003"  //01003 ����������:���������Ӳ�̽���"
/******************************************************************************************************
*���Ӱ�   (��)
******************************************************************************************************/
#define ID_DEV_CXP						"02"							//���Ӱ�   (��)   
#define ID_STATUS_CXP_COMMERR			"02001ͨ�Ź���"					//02001 ���Ӱ�:ͨ�Ź���"(��)
#define ID_STATUS_CXP_PALERR 			"02003ͨ����Ȧ����"				//02003 ���Ӱ�:ͨ����Ȧ����"(��,������)
#define ID_STATUS_CXP_PRLERR			"02004������Ȧ"					//02004 ���Ӱ�:������Ȧ����"

/******************************************************************************************************
*�շ�Ա����̨
******************************************************************************************************/
#define ID_DEV_SFC						"03"							//�շ�Ա����̨
#define ID_STATUS_SFC_COMMERR 			"03001ͨ�Ź���"					//03001 �շ�Ա����̨:ͨ�Ź���"
/******************************************************************************************************
*Ʊ�ݴ�ӡ��
******************************************************************************************************/
#define ID_DEV_DCP						"09"							//Ʊ�ݴ�ӡ��  (��)
#define ID_STATUS_DCP_COMMERR 			"001"							//09001 Ʊ�ݴ�ӡ��:ͨ�Ź���"(��)
#define ID_STATUS_DCP_BLANK				"007"							//09007 Ʊ�ݴ�ӡ��:��ӡ��ȱֽ"(��)
/******************************************************************************************************
*�Ѷ���ʾ��  
******************************************************************************************************/
#define ID_DEV_TFI						"11"							//�Ѷ���ʾ��  
#define ID_STATUS_TFI_COMMERR 			"001"			//11001 �Ѷ���ʾ��:ͨ�Ź���"
/******************************************************************************************************
*�Ųȿ���
******************************************************************************************************/
#define ID_DEV_FSW						"33"							//�Ųȿ���    (��)
#define ID_STATUS_FSW_ACTIVE			"33008�Ųȿ��ؼ���"				//33008 �Ųȿ���:����"(��,�ֶ�������)
/******************************************************************************************************
*�Ųȿ���
******************************************************************************************************/
#define ID_DEV_CSC						"35"			//IC����д����(��)
#define ID_STATUS_CSC_COMMERR 			"001IC"			//35001 IC����д����:�շ���������ͨ�Ź���"
#define ID_STATUS_CSC_WRITEERR			"002IC"			//35002 IC����д����:�շ���������д����"(��)
#define ID_STATUS_CSC_WRITECOMMERR		"003IC"			//35003 IC����д����:�շ���������д��ͨ�Ŵ���"
/******************************************************************************************************
*�շ�����
******************************************************************************************************/
#define ID_DEV_CICM						"38"		//�շ�����    (��)
#define ID_STATUS_CICM_COMMERR 	 		"001"		//38001 �շ�����:�շ�����ͨ�Ź���"
#define ID_STATUS_CICM_CHANGE			"003"		//38003 �շ�����:��������"(��)
#define ID_STATUS_CICM_WILLEMPTY		"005"		//38005 �շ�����:��ڳ������佫��"(��)
#define ID_STATUS_CICM_EMPTY			"006"		//38006 �շ�����:��ڳ��������"(��)
#define ID_STATUS_CICM_WILLFULL	 		"007"		//38007 �շ�����:���ڳ������佫��"(��)
#define ID_STATUS_CICM_FULL				"008"		//38008 �շ�����:���ڳ���������"(��)
#define ID_STATUS_CICM_FORCED_CTID		"012"		//38012 �շ�����:ǿ��ȡ�����䣺�����ǩ����"(��)
#define ID_STATUS_CICM_FORCED_CT 		"013"		//38013 �շ�����:ǿ��ȡ�����䣺���ڿ�������"(��)
#define ID_STATUS_CICM_COVEROPEN 		"014"		//38014 �շ�����:���շ�����������"(��)
#define ID_STATUS_CICM_COVEROPENSP		"015"		//38015 �շ�����:������շ�����������"
#define ID_STATUS_CICM_NOCART			"016"		//38016 �շ�����:�޿���"(��)
/******************************************************************************************************
*������
SendMsgEvent(EVENT_TYPE_NORMAL,ID_DEV_PTFARE,,"");
SendMsgEvent(EVENT_TYPE_RESUME,ID_DEV_PTFARE,,"");
SendMsgEvent(EVENT_TYPE_ALARM,ID_DEV_PTFARE,,"");
******************************************************************************************************/
#define ID_DEV_PTFARE          "50"  //���ʱ�      
#define ID_DEV_PTJOUR          "51"  //�г�ʱ���  
#define ID_DEV_PTSTAFF         "56"  //��ȨְԱ��  
#define ID_DEV_PTBSTAF         "57"  //��ݿ�������
#define ID_DEV_PTBSEVR         "58"  //���񿨺�����
#define ID_DEV_PTBSVC          "59"  //��ֵ��������
#define ID_DEV_PTCONST         "60"  //������      
#define ID_DEV_PTIMG           "62"  //ͼ�������  
#define ID_DEV_PTL             "63"  //ʹ�ü����  
#define ID_DEV_PTS             "64"  //�Ϸ����񿨱�
#define ID_DEV_PTP             "70"  //ͨ�ò����� 
#define ID_STATUS_PARATAB_READERR 		"001"  //XX001 ������:�������ȡ����"
#define ID_STATUS_PARATAB_HEADERR		"002"  //XX002 ������:�������ͷ����"
#define ID_STATUS_PARATAB_TYPEERR		"003"  //XX003 ������:���������ʹ���"
#define ID_STATUS_PARATAB_NETNOERR		"004"  //XX004 ������:����������"
#define ID_STATUS_PARATAB_PLAZANOERR	"005"  //XX005 ������:վ�������"
#define ID_STATUS_PARATAB_VERNOERR		"006"  //XX006 ������:�汾�Ŵ���"
#define ID_STATUS_PARATAB_SIZEERR		"007"  //XX007 ������:��¼�ߴ����"
#define ID_STATUS_PARATAB_NUMERR		"008"  //XX008 ������:��¼��Ŀ����"
#define ID_STATUS_PARPLATE_BLACKLIST	"110"
/******************************************************************************************************
*ͨ���豸
SendMsgEvent(EVENT_TYPE_NORMAL,ID_DEV_DVP,,"");
SendMsgEvent(EVENT_TYPE_RESUME,ID_DEV_DVP,,"");
SendMsgEvent(EVENT_TYPE_ALARM,ID_DEV_DVP,,"");
******************************************************************************************************/
#define ID_DEV_DVP						"80"							//ͨ���豸   (��) 
#define ID_STATUS_DVP_MLBOPEN 			"009"			//80009 ͨ���豸:�򿪳����ֶ�����"(��)
#define ID_STATUS_DVP_MLBCLOSE			"010"			//80010 ͨ���豸:�رճ����ֶ�����"(��)
#define ID_STATUS_DVP_CSLRED			"013"			//80013 ͨ���豸:�����źŵƺ�ɫ"(��)
#define ID_STATUS_DVP_CSLGREEN			"014"			//80014 ͨ���豸:�����źŵ���ɫ"(��)
#define ID_STATUS_DVP_REVERSING			"015"			//80015 ͨ���豸:����"(��)
#define ID_STATUS_DVP_DIFFCLASS			"016"			//80016 ͨ���豸:���Ͳ���"(��)
#define ID_STATUS_DVP_MOTORCADE			"017"			//80017 ͨ���豸:����"(��)
#define ID_STATUS_DVP_SIMULATE 			"018"			//80018 ͨ���豸:����ͨ�����ģ��"(��)
#define ID_STATUS_DVP_VIOLATION			"019"			//80019 ͨ���豸:����Υ��ǿ��ͨ��"(��,���°������¼�)
#define ID_STATUS_DVP_CLASSCONFIRM		"021"			//80021 ͨ���豸:����ȷ������"(��)
#define ID_STATUS_DVP_USERHURRY	 		"023"			//80023 ͨ���豸:�û���æ"(��)
#define ID_STATUS_DVP_CHANGE_PARA		"029"			//80029 ͨ���豸:�޸Ĳ���"
#define ID_STATUS_DVP_CHANGE_CONFIG		"030"			//80030 ͨ���豸:�޸�����"
#define ID_STATUS_DVP_LANEOPEN			"031"			//80031 ͨ���豸:������"(��)
#define ID_STATUS_DVP_LANECLOSE			"032"			//80032 ͨ���豸:�����ر�"(��)
#define ID_STATUS_DVP_NOTELECONTROL		"033"			//80033 ͨ���豸:�ܾ�ң��"
#define ID_STATUS_DVP_TESTMODE_START	"034"			//80034 ͨ���豸:����ģʽ��ʼ"(��)
#define ID_STATUS_DVP_TESTMODE_END		"035"			//80035 ͨ���豸:����ģʽ����"(��)
#define ID_STATUS_DVP_COMM65_NORMAL		"036"			//80036 ͨ���豸:������վ���ͨ������"
#define ID_STATUS_DVP_STAFFCSC_CONFUSE	"038"			//80038 ͨ���豸:�ܾ�ְԱ��ݿ�"(��)
#define ID_STATUS_DVP_TCSC_ERR			"045"			//80045 ͨ���豸:ͨ�п�������"
#define ID_STATUS_DVP_PLAZACONFIRM		"053"			//80053 ͨ���豸:���վȷ��"(��)
#define ID_STATUS_DVP_CHANGETYPE		"054"			//80054 ͨ���豸:���ĳ���"(��)
#define ID_STATUS_DVP_CSC_DISAPPEAR		"055"			//80055 ͨ���豸:����һ�μ�⵽���ſ�"
#define ID_STATUS_DVP_OUT_ORDER			"056"			//80056 ͨ���豸:ͨ�п�˳��Ż���"(��)
#define ID_STATUS_DVP_EXTRA_CSC			"057"			//80057 ͨ���豸:���⿨"(��)
#define ID_STATUS_DVP_REPRINT_RECEIPT	"067"			//80067 ͨ���豸:�ش�ӡ��Ʊ"(��)
#define ID_STATUS_DVP_UPDATE_ALLOW		"077"			//80077 ͨ���豸:���������������"
#define ID_STATUS_DVP_PLATE_CONFIRM		"083"			//80083 ͨ���豸:������ĳ��ƺ���λ��"(��)
#define ID_STATUS_DVP_POINTPLATE		"084"			//80084 ͨ���豸:����ĳ��ƺ��з������ַ�������'.'�滻"
#define ID_STATUS_DVP_CONFUSE_LOGIN		"085"			//80085 ͨ���豸:�ܾ���½"
#define ID_STATUS_DVP_WEIGHT_COMMERR	"997"			//80997 ͨ���豸:����ͨѶ����
#define ID_STATUS_DVP_WEIGHT_CLEAR		"998"			//80998 ͨ���豸:��������¼�����������ĳ��޼�����ݣ���ౣ��������Ϣ���䳤��ʽ����������������1λ������������1������1λ������������1���أ�6λ������������n������1λ������������n���أ�6λ����
#define ID_STATUS_DVP_TICKET			"086"			//��Ʊ����

#define ID_STATUS_DVP_WEIGHT			"80999�����¼�"  //80999 ͨ���豸:�����¼�����Ϊ�������ͣ����ڽ�����Ϣ�Ͳ����ڽ�����Ϣ��
//(1) ���ڽ�����Ϣ������21�����ݸ�ʽ�����׺ţ�5λ����˳��ţ�1λ������ڳ�������1λ������ڳ����أ�6λ�������ڳ�������1λ�������ڳ����أ�6λ��������ԭ��1λ����
//(2) �����ڽ�����Ϣ������10�����ݸ�ʽ: ���ƺţ�3λ������ڳ�������1λ������ڳ����أ�6λ�������ڳ�������1λ�������ڳ����أ�6λ��������ԭ��1λ��

/******************************************************************************************************
*վ������
******************************************************************************************************/
#define ID_DEV_PSS						"85"  //վ������    
#define ID_STATUS_PSS_COMMERR			"001"  //85011 ������:ͨ�Ź���"
#define ID_STATUS_PSS_PTERR				"011"  //85011 վ������:���������ʱ����"
#define ID_STATUS_PSS_DATAERR			"012"  //85012 վ������:�����շ�����ʱ����"
#define ID_STATUS_PSS_CLEARERR			"013"  //85013 վ������:���ݿ������������"
#define ID_STATUS_PSS_INIERR	  		"014"  //85014 վ������ϵͳ���ô���"
/******************************************************************************************************
*���ķ�����  
******************************************************************************************************/
#define ID_DEV_CSS             "86"  //���ķ�����  
#define ID_STATUS_CSS_COMMERR 			"001"  //86001 ������:����ͨ�Ź���"
/******************************************************************************************************
*������վ  
******************************************************************************************************/
#define ID_DEV_FSD             "87"  //������վ 
#define ID_STATUS_FSD_TODDIFF			"001"  //87001 ������վ:����ɿ����"
#define ID_STATUS_FSD_CONN_AFTERTOD		"002"  //87002 ������վ:�°������ڽ���ɿ�����"
#define ID_STATUS_FSD_DIFFJOB			"003"  //87003 ������վ:�����Ŀ����"
/******************************************************************************************************
*�����豸  
******************************************************************************************************/
#define ID_DEV_WDS			   "45"  //�����豸
#define  ID_STATUE_WDS_COMMOK			"200"
#define  ID_STATUS_WDS_COMMERR			"201"
#define  ID_STATUS_WDS_OPTERR			"207"
#define  ID_STATUS_WDS_OPTON			"210"
#define  ID_STATUS_WDS_LOOPERR			"211"
#define  ID_STATUS_WDS_WHEELERR			"213"
#define  ID_STATUS_WDS_WEIGHTERR		"214"
#define  ID_STATUS_WEIGHT_CONFIRM		"108"
#define  ID_STATUS_WEIGHT_DIFFERENT		"109"
#define  ID_STATUS_WEIGHT_LOG			"300"
/******************************************************************************************************
*����ʶ��  
******************************************************************************************************/
#define ID_DEV_LPR			   "21"	 //����ʶ��	
#define  ID_STATUS_LPR_COMMERR			"001"



#define		DEVCOMSTATE_CONNECT		1
#define		DEVCOMSTATE_DISCONNECT	0



#define BPLA_OK             1000     //һ������
#define BPLA_COMERROR       1001     //ͨѶ�����δ���Ӵ�ӡ��
#define BPLA_PARAERROR      1002     //��������
#define BPLA_FILEOPENERROR  1003     //�ļ��򿪴���
#define BPLA_FILEREADERROR  1004     //�ļ�������
#define BPLA_FILEWRITEERROR 1005     //�ļ�д����
#define BPLA_FILEERROR      1006     //�ļ�����Ҫ��
#define BPLA_NUMBEROVER     1007     //ָ���Ľ�����Ϣ��������
#define BPLA_IMAGETYPEERROR 1008     //ͼ���ļ���ʽ����ȷ 
#define BPLA_NOPAPER		1009	 //��ӡ��û��ֽ
#define BPLA_NOCHECK        1009     //δ��⣡

void DevComStateSendNORMAL(char *InptNormal);
void DevComStateSendALARM(char *InptALARM);
void DevComStateSendARESUME(char *InptALARM);
 
void SetDevCStatePlazaServerState(int InputDevCStatePlazaServerState);
void ShowDevCStatePlazaServerState(void);
int GetDevCStatePlazaServerState(void);
void SetDevCStateTCOState(int InputDevCStateTCOState);
int GetDevCStateTCOState(void);
void ShowDevCStateTCOState(void);
void SetDevCStatePrinterState (int InputDevCStatePrinterState);
void ShowDevCStatePrinterState(void);
void SetDevCStateCICMState (int InputDevCStateCICMState);
void ShowDevCStateCICMState(void);
int GetDevCStateCICMState(void);
int GetDevCStatePrinterState(void);
void SetDevCStateTFIState (int InputDevCStateTFIState);
void ShowDevCStateTFIState(void);
 
 
 
char *GetDevCStatePrinterState_Str(void);


 

struct DAL_CSC_VAR
{
	BOOL bIsInit;
};
 
//�ⲿ�ú���
int WF_IC_Init(HWND pWnd);//��ʼ��
int  WF_IC_GetCSCType(char *pCardNo);//�õ�������
 void WF_TestICReader(void);
int DAL_CSC_GValueINC(UINT val,UINT* tval);
int DAL_CSC_GValueDEC(UINT val,UINT* tval);
int WF_IC_GOpenCard(void);
int WF_IC_GCloseCard(void);
BOOL  WF_IC_WriteBase(void);
/** 
 * 
 * 
 * 
 * @return int
 */
int WF_IC_TESTIC_STATE(void);
 
BOOL  WF_IC_WriteSVCMoney(  float addnumber );
float WF_IC_ReadSVCMoney( void);
char * ReadStaffCard(void);
#define WRITEMONEY 2
#define READMONEY 3
#endif
