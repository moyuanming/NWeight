#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//处理上班后按一下雨棚灯立即关闭不能收费的问题
int GetYuPengState(void );
void SetYuPengState(int inputYuPengState);
//帮助窗口有信息输入标志
extern volatile int g_nHelpTimer;
extern volatile int g_TranNo;


#define T TRUE
#define F FALSE

#define INFORMATION_NODE_LEN sizeof (struct Information_Node)

int GetbillCount(void);
void SetbillCount(int inputbillCount);

int Getg_bWeiZhangCount(void);
void Setg_bWeiZhangCount(int inputg_bWeiZhangCount);
void AutoManHandl(void);
volatile int YaxianquanNum;    //拖车模拟的时候连续压线圈次数
volatile int SynOn;//同步开关
volatile int wzCarType;

//---------------------------------------------------------------------------


struct currentSystemdevStatus
{
    int YuPeng;
    int LanGan;
    int JIaoTong;
    int PrintStatus;
    int ZhuaPaiLine;
    int TongGuoLine;
    int Ring;
};

/**
 * 票据参数
 *
 * @author 马燕洪
 * @see 用于票据打票的结构。
 */
struct BILLPARAM
{
    char billNumber[40];
    char carType[10];
    char carKind[10];
    char Charge[10];
};

//循环连表来显示过车信息
struct Information_Node
{
    char Car_Type[20];
    char Car_Kind[20];
    char Car_Team[9];
    float  Charge;
    struct Information_Node *Next;
    struct Information_Node *Back;
};

struct Led_protocol
{
    unsigned char ShowChargeAndSound[9];
    unsigned char ShowChargeNotSound[9];
    unsigned char ClearAndSound[4];
    unsigned char ClearNotSound[4];
    unsigned char Hello[4];
    unsigned char Thanks[4];
    unsigned char WelCome[4];
    unsigned char ItEasy[4];
    unsigned char PleGo[4];
    unsigned char Go[4];
    unsigned char GoodBye[4];

    unsigned char SoundStart[4];
    unsigned char soundEnd[4];
};


struct  currentSystemdevStatus G_CurrentSystemDevStatus;
struct  Information_Node  *G_Head_Information_Node;
struct  BILLPARAM g_currentPrint;

sem_t ftp_semt,Device_semt,MSG_Node_sem;

struct sys_ini_t
{
	//票打端口 默认  4
	char    print_tty[2];
//重打票据次数
	char reprintbillnum[2];
//费显端口 默认 3
	char    led_tty[2];
	//读卡器端口 默认2
	char     csc_tty[20];
	char  CSC_SPEED[20];
	char MaxArrearageNumber[10];
	char IsInPueArrearageCharege[10];

	char GeneralCatTeam[10];
//是否启用费显的语言报价功能
	char LedSoundEnabled[10];
	char GoodBeySay[10];
	char HelloEnabled[10];
	char HelloSay[10];

	char SetVolume[10];
	char EnabledLanGanKey[10];
	char EnabledBeiyongKey[10];

	char ISSimulateTwoOkType[5];// 0 吐鲁番 ，1:双涝坝

	char OnceOkEnabledCancel[5]; //第一次确认后是否可以确认
	char SimulateEnabledCancel[5]; //模拟状态是否可以取消
	char SimulateEnabledFistTuoChe[5];//第一个拖车后是否可以模拟

	char AbateMaxLengh[5];//优惠卡最大长度
	char MonthCardMaxLengh[5]; //月票卡最大长度
	char RushCancelTime[5];

	//计重设备
	char     weight_tty[20];
	char  weight_speed[20];
};
int Getg_tuocheNum(void);
void Initg_tuocheNum(void);
void Addg_tuocheNum(void);
int GetSubTransNo(void);
void AddSubTransNo(void);
void InitSubTransNo(void);
int GlobalFunc_atoi(char *str, int len);
int getmin(int a,int b) ;
#endif
