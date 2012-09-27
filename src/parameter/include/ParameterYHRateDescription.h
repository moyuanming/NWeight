//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _YHRateDescription_H_
#define _YHRateDescription_H_
#define YHRateDescriptionSTRLENGTH  35
struct  MSG_YHRATEDESCRIPTION
{
      char YHCode[3];
      char YHRate[3];
      char AdjustMode[4];
      char CarryMode[2];
      char EffectDateTime[23];
};//endstructYHRateDescription


int  ParseRecordYHRateDescription(char *RecordStr,int Rowindex);
int LoadYHRateDescriptionRecord(int IsFirst);
char  * GetEffectDateTime(char *InputYHcode);
int  GetAdjustMode(char *InputYHcode);
int   GetCarryMode(char *InputYHcode);
int   GetYHRate(char *InputYHcode);
int GetFactMoney(int Input,int YHL ,int adjustmod,int carrymod);
int  FactMoney(float  receivemoney);

#endif 
