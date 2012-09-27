//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"


/*******************************************************************************
*公务车队数据     结构体对应数据库中MsgOF表
*******************************************************************************/
 struct MSG_MSGOF MsgMsgOF;
void  InitMsgMsgOF(void)
{	
	memset((char *)&MsgMsgOF,'0',sizeof(struct MSG_MSGOF));	
}

/*******************************************************************************
*获取MsgMsgOF的地址
*******************************************************************************/
struct MSG_MSGOF *GetMsgMsgOF(void)
{	
	return (struct MSG_MSGOF  *)&MsgMsgOF;
}

/*******************************************************************************
*设置 车队开始、结束的标志       B-开始，E-结束
*******************************************************************************/
void SetMsgOFMsgFLAG(char InputFLAG)
{	
	MsgMsgOF.FLAG=InputFLAG;
}

/*******************************************************************************
*设置  车队开始时间
*******************************************************************************/
void SetMsgOFMsgBeginTime(char* InputBeginTime)
{	
	strncpy(MsgMsgOF.BeginTime,InputBeginTime,sizeof(MsgMsgOF.BeginTime));	
}


/*******************************************************************************
*  车辆计数
*******************************************************************************/
void SetMsgOFMsgVehicleCount(char* InputVehicleCount)
{	
	strncpy(MsgMsgOF.VehicleCount,InputVehicleCount,sizeof(MsgMsgOF.VehicleCount));	
}

/*******************************************************************************
*  备注
*******************************************************************************/
void SetMsgOFMsgMARK(char InputMARK)
{	
	MsgMsgOF.MARK=InputMARK;
}

//end_MsgOF
