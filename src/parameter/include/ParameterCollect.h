//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "ParameterTable.h"
#ifndef _Collect_H_
#define _Collect_H_
#define  LENGHT_MSG_COLLECT 55
struct PARAM_HEAD  CollectHead;
struct MSG_COLLECT
{

    char collno[6];
    char collname[20];
    char password[8];
    char identify[1];
    char Validate[10];
    char Status[10];

};
struct MSG_COLLECT  MsgCollect[MAXPAEAMRECORDS];



struct MSG_COLLECT  * GetIndexCollect(int InputIndex);

int ParseRecordCollect(char * RecordStr,int Rowindex);
int LoadCollectRecord(int IsFirst);
char * PwdEncrypt(char *InputPassword);
int UserExist(char *InputUserNumber,char *InputPassword);
BOOL UserNumberExist(char *userNumber);
char *GetUserAccessLevelCodeOfIndex(int InputIndex);
char * GetUserGroup(char Identify);

char * trim(char * src);
#endif //define t_tablename



