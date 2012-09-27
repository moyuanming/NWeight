//By GER.Cmd.buildgcc   CreateDate:2011/5/31 10:42:12
#ifndef _FreeCarList_H_
#define _FreeCarList_H_
struct MSG_FREECARLIST
{
      char NetWork[2];
      char Plaza[2];
      char CarCode[5];
      char CarNo[5];
      char CarType;
      char Units[15];
      char Remarks[10];
      char AddDate[8];
      char BeginDate[8];
      char EndDate[8];
};//endstructFreeCarList
#define  LENGHT_MSG_FREECARLIST 64
int GetCarInfoStaue(void);
char * GetCarInfo(char *CarNo);
int  ParseRecordFreeCarList(char *RecordStr,int Rowindex);
int LoadFreeCarListRecord(int IsFirst);
#endif //define t_tablename

