//By GER.Cmd.buildgcc   CreateDate:2008-7-1 11:10:09
#include "LocalIncludeFile.h"
struct MSG_LANEINFO MsgLaneInfo;
void InitMsgLaneInfo(void)
{	
memset((char *)&MsgLaneInfo,'0',sizeof(struct MSG_LANEINFO));	
}
struct MSG_LANEINFO *GetMsgLaneInfo(void)
{	
return (struct MSG_LANEINFO  *)&MsgLaneInfo;
}
void SetLaneInfoMsgLaneNo(char* InputLaneNo)
{	
	strncpy(MsgLaneInfo.LaneNo,InputLaneNo,sizeof(MsgLaneInfo.LaneNo));	
}
void SetLaneInfoMsgCollName(char* InputCollName)
{	
	strncpy(MsgLaneInfo.CollName,InputCollName,sizeof(MsgLaneInfo.CollName));	
}
void SetLaneInfoMsgCollNo(char* InputCollNo)
{	
	strncpy(MsgLaneInfo.CollNo,InputCollNo,sizeof(MsgLaneInfo.CollNo));	
}
void SetLaneInfoMsgClientMsg(char* InputClientMsg)
{	
	strncpy(MsgLaneInfo.ClientMsg,InputClientMsg,sizeof(MsgLaneInfo.ClientMsg));	
}
void SetLaneInfoMsgCarType(char* InputCarType)
{	
	strncpy(MsgLaneInfo.CarType,InputCarType,sizeof(MsgLaneInfo.CarType));	
}
void SetLaneInfoMsgMoney(char* InputMoney)
{	
	strncpy(MsgLaneInfo.Money,InputMoney,sizeof(MsgLaneInfo.Money));	
}
void SetLaneInfoMsgCarKind(char* InputCarKind)
{	
	strncpy(MsgLaneInfo.CarKind,InputCarKind,sizeof(MsgLaneInfo.CarKind));	
}
void SetLaneInfoMsgWrokMode(char* InputWrokMode)
{	
	strncpy(MsgLaneInfo.WrokMode,InputWrokMode,sizeof(MsgLaneInfo.WrokMode));	
}
void SetLaneInfoMsgJobBeginTime(char* InputJobBeginTime)
{	
	strncpy(MsgLaneInfo.JobBeginTime,InputJobBeginTime,sizeof(MsgLaneInfo.JobBeginTime));	
}
void SetLaneInfoMsgYuPengDeng(char InputYuPengDeng)
{	
MsgLaneInfo.YuPengDeng=InputYuPengDeng;
}
void SetLaneInfoMsgJiaoTongDeng(char InputJiaoTongDeng)
{	
MsgLaneInfo.JiaoTongDeng=InputJiaoTongDeng;
}
void SetLaneInfoMsgLanGan(char InputLanGan)
{	
MsgLaneInfo.LanGan=InputLanGan;
}
void SetLaneInfoMsgPrinter(char InputPrinter)
{	
MsgLaneInfo.Printer=InputPrinter;
}
void SetLaneInfoMsgNetwork(char InputNetwork)
{	
MsgLaneInfo.Network=InputNetwork;
}

//end_LaneInfo
