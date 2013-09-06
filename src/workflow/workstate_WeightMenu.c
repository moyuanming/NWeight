#include "LocalIncludeFile.h"
void WorkStation_67_GotoHistory(void)
{
	switch(GetLastWorkState())
	{
	case 3:
		Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");	
		break;
	case 4:
		GetCarWeightInfoForWeight_InterFace();
		if(GetG_WeightMenuStues()==8||GetG_WeightMenuStues()==9)
		{
			HandOnceOK(VK_RETURN,4);
		}
		else
		{
			Set_WorkStation_04_General_Validate_Car_Type_And_First_OK();	
		}
		break;
	case 7:
		GetCarWeightInfoForWeight_InterFace();
		Set_WorkStation_07_General_Second_OK("�����շ�","���ʵ��ȷ��");
		break;
	default:
		Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");	
		break;
	}
}
void WorkStation_67_WeightMenu(int nKey)
{
	switch (nKey)
	{
	case VK_0:
		if(!Get_MenuCZ_Enable(0))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		if(Car_GetNum()>0&&Car_GetCarWeight(0)>0&&(
			WeightCarClassTruck == GetWeightCarClass()||
			WeightCarClassTruckSpecialVehicles==GetWeightCarClass()||
			WeightCarClassBIGTruckVehicles==GetWeightCarClass()))
		{
			SetG_WeightMenuStues(0);
			if(WeightCarClassBIGTruckVehicles==GetWeightCarClass())
			{
				UI_Show_Info("��ʾ��\n��ǰ������Ϊ������䳵\n��ȷ���Ƿ�ȡ��������䳵����\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
			}
			else
			{
				UI_Show_Info("��ʾ��\n��ȷ���Ƿ�����Ϊ������䳵����\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
			}
		}
		else
		{
			UI_Show_Help_Info("�޳�����Ϣ���޷�ת��������䳵");
		}
		break;
		break;
	case VK_1:
		if(!Get_MenuCZ_Enable(1))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		break;
	case VK_2:
		if(!Get_MenuCZ_Enable(2))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		break;
	case VK_3:
		if(!Get_MenuCZ_Enable(3))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		if(Car_GetNum()>0)
		{
			SetG_WeightMenuStues(3);	
			Set_WorkStation_68_WeightMenuCC();
		}
		else
		{
			UI_Show_Help_Info("�޳�����Ϣ���޷�����������Ϣ");
		}
		break;
	case VK_4://�ӳ�
		if(!Get_MenuCZ_Enable(4))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		SetG_WeightMenuStues(4);	
		Set_WorkStation_68_WeightMenuCC();
		//UI_Show_Info("��ʾ��\n��ȷ���Ƿ�ӳ�\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
		break;
	case VK_5://ɾ��
		if(!Get_MenuCZ_Enable(5))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		if(Car_GetNum()>0)
		{
			SetG_WeightMenuStues(5);
			UI_Show_Info("��ʾ��\n��ȷ���Ƿ�ɾ��\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
		}
		else
		{
			UI_Show_Help_Info("�޳�����Ϣ���޷�ɾ��");
		}
		break;
	case VK_6:
		if(!Get_MenuCZ_Enable(6))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		if(Car_GetNum()>0)
		{
			SetG_WeightMenuStues(6);	
			Set_WorkStation_68_WeightMenuCC();
		}
		else
		{
			UI_Show_Help_Info("�޳�����Ϣ���޷�������ǰ������");
		}
		break;
	case VK_7://����
		if(!Get_MenuCZ_Enable(7))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		if(Car_GetNum()==0&&TempCar_GetCarAxlesNum()>0)
		{
			SetG_WeightMenuStues(7);
			UI_Show_Info("��ʾ��\n��ȷ���Ƿ񳤳�����\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
		}
		else
		{
			UI_Show_Help_Info("������������");
		}
		break;
	case VK_8://�������복��
		if(!Get_MenuCZ_Enable(8))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		if(Car_GetNum()>0&&Car_GetCarWeight(0)>0&&(
			WeightCarClassTruck == GetWeightCarClass()||
			WeightCarClassTruckSpecialVehicles==GetWeightCarClass()||
			WeightCarClassBIGTruckVehicles==GetWeightCarClass()))
		{
			SetG_WeightMenuStues(8);
			if(WeightCarClassTruckSpecialVehicles==GetWeightCarClass())
			{
				UI_Show_Info("��ʾ��\n��ǰ������Ϊ���ֳ���\n��ȷ���Ƿ�ȡ�����ֳ�������\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
			}
			else
			{
				UI_Show_Info("��ʾ��\n��ȷ���Ƿ�����Ϊ���ֳ�������\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
			}
		}
		else
		{
			UI_Show_Help_Info("�޳�����Ϣ���޷�ת�����ֳ���");
		}
		break;
		
	case VK_9://ת������
		if(!Get_MenuCZ_Enable(9))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		if(WeightCarClassBUS==GetWeightCarClass()||
			WeightCarClassTruck==GetWeightCarClass()||
			WeightCarClassTruckSpecialVehicles==GetWeightCarClass()||
			WeightCarClassBIGTruckVehicles==GetWeightCarClass())
		{
			SetG_WeightMenuStues(9);
			UI_Show_Info("��ʾ��\n��ȷ���Ƿ�ת������\n����ȷ�ϡ���ȷ��,\n����ȡ������ȡ����");
		}
		else
		{
			UI_Show_Help_Info("��ǰ�޷�ת������");
		}
		break;
	case VK_CANCEL:
		if(GetG_WeightMenuStues()>=0)
		{
			SetG_WeightMenuStues(-1);
			UI_Show_Info("��ʾ��\n�밴�����֡���ѡ��˵�\n����ȡ������ȡ����");
		}
		else
		{
			WorkStation_67_GotoHistory();
		}
		break;
	case VK_RETURN:
		if(!Get_MenuCZ_Enable(GetG_WeightMenuStues()))
		{
			UI_Show_Help_Info("��ǰ�˵�����ѡ");
			break;
		}
		switch(GetG_WeightMenuStues())
		{
		case 0:
			if(Car_GetNum()>0&&Car_GetCarWeight(0)>0&&(
				WeightCarClassTruck == GetWeightCarClass()||
				WeightCarClassTruckSpecialVehicles==GetWeightCarClass()||
				WeightCarClassBIGTruckVehicles==GetWeightCarClass()))
			{
				if(WeightCarClassBIGTruckVehicles==GetWeightCarClass())
				{
					SetWeightCarClass(WeightCarClassTruck);
				}
				else
				{
					SetWeightCarClass(WeightCarClassBIGTruckVehicles);
					SendExitEI(EI_Type_JZ_DJHC);
				}
				WorkStation_67_GotoHistory();
			}
			else
			{
				UI_Show_Help_Info("�޳�����Ϣ���޷�ʹ�����ֳ���");
			}
			break;
		/*case 4:
				AddTempCarInfo();
				WorkStation_67_GotoHistory();
			break;*/
		case 5:
			if(Car_GetNum()>0)
			{
				/*
				wds_Wait_SEM();
				Car_QueuePop();
				CarList_Change();
				wds_Post_SEM();
				*/
				RemoveFirstCarWeightInfo();
				SendExitEI(EI_Type_JZ_SCCLXX);
				WorkStation_67_GotoHistory();	
			}
			else
			{
				UI_Show_Help_Info("�޳�����Ϣ���޷�ɾ��");
			}
			break;
		case 7:
			if(Car_GetNum()==0&&TempCar_GetCarAxlesNum()>0)
			{
				SetG_IsChangche(1);
				SetLanGan(T);
				SetJiaoTong(T);
				SendExitEI(EI_Type_JZ_CC);
				WorkStation_67_GotoHistory();
			}
			else
			{
				UI_Show_Help_Info("������������");
			}
			break;
		case 8:
			if(Car_GetNum()>0&&Car_GetCarWeight(0)>0&&(
				WeightCarClassTruck == GetWeightCarClass()||
				WeightCarClassTruckSpecialVehicles==GetWeightCarClass()||
				WeightCarClassBIGTruckVehicles==GetWeightCarClass()))
			{
				if(WeightCarClassTruckSpecialVehicles==GetWeightCarClass())
				{
					SetWeightCarClass(WeightCarClassTruck);
				}
				else
				{
					SetWeightCarClass(WeightCarClassTruckSpecialVehicles);
					SendExitEI(EI_Type_JZ_TZCL);
				}
				WorkStation_67_GotoHistory();
			}
			else
			{
				UI_Show_Help_Info("�޳�����Ϣ���޷�ʹ�����ֳ���");
			}
			break;
		case 9:
			if(WeightCarClassBUS==GetWeightCarClass()||WeightCarClassTruck==GetWeightCarClass()||WeightCarClassTruckSpecialVehicles==GetWeightCarClass())
			{
				SetWeightCarClass(WeightCarClassTruckISNotUseWeight);
				UI_ShowTruck();
				SendExitEI(EI_Type_JZ_ZHCL);
				WorkStation_67_GotoHistory();
			}
			else
			{
				UI_Show_Help_Info("��ǰ�޷�ת������");
			}
			break;
		default:
			ErrorPressKey();
			break;
		}
		break;
	default:
		ErrorPressKey();
		break;
	}
}
///
void WorkStation_68_WeightMenuCC(int nKey)
{
	int AxlesNum = 0;
	switch(GetG_WeightMenuStues())
	{
	case 3:
		if(Car_GetNum()==0)
		{
			UI_Show_Help_Info("�޳�����Ϣ���޷�����������Ϣ");
			Set_WorkStation_67_WeightMenu();
			return;
		}
		break;
	case 6:
		if(Car_GetNum()==0)
		{
			UI_Show_Help_Info("�޳�����Ϣ���޷���������");
			Set_WorkStation_67_WeightMenu();
			return;
		}
		break;
	}
	switch (nKey)
	{
	case VK_0:
	case VK_1:
	case VK_2:
	case VK_3:
	case VK_4:
	case VK_5:
	case VK_6:
	case VK_7:
	case VK_8:
	case VK_9:
		GetG_CarAxlesNum()[strlen(GetG_CarAxlesNum())] = KeyChangCode(nKey);
		AxlesNum = atoi(GetG_CarAxlesNum());
		switch(GetG_WeightMenuStues())
		{
		case 3:
			if(AxlesNum<=Car_GetCarListAxlesNum())
			{
				UI_Show_Input_Text(GetG_CarAxlesNum());
			}
			else
			{
				GetG_CarAxlesNum()[strlen(GetG_CarAxlesNum())-1] = 0;
				UI_Show_Help_Info("������ǰ��������");
			}
			break;
		case 6:
		case 4:
			if(AxlesNum<200)
			{
				UI_Show_Input_Text(GetG_CarAxlesNum());
			}
			else
			{
				GetG_CarAxlesNum()[strlen(GetG_CarAxlesNum())-1] = 0;
				UI_Show_Help_Info("���복��������");
			}
			break;
		}
		break;
	case VK_CANCEL:
		if(GetG_CarAxlesNum()[0]==0)
		{
			Set_WorkStation_67_WeightMenu();
		}
		else
		{
			InitG_CarAxlesNum();
			UI_Show_Input_Text(GetG_CarAxlesNum());
		}
		break;
	case VK_RETURN:
		AxlesNum = atoi(GetG_CarAxlesNum());
		switch(GetG_WeightMenuStues())
		{
		case 3:
			if(AxlesNum<=Car_GetCarListAxlesNum()&&AxlesNum>1)
			{
				InitG_CarAxlesNum();
				ModifyAxlesNo(AxlesNum);
				SendExitEI(EI_Type_JZ_XZCLXX);
				WorkStation_67_GotoHistory();	
				return;
			}
			break;
		case 4:
			if(AxlesNum>1)
			{
				InitG_CarAxlesNum();
				AddTempCarInfo(AxlesNum);
				SendExitEI(EI_Type_JZ_TJCLXX);
				WorkStation_67_GotoHistory();	
				return;
			}
			break;
		case 6:
			if(AxlesNum>1)
			{
				InitG_CarAxlesNum();
				ModifyCarAxlesByNo(AxlesNum);
				SendExitEI(EI_Type_JZ_XZCLZS);
				WorkStation_67_GotoHistory();	
				return;
			}
			break;
		}
		UI_Show_Help_Info("�������������");
		break;
	default:
		ErrorPressKey();
		break;
	}
}

