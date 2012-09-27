#include "LocalIncludeFile.h"

void WorkStation_45_SimulateOnceOk_MoNITuoche(void)
{
	Addg_tuocheNum();
	SetG_IsTuoche(1);
	if (WorkStation_07_FUN_General_Second_OK_7(0))
	{
		AddExitESMsgCounter4();
		SendLaneInfo("�ϳ�ģ��");
		SendMsgInfo("ģ����Ϣ","","�����ϳ�");
		AddYCQK("�ϳ�");
		SetExitTRMsgDisputeType('4');
		TransDoTuoche();
		SendMsgInfo("������Ϣ","","��ͨ����");
		InitMsgExitTR();
		SendLaneInfo_default();
		Set_WorkStation_51_Tuo_cheMoNi_Like_work3("�����շ�","ģ���ϳ�");
		SendExitEI(EI_Type_MN_TC);
	}
}
void WorkStation_45_SimulateOnceOk(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			Setg_DisputeType(1);
			AddExitESMsgCounter2();
			SendLaneInfo("���ĳ���");
			SendMsgInfo("ģ����Ϣ","","���ĳ���");
			AddYCQK("���ĳ���");
			SendLaneInfo_default();
			SetExitTRMsgDisputeType('2');
			AfterOfTransDo(0,F);
			Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
			SendExitEI(EI_Type_MN_GGCX);
			break;
		case VK_2:
			Setg_DisputeType(1);
			AddExitESMsgCounter3();
			SendLaneInfo("���ĳ���");
			SendMsgInfo("ģ����Ϣ","","���ĳ���");
			AddYCQK("���ĳ���");
			SendLaneInfo_default();
			SetExitTRMsgDisputeType('3');
			AfterOfTransDo(0,F);
			Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
			SendExitEI(EI_Type_MN_GGCZ);
			break;
		case VK_3:
			WorkStation_45_SimulateOnceOk_MoNITuoche();
			break;
		case VK_CANCEL:
			//�Ƿ����ȡ��ģ��״̬
			if (1==atoi(sys_ini.SimulateEnabledCancel))
			{
				Set_WorkStation_07_General_Second_OK(GetG_SaveBeforTipOne(),GetG_SaveBeforTipTwo());
			}
			else
			{
				ErrorPressKey();
			}
			break;
	default:
		ErrorPressKey();
		break;
	}
}
void WorkStation_53_SimulateOnceOkTuoche(int nKey)
{
	switch (nKey)
	{
		case VK_3:
			ErrorPressKey();			
		default:
			WorkStation_45_SimulateOnceOk(nKey);
			break;
	}
}


void WorkStation_51_Tuo_cheMoNi_Like_work3(int nKey)
{
	switch (nKey)
	{
	case VK_1:
	case VK_2:
	case VK_3:
	case VK_4:
	case VK_5:
		SendLaneInfo("������");
		UI_SetCarType(nKey);
		Set_WorkStation_04_General_Validate_Car_Type_And_First_OK();
		break;
	case VK_CLOSE_YPD:		
		SetYuPeng(F);
		break;
	case VK_OPEN_YPD:	
		SetYuPeng(T);
		break;	
	case S_PASSLINEUP://ģ�������ѹ��Ȧ���α���
		if (1==YaxianquanNum)
		{
			SetRing(T);
			Set_WorkStation_49_WeiZhang();
		}
		else
		{
			SetJiaoTong(F);
		}
		break;
	default:
		ErrorPressKey();
		break;
	}
}
