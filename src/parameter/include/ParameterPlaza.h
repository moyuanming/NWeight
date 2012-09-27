//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _PLAZA_H_
#define _PLAZA_H_
struct MSG_PLAZA
{
      char NetWork[2];
      char PLAZA[2];
      char PLAZANAME[20];
      char NetWorkName[20];
}//endstructPLAZA
#define  LENGHT_MSG_PLAZA 44
void InitMsgPLAZA(void);
struct MSG_PLAZA *GetMsgPLAZA(void);
void SetPLAZAMsgNetWork(char* InputNetWork);
void SetPLAZAMsgPLAZA(char* InputPLAZA);
void SetPLAZAMsgPLAZANAME(char* InputPLAZANAME);
void SetPLAZAMsgNetWorkName(char* InputNetWorkName);
#endif //define t_tablename

