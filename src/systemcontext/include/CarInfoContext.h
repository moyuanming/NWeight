#ifndef __CarInfoAndAffair_H__
#define __CarInfoAndAffair_H__

#define  WeightCarClassBUS 'A'
#define  WeightCarClassTruck 'B'
#define  WeightCarClassTruckISNotUseWeight 'C'
#define  WeightCarClassTruckSpecialVehicles 'D'
#define  WeightCarClassBIGTruckVehicles 'E'

#define CARKIND_WEIZHANG	'0' // 违章    0          是      E 0 00000000
#define CARKIND_SHOUFEI		'1' // 收费车  1  确认    是      1 2810101090
#define CARKIND_JUNCHE		'2' //军车    0  军车    是      1 3730005000
#define CARKIND_GONGWU		'3' //公务车  0  公务    是      3 3820006000
#define CARKIND_JINJI		'4' //紧急车  0  紧急    是      T 2370000090
#define CARKIND_LSTD		'9' //绿色通道0          是      1 4780004001
#define CARKIND_YPC			'6' //月票车  1  月票    月票表  4 2560008000
#define CARKIND_YHC			'7' //优惠卡车1  优惠    优惠卡表172470102100
#define CARKIND_JINCHE		'8' //警车    0          是      1 0 00000000
#define CARKIND_NONGYONG	'A' //农用车  0          是      1 4990007001

void SetUrgentType(int ut);
int GetUrgentType(void);
void SetG_Urgent_Car_Team_Enabled(BOOL  value);
int GetG_Urgent_Car_Team_Enabled(void);
void AddG_Car_Pass_Count(void);
int GetG_Car_Pass_Count(void);

void SetWeightCarClass(char _WeightCarClass);
char  GetWeightCarClass(void);

void SetG_Car_Pass_Count(int value);
void AddG_reprintbillnum(void);
void SetG_weiZhangState(int value);
int GetG_weiZhangState(void);
void SetG_weiZhangType(int value);
int GetG_weiZhangType(void);
void SetG_simulateWorkState(int  value);
int GetG_simulateWorkState(void);
void SetG_billRePrintEnabled(BOOL  value);
int GetG_billRePrintEnabled(void);
void SetG_reprintbillnum(int  value);
int GetG_reprintbillnum(void);
void SetG_BeforWzWorkstation(int  value);
int GetG_BeforWzWorkstation(void);
void SetG_BeforWzLaneState(int  value);
int GetG_BeforWzLaneState(void);
void SetG_BillPrintFlag(int value);
int GetG_BillPrintFlag(void);
char *GetG_ArrearageNumber(void);
void SetG_ArrearageCharge(int  value);
int GetG_ArrearageCharge(void);
void SetG_ArrearageChargeChar(char  *value);
char *GetG_ArrearageChargeChar(void);
void SetG_Current_Handl_Car_Kind(char  *value);
char *GetG_Current_Handl_Car_Kind(void);
void SetG_Current_Handl_Car_Kind_INT(int value);
int Validate_Car_Kind(int keyboardValue);


char *Get_Current_Car_Type(void);
void SendTcoWaingMsg(char *Msg);
void InitG_Current_Handl_Car_Kind(void);
void Init_Current_Car_Type(void);
void  InitG_CarNumber(void);
void  InitG_ArrearageNumber(void);
void InitG_ArrearageChargeChar(void);
void  SETG_ArrearageNumber_end(int  value);
void  SETG_ArrearageChargeChar_end(int  value);


char * GetbillNumber_str(void);
void InitYCQK(void);
void AddYCQK(char * tmp);
char * GetYCQK(void);
#endif

