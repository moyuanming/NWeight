//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _FareList_H_
#define _FareList_H_
  struct MSG_FARELIST
{
      char ExitLaneNo[3];
      char FareNo[10];
      char EffectDateTime[23];
      char Type1Fare[10];
      char Type2Fare[10];
      char Type3Fare[10];
      char Type4Fare[10];
      char Type5Fare[10];
      char Type6Fare[10];
      char Type7Fare[10];
      char Type8Fare[10];
      char Type9Fare[10];
};
int LoadFareRecord(int IsFirst);
int GetFareValue(int InputVehiClass);
char * GetFareVersion(void);
int  GetFareValue_extracted(int InputVehiClass,   int i, char * FareSum );
#endif
