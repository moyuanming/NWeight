//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _CarClass_H_
#define _CarClass_H_
struct MSG_CARCLASS
{
      char ExitClass[10];
      char Description[10];
};//endstructCarClass
#define  LENGHT_MSG_CARCLASS 20
void InitMsgCarClass(void);
struct MSG_CARCLASS *GetMsgCarClass(void);
void SetCarClassMsgExitClass(char* InputExitClass);
void SetCarClassMsgDescription(char* InputDescription);
#endif //define t_tablename

