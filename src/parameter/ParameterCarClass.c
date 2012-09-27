

#include "include\CarClass.h"
struct MSG_CARCLASS MsgCarClass;
void InitMsgCarClass(void)
{
	memset((char *)&MsgCarClass,'0',sizeof(struct MSG_CARCLASS));
}
struct MSG_CARCLASS *GetMsgCarClass(void)
{
	return (struct MSG_CARCLASS  *)&MsgCarClass;
}
void SetCarClassMsgExitClass(char* InputExitClass)
{
	strncpy(MsgCarClass.ExitClass,InputExitClass,sizeof(MsgCarClass.ExitClass));
}
void SetCarClassMsgDescription(char* InputDescription)
{
	strncpy(MsgCarClass.Description,InputDescription,sizeof(MsgCarClass.Description));
}

