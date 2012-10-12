#ifndef		DEVCE_H
#define		DEVCE_H
 //定义模块连接的串口
//金额显示器串口号
#define LED_COM         (Get_LEDCOM())

/*票据打印机串口号*/
#define PRINTER_COM		(Get_PrintCOM())
  
int serial_read(int nCOM,unsigned char *byReadBuf,int nReadLen);
int serial_write(int nCOM,unsigned char *byWriteBuf,int nWriteLen);

int serial_init(int nCOM, int nBaud);
 
#define IMG_FIRST  '1' //第一张图片
#define IMG_SECOND  '2' //第二张图片

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
void ShowCarType(char ct);
void Showcharge(int ct);
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

//读卡器串口
#define SERIAL_CSC_ID    GetCSCCOM( )
 
//读卡器波特率
#define SERIAL_CSC_SPEED  atoi(GetSysConfig( )->CSC_SPEED)
#define MSG_CRADENENT		(MSG_USER+14)
 
#define CSC_CARDENTER					1201  //卡进入读卡器可读范围
#define CSC_CARDEXIT					1202  //卡退出了读卡器可读范围





/******************************************************************************************************
*发送事件类型
******************************************************************************************************/
#define  EVENT_TYPE_NORMAL				'2'		//发送普通事件消息
#define  EVENT_TYPE_ALARM				'1'		//发送报警事件消息
#define  EVENT_TYPE_RESUME				'0'		//发送报警恢复事件消息
/******************************************************************************************************
*车道控制器 
******************************************************************************************************/
#define ID_DEV_LCL						"01"  //车道控制器 
#define ID_STATUS_LCL_COMMERR 			"001"  //01001 车道控制器:通信故障" 
#define ID_STATUS_LCL_INI 				"002"  //01002 车道控制器:计算机初始化"
#define ID_STATUS_LCL_DISKFULL 	 		"003"  //01003 车道控制器:车道计算机硬盘将满"
/******************************************************************************************************
*连接板   (有)
******************************************************************************************************/
#define ID_DEV_CXP						"02"							//连接板   (有)   
#define ID_STATUS_CXP_COMMERR			"02001通信故障"					//02001 连接板:通信故障"(有)
#define ID_STATUS_CXP_PALERR 			"02003通道线圈故障"				//02003 连接板:通道线圈故障"(有,长激励)
#define ID_STATUS_CXP_PRLERR			"02004到达线圈"					//02004 连接板:到达线圈故障"

/******************************************************************************************************
*收费员操作台
******************************************************************************************************/
#define ID_DEV_SFC						"03"							//收费员操作台
#define ID_STATUS_SFC_COMMERR 			"03001通信故障"					//03001 收费员操作台:通信故障"
/******************************************************************************************************
*票据打印机
******************************************************************************************************/
#define ID_DEV_DCP						"09"							//票据打印机  (有)
#define ID_STATUS_DCP_COMMERR 			"001"							//09001 票据打印机:通信故障"(有)
#define ID_STATUS_DCP_BLANK				"007"							//09007 票据打印机:打印机缺纸"(有)
/******************************************************************************************************
*费额显示器  
******************************************************************************************************/
#define ID_DEV_TFI						"11"							//费额显示器  
#define ID_STATUS_TFI_COMMERR 			"001"			//11001 费额显示器:通信故障"
/******************************************************************************************************
*脚踩开关
******************************************************************************************************/
#define ID_DEV_FSW						"33"							//脚踩开关    (有)
#define ID_STATUS_FSW_ACTIVE			"33008脚踩开关激活"				//33008 脚踩开关:激活"(有,手动报警器)
/******************************************************************************************************
*脚踩开关
******************************************************************************************************/
#define ID_DEV_CSC						"35"			//IC卡读写天线(有)
#define ID_STATUS_CSC_COMMERR 			"001IC"			//35001 IC卡读写天线:收发卡机天线通信故障"
#define ID_STATUS_CSC_WRITEERR			"002IC"			//35002 IC卡读写天线:收发卡机天线写故障"(有)
#define ID_STATUS_CSC_WRITECOMMERR		"003IC"			//35003 IC卡读写天线:收发卡机天线写和通信错误"
/******************************************************************************************************
*收发卡机
******************************************************************************************************/
#define ID_DEV_CICM						"38"		//收发卡机    (有)
#define ID_STATUS_CICM_COMMERR 	 		"001"		//38001 收发卡机:收发卡机通信故障"
#define ID_STATUS_CICM_CHANGE			"003"		//38003 收发卡机:更换卡箱"(有)
#define ID_STATUS_CICM_WILLEMPTY		"005"		//38005 收发卡机:入口车道卡箱将空"(有)
#define ID_STATUS_CICM_EMPTY			"006"		//38006 收发卡机:入口车道卡箱空"(有)
#define ID_STATUS_CICM_WILLFULL	 		"007"		//38007 收发卡机:出口车道卡箱将满"(有)
#define ID_STATUS_CICM_FULL				"008"		//38008 收发卡机:出口车道卡箱满"(有)
#define ID_STATUS_CICM_FORCED_CTID		"012"		//38012 收发卡机:强行取出卡箱：卡箱标签问题"(有)
#define ID_STATUS_CICM_FORCED_CT 		"013"		//38013 收发卡机:强行取出卡箱：箱内卡有问题"(有)
#define ID_STATUS_CICM_COVEROPEN 		"014"		//38014 收发卡机:打开收发卡机保护盖"(有)
#define ID_STATUS_CICM_COVEROPENSP		"015"		//38015 收发卡机:例外打开收发卡机保护盖"
#define ID_STATUS_CICM_NOCART			"016"		//38016 收发卡机:无卡箱"(有)
/******************************************************************************************************
*参数表
SendMsgEvent(EVENT_TYPE_NORMAL,ID_DEV_PTFARE,,"");
SendMsgEvent(EVENT_TYPE_RESUME,ID_DEV_PTFARE,,"");
SendMsgEvent(EVENT_TYPE_ALARM,ID_DEV_PTFARE,,"");
******************************************************************************************************/
#define ID_DEV_PTFARE          "50"  //费率表      
#define ID_DEV_PTJOUR          "51"  //行程时间表  
#define ID_DEV_PTSTAFF         "56"  //授权职员表  
#define ID_DEV_PTBSTAF         "57"  //身份卡黑名单
#define ID_DEV_PTBSEVR         "58"  //公务卡黑名单
#define ID_DEV_PTBSVC          "59"  //储值卡黑名单
#define ID_DEV_PTCONST         "60"  //常数表      
#define ID_DEV_PTIMG           "62"  //图像参数表  
#define ID_DEV_PTL             "63"  //使用级别表  
#define ID_DEV_PTS             "64"  //合法公务卡表
#define ID_DEV_PTP             "70"  //通用参数表 
#define ID_STATUS_PARATAB_READERR 		"001"  //XX001 参数表:参数表读取错误"
#define ID_STATUS_PARATAB_HEADERR		"002"  //XX002 参数表:参数表表头错误"
#define ID_STATUS_PARATAB_TYPEERR		"003"  //XX003 参数表:参数表类型错误"
#define ID_STATUS_PARATAB_NETNOERR		"004"  //XX004 参数表:网络代码错误"
#define ID_STATUS_PARATAB_PLAZANOERR	"005"  //XX005 参数表:站代码错误"
#define ID_STATUS_PARATAB_VERNOERR		"006"  //XX006 参数表:版本号错误"
#define ID_STATUS_PARATAB_SIZEERR		"007"  //XX007 参数表:记录尺寸错误"
#define ID_STATUS_PARATAB_NUMERR		"008"  //XX008 参数表:记录数目错误"
#define ID_STATUS_PARPLATE_BLACKLIST	"110"
/******************************************************************************************************
*通用设备
SendMsgEvent(EVENT_TYPE_NORMAL,ID_DEV_DVP,,"");
SendMsgEvent(EVENT_TYPE_RESUME,ID_DEV_DVP,,"");
SendMsgEvent(EVENT_TYPE_ALARM,ID_DEV_DVP,,"");
******************************************************************************************************/
#define ID_DEV_DVP						"80"							//通用设备   (有) 
#define ID_STATUS_DVP_MLBOPEN 			"009"			//80009 通用设备:打开车道手动栏杆"(有)
#define ID_STATUS_DVP_MLBCLOSE			"010"			//80010 通用设备:关闭车道手动栏杆"(有)
#define ID_STATUS_DVP_CSLRED			"013"			//80013 通用设备:雨棚信号灯红色"(有)
#define ID_STATUS_DVP_CSLGREEN			"014"			//80014 通用设备:雨棚信号灯绿色"(有)
#define ID_STATUS_DVP_REVERSING			"015"			//80015 通用设备:倒车"(有)
#define ID_STATUS_DVP_DIFFCLASS			"016"			//80016 通用设备:车型差异"(有)
#define ID_STATUS_DVP_MOTORCADE			"017"			//80017 通用设备:车队"(有)
#define ID_STATUS_DVP_SIMULATE 			"018"			//80018 通用设备:车辆通行情况模拟"(有)
#define ID_STATUS_DVP_VIOLATION			"019"			//80019 通用设备:车辆违章强行通过"(有,上下班两个事件)
#define ID_STATUS_DVP_CLASSCONFIRM		"021"			//80021 通用设备:重新确定车型"(有)
#define ID_STATUS_DVP_USERHURRY	 		"023"			//80023 通用设备:用户匆忙"(有)
#define ID_STATUS_DVP_CHANGE_PARA		"029"			//80029 通用设备:修改参数"
#define ID_STATUS_DVP_CHANGE_CONFIG		"030"			//80030 通用设备:修改配置"
#define ID_STATUS_DVP_LANEOPEN			"031"			//80031 通用设备:车道打开"(有)
#define ID_STATUS_DVP_LANECLOSE			"032"			//80032 通用设备:车道关闭"(有)
#define ID_STATUS_DVP_NOTELECONTROL		"033"			//80033 通用设备:拒绝遥控"
#define ID_STATUS_DVP_TESTMODE_START	"034"			//80034 通用设备:测试模式开始"(有)
#define ID_STATUS_DVP_TESTMODE_END		"035"			//80035 通用设备:测试模式结束"(有)
#define ID_STATUS_DVP_COMM65_NORMAL		"036"			//80036 通用设备:车道和站间的通信正常"
#define ID_STATUS_DVP_STAFFCSC_CONFUSE	"038"			//80038 通用设备:拒绝职员身份卡"(有)
#define ID_STATUS_DVP_TCSC_ERR			"045"			//80045 通用设备:通行卡有问题"
#define ID_STATUS_DVP_PLAZACONFIRM		"053"			//80053 通用设备:入口站确认"(有)
#define ID_STATUS_DVP_CHANGETYPE		"054"			//80054 通用设备:更改车种"(有)
#define ID_STATUS_DVP_CSC_DISAPPEAR		"055"			//80055 通用设备:卡机一次检测到多张卡"
#define ID_STATUS_DVP_OUT_ORDER			"056"			//80056 通用设备:通行卡顺序号混乱"(有)
#define ID_STATUS_DVP_EXTRA_CSC			"057"			//80057 通用设备:额外卡"(有)
#define ID_STATUS_DVP_REPRINT_RECEIPT	"067"			//80067 通用设备:重打印发票"(有)
#define ID_STATUS_DVP_UPDATE_ALLOW		"077"			//80077 通用设备:接受软件升级请求"
#define ID_STATUS_DVP_PLATE_CONFIRM		"083"			//80083 通用设备:新输入的车牌后三位号"(有)
#define ID_STATUS_DVP_POINTPLATE		"084"			//80084 通用设备:输入的车牌号有非数字字符并都被'.'替换"
#define ID_STATUS_DVP_CONFUSE_LOGIN		"085"			//80085 通用设备:拒绝登陆"
#define ID_STATUS_DVP_WEIGHT_COMMERR	"997"			//80997 通用设备:超限通讯故障
#define ID_STATUS_DVP_WEIGHT_CLEAR		"998"			//80998 通用设备:超限清除事件，保存清除的超限检测数据，最多保存三笔信息，变长格式：超限数据数量（1位）＋超限数据1轴数（1位）＋超限数据1车重（6位）＋超限数据n轴数（1位）＋超限数据n车重（6位）。
#define ID_STATUS_DVP_TICKET			"086"			//补票操作

#define ID_STATUS_DVP_WEIGHT			"80999超限事件"  //80999 通用设备:超限事件，分为两种类型：存在交易信息和不存在交易信息。
//(1) 存在交易信息。定长21。数据格式：交易号（5位）＋顺序号（1位）＋入口车轴数（1位）＋入口车总重（6位）＋出口车轴数（1位）＋出口车总重（6位）＋超限原因（1位）。
//(2) 不存在交易信息。定长10。数据格式: 车牌号（3位）＋入口车轴数（1位）＋入口车总重（6位）＋出口车轴数（1位）＋出口车总重（6位）＋超限原因（1位）

/******************************************************************************************************
*站服务器
******************************************************************************************************/
#define ID_DEV_PSS						"85"  //站服务器    
#define ID_STATUS_PSS_COMMERR			"001"  //85011 服务器:通信故障"
#define ID_STATUS_PSS_PTERR				"011"  //85011 站服务器:载入参数表时出错"
#define ID_STATUS_PSS_DATAERR			"012"  //85012 站服务器:载入收费数据时出错"
#define ID_STATUS_PSS_CLEARERR			"013"  //85013 站服务器:数据库数据清除出错"
#define ID_STATUS_PSS_INIERR	  		"014"  //85014 站服务器系统配置错误"
/******************************************************************************************************
*中心服务器  
******************************************************************************************************/
#define ID_DEV_CSS             "86"  //中心服务器  
#define ID_STATUS_CSS_COMMERR 			"001"  //86001 服务器:中心通信故障"
/******************************************************************************************************
*财务工作站  
******************************************************************************************************/
#define ID_DEV_FSD             "87"  //财务工作站 
#define ID_STATUS_FSD_TODDIFF			"001"  //87001 财务工作站:交班缴款差异"
#define ID_STATUS_FSD_CONN_AFTERTOD		"002"  //87002 财务工作站:下班联机在交班缴款后进行"
#define ID_STATUS_FSD_DIFFJOB			"003"  //87003 财务工作站:班次数目差异"
/******************************************************************************************************
*计重设备  
******************************************************************************************************/
#define ID_DEV_WDS			   "45"  //计重设备
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
*车牌识别  
******************************************************************************************************/
#define ID_DEV_LPR			   "21"	 //车牌识别	
#define  ID_STATUS_LPR_COMMERR			"001"



#define		DEVCOMSTATE_CONNECT		1
#define		DEVCOMSTATE_DISCONNECT	0



#define BPLA_OK             1000     //一切正常
#define BPLA_COMERROR       1001     //通讯错或者未联接打印机
#define BPLA_PARAERROR      1002     //参数错误
#define BPLA_FILEOPENERROR  1003     //文件打开错误
#define BPLA_FILEREADERROR  1004     //文件读错误
#define BPLA_FILEWRITEERROR 1005     //文件写错误
#define BPLA_FILEERROR      1006     //文件不合要求
#define BPLA_NUMBEROVER     1007     //指定的接收信息数量过大
#define BPLA_IMAGETYPEERROR 1008     //图象文件格式不正确 
#define BPLA_NOPAPER		1009	 //打印机没有纸
#define BPLA_NOCHECK        1009     //未检测！

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
 
//外部用函数
int WF_IC_Init(HWND pWnd);//初始化
int  WF_IC_GetCSCType(char *pCardNo);//得到卡类型
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
