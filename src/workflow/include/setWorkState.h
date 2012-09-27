#ifndef __setWorkState_H__
#define __setWorkState_H__
void Set_WorkStation(int Index);

void Set_WorkStation_00_Wait_Begin_Work(void);
void Set_WorkStation_01_Handl_Input_Number(void);
void Set_WorkStation_02_Handl_Input_Password(void);
void Set_WorkStation_03_Main_Work(char *left,char *right);
void Set_WorkStation_03_Main_Work_extracted2(void);
void Set_WorkStation_03_Main_Work_extracted1(char * left, char * right);
void Set_WorkStation_51_Tuo_cheMoNi_Like_work3(char *left,char *right);
void Set_WorkStation_04_General_Validate_Car_Type_And_First_OK(void);
void Set_WorkStation_204_FreeCar(void);
void Set_WorkStation_09_Handl_Urgent_Car_Team(void);
void Set_WorkStation_13_Urgent_Car_Team_Passing(void);
void Set_WorkStation_16_Handl_Urgent_Car_Team_End(void);

void Set_WorkStation_06_Closed_Road(void);
void Set_WorkStation_07_General_Second_OK(char *left,char *right);
void Set_WorkStation_10_Up_Parapet_Pass(void);

void Set_WorkStation_20_EndWorkOk(void);
void Set_WorkStation_49_WeiZhang(void);
void SetWorkSationEndWz(void);
void Set_WorkStation_59_WeiZhangHandl(char *weiZhangType);

void Set_WorkStation_23_Abate(char *Type);




void Set_WorkStation_28_CarNumber_Second_OK(char *left,char *rihgt);

void Set_WorkStation_30_SelectWorkMod(void);
void Set_WorkStation_31_SelectCheckDev(void);
void Set_WorkStation_32_CheckBar(void);
void Set_WorkStation_33_CheckPassLight(void);
void Set_WorkStation_34_CheckSkyLight(void);
void Set_WorkStation_35_SelectCheckResult(void);
void Set_WorkStation_36_CheckPrinterResult(void);
void Set_WorkStation_37_CheckKeyBord(void);
void Set_WorkStation_38_CheckKeyBordResult(void);
void Set_WorkStation_39_CheckRing(void);
void Set_WorkStation_40_InPutWzCarType(void);
void Set_WorkStation_41_WzOK(char *CarType);
void Set_WorkStation_42_HandArrearageNumber(int BefWorkStation);
void Set_WorkStation_43_HandArrearageCharge(void);
void Set_WorkStation_44_TestLed(void);
void Set_WorkStation_45_SimulateOnceOk(void);
void Set_WorkStation_53_SimulateOnceOkTuoche(void);
void Set_WorkStation_46_SimulateTwoOk(void);
void Set_WorkStation_47_FavourCardOK(char *left,char *rihgt,char *startData,char *endData);
void Set_WorkStation_48_VK_OK(void);
void Set_WorkStation_52_VKABATE_OK(void);
void Set_WorkStation_50_DataExporter(void);
void Set_WorkStation_56_CheckCharFold(void);
void Set_WorkStation_57_CheckCharFoldResult(void);
#define   UBOUND_promptInformation 58 //promptInformation的数组上限

void Set_WorkStation_60_ConfirmPayBy_MonthCard(void);
void Set_WorkStation_62_ConfirmPayBy_OfficialCard(void);
void Set_WorkStation_61_ConfirmPayBy_SVCCard(void);
void Set_WorkStation_63_IC_Moni_SVC(void);
void Set_WorkStation_64_IC_Moni_Month(void);
void Set_WorkStation_65_IC_Moni_Official(void);
void Set_WorkStation_66_InputCarNo(char *left);

void Set_WorkStation_67_WeightMenu(void);
void Set_WorkStation_68_WeightMenuCC(void);
BOOL  WF_IC_WriteYPK(void);
#endif

