//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"

/*******************************************************************************
*例外信息数据   结构体对应数据库中MsgEI表
*******************************************************************************/
 struct  MSG_MSGEI MsgMsgEI;
void InitMsgMsgEI(void)
{	
	memset((char *)&MsgMsgEI,'0',sizeof(struct MSG_MSGEI));	
}


/*******************************************************************************
*获取MsgMsgEI的地址
*******************************************************************************/
struct MSG_MSGEI *GetMsgMsgEI(void)
{	
	return (struct MSG_MSGEI  *)&MsgMsgEI;
}

/*******************************************************************************
*设置 设备故障号
*******************************************************************************/
void SetMsgEIMsgEquipment(char* InputEquipment)
{	
	strncpy(MsgMsgEI.Equipment,InputEquipment,sizeof(MsgMsgEI.Equipment));	
}

/*******************************************************************************
*设置   故障处理状态
*******************************************************************************/
void SetMsgEIMsgStatus(char InputStatus)
{	
	MsgMsgEI.Status=InputStatus;
}


/*******************************************************************************
*设置    消息说明
*******************************************************************************/
void SetMsgEIMsgMemo(char* InputMemo)
{	
	strncpy(MsgMsgEI.Memo,InputMemo,sizeof(MsgMsgEI.Memo));	
}


/*******************************************************************************
*设置    消息备注
*******************************************************************************/
void SetMsgEIMsgMARK(char InputMARK)
{	
	MsgMsgEI.MARK=InputMARK;
}

//end_MsgEI
