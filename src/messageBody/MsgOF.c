//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"


/*******************************************************************************
*���񳵶�����     �ṹ���Ӧ���ݿ���MsgOF��
*******************************************************************************/
 struct MSG_MSGOF MsgMsgOF;
void  InitMsgMsgOF(void)
{	
	memset((char *)&MsgMsgOF,'0',sizeof(struct MSG_MSGOF));	
}

/*******************************************************************************
*��ȡMsgMsgOF�ĵ�ַ
*******************************************************************************/
struct MSG_MSGOF *GetMsgMsgOF(void)
{	
	return (struct MSG_MSGOF  *)&MsgMsgOF;
}

/*******************************************************************************
*���� ���ӿ�ʼ�������ı�־       B-��ʼ��E-����
*******************************************************************************/
void SetMsgOFMsgFLAG(char InputFLAG)
{	
	MsgMsgOF.FLAG=InputFLAG;
}

/*******************************************************************************
*����  ���ӿ�ʼʱ��
*******************************************************************************/
void SetMsgOFMsgBeginTime(char* InputBeginTime)
{	
	strncpy(MsgMsgOF.BeginTime,InputBeginTime,sizeof(MsgMsgOF.BeginTime));	
}


/*******************************************************************************
*  ��������
*******************************************************************************/
void SetMsgOFMsgVehicleCount(char* InputVehicleCount)
{	
	strncpy(MsgMsgOF.VehicleCount,InputVehicleCount,sizeof(MsgMsgOF.VehicleCount));	
}

/*******************************************************************************
*  ��ע
*******************************************************************************/
void SetMsgOFMsgMARK(char InputMARK)
{	
	MsgMsgOF.MARK=InputMARK;
}

//end_MsgOF
