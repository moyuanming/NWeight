#ifndef _MessageDef_H_
#define _MessageDef_H_



#define MAXMSGBODYLENGTH 32768
#define MSG_HEAD_LENGTH 70
#define ID_MSGEXITBS            'B' //�ϰ���Ϣ


#define ID_MSGEXITHT            'H' //Сʱ��ͨ��
#define ID_MSGEXITES            'E' //�°���Ϣ


#define ID_MSGNEWEXITHT            'X' //Сʱ��ͨ��
#define ID_MSGNEWEXITES            'W' //�°���Ϣ 


#define ID_MSGEXITTR            'T' //������Ϣ
#define ID_MSGEXITVI            'V' //Υ�¼�¼
#define ID_MSGEXITEI            'D' //�����¼
#define ID_MSGEM                'M' //������
#define ID_MSGEI                'I' //������Ϣ
#define ID_MSGGR                'G' //�����
#define ID_MSGOF                'O' //����
#define ID_MSGAK                'A' //�ļ�ȷ��
#define ID_MSG2N                '2'
#define ID_SETEXCEPTION			'F'//�豸�쳣
#define ID_BADBILL              'Z' //��Ʊ��Ϣ
#define ID_TCOMSG               'C' //tco��Ϣ
#define ID_LANEINFO				'L'
#define ID_MSGVIEW				'S'

 
#define  MSGTCO_NETWORK  'W' //�����˷�����
#define MSGTCO_CMD_RETTIME          'A' //Ҫ�󷵻�ʱ��
#define MSGTCO_CMD_PARAMVER          'B' //Ҫ�󷵻��ļ��汾
#define MSGTCO_CMD_PARAMUPDATE          'C' //���ظ������
#define MSGTCO_CMD_BILLNUMBER   'G' //���ظ������
#define MSGTCO_CMD_TCOWAING  'D' //TCO����                                   //
#define MSGTCO_CMD_TCOQUERY  'E' //TCO���� 
#define MSGTCO_CMD_MD5SUMFILE  'F' //TCO����
#define MSGTCO_CMD_TIMESYNC  'G' //TCO����
struct MSG_HEAD
{
    char ID[18];
    char MsgType;
    char LaneType;
    char LaneMode;
    char NetNo[2];
    char PlazaNo[2];
    char Year[4];
    char Day[4];
    char Hour[6];
    char YYYYMMDD[8];
    char YYYYMMDDHHMMSS[14];
    char LaneNo[3];
    char Collector[6];
	char unused[2];
};
struct MSG_HOUR *MsgHour;
//struct MSG_HEAD *MsgHead;
#define MSG_EVENT_LENGHT  81
#define LEN_ID_MSGEXITBS        95
struct MSG_EVENT            //�¼���Ϣ  0x6505
{
    char JobBegin[14];      //��ο�ʼʱ��
    char EventT;            //0:Event 1:alarm occurred 2:alarm recovered
    char DevID[2];          //�豸����
    char EventID[3];        //�¼�����
    char Detail[60];        //�¼�˵��
    char ShiftNo;
};

#define ID_MSGEVENT         "G0"

#define LaneConfig_LENGHT  8
struct LaneConfig
{
    char NetNo[2];
    char PlazaNo[2];
    char LaneType;
    char LaneNo[3];
}  ;
#define TCOMSG_LENGHT  sizeof(struct TCOMSG)
struct TCOMSG
{
	char MsgType;
	char MsgContext[50];
	char MsgTitle[50];
	char MsgImagePath[50];
	char MsgOption1[50];
	char MsgOption2[50];
	char MsgOption3[50];
	char MsgOption4[50];
	char MsgOption5[50];

};
/******************************************************************************************************
* ǰ20λ�洢����Ϣͷ��Ϣ
* 20λ��洢 һЩϵͳ������Ϣ
******************************************************************************************************/
#define MSG_SubHead_LENGHT 20
struct MSG_SubHead
{
    char LaneMode;          //����״̬ 0-�ر� 1-Ӫ�� 3-ģ�� 4-����(����: 2-�� 5-����)
    char CETC;              //ETC״̬
    char StaffID[6];        //ְԱID
    char StaffName[8];      //ְԱ����
    char JobNo[2];          //���ID
    char SquadID;
    char ShiftNo;
    char TFITextIndex[3];
    char ImageIndex[4];
};

struct MSG_HOUR
{
    char HourTime[10];
    char tmGreen[10];
};
void InitMsgHour(void);
void LoadMsgHour(void);
void AddMsgHourtmGreene(void);
#endif
