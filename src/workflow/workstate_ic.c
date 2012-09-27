#include "LocalIncludeFile.h"

void WorkStation_60_ConfirmPayBy_MonthCard_extracted(void)
{
	if (Get_CardContext_MonthCard_CanPay())
	{
		if (GetIs_CardContext_MonthCard_Paid()==FALSE )
		{
			if (Use_CardContext_MonthCard_PayByCard())
			{
				SetIs_CardContext_MonthCard_Paid(TRUE);
				Setg_AbateType(1);//月票卡
				SetG_AbateNumber(GetCardNOByString());
				SendLaneInfo("月票卡已刷卡");   
			}
			else
			{
				UI_Show_Help_Info("次数扣除失败!请将月票卡重新放在天线上!");
			}
		}
	}
	else
	{
		
		UI_Show_Help_Info("抱歉！此卡不能用于支付！");
	}
}
void WorkStation_60_ConfirmPayBy_MonthCard(int nKey)
{
	switch (nKey)
	{
		case CSC_CARDENTER:
			if (0!=strncmp(GetCardContext_CardNumber(),GetCardNOByString(),10))
			{
				WorkStation_07_General_Second_OK(CSC_CARDENTER);
			}
			break;
		case VK_RETURN:
			WorkStation_60_ConfirmPayBy_MonthCard_extracted();
			if (GetIs_CardContext_MonthCard_Paid())
			{
				WorkStation_47_FavourCardOK(nKey);
			}
			break;
		case VK_MONI:
			if (Get_CardContext_MonthCard_CanPay()==T)
			{
				Set_WorkStation_64_IC_Moni_Month();
			}
			break;
		case CSC_CARDEXIT:
		case VK_CANCEL:
			HandOnceOK(VK_RETURN,4);
			break;
		default:
			ErrorPressKey();
			break;
	}
}

 
void WorkStation_61_ConfirmPayBy_SVCCard_extracted(void)
{
	TestPrintState();
	if (!Getg_bPrint())
	{
		UI_Show_Help_Info("打印机故障，请先修复票打再刷卡!");
	}
	else if (Get_CardContext_SVCCard_CanPay())
	{
		if (FALSE==GetIs_CardContext_SVCCard_Paid())//放置二次刷卡
		{
			if (Use_CardContext_SVCCard_PayByCard())
			{
				SetIs_CardContext_SVCCard_Paid(T);
				SendLaneInfo("储值卡已刷卡");    

			}
			else
			{
				UI_Show_Help_Info("扣款失败!请将储值卡重新放在天线上!");
			}
		}

		echoic("asdf");
	}
	else
	{
		echoic("asdf");
		UI_Show_Help_Info("抱歉！无法使用此卡支付!");
	}
}
void WorkStation_61_ConfirmPayBy_SVCCard(int nKey)
{
	switch (nKey)
	{
		case VK_RETURN:
			WorkStation_61_ConfirmPayBy_SVCCard_extracted();
			if (GetIs_CardContext_SVCCard_Paid() )
			{
				WorkStation_07_General_Second_OK(VK_RETURN);
			}
			break;
		case CSC_CARDEXIT:
		case VK_CANCEL:
			HandOnceOK(VK_RETURN,4);
			break;
		case VK_MONI:
			if (Get_CardContext_SVCCard_CanPay()==T)
			{
				Set_WorkStation_63_IC_Moni_SVC();
			}
			break;
		case CSC_CARDENTER:
			if (0!=strncmp(GetCardContext_CardNumber(),GetCardNOByString(),10))
			{
				HandOnceOK(VK_RETURN,4);
				WorkStation_07_General_Second_OK(nKey);
			}
			break;
		
			
		default:
			ErrorPressKey();
			break;
	}

}

 

/**
 * 如果使用了IC卡支付，则设置支付方式
 */
void SetICExitTRPayMethod(void)
{
	BOOL isP=F;
	 
	  if (GetIs_CardContext_MonthCard_Paid())
	{
		SetExitTRMsgMethod_Pay(MP_MONTH);
		isP=T;
	}
	else if (GetIs_CardContext_SVCCard_Paid())
	{
		SetExitTRMsgMethod_Pay(MP_SVC);
	
		isP=T;
	}
	else if (GetIs_CardContext_OfficialCard_Paid ())
	{
		SetExitTRMsgMethod_Pay(MP_OFFICE);//公务卡为 3
	
		isP=T;
	}
	if (isP)
	{
		 SetExitTRMsgServiceCard(GetCardContext_CardNumber ());
		 
	}
}
 
void WorkStation_63_IC_Moni_SVC(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			WorkStation_61_ConfirmPayBy_SVCCard_extracted();
			if (GetIs_CardContext_SVCCard_Paid() )
			{
				WorkStation_45_SimulateOnceOk_MoNITuoche();
			}
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_64_IC_Moni_Month(int nKey)
{
	switch (nKey)
	{
	case VK_1:
		WorkStation_60_ConfirmPayBy_MonthCard_extracted();
		if (GetIs_CardContext_MonthCard_Paid())
		{
			WorkStation_45_SimulateOnceOk_MoNITuoche();
		}
		break;
	default:
		ErrorPressKey();
		break;
	}
}




/*公务卡处理*/
void WorkStation_62_ConfirmPayBy_OfficialCard_extracted(void)
{
	if (Get_CardContext_OfficialCard_CanPay())
	{
		if (GetIs_CardContext_OfficialCard_Paid()==FALSE )
		{
			if (Use_CardContext_OfficialCard_PayByCard())
			{
				SetIs_CardContext_OfficialCard_Paid(TRUE);
				Setg_AbateType(1);//公务卡
				SetG_AbateNumber(GetCardNOByString());
				echoic("asdf");

				SendLaneInfo("公务卡已刷卡");   
			}
			else
			{
				UI_Show_Help_Info("次数扣除失败!请将月票卡重新放在天线上!");
			}
		}
	}
	else
	{
		echoic("asdf");
		UI_Show_Help_Info("抱歉！此卡不能用于支付！");
	}
}

 
void WorkStation_62_ConfirmPayBy_OfficialCard(int nKey)
{
	switch (nKey)
	{
		case CSC_CARDENTER:
			if (0!=strncmp(GetCardContext_CardNumber(),GetCardNOByString(),10))
			{
				WorkStation_07_General_Second_OK(CSC_CARDENTER);
			}
			break;
		
			
		case VK_RETURN:
			WorkStation_62_ConfirmPayBy_OfficialCard_extracted();
			if (GetIs_CardContext_OfficialCard_Paid())
			{
				WorkStation_47_FavourCardOK(nKey);
			}
			echoic("asdf");
			break;
		case VK_MONI:
			if (Get_CardContext_OfficialCard_CanPay()==T)
			{
				Set_WorkStation_65_IC_Moni_Official();
			}
			break;
		case CSC_CARDEXIT:
		case VK_CANCEL:
			HandOnceOK(VK_RETURN,4);
			break;
		default:
			ErrorPressKey();
			break;
	}
}

 


void WorkStation_62_IC_Moni__Official(int nKey)
{
	switch (nKey)
	{
		case VK_1:
 
			WorkStation_62_ConfirmPayBy_OfficialCard_extracted();
			if (GetIs_CardContext_OfficialCard_Paid())
			{
				WorkStation_45_SimulateOnceOk_MoNITuoche();
			}

			break;
		default:
			ErrorPressKey();
			break;
	}
}


