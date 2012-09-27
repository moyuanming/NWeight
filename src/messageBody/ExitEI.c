//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "LocalIncludeFile.h"
struct MSG_EXITEI MsgExitEI;
void InitMsgExitEI(void)
{	
	memset((char *)&MsgExitEI,'0',sizeof(struct MSG_EXITEI));	
}
struct MSG_EXITEI *GetMsgExitEI(void)
{	
	return (struct MSG_EXITEI  *)&MsgExitEI;
}
void SetExitEIMsgErrorNO(char* InputErrorNO)
{	
	strncpy(MsgExitEI.ErrorNO,InputErrorNO,sizeof(MsgExitEI.ErrorNO));	
}
void SetExitEIMsgOcc_Rec(char InputOcc_Rec)
{	
	MsgExitEI.Occ_Rec=InputOcc_Rec;
}
void SetExitEIMsgMARK(char InputMARK)
{	
	MsgExitEI.MARK=InputMARK;
}
void SendExitEI(char* EI_Type)
{
	InitMsgExitEI();
	SetExitEIMsgErrorNO(EI_Type);
	SendMessageToQueue(ID_MSGEXITEI);
}
//end_ExitEI
