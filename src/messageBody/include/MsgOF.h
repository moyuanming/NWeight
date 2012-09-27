//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _MsgOF_H_
#define _MsgOF_H_
#define  LENGHT_MSG_MSGOF 19
struct MSG_MSGOF
{
      char FLAG;
      char BeginTime[14];
      char VehicleCount[3];
      char MARK;
};//endstructMsgOF

/********************************************************************************************************************
*公务车队数据  MsgOF  消息将要用的变量
*********************************************************************************************************************/
#define  MSGOF_FLAG_BEGIN     "B"      //开始
#define  MSGOF_FLAG_END        "E"      //结束

#define MSGOF_BOOL_TURE  '1'
#define MSGOF_BOOL_FALSE '0'
void InitMsgMsgOF(void);
struct MSG_MSGOF *GetMsgMsgOF(void);
void SetMsgOFMsgFLAG(char InputFLAG);
void SetMsgOFMsgBeginTime(char* InputBeginTime);
void SetMsgOFMsgVehicleCount(char* InputVehicleCount);
void SetMsgOFMsgMARK(char InputMARK);
#endif //define t_tablename

