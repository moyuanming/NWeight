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
				Setg_AbateType(1);//��Ʊ��
				SetG_AbateNumber(GetCardNOByString());
				SendLaneInfo("��Ʊ����ˢ��");   
			}
			else
			{
				UI_Show_Help_Info("�����۳�ʧ��!�뽫��Ʊ�����·���������!");
			}
		}
	}
	else
	{
		
		UI_Show_Help_Info("��Ǹ���˿���������֧����");
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
		UI_Show_Help_Info("��ӡ�����ϣ������޸�Ʊ����ˢ��!");
	}
	else if (Get_CardContext_SVCCard_CanPay())
	{
		if (FALSE==GetIs_CardContext_SVCCard_Paid())//���ö���ˢ��
		{
			if (Use_CardContext_SVCCard_PayByCard())
			{
				SetIs_CardContext_SVCCard_Paid(T);
				SendLaneInfo("��ֵ����ˢ��");    

			}
			else
			{
				UI_Show_Help_Info("�ۿ�ʧ��!�뽫��ֵ�����·���������!");
			}
		}

		echoic("asdf");
	}
	else
	{
		echoic("asdf");
		UI_Show_Help_Info("��Ǹ���޷�ʹ�ô˿�֧��!");
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
 * ���ʹ����IC��֧����������֧����ʽ
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
		SetExitTRMsgMethod_Pay(MP_OFFICE);//����Ϊ 3
	
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




/*���񿨴���*/
void WorkStation_62_ConfirmPayBy_OfficialCard_extracted(void)
{
	if (Get_CardContext_OfficialCard_CanPay())
	{
		if (GetIs_CardContext_OfficialCard_Paid()==FALSE )
		{
			if (Use_CardContext_OfficialCard_PayByCard())
			{
				SetIs_CardContext_OfficialCard_Paid(TRUE);
				Setg_AbateType(1);//����
				SetG_AbateNumber(GetCardNOByString());
				echoic("asdf");

				SendLaneInfo("������ˢ��");   
			}
			else
			{
				UI_Show_Help_Info("�����۳�ʧ��!�뽫��Ʊ�����·���������!");
			}
		}
	}
	else
	{
		echoic("asdf");
		UI_Show_Help_Info("��Ǹ���˿���������֧����");
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


