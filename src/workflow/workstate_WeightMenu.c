

#include "LocalIncludeFile.h"
void WorkStation_67_GotoHistory()
{
	switch(GetLastWorkState())
	{
	case 3:
		Set_WorkStation_03_Main_Work("正常收费","等待来车");	
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
		Set_WorkStation_07_General_Second_OK("正常收费","请核实并确认");
		break;
	default:
		Set_WorkStation_03_Main_Work("正常收费","等待来车");	
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
			UI_Show_Help_Info("当前菜单不可选");
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
				UI_Show_Info("提示：\n当前已设置为大件运输车\n请确认是否取消大件运输车操作\n按【确认】键确认,\n按【取消】键取消。");
			}
			else
			{
				UI_Show_Info("提示：\n请确认是否设置为大件运输车操作\n按【确认】键确认,\n按【取消】键取消。");
			}
		}
		else
		{
			UI_Show_Help_Info("无称重信息，无法转换大件运输车");
		}
		break;
		break;
	case VK_1:
		if(!Get_MenuCZ_Enable(1))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		break;
	case VK_2:
		if(!Get_MenuCZ_Enable(2))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		break;
	case VK_3:
		if(!Get_MenuCZ_Enable(3))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		if(Car_GetNum()>0)
		{
			SetG_WeightMenuStues(3);	
			Set_WorkStation_68_WeightMenuCC();
		}
		else
		{
			UI_Show_Help_Info("无称重信息，无法修正称重信息");
		}
		break;
	case VK_4://加车
		if(!Get_MenuCZ_Enable(4))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		SetG_WeightMenuStues(4);	
		Set_WorkStation_68_WeightMenuCC();
		//UI_Show_Info("提示：\n请确认是否加车\n按【确认】键确认,\n按【取消】键取消。");
		break;
	case VK_5://删车
		if(!Get_MenuCZ_Enable(5))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		if(Car_GetNum()>0)
		{
			SetG_WeightMenuStues(5);
			UI_Show_Info("提示：\n请确认是否删车\n按【确认】键确认,\n按【取消】键取消。");
		}
		else
		{
			UI_Show_Help_Info("无称重信息，无法删车");
		}
		break;
	case VK_6:
		if(!Get_MenuCZ_Enable(6))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		if(Car_GetNum()>0)
		{
			SetG_WeightMenuStues(6);	
			Set_WorkStation_68_WeightMenuCC();
		}
		else
		{
			UI_Show_Help_Info("无称重信息，无法修正当前车轴数");
		}
		break;
	case VK_7://长车
		if(!Get_MenuCZ_Enable(7))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		if(Car_GetNum()==0&&TempCar_GetCarAxlesNum()>0)
		{
			SetG_WeightMenuStues(7);
			UI_Show_Info("提示：\n请确认是否长车操作\n按【确认】键确认,\n按【取消】键取消。");
		}
		else
		{
			UI_Show_Help_Info("不允许长车操作");
		}
		break;
	case VK_8://重量减半车辆
		if(!Get_MenuCZ_Enable(8))
		{
			UI_Show_Help_Info("当前菜单不可选");
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
				UI_Show_Info("提示：\n当前已设置为特种车辆\n请确认是否取消特种车辆操作\n按【确认】键确认,\n按【取消】键取消。");
			}
			else
			{
				UI_Show_Info("提示：\n请确认是否设置为特种车辆操作\n按【确认】键确认,\n按【取消】键取消。");
			}
		}
		else
		{
			UI_Show_Help_Info("无称重信息，无法转换特种车辆");
		}
		break;
		
	case VK_9://转换车辆
		if(!Get_MenuCZ_Enable(9))
		{
			UI_Show_Help_Info("当前菜单不可选");
			break;
		}
		if(WeightCarClassBUS==GetWeightCarClass()||
			WeightCarClassTruck==GetWeightCarClass()||
			WeightCarClassTruckSpecialVehicles==GetWeightCarClass()||
			WeightCarClassBIGTruckVehicles==GetWeightCarClass())
		{
			SetG_WeightMenuStues(9);
			UI_Show_Info("提示：\n请确认是否转换车辆\n按【确认】键确认,\n按【取消】键取消。");
		}
		else
		{
			UI_Show_Help_Info("当前无法转换货车");
		}
		break;
	case VK_CANCEL:
		if(GetG_WeightMenuStues()>=0)
		{
			SetG_WeightMenuStues(-1);
			UI_Show_Info("提示：\n请按【数字】键选择菜单\n按【取消】键取消。");
		}
		else
		{
			WorkStation_67_GotoHistory();
		}
		break;
	case VK_RETURN:
		if(!Get_MenuCZ_Enable(GetG_WeightMenuStues()))
		{
			UI_Show_Help_Info("当前菜单不可选");
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
				UI_Show_Help_Info("无称重信息，无法使用特种车辆");
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
				UI_Show_Help_Info("无称重信息，无法删车");
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
				UI_Show_Help_Info("不允许长车操作");
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
				UI_Show_Help_Info("无称重信息，无法使用特种车辆");
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
				UI_Show_Help_Info("当前无法转换货车");
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
			UI_Show_Help_Info("无称重信息，无法修正称重信息");
			Set_WorkStation_67_WeightMenu();
			return;
		}
		break;
	case 6:
		if(Car_GetNum()==0)
		{
			UI_Show_Help_Info("无称重信息，无法修正轴数");
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
				UI_Show_Help_Info("超过当前车轴总数");
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
				UI_Show_Help_Info("输入车轴数过大");
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
		UI_Show_Help_Info("车轴数输入错误");
		break;
	default:
		ErrorPressKey();
		break;
	}
}

