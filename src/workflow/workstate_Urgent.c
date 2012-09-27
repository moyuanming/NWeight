#include "LocalIncludeFile.h"



volatile BOOL G_Urgent_Car_Team_Enabled = F;
void SetG_Urgent_Car_Team_Enabled(BOOL  value)
{	
	G_Urgent_Car_Team_Enabled=value;
}

int GetG_Urgent_Car_Team_Enabled(void)
{	
	return G_Urgent_Car_Team_Enabled;
}

volatile int G_Car_Pass_Count=0;
void AddG_Car_Pass_Count(void)
{	
	++G_Car_Pass_Count;
}


void SetG_Car_Pass_Count(int value)
{	
	G_Car_Pass_Count=value;
}

int GetG_Car_Pass_Count(void)
{	
	return G_Car_Pass_Count;
}



void WorkStation_09_Handl_Urgent_Car_Team(int nKey)
{
	switch (nKey)
	{
	case VK_RETURN:
		SetRingVoide(T);
		Set_WorkStation_13_Urgent_Car_Team_Passing();
		break;
	case VK_CANCEL:
		Set_WorkStation_03_Main_Work("正常收费","等待来车");
		break;
	case VK_CLOSE_YPD:
		SetYuPeng(F);
		break;
	case VK_OPEN_YPD:
		SetYuPeng(T);
		break;
	default:
		ErrorPressKey();
		break;
	}
}

void WorkStation_13_Urgent_Car_Team_Passing(int nKey)
{
	switch (nKey)
	{

		case VK_URGENT:
			Set_WorkStation_16_Handl_Urgent_Car_Team_End();
			break;
		case S_PASSLINEUP:
			AddMsgtotal_emergency();
			AddExitESMsgTotal_Emergency();
			AfterOfTransDo(1,T);
			setLed();
			break;
		case VK_CLOSE_YPD:
			SetYuPeng(F);
			break;
		case VK_OPEN_YPD:
			SetYuPeng(T);
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_16_Handl_Urgent_Car_Team_End(int nKey)
{
	switch (nKey)
	{
	case VK_RETURN:
		SetLanGan(F);
		SetJiaoTong(F);
		SendMsgEI(MSGEI_CARTEAM_END ,MSGEI_STATUS_MSGINFO,"紧急车已过");
		SendMsgEM('1');
		SendLaneInfo_default();
		SetG_weiZhangType(4);
		SendMsgInfo("紧急车队","","紧急过车");	 //qq
		Set_WorkStation_03_Main_Work("正常收费","等待来车");
		break;
	case VK_CANCEL:
		Set_WorkStation_13_Urgent_Car_Team_Passing();
		break;
	case VK_CLOSE_YPD:
		SetYuPeng(F);
		break;
	case VK_OPEN_YPD:
		SetYuPeng(T);
		break;
	default:
		ErrorPressKey();
		break;
	}
}


