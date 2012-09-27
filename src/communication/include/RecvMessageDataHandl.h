#ifndef _RecvMessageDataHandl_H_
#define _RecvMessageDataHandl_H_
#define TCOCMD_RETURNDATETIME      "RETNOWTIME"//服务端要求立刻返回时间
#define TCOCMD_NOWSYNTIME            "NOWSYNTIME"//服务端要求立刻同步时间
#define TCOCMD_RETURNPARAMVER    "RETPARMVER"//服务端要求返回参数版本号
#define TCOCMD_NOWUPDATEPARAM   "PARMUPDATE"//要求客户端立刻更新参数
#define TCOCMD_TCOSTARTED            "TCOSTARTED"//TCO已启动
#define TCOCMD_TCODOWN                 "TCODOWN"//guaji 
#define TCOCMD_BILLNUMBER                  "BILLNUMBER" //发送票据号码
#define TCOCMD_REMOTCOMD                  "REMOTCOMD" //发送票据号码
#define TCOTYPE_TCOCMD   "00" //命令
#define TCOTYPE_TCORET    "01" //
struct MSG_TCOCMD
{
	char TCOType[2];
	char NetNo[2];
	char PlazaNo[2];
	char LaneType;
	char LaneNo[3];
	char CMD[10];
	char Param[100];
};
 
struct MSG_TCOCMD *GetMsgTcoCommand(void);
void RecvMsgDataHandl(unsigned char * InputRevbData);
void ExecTCOCommand(  const char *  InputRevbData);
void CheckBilNumber(void );
void InitMsgTcoCommand(void);
int GetParamIsOK(void);
void SetParamIsOK(int ok);
#endif



