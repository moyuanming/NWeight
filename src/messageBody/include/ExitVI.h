//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _ExitVI_H_
#define _ExitVI_H_
struct MSG_EXITVI
{
      char entrynetwork[2];
      char EntryPlaza[2];
      char EntryLane[3];
      char EntryCollector[6];
      char EntryClass;
      char ExitClass;
      char EntryType;
      char ExitType;
      char MARK;
};//endstructExitVI
#define  LENGHT_MSG_EXITVI 18
void InitMsgExitVI(void);
struct MSG_EXITVI *GetMsgExitVI(void);
void SetExitVIMsgentrynetwork(char* Inputentrynetwork);
void SetExitVIMsgEntryPlaza(char* InputEntryPlaza);
void SetExitVIMsgEntryLane(char* InputEntryLane);
void SetExitVIMsgEntryCollector(char* InputEntryCollector);
void SetExitVIMsgEntryClass(char InputEntryClass);
void SetExitVIMsgExitClass(char InputExitClass);
void SetExitVIMsgEntryType(char InputEntryType);
void SetExitVIMsgExitType(int InputExitType);
void SetExitVIMsgMARK(char InputMARK);
#endif //define t_tablename

