//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"

/*******************************************************************************
*������Ϣ����   �ṹ���Ӧ���ݿ���MsgEI��
*******************************************************************************/
 struct  MSG_MSGEI MsgMsgEI;
void InitMsgMsgEI(void)
{	
	memset((char *)&MsgMsgEI,'0',sizeof(struct MSG_MSGEI));	
}


/*******************************************************************************
*��ȡMsgMsgEI�ĵ�ַ
*******************************************************************************/
struct MSG_MSGEI *GetMsgMsgEI(void)
{	
	return (struct MSG_MSGEI  *)&MsgMsgEI;
}

/*******************************************************************************
*���� �豸���Ϻ�
*******************************************************************************/
void SetMsgEIMsgEquipment(char* InputEquipment)
{	
	strncpy(MsgMsgEI.Equipment,InputEquipment,sizeof(MsgMsgEI.Equipment));	
}

/*******************************************************************************
*����   ���ϴ���״̬
*******************************************************************************/
void SetMsgEIMsgStatus(char InputStatus)
{	
	MsgMsgEI.Status=InputStatus;
}


/*******************************************************************************
*����    ��Ϣ˵��
*******************************************************************************/
void SetMsgEIMsgMemo(char* InputMemo)
{	
	strncpy(MsgMsgEI.Memo,InputMemo,sizeof(MsgMsgEI.Memo));	
}


/*******************************************************************************
*����    ��Ϣ��ע
*******************************************************************************/
void SetMsgEIMsgMARK(char InputMARK)
{	
	MsgMsgEI.MARK=InputMARK;
}

//end_MsgEI
