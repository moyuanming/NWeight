#ifndef _MessageDef_H_
#define _MessageDef_H_



#define MAXMSGBODYLENGTH 32768
#define MSG_HEAD_LENGTH 70
#define ID_MSGEXITBS            'B' //上班消息


#define ID_MSGEXITHT            'H' //小时交通量
#define ID_MSGEXITES            'E' //下班消息


#define ID_MSGNEWEXITHT            'X' //小时交通量
#define ID_MSGNEWEXITES            'W' //下班消息 


#define ID_MSGEXITTR            'T' //过车消息
#define ID_MSGEXITVI            'V' //违章记录
#define ID_MSGEXITEI            'D' //例外记录
#define ID_MSGEM                'M' //紧急车
#define ID_MSGEI                'I' //例外信息
#define ID_MSGGR                'G' //顶棚灯
#define ID_MSGOF                'O' //公务车
#define ID_MSGAK                'A' //文件确认
#define ID_MSG2N                '2'
#define ID_SETEXCEPTION			'F'//设备异常
#define ID_BADBILL              'Z' //坏票消息
#define ID_TCOMSG               'C' //tco消息
#define ID_LANEINFO				'L'
#define ID_MSGVIEW				'S'

 
#define  MSGTCO_NETWORK  'W' //链接了服务器
#define MSGTCO_CMD_RETTIME          'A' //要求返回时间
#define MSGTCO_CMD_PARAMVER          'B' //要求返回文件版本
#define MSGTCO_CMD_PARAMUPDATE          'C' //返回更新情况
#define MSGTCO_CMD_BILLNUMBER   'G' //返回更新情况
#define MSGTCO_CMD_TCOWAING  'D' //TCO警告                                   //
#define MSGTCO_CMD_TCOQUERY  'E' //TCO警告 
#define MSGTCO_CMD_MD5SUMFILE  'F' //TCO警告
#define MSGTCO_CMD_TIMESYNC  'G' //TCO警告
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
struct MSG_EVENT            //事件消息  0x6505
{
    char JobBegin[14];      //班次开始时间
    char EventT;            //0:Event 1:alarm occurred 2:alarm recovered
    char DevID[2];          //设备代码
    char EventID[3];        //事件代码
    char Detail[60];        //事件说明
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
* 前20位存储子消息头消息
* 20位后存储 一些系统环境信息
******************************************************************************************************/
#define MSG_SubHead_LENGHT 20
struct MSG_SubHead
{
    char LaneMode;          //车道状态 0-关闭 1-营运 3-模拟 4-测试(保留: 2-无 5-设置)
    char CETC;              //ETC状态
    char StaffID[6];        //职员ID
    char StaffName[8];      //职员名称
    char JobNo[2];          //班次ID
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
