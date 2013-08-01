#include "LocalIncludeFile.h"



void ErrorPressKey()
{
	setLed();
	if (GetEnableIC() && IsCardInReader())
	{
		UI_Show_Help_Info("抱歉,当前状态并不使用IC卡！");
	}
	else
	{
		UI_Show_Help_Info("按键无效，请按提示进行操作。");
	}
	return;

}
void ErrorShow(char *ErrorMessageShow)
{
	setLed();
	UI_Show_Help_Info(ErrorMessageShow);
	return;
}



void WorkStation(int nKey)
{

	UI_Show_Help_Info("");
	if(nKey==VK_00)
	{
		WorkStation(VK_0);
		WorkStation(VK_0);
		return;
	}
	if ( WorkFlow_Peccancy(nKey))
	{
		return;
	}
	if (nKey==VK_BREAKAUTOMAN)
	{
		SetUseAutoMan(0);//abs(GetUseAutoMan()-1));
	}
	echo("状态 %d",GetWorkState());
	switch (GetWorkState())
	{
	case 0:
		WorkStation_00_Wait_Begin_Work(nKey);
		break;
	case 1:
		WorkStation_01_Handl_Input_Number( nKey);
		break;
	case 2:
		WorkStation_02_Handl_Input_Password( nKey);
		break;
	case 3:
		WorkStation_03_Main_Work( nKey);
		break;
	case 4:
		WorkStation_04_General_Validate_Car_Type_And_First_OK( nKey);
		break;
	
	case 6:
		WorkStation_06_Closed_Road( nKey);
		break;
	case 7:
		WorkStation_07_General_Second_OK( nKey);
		break;
	
	case 9:
		WorkStation_09_Handl_Urgent_Car_Team( nKey);
		break;
	case 10:
		WorkStation_10_Up_Parapet_Pass( nKey);
		break;

	
	case 13:
		WorkStation_13_Urgent_Car_Team_Passing( nKey);
		break;
	

	case 16:
		WorkStation_16_Handl_Urgent_Car_Team_End( nKey);
		break;

	
	case 20:
		WorkStation_20_EndWorkOk( nKey);
		break;
	case 23:
		WorkStation_23_Abate( nKey);
		break;	
	case 204:
		WorkStation_204_FreeCar( nKey);
		break;
	case 28:
		WorkStation_28_CarNumber_Second_OK( nKey);
		break;

	case 30:
		WorkStation_30_SelectWorkMod( nKey);
		break;
	case 31:
		WorkStation_31_SelectCheckDev( nKey);
		break;
	case 32:
		WorkStation_32_CheckBar( nKey);
		break;
	case 33:
		WorkStation_33_CheckPassLight( nKey);
		break;
	case 34:
		WorkStation_34_CheckSkyLight( nKey);
		break;
	case 35:
		WorkStation_35_SelectCheckResult( nKey);
		break;
	case 36:
		WorkStation_36_CheckPrinterResult( nKey);
		break;
	case 37:
		WorkStation_37_CheckKeyBord( nKey);
		break;
	case 38:
		WorkStation_38_CheckKeyBordResult( nKey);
		break;
	case 39:
		WorkStation_39_CheckRing( nKey);
		break;
	case 42:
		WorkStation_42_HandArrearageNumber( nKey);
		break;
	case 43:
		WorkStation_43_HandArrearageCharge( nKey);
		break;
	case 44:
		WorkStation_44_TestLed( nKey);
		break;
	case 45:
		WorkStation_45_SimulateOnceOk( nKey);
		break;
	case 46:
		WorkStation_46_SimulateTwoOk( nKey);
		break;
	case 47:
		WorkStation_47_FavourCardOK(nKey);
		break;
	case 48:
		WorkStation_48_VK_OK(nKey);
		break;
	case 50:
		WorkStation_50_DataExporter(nKey);
		break;
	case 51:
		WorkStation_51_Tuo_cheMoNi_Like_work3(nKey);
		break;
	case 52:
		WorkStation_52_Abate_OK(nKey);
		break;
	case 53:
		WorkStation_53_SimulateOnceOkTuoche(nKey);
		break;
	case 56:
		WorkStation_56_CheckCharFold(nKey);
		break;
	case 57:
		WorkStation_57_CheckCharFoldResult( nKey);
		break;
	case 60:
		WorkStation_60_ConfirmPayBy_MonthCard(nKey);
		break;
	case 61:
		WorkStation_61_ConfirmPayBy_SVCCard(nKey);
		break;
	case 62:
		WorkStation_62_ConfirmPayBy_OfficialCard(nKey);
		break;
	case 63:
		WorkStation_63_IC_Moni_SVC(nKey);
		break;
	case 64:
		WorkStation_64_IC_Moni_Month(nKey);
		break;
	case 66:
		WorkStation_66_InputCarNo(nKey);
		break;
	case 67:
		WorkStation_67_WeightMenu(nKey);
		break;
	case 68:
		WorkStation_68_WeightMenuCC(nKey);
		break;
	case 200:
		WorkStation_200_SetConfig(nKey);
		break;
	case 201:
		WorkStation_201SetLanInfo(nKey);
		break;
	case 202:
		WorkStation_202_SetCommunction(nKey);
		break;
	case 203:
		WorkStation_203_SetDevConfig(nKey);
		break;
	case 205:
		WorkStation_205_SetMode(nKey);
		break;
	default:
		break;
	}

}
