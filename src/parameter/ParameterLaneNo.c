//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "include\LANENO.h"
struct MSG_LANENO MsgLANENO;
void InitMsgLANENO(void)
{	
memset((char *)&MsgLANENO,'0',sizeof(struct MSG_LANENO));	
}
struct MSG_LANENO *GetMsgLANENO(void)
{	
return (struct MSG_LANENO  *)&MsgLANENO;
}
void SetLANENOMsgNetWork(char* InputNetWork)
{	
	strncpy(MsgLANENO.NetWork,InputNetWork,sizeof(MsgLANENO.NetWork));	
}
void SetLANENOMsgPlaza(char* InputPlaza)
{	
	strncpy(MsgLANENO.Plaza,InputPlaza,sizeof(MsgLANENO.Plaza));	
}
void SetLANENOMsgLANENO(char* InputLANENO)
{	
	strncpy(MsgLANENO.LANENO,InputLANENO,sizeof(MsgLANENO.LANENO));	
}
void SetLANENOMsgTYPE(char InputTYPE)
{	
MsgLANENO.TYPE=InputTYPE;
}
void SetLANENOMsgDESCRIPTION(char* InputDESCRIPTION)
{	
	strncpy(MsgLANENO.DESCRIPTION,InputDESCRIPTION,sizeof(MsgLANENO.DESCRIPTION));	
}
void SetLANENOMsgCapture(char InputCapture)
{	
MsgLANENO.Capture=InputCapture;
}

//end_LANENO
