//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"
struct MSG_EXITVI MsgExitVI;
void InitMsgExitVI(void)
{	
memset((char *)&MsgExitVI,'0',sizeof(struct MSG_EXITVI));	
}
struct MSG_EXITVI *GetMsgExitVI(void)
{	
return (struct MSG_EXITVI  *)&MsgExitVI;
}
void SetExitVIMsgentrynetwork(char* Inputentrynetwork)
{	
	strncpy(MsgExitVI.entrynetwork,Inputentrynetwork,sizeof(MsgExitVI.entrynetwork));	
}
void SetExitVIMsgEntryPlaza(char* InputEntryPlaza)
{	
	strncpy(MsgExitVI.EntryPlaza,InputEntryPlaza,sizeof(MsgExitVI.EntryPlaza));	
}
void SetExitVIMsgEntryLane(char* InputEntryLane)
{	
	strncpy(MsgExitVI.EntryLane,InputEntryLane,sizeof(MsgExitVI.EntryLane));	
}
void SetExitVIMsgEntryCollector(char* InputEntryCollector)
{	
	strncpy(MsgExitVI.EntryCollector,InputEntryCollector,sizeof(MsgExitVI.EntryCollector));	
}
void SetExitVIMsgEntryClass(char InputEntryClass)
{	
MsgExitVI.EntryClass=InputEntryClass;
}
void SetExitVIMsgExitClass(char InputExitClass)
{	
MsgExitVI.ExitClass=InputExitClass;
}
void SetExitVIMsgEntryType(char InputEntryType)
{	
	MsgExitVI.EntryType=InputEntryType;
}
void SetExitVIMsgExitType(int InputExitType)
{	
	char temp[2];
	temp[1]=0x00;
	sprintf(temp,"%d",InputExitType);	
	MsgExitVI.ExitType=temp[0];
}
void SetExitVIMsgMARK(char InputMARK)
{	
MsgExitVI.MARK=InputMARK;
}

//end_ExitVI
