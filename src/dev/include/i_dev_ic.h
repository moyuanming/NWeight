#ifndef __DAL_CSC_DLL_H__
#define __DAL_CSC_DLL_H__

/************************************************************************/
/* 卡动态库 liujl 2008.6.10                                             */
/************************************************************************/
#define WM_USER 0x0400

#define CARDTYPE_0    0
#define CARDTYPE_SVCCard  	  1  //储值卡
#define CARDTYPE_MonthCard    2  //月票卡
#define CARDTYPE_TallyCard    3  //记账卡
#define CARDTYPE_StaffCard 	  4   //身份卡 
#define CARDTYPE_OfficialCard  5  //卡箱标签
#define CARDTYPE_6    6
#define CARDTYPE_7    7
#define CARDTYPE_8    8
#define CARDTYPE_9    9
#define CARDTYPESTR_ //01 

//字符串形式的
#define CARDTYPESTR_SCVCard  	  	"01"  //储值卡
#define CARDTYPESTR_MonthCard    	"02"  //月票卡
#define CARDTYPESTR_TallyCard    	"03"  //记账卡
#define CARDTYPESTR_StaffCard 	  	"04"   //身份卡 
#define CARDTYPESTR_CardBoxCard  	"05"  //卡箱标签
//02  月票卡
//03  记账卡
//04  身份卡
//05  卡箱标签
#define ELESTATUS_UNUSER    "00"  //未制作
#define ELESTATUS_NORMAL  	"01"	//正常
#define ELESTATUS_RECLAIM 	"02"	//回收
#define ELESTATUS_SCRAP 	"03"	//报废
#define ELESTATUS_LOCK 		"04" //	挂失

//Mifare部分常量
#define MIF_NoErr			 0		// = No error OK
#define	MIF_BadParam		 -200
#define	MIF_ErrMemory        -201
#define	MIF_ErrCreateEvent   -202
#define MIF_ErrCreateMutex   -203
#define	MIF_ErrEvent		 -204
#define	MIF_NotActif		 -205
#define	MIF_Busy			 -206
#define	MIF_CommAborted		 -207
#define	MIF_CommTimeout		 -208
#define	MIF_ErrReponse		 -209
#define	MIF_ErrCRC			 -210		// used by function ReadCRC
#define	MIF_CmdInProgress	 -211

#define COMM_BadParam		 -1000
#define	COMM_PortNotActif	 -1001
#define	COMM_PortNotReady	 -1002
#define	COMM_PortOutBusy	 -1003
#define	COMM_ErrCreateBuffer -1004
#define	COMM_ErrCreateEvent	 -1005
#define	COMM_ErrCreateThread -1006
#define	COMM_ErrSetPriority	 -1007
#define	COMM_ErrSetEvent	 -1008
#define	COMM_ErrTypePort	 -1009
#define	COMM_ErrOpenPort	 -1010
#define	COMM_ErrConfigPort	 -1011
#define	COMM_ErrClosePort	 -1012
#define	COMM_ErrReadPort	 -1013
#define	COMM_ErrWritePort	 -1014
#define	COMM_ErrEvent		 -1015


#define MIF_CB_IN            0				// Callback reception of character string (trame)
#define	MIF_CB_ERR           3			// Callback end of transmission of character string


#define MIF_KEYA			0		// key A
#define MIF_KEYB			4		// key B

//沈大测试密钥
#define MIF_SEC1_KEYA        "4C4941474541" //"A0A1A2A3A4A5"
#define MIF_SEC1_KEYB        "393836313635" //"B0B1B2B3B4B5"
#define MIF_SEC2_KEYA        "474541303338" //"A0A1A2A3A4A5"
#define MIF_SEC2_KEYB        "393836313635" //"B0B1B2B3B4B5"
//出厂时的密钥
#define MIF_SEC1_BlankKEYA        "A0A1A2A3A4A5" //"A0A1A2A3A4A5"
#define MIF_SEC1_BlankKEYB        "B0B1B2B3B4B5" //"B0B1B2B3B4B5"
#define MIF_SEC2_BlankKEYA        "A0A1A2A3A4A5" //"A0A1A2A3A4A5"
#define MIF_SEC2_BlankKEYB        "B0B1B2B3B4B5" //"B0B1B2B3B4B5"

#define	MIF_KEYSET0			0		// keyset 0 (practically the only one used)
#define	MIF_KEYSET1			1		// 
#define	MIF_KEYSET2			2		// 
#define MIF_KEYSET3			3		// 

//Blocks and sectors
#define MIF_BLOCK0			0
#define MIF_BLOCK1			1
#define MIF_BLOCK2			2
#define MIF_BLOCK3			3

#define MIF_SECT0			0
#define MIF_SECT1			1
#define MIF_SECT2			2
#define MIF_SECT3			3
#define MIF_SECT4			4
#define MIF_SECT5			5
#define MIF_SECT6			6
#define MIF_SECT7			7
#define MIF_SECT8			8
#define MIF_SECT9			9
#define MIF_SECT10			10
#define MIF_SECT11			11
#define MIF_SECT12			12
#define MIF_SECT13			13
#define MIF_SECT14			14
#define MIF_SECT15			15

#define MIF_REQ_IDLE	    0	// Request only the cards which are activated  (not been put to sleep)
#define MIF_REQ_ALL	        1	// Request all cards (and reactivate the cards which have been put to sleep) 
#define MIF_REQ_ONCE	    0	// Looks only for one card and returns an error if no card is found
#define MIF_REQ_REPEAT      128	// Repeats for ever  until a card is detected

#define MIF_NO_CRC          0   //NO CRC Read or Write Flag
#define MIF_CRC             1   //With CRC Read or Write

#define MIF_NO_SELECTEx     0   //select
#define MIF_SELECTEx        1   //SelectEx
struct ICCARD
{
	char    CardType[ 2];//0 卡类型 
	char    Version [ 2]; //2  卡版本
	char    Network [2]; //4   网号
	char    EnableDate[4];// 6  启用日期 
	char    Validitydate[4]; //  10   失效日期
	char    Code[5];//14     代码
	char    SVCPwsSID[6];//19   SVCPws 储值卡 交易密码  SID 身份卡工号
	char    Reserve[5];//25  保留
	char    CRC[2];//30  crc校验
	//上次交易信息 位于第二块
	struct 
	{
		char Status[2];//30+ 0  状态
		char USERDATE[8];// 30+2  上一次使用日期
		char Netwrok[2];// 30+10;  路网号
		char Plaza[2];// 30+12  站号
		char Lane[4];//30+4 //  车道号 X99
		char StaffId[6];//30+18 工号
		char UserCount[6];//30+24//使用次数
	}LastTranInfo;
	union
	{
//储值卡结构
		struct 
		{
			char Reser0[1];//60+0//
			char Balance[6];//60+1 结余
			char Reser1[3]  ;//60+7 保留位
			char UsedCash[4];//60+10  消费金额
			char Reser2[1];//60+ 14
			char BeforeBalance[6];//60+15 上次结余
			char Reser3[10];//60+21 未使用 
			char CRC2[2];//60+30  
		}  SCVCard ;
//月票卡
		struct 
		{
			char Reser0[1];//保留位置
			char BlanceCount[6]; //60+1  结余刷卡次数 
			char CarID[3];//60+7  最后三位车牌 
			char Reser1[4];	// 60+10  
			char Reser2[1]; // 60+14
			char Count[6];//60+15 标准刷卡次数 
			char CarType[2];//60+21 车型 
			char Reser3[8];//60+23
			char CRC2[2];// 
		} MonthCard ;
//记账卡
		struct 
		{
			char BlanceSign[1];//60+0 
			char Blance[6]; //60+1  结余刷卡次数 
			char CardID[3];//60+7 最后三位车牌 
			char LastPay[4];// 60+10 //上次消费
			char LowerLimitSign[1];//60+14
			char LowerLimit[6];//60+15 
			char CarType[2];//60+21
			char Reser3[8];//60+23 
			char CRC2[2];//  
		}TallyCard ;

//身份卡
		struct 
		{
			char Reser2[30];	// 保留0
			char CRC2[2];//  
		}StaffCard;
	} ;
}; 
int I_DEV_IC_CreateThread(void);
unsigned int  cardNum;
char strCardNo[10];
int I_DEV_IC_Init(HWND pWnd);
void I_DEV_IC_Close(void);
char *Get15File(void);
char *Get16File(void);
int GetCardExist(void );
int I_DEV_IC_ReadByBlock(int block,int keyType,char* data);
int I_DEV_IC_WriteByBlock(int block,int keyType,char* data);
int CSC_DLL_WriteBySector(int sector,int keyType,char* data);
 
int CSC_DLL_GValueCreate(void);
int CSC_DLL_GValueINC(UINT val,UINT* tval);
int CSC_DLL_GValueDEC(UINT val,UINT* tval);
int I_DEV_IC_OpenCard(void);
int I_DEV_IC_CloseCard(void);

char *G_IC_ConvertDateTime(char strCardDate[8]);
char *G_IC_MakeDateTime(char *strCardDate,int iSize);
char *G_IC_MakeDate(char *strCardDate);
char *CSC_DLL_Convert_LaneNo(char *strLaneNo);
char *CSC_DLL_Convert_WriteLaneNO(char *strLaneNo);
void G_IC_itoa(unsigned long val,char *buf,unsigned radix);
 
UINT CSC_DLL_IcCheck(void);//卡的轮检
char * GetHexCardNumber(void);
#endif 

