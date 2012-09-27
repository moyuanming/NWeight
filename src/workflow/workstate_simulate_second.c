#include "LocalIncludeFile.h"


/*******************************************************************************/
//标识是那个工作状态进行的模拟操作 不同的工作状态决定模拟完成后将回到什么状态
/*******************************************************************************/
volatile int G_simulateWorkState=0;
void SetG_simulateWorkState(int value)
{	
	G_simulateWorkState=value;
}

int GetG_simulateWorkState(void)
{	
	return  G_simulateWorkState;
}

/*******************************************************************************/
//重打票据次数
/*******************************************************************************/
volatile int G_reprintbillnum=0;
void SetG_reprintbillnum(int value)
{	
	G_reprintbillnum=value;
}
void AddG_reprintbillnum(void)
{	
	G_reprintbillnum++;
}
int GetG_reprintbillnum(void)
{	
	return  G_reprintbillnum;
}
void WorkStation_46_SimulateTwoOk(int nKey)
{
	switch (nKey)
	{
	case VK_1: 
		SendMsgInfo("异常消息","","线圈异常");	   
		SendMsgInfo("模拟消息","","过车模拟");	
		SetLanGan(F);
		SetExitTRMsgPassageLoopError('1');
		AddYCQK("过车模拟");
		SetExitTRMsgDisputeType('1');
		SendExitEI(EI_Type_MN_GCMN);
		SetNotRemoveFirstCarWeightInfo();
	case S_PASSLINEUP:			
		SetJiaoTong(F);		
		if (0!=GetG_IsTuoche())
		{
			AddYCQK("被拖车");
		}
		AfterOfTransDo(1,F);
		SetG_IsTuoche(0);	
		if(0!=GetG_IsChangche())
		{
			SetG_IsChangche(0);
		}
		/*if(0!=GetG_IsTeZhongChe())
		{
			SetG_IsTeZhongChe(0);
		}	*/
		SendMsgInfo("过车消息","","普通过车");	   
		Set_WorkStation_03_Main_Work("正常收费","等待来车");		
		SendLaneInfo_default();
		SendLaneInfo("等待来车");
		break;
	case VK_2:
		if ( 1==GetG_BillPrintFlag())
		{
			if (GetG_reprintbillnum()<atoi(sys_ini.reprintbillnum))
			{
				AddG_reprintbillnum ();
				RePrintBill();
				if (10==GetG_simulateWorkState())
				{
					Set_WorkStation_10_Up_Parapet_Pass();
				}
				AddExitESMsgCounter5();
				SendMsgInfo("模拟消息","","重打票据");
				AddYCQK("重打票据");
				SetExitTRMsgDisputeType('5');
				SendExitEI(EI_Type_MN_CDPJ);
			}
			else
			{
				UI_Show_Help_Info("重打票据次数上限!");
			}

		}
		else
		{
			UI_Show_Help_Info("免费车没有票据！");
			setLed();
		}
		break;
	default:
		ErrorPressKey();
		break;
	}
}

