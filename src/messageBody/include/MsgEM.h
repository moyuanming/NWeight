//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _MsgEM_H_
#define _MsgEM_H_
struct MSG_MSGEM
{
      char DetectorError;
      char MARK;
};//endstructMsgEM
#define  LENGHT_MSG_MSGEM 2
/********************************************************************************************************************
*����������MsgEM ��Ϣ��Ҫ�õı���
*********************************************************************************************************************/
#define  MSGEM_DETECTORERROR        "1"  // �������������ʱ�������˼�ǿ�����ʱ��Ϊ1

#define MSGEM_BOOL_TURE  '1'
#define MSGEM_BOOL_FALSE '0'
void InitMsgMsgEM(void);
struct MSG_MSGEM *GetMsgMsgEM(void);
void SetMsgEMMsgDetectorError(char InputDetectorError);
void SetMsgEMMsgMARK(char InputMARK);
#endif //define t_tablename

