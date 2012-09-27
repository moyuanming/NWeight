#ifndef __workState_H__
#define __workState_H__
void ErrorPressKey(void);
void simulateReturn(void);
void WorkStation(int nKey);
void  HandOnceOK(int keyboardValue,int currentworkstate);
BOOL WorkFlow_Peccancy(int nKey);
void WorkFlow_WeiZhang(int nKey);
void readConfigureFile(int index);
void WorkStation_00_Wait_Begin_Work(int nKey);
void WorkStation_01_Handl_Input_Number_ReadSIDCARD(BOOL UsedCar);
void WorkStation_02_Handl_Input_Password(int nKey);
void WorkStation_03_Main_Work(int nKey);
void WorkStation_51_Tuo_cheMoNi_Like_work3(int nKey);
void WorkStation_04_General_Validate_Car_Type_And_First_OK(int nKey);

void WorkStation_06_Closed_Road(int nKey);
void WorkStation_07_General_Second_OK(int nKey);
void WorkStation_09_Handl_Urgent_Car_Team(int nKey);
void WorkStation_10_Up_Parapet_Pass(int nKey);
void WorkStation_13_Urgent_Car_Team_Passing(int nKey);
void WorkStation_16_Handl_Urgent_Car_Team_End(int nKey);
void WorkStation_20_EndWorkOk(int nKey);
void WorkStation_23_Abate(int nKey);
void WorkStation_204_FreeCar(int nKey);
void WorkStation_24_General_Team_Abate(int nKey);
void WorkStation_25_In_General_Team_Passing_Abate(int nKey);
void WorkStation_27_CardNumber(int nKey);
void WorkStation_28_CarNumber_Second_OK(int nKey);
void WorkStation_29_OfflineWorkEnd(int nKey);
void WorkStation_30_SelectWorkMod(int nKey);
void WorkStation_31_SelectCheckDev(int nKey);
void WorkStation_32_CheckBar(int nKey);
void WorkStation_33_CheckPassLight(int nKey);
void WorkStation_34_CheckSkyLight(int nKey);
void WorkStation_35_SelectCheckResult(int nKey);
void WorkStation_36_CheckPrinterResult(int nKey);
void WorkStation_37_CheckKeyBord(int nKey);
void WorkStation_38_CheckKeyBordResult(int nKey);
void WorkStation_39_CheckRing(int nKey);
void WorkStation_40_InPutWzCarType(int nKey);
void WorkStation_41_WzOK(int nKey);
void WorkStation_42_HandArrearageNumber(int nKey);
void WorkStation_43_HandArrearageCharge(int nKey);
void WorkStation_44_TestLed(int nKey);
void WorkStation_45_SimulateOnceOk_Moni_Tuoche(void);
void WorkStation_53_SimulateOnceOkTuoche(int nKey);
void WorkStation_46_SimulateTwoOk(int nKey);
void WorkStation_47_FavourCardOK(int nKey);
void WorkStation_49_WeiZhang(int nKey);
void WorkStation_59_WeiZhangHandl(int nKey);
int WorkStation_07_FUN_General_Second_OK_7(int Flag );
void WorkStation_48_VK_OK(int nKey);
void WorkStation_52_Abate_OK(int nKey);
void WorkStation_56_CheckCharFold(int  nkey);
void WorkStation_57_CheckCharFoldResult(int nKey);
void RePrintBill(void);
void WorkStation_60_ConfirmPayBy_MonthCard_extracted(void);
void WorkStation_61_ConfirmPayBy_SVCCard_extracted(void);
 void GetUserNumberFromStatffCard(void);
void SetICExitTRPayMethod(void);
void WorkStation_64_IC_Moni_Month(int nKey);
void WorkStation_63_IC_Moni_SVC(int nKey);
void WorkStation_45_SimulateOnceOk_MoNITuoche(void);
void WorkStation_45_SimulateOnceOk(int nKey);
void WorkStation_60_ConfirmPayBy_MonthCard(int nKey);
void WorkStation_61_ConfirmPayBy_SVCCard(int nKey);
void WorkStation_62_ConfirmPayBy_OfficialCard_extracted(void);
void WorkStation_62_ConfirmPayBy_OfficialCard(int nKey);
void WorkStation_64_IC_Moni__Official(int nKey);
void ErrorShow(char *ErrorMessageShow);
void WorkStation_01_Handl_Input_Number(int nKey);
void WorkStation_50_DataExporter(int nKey);

void WorkStation_67_WeightMenu(int nKey);
void WorkStation_67_WeightMenu(int nKey);
#endif


