//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"

/*******************************************************************************
*文件确认数据   结构体对应数据库中MsgAK表
*******************************************************************************/
 struct  MSG_MSGAK MsgMsgAK;
void InitMsgMsgAK(void)
{	
    memset((char *)&MsgMsgAK,'0',sizeof(struct MSG_MSGAK));	
}

/*******************************************************************************
*获取MsgMsgAK的地址
*******************************************************************************/
struct MSG_MSGAK *GetMsgMsgAK(void)
{	
    return (struct MSG_MSGAK  *)&MsgMsgAK;
}

/*******************************************************************************
*设置下发文件类型
*******************************************************************************/
void SetMsgAKMsgFileType(char InputFileType)
{	
    MsgMsgAK.FileType=InputFileType;
}


/*******************************************************************************
*设置接收状态
*******************************************************************************/
void SetMsgAKMsgRecStatus(char InputRecStatus)
{	
    MsgMsgAK.RecStatus=InputRecStatus;
}


/*******************************************************************************
*备注
*******************************************************************************/
void SetMsgAKMsgMARK(char InputMARK)
{	
    MsgMsgAK.MARK=InputMARK;
}

//end_MsgAK
