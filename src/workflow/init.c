

#include "LocalIncludeFile.h"
#include "MemSyncFile.h"
#define AT91_SET 1
#define AT91_CLEAR 2
#define AT91_READ 3
#define AT91_INIT_IN 4
#define AT91_INIT_OUT 5
#define AT91_RESET 6
void wds_Destroy_SEM(void);
static void I_DEV_Weight_Init(void)
{
	int fd = Serial_Open(GetWeightCOMStr(),Get_WeightCOMSpeed());
	Wds_Run(fd);
}
static void Init_DevInit(void)
{	
	echoic("初始化IO板");
	I_DEV_IOBoard_Init();
	echoic("初始化票打");
	I_DEV_Printer_Init();
	echoic("初始化费显");
	I_DEV_LED_Init();
	echoic("初始化费显");
	if (EnabledVideo())
	{
		echoic("启用了摄像机，开始初始化");
		Create_camera();
	}
	if (EnabledWeight() && UI_DISPLAY_RESOLUTION == DISPPLAY_800_600)
	{
		echoic("启用了记重设备，开始初始化");
		I_DEV_Weight_Init();
		echoic("启用了记重设备，初始化完成");
	}
	if (TRUE == GetEnableIC())
	{
		echoic("启用了IC卡,开始初始化...");
		SyncToDo("SYNCREMOTE");
		WF_IC_Init(UI_Get_From_Handl());
	}
	if (TRUE==EnabledCPSB())
	{
		 CPSB_Load();
	}
	SetCloseDev();
	echoic("设备就绪");
}
static void Init_SEM(void)
{	
	sem_init(&Device_semt,0,0); 
	wds_Init_SEM();
	InitImgSync();
	PostImgSync();
	postLogcSync();	
}
static void Init_Config(void)
{
	LoadAppFunction();
	LoadCommunctionConfig();
	LoadGetParameterFileList();	
	LoadLanConfig();
	read_sys_ini_file();
	InitKeyBoard_KeyMap(); 
	LoadTTyConfig();
}
static void Init_Parameter(void)
{
	InitMsgRevision();
	LoadCurrentUseParameterVersionNumber();
	LoadParameter(ISLOADFIRST);	
	LoadLanKey();

}
static void Init_MsgThread(void)
{

	DB_Init();	
	Init_UDP_Socket();
	Init_TCP_Socket();
}
static void Init_Message(void)
{
	LoadMemSyncFile();
	InitMsgMsgGR();	
	InitMsgExitTR();	
	InitMsgExitBS();
	ReadBillNumber();	
}
//系统初始化
void init(void)
{	
	Init_SEM();
	Init_Config();
	Init_MsgThread();
	Init_Parameter();
	Init_DevInit();
	Init_Message();
    setLed();	
    SetWorkState( 0);	
	Setg_CurrentLaneState(10);	
    SendTCOMsg(MSGTCO_CMD_RETTIME, "");	//请求时间
    SendTCOMsg(MSGTCO_CMD_BILLNUMBER,"");	//请求票据号。CheckBilNumber用来决定是否使用服务器指定的票据号码
	SynOn=1;
	LedClare(F);
	echoic("测试费率 50 4 ：=<%d>",FareForTrucks(95,5,GetTollFareDistance()));
	echoic("测试费率 车型%d 费额 %d",1,GetFareValue(1));
}



void system_close(void)
{	
   I_DEV_LED_Close();
    I_DEV_Printer_Close();
    sem_destroy(&Device_semt);
	CarListDestroy();
	UI_Destroy_SEM();
	wds_Destroy_SEM();
		CPSB_UnLoad();
    return;
}

void readItemInsysConfigFile(char *SystemFile,char *ItemName ,char *ItemValue)
{	
    char *ini_addr_ptr;
    int len;
    ini_addr_ptr = strstr(SystemFile,ItemName);	
    ini_addr_ptr = strchr(ini_addr_ptr,'<')+1;
    len=strchr(ini_addr_ptr,'>')-ini_addr_ptr;
    strncpy(ItemValue,ini_addr_ptr,len);	
}


void read_sys_ini_file(void)
{	
    char read_ini_ptr[MAXSYSINI];
    int sysinifd;
    echoic("正在装载配置杂项...");
    memset(&sys_ini,0x00,sizeof(sys_ini));	
    sysinifd=open(LANEOLDCONFIG_FILE,O_RDONLY);	
    if(sysinifd<0)
    {	
        exit(0);	
    }
    lseek(sysinifd,SEEK_SET,0);	
    if(read(sysinifd,read_ini_ptr,MAXSYSINI)<0)
    {	
        close(sysinifd);	
        exit(0);	
    }
    close(sysinifd);	
    
    //[Simulate]
    readItemInsysConfigFile(read_ini_ptr,"SimulateEnabledCancel",sys_ini.SimulateEnabledCancel);	
    readItemInsysConfigFile(read_ini_ptr,"SimulateEnabledFistTuoChe",sys_ini.SimulateEnabledFistTuoChe);	



    //[ArrearageHand]
    readItemInsysConfigFile(read_ini_ptr,"MaxArrearageNumber",sys_ini.MaxArrearageNumber);	
    readItemInsysConfigFile(read_ini_ptr,"IsInPueArrearageCharege",sys_ini.IsInPueArrearageCharege);	

    //[CardMaxLengh]
    readItemInsysConfigFile(read_ini_ptr,"AbateMaxLengh",sys_ini.AbateMaxLengh);	
    readItemInsysConfigFile(read_ini_ptr,"MonthCardMaxLengh",sys_ini.MonthCardMaxLengh);	

    //[OnceOK]
    readItemInsysConfigFile(read_ini_ptr,"OnceOkEnabledCancel",sys_ini.OnceOkEnabledCancel);	

    //[ProFunction]	
    readItemInsysConfigFile(read_ini_ptr,"EnabledLanGanKey",sys_ini.EnabledLanGanKey);	
    readItemInsysConfigFile(read_ini_ptr,"RushCancelTime",sys_ini.RushCancelTime);	

    //[LedFunction]
    readItemInsysConfigFile(read_ini_ptr,"LedSoundEnabled",sys_ini.LedSoundEnabled);	
    readItemInsysConfigFile(read_ini_ptr,"GoodBeySay",sys_ini.GoodBeySay);	
    readItemInsysConfigFile(read_ini_ptr,"HelloEnabled",sys_ini.HelloEnabled);	
    readItemInsysConfigFile(read_ini_ptr,"HelloSay",sys_ini.HelloSay);	
    readItemInsysConfigFile(read_ini_ptr,"SetVolume",sys_ini.SetVolume);	
  
	//[print]
	readItemInsysConfigFile(read_ini_ptr,"reprintbillnum",sys_ini.reprintbillnum);  

	//[Led]
	readItemInsysConfigFile(read_ini_ptr,"led_tty",sys_ini.led_tty);    
	//ic卡
	readItemInsysConfigFile(read_ini_ptr,"csc_tty",sys_ini.csc_tty); 
	readItemInsysConfigFile(read_ini_ptr,"CSC_SPEED",sys_ini.CSC_SPEED);    
	//[weight]
	readItemInsysConfigFile(read_ini_ptr,"weight_tty",sys_ini.weight_tty); 
	readItemInsysConfigFile(read_ini_ptr,"weight_speed",sys_ini.weight_speed);   

	echoic("装载配置杂项完成");
}

char var_csccom[20];
char* GetCSCCOM(void)
{
	memset(var_csccom,0x00,20);
	sprintf(var_csccom,"/dev/COM%d",atoi(sys_ini.csc_tty));	
	echoic("IC卡串口:Com%d  速率 %s",atoi(sys_ini.csc_tty), (sys_ini.CSC_SPEED));
	return var_csccom;
}
char var_weightcom[80];
char * GetWeightCOMStr(void)
{
	memset(var_weightcom,0x00,80);
	sprintf(var_weightcom,"/dev/COM%d",Get_WeightCOM());	
	echoic("计重设备串口:Com%d  速率 %d",Get_WeightCOM(), Get_WeightCOMSpeed());
	return var_weightcom;
}
//获得设备配置信息和一些业务配置信息
 struct  sys_ini_t *  GetSysConfig(void)
{
	return &sys_ini ;
}
