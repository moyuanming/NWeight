//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _YPKList_H_
#define _YPKList_H_
struct MSG_YPKLIST
{
      char CardNumber[8];
      char BeginDate[8];
      char EndDate[8];
      char Status[10];
};

#define YPKListSTRLENGTH  34
void InitMsgYPKList(void);
struct MSG_YPKLIST *GetMsgYPKList(void);
void SetYPKListMsgNetwork(char* InputNetwork);
void SetYPKListMsgPlaza(char* InputPlaza);
void SetYPKListMsgCardNumber(char* InputCardNumber);
void SetYPKListMsgBeginDate(char* InputBeginDate);
void SetYPKListMsgEndDate(char* InputEndDate);
void SetYPKListMsgStatus(int InputStatus);

int CheckCardNumber(char *Inputcardnumber);
int LoadYPKListRecord(int IsFirst);
int  ParseRecordYPKList(char *RecordStr,int Rowindex);
int ValidateYPKCarEndDate(char *Inputcardnumber,time_t Currenttime);
int ValidateYPKCarStartDate(char *Inputcardnumber,time_t Currenttime);
char * GetYPKCarEndDate(char *Inputcardnumber);
char * GetYPKCarStartTime(char *Inputcardnumber);
#endif //define t_tablename

