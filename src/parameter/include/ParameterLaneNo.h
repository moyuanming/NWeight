//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _LANENO_H_
#define _LANENO_H_
struct MSG_LANENO
{
      char NetWork[2];
      char Plaza[3];
      char LANENO[3];
      char TYPE;
      char DESCRIPTION[10];
      char Capture;
}//endstructLANENO
#define  LENGHT_MSG_LANENO 20
void InitMsgLANENO(void);
struct MSG_LANENO *GetMsgLANENO(void);
void SetLANENOMsgNetWork(char* InputNetWork);
void SetLANENOMsgPlaza(char* InputPlaza);
void SetLANENOMsgLANENO(char* InputLANENO);
void SetLANENOMsgTYPE(char InputTYPE);
void SetLANENOMsgDESCRIPTION(char* InputDESCRIPTION);
void SetLANENOMsgCapture(char InputCapture);
#endif //define t_tablename

