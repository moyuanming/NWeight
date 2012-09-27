#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//�����ϰ��һ������������رղ����շѵ�����
int GetYuPengState(void );
void SetYuPengState(int inputYuPengState);
//������������Ϣ�����־
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
volatile int YaxianquanNum;    //�ϳ�ģ���ʱ������ѹ��Ȧ����
volatile int SynOn;//ͬ������
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
 * Ʊ�ݲ���
 *
 * @author �����
 * @see ����Ʊ�ݴ�Ʊ�Ľṹ��
 */
struct BILLPARAM
{
    char billNumber[40];
    char carType[10];
    char carKind[10];
    char Charge[10];
};

//ѭ����������ʾ������Ϣ
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
	//Ʊ��˿� Ĭ��  4
	char    print_tty[2];
//�ش�Ʊ�ݴ���
	char reprintbillnum[2];
//���Զ˿� Ĭ�� 3
	char    led_tty[2];
	//�������˿� Ĭ��2
	char     csc_tty[20];
	char  CSC_SPEED[20];
	char MaxArrearageNumber[10];
	char IsInPueArrearageCharege[10];

	char GeneralCatTeam[10];
//�Ƿ����÷��Ե����Ա��۹���
	char LedSoundEnabled[10];
	char GoodBeySay[10];
	char HelloEnabled[10];
	char HelloSay[10];

	char SetVolume[10];
	char EnabledLanGanKey[10];
	char EnabledBeiyongKey[10];

	char ISSimulateTwoOkType[5];// 0 ��³�� ��1:˫�԰�

	char OnceOkEnabledCancel[5]; //��һ��ȷ�Ϻ��Ƿ����ȷ��
	char SimulateEnabledCancel[5]; //ģ��״̬�Ƿ����ȡ��
	char SimulateEnabledFistTuoChe[5];//��һ���ϳ����Ƿ����ģ��

	char AbateMaxLengh[5];//�Żݿ���󳤶�
	char MonthCardMaxLengh[5]; //��Ʊ����󳤶�
	char RushCancelTime[5];

	//�����豸
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
