#ifndef _FareContext_h_
#define _FareContext_h_
int GetFareContext_CarAxleNumber(void);

float GetFareContext_CarWeight(void);
void Set_G_Current_Actual_pay(float value);
float Get_G_Current_Actual_pay(void);
char * GetG_Current_Handl_Charge_str(void);
void Init_G_Current_Actual_pay(void);
void Set_G_Current_Toll_Fare(float value);
float Get_G_Current_Toll_Fare(void);






#endif

