#ifndef _RecvMessageDataHandl_H_
#define _RecvMessageDataHandl_H_
#define TCOCMD_RETURNDATETIME      "RETNOWTIME"//�����Ҫ�����̷���ʱ��
#define TCOCMD_NOWSYNTIME            "NOWSYNTIME"//�����Ҫ������ͬ��ʱ��
#define TCOCMD_RETURNPARAMVER    "RETPARMVER"//�����Ҫ�󷵻ز����汾��
#define TCOCMD_NOWUPDATEPARAM   "PARMUPDATE"//Ҫ��ͻ������̸��²���
#define TCOCMD_TCOSTARTED            "TCOSTARTED"//TCO������
#define TCOCMD_TCODOWN                 "TCODOWN"//guaji 
#define TCOCMD_BILLNUMBER                  "BILLNUMBER" //����Ʊ�ݺ���
#define TCOCMD_REMOTCOMD                  "REMOTCOMD" //����Ʊ�ݺ���
#define TCOTYPE_TCOCMD   "00" //����
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



