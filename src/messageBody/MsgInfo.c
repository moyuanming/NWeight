//By GER.Cmd.buildgcc   CreateDate:2008-7-1 11:10:09
#include "LocalIncludeFile.h"
struct MSG_MSGINFO MsgMsgInfo;
void InitMsgMsgInfo(void)
{	
memset((char *)&MsgMsgInfo,' ',sizeof(struct MSG_MSGINFO));	
}
struct MSG_MSGINFO *GetMsgMsgInfo(void)
{	
return (struct MSG_MSGINFO  *)&MsgMsgInfo;
}
void SetMsgInfoMsgLaneNo(char* InputLaneNo)
{	
	strncpy(MsgMsgInfo.LaneNo,InputLaneNo,sizeof(MsgMsgInfo.LaneNo));	
}
void SetMsgInfoMsgMsgType(char* InputMsgType)
{	
	strncpy(MsgMsgInfo.MsgType,InputMsgType,sizeof(MsgMsgInfo.MsgType));	
}
void SetMsgInfoMsgOccDate(char* InputOccDate)
{	
	strncpy(MsgMsgInfo.OccDate,InputOccDate,sizeof(MsgMsgInfo.OccDate));	
}
void SetMsgInfoMsgOccTime(char* InputOccTime)
{	
	strncpy(MsgMsgInfo.OccTime,InputOccTime,sizeof(MsgMsgInfo.OccTime));	
}
void SetMsgInfoMsgCollNo(char* InputCollNo)
{	
	strncpy(MsgMsgInfo.CollNo,InputCollNo,sizeof(MsgMsgInfo.CollNo));	
}
void SetMsgInfoMsgCarKind(char* InputCarKind)
{	
	strncpy(MsgMsgInfo.CarKind,InputCarKind,sizeof(MsgMsgInfo.CarKind));	
}
void SetMsgInfoMsgCarType(char* InputCarType)
{	
	strncpy(MsgMsgInfo.CarType,InputCarType,sizeof(MsgMsgInfo.CarType));	
}
void SetMsgInfoMsgPayType(char* InputPayType)
{	
	strncpy(MsgMsgInfo.PayType,InputPayType,sizeof(MsgMsgInfo.PayType));	
}
void SetMsgInfoMsgCash(char* InputCash)
{	
	strncpy(MsgMsgInfo.Cash,InputCash,sizeof(MsgMsgInfo.Cash));	
}
void SetMsgInfoMsgReceipt(char* InputReceipt)
{	
	strncpy(MsgMsgInfo.Receipt,InputReceipt,sizeof(MsgMsgInfo.Receipt));	
}
void SetMsgInfoMsgException(char* InputException)
{	
	strncpy(MsgMsgInfo.Exception,InputException,sizeof(MsgMsgInfo.Exception));	
}
void SetMsgInfoMsgPeccancy(char* InputPeccancy)
{	
	strncpy(MsgMsgInfo.Peccancy,InputPeccancy,sizeof(MsgMsgInfo.Peccancy));	
}
void SetMsgInfoMsgDevStatus(char* InputDevStatus)
{	
	strncpy(MsgMsgInfo.DevStatus,InputDevStatus,sizeof(MsgMsgInfo.DevStatus));	
}
void SetMsgInfoMsgPromptMsg(char* InputPromptMsg)
{	
	strncpy(MsgMsgInfo.PromptMsg,InputPromptMsg,sizeof(MsgMsgInfo.PromptMsg));	
}

//end_MsgInfo
