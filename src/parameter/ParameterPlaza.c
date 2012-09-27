//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "include\PLAZA.h"
struct MSG_PLAZA MsgPLAZA;
void InitMsgPLAZA(void)
{	
memset((char *)&MsgPLAZA,'0',sizeof(struct MSG_PLAZA));	
}
struct MSG_PLAZA *GetMsgPLAZA(void)
{	
return (struct MSG_PLAZA  *)&MsgPLAZA;
}
void SetPLAZAMsgNetWork(char* InputNetWork)
{	
	strncpy(MsgPLAZA.NetWork,InputNetWork,sizeof(MsgPLAZA.NetWork));	
}
void SetPLAZAMsgPLAZA(char* InputPLAZA)
{	
	strncpy(MsgPLAZA.PLAZA,InputPLAZA,sizeof(MsgPLAZA.PLAZA));	
}
void SetPLAZAMsgPLAZANAME(char* InputPLAZANAME)
{	
	strncpy(MsgPLAZA.PLAZANAME,InputPLAZANAME,sizeof(MsgPLAZA.PLAZANAME));	
}
void SetPLAZAMsgNetWorkName(char* InputNetWorkName)
{	
	strncpy(MsgPLAZA.NetWorkName,InputNetWorkName,sizeof(MsgPLAZA.NetWorkName));	
}

//end_PLAZA
