//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _ExitBS_H_
#define _ExitBS_H_
struct MSG_EXITBS
{
      char collectortype;
      char WorkStatus;
      char  ICBox[4];
      char  TotalTraffic[10];
      char BeginSTicketNo[8];
      char MARK;
};//endstructExitBS
#define  LENGHT_MSG_EXITBS 95
#define  COLLECTORTYPE_CONLLECTOR '1'//�շ�Ա
#define  COLLECTORTYPE_VINDICATOR  '2'// ά��Ա
#define  WORKSTAUS_NORMAL  '1'//�����շ�
#define  WORKSTAUS_SIMULATRO '2'//ģ���շ�
#define WORKSTAUS_SETTEST '3'//�豸����
#define WORKSTAUS_EXPORTDATA '4'//��������
#define WORKSTAUS_XIABAN	'0'


void   InitMsgExitBS(void);
struct MSG_EXITBS *GetMsgExitBS(void);
void SetExitBSMsgcollectortype(char Inputcollectortype);
void SetExitBSMsgWorkStatus(char InputWorkStatus);
void SetExitBSMsgICBox(char* InputICBox);
void AddTotalTraffic(void);
void SetExitBSMsgBeginSTicketNo(char* InputBeginSTicketNo);
void SetExitBSMsgMARK(char InputMARK);
 char * GetUpdatedLoginTime(BOOL bEmpty);
#endif 

