// ***************************************************************
//  MsgRevsion   version:  1.0   ·  date: 01/08/2008
//  -------------------------------------------------------------
//  系统使用参数表信息
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "MsgRevsion.h"
#include "LocalIncludeFile.h"

struct  MSG_REVISION MsgRevision;
struct MSG_REVISION *GetMsgRevision(void)
{	
	return &MsgRevision;
}

void InitMsgRevision(void)
{	
	memset((char *)&MsgRevision,' ',sizeof(struct MSG_REVISION));	
}

