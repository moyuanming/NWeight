//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "include\Staff.h"
struct MSG_STAFF MsgStaff;
void InitMsgStaff(void)
{	
memset((char *)&MsgStaff,'0',sizeof(struct MSG_STAFF));	
}
struct MSG_STAFF *GetMsgStaff(void)
{	
return (struct MSG_STAFF  *)&MsgStaff;
}
void SetStaffMsgNetwork(char* InputNetwork)
{	
	strncpy(MsgStaff.Network,InputNetwork,sizeof(MsgStaff.Network));	
}
void SetStaffMsgPlaza(char* InputPlaza)
{	
	strncpy(MsgStaff.Plaza,InputPlaza,sizeof(MsgStaff.Plaza));	
}
void SetStaffMsgcollno(char* Inputcollno)
{	
	strncpy(MsgStaff.collno,Inputcollno,sizeof(MsgStaff.collno));	
}
void SetStaffMsgcollname(char* Inputcollname)
{	
	strncpy(MsgStaff.collname,Inputcollname,sizeof(MsgStaff.collname));	
}
void SetStaffMsgpassword(char* Inputpassword)
{	
	strncpy(MsgStaff.password,Inputpassword,sizeof(MsgStaff.password));	
}
void SetStaffMsgidentify(char Inputidentify)
{	
MsgStaff.identify=Inputidentify;
}
void SetStaffMsgPrivilege(char* InputPrivilege)
{	
	strncpy(MsgStaff.Privilege,InputPrivilege,sizeof(MsgStaff.Privilege));	
}
void SetStaffMsgValidate(char* InputValidate)
{	
	strncpy(MsgStaff.Validate,InputValidate,sizeof(MsgStaff.Validate));	
}
void SetStaffMsgStatus(int InputStatus)
{	
	sprintf(MsgStaff.Status,"%010d",InputStatus);	
}
void SetStaffMsgCapture(char InputCapture)
{	
MsgStaff.Capture=InputCapture;
}
void SetStaffMsgFounder(char* InputFounder)
{	
	strncpy(MsgStaff.Founder,InputFounder,sizeof(MsgStaff.Founder));	
}

//end_Staff
