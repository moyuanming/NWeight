//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _YHKList_H_
#define _YHKList_H_
#define  LENGHT_MSG_YHKLIST 37

struct MSG_YHKLIST 
{
      char CardNumber[8];
      char BeginDate[8];
      char EndDate[8];
      char YHCode[3];
      char Status[10];
}  ;//endstructYHKList


int LoadYHKListRecord(int IsFirst);
int  ParseRecordYHKList(char *RecordStr,int Rowindex);
int CheckYHKCardNumber(char *Inputcardnumber);
char  *GetYHCode(char *Inputcardnumber);
int  ValidateCardEnable(char *InputTime);
int ValidateYHCarEndDate(char *Inputcardnumber,time_t Currenttime);
int ValidateYHCarStartDate(char *Inputcardnumber,time_t Currenttime);
char * GetYHCarEndDate(char *Inputcardnumber);
char * GetYHCarStartDate(char *Inputcardnumber);
#endif //define t_tablename

