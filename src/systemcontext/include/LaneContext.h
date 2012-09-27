#ifndef __LaneContext_H__
#define __LaneContext_H__

int GetG_Lane_carTypeCount(void);
int GetG_Lane_carKindCount(void);
void SetG_Current_LaneCarTypeTableID(int  value);
int GetG_Current_LaneCarTypeTableID(void);
void SetG_Current_CarKindID(int value);
int GetG_Current_CarKindID(void);
char *GetG_SaveBeforTipOne(void);

void SetG_Lane_carTypeCount(int  value);
void SetG_Lane_carKindCount(int  value);
char *GetG_SaveBeforTipTwo(void);
void SetG_IsTuoche(int value);
int GetG_IsTuoche(void);
void SetG_IsTuoCheUp(int  value);
int GetG_IsTuoCheUp(void);
void SetG_IsChangche(int value);
int GetG_IsChangche(void);
void SetG_IsTeZhongChe(int value);
int GetG_IsTeZhongChe(void);
void InitG_SaveBeforTipOne(void);
void InitG_SaveBeforTipTwo(void);
void SetG_SaveBeforTipOne(char * inputG_SaveBeforTipOne);
void SetG_SaveBeforTipTwo(char * inputG_SaveBeforTipTwo);

#endif
