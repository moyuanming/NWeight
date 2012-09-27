//By GER.Cmd.buildgcc   CreateDate:2008-7-1 11:10:09
#ifndef _MsgInfo_H_
#define _MsgInfo_H_
struct MSG_MSGINFO
{
      char LaneNo[3];
      char MsgType[10];
      char OccDate[14];
      char OccTime[14];
      char CollNo[10];
      char CarKind[16];
      char CarType[5];
      char PayType[16];
      char Cash[16];
      char Receipt[16];
      char Exception[32];
      char Peccancy[32];
      char DevStatus[32];
      char PromptMsg[64];
};//endstructMsgInfo
#define  LENGHT_MSG_MSGINFO 280
void InitMsgMsgInfo(void);
struct MSG_MSGINFO *GetMsgMsgInfo(void);
void SetMsgInfoMsgLaneNo(char* InputLaneNo);
void SetMsgInfoMsgMsgType(char* InputMsgType);
void SetMsgInfoMsgOccDate(char* InputOccDate);
void SetMsgInfoMsgOccTime(char* InputOccTime);
void SetMsgInfoMsgCollNo(char* InputCollNo);
void SetMsgInfoMsgCarKind(char* InputCarKind);
void SetMsgInfoMsgCarType(char* InputCarType);
void SetMsgInfoMsgPayType(char* InputPayType);
void SetMsgInfoMsgCash(char* InputCash);
void SetMsgInfoMsgReceipt(char* InputReceipt);
void SetMsgInfoMsgException(char* InputException);
void SetMsgInfoMsgPeccancy(char* InputPeccancy);
void SetMsgInfoMsgDevStatus(char* InputDevStatus);
void SetMsgInfoMsgPromptMsg(char* InputPromptMsg);
#endif //define t_tablename


