//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"


/*******************************************************************************
*顶棚灯数据    结构体对应数据库中MsgGR表
*******************************************************************************/
 struct  MSG_MSGGR MsgMsgGR;
void InitMsgMsgGR(void)
{	
	memset((char *)&MsgMsgGR,'0',sizeof(struct MSG_MSGGR));	
}

/*******************************************************************************
*获取MsgMsgGR的地址
*******************************************************************************/
struct MSG_MSGGR *GetMsgMsgGR(void)
{	
	return (struct MSG_MSGGR  *)&MsgMsgGR;
}


/*******************************************************************************
*设置 顶棚灯显示状态    R红   G绿
*******************************************************************************/
void SetMsgGRMsgCanopy(char InputCanopy)
{	
	MsgMsgGR.Canopy=InputCanopy;
}

/*******************************************************************************
*备注
*******************************************************************************/
void SetMsgGRMsgMARK(char InputMARK)
{	
	MsgMsgGR.MARK=InputMARK;
}

//end_MsgGR
