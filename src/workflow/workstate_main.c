#include "LocalIncludeFile.h"
#include "mac.h"
#include "imf.h"
#include "3des.h"
static void KeyPressHandl(int currentworkstate)
{		

	//G_Calculate_Final_Fare();	
	if(0!=strcmp(trim(Getg_CurrentCarKindExplain()),"收费车"))
	{	
		SetVideoAlarm(T);	
	}
	else
	{
		OpenMoneyBox();
	}
	switch(currentworkstate)
	{	
	case 4:
		if (5==Getg_CurrentCarKindIndex()  || 9==Getg_CurrentCarKindIndex() )
		{
			Set_WorkStation_66_InputCarNo("输入车牌号");
		}
		else
		{
			Set_WorkStation_07_General_Second_OK("正常收费","请核实并确认");	
		}              
		break;       
	default:
		break;
	}



}


void  HandOnceOK(int keyboardValue,int currentworkstate)
{	
	if(-1 ==Validate_Car_Kind(keyboardValue))
	{	
		ErrorPressKey();
		return;
	}
	if(-1==Get_Current_Car_Type_Index())
	{	
		switch(currentworkstate)
		{	
		case 4:
			Set_WorkStation_03_Main_Work("正常收费","等待来车");	
			SendLaneInfo("等待来车");	
			break;               
		default:
			break;
		}
		UI_Show_Help_Info("车型输入不正确请重新输入!");	
	}
	else
	{	
		KeyPressHandl(currentworkstate);	
	}


}
/*----------------------------------------------------------------------
函数名称：      void WorkStation_0_Wait_Begin_Work(int nKey)
作用：          开启车道等待上班，下班后等上班。
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (1)
创建日期：      2005.10
创建人:         莫远明
最后修改日期:   2008.05
最后修改人:     王海伟
----------------------------------------------------------------------*/

void WorkStation_03_Main_Work(int nKey)
{
	switch (nKey)
	{
		//case VK_0:

		case VK_6:
		case VK_7:
		case VK_8:
		case VK_9:
			if( Getg_carTypeLen() ==1)
			{
				ErrorPressKey();  
				break;
			}
		case VK_1:
		case VK_2:
		case VK_3:
		case VK_4:
		case VK_5:
			if(GetYuPengState())
			{
				SendLaneInfo("处理车型");
				UI_SetCarType(nKey);
				Set_WorkStation_04_General_Validate_Car_Type_And_First_OK(); 
			}
			else
			{
				UI_Show_Help_Info("请首先打开雨棚灯再进行收费。");
			}
			break;
		case VK_CLOSE_YPD:
			if (Getg_bYuPeng())
			{
				UI_Show_Info("提示：\n按【数字】键输入车型；\n按【紧急】键处理紧急车\n按【绿↓】键打开雨棚灯\n按【下班】键下班");
				
			}
			SetYuPeng(F);
			break;
		case VK_OPEN_YPD:	
			if (!Getg_bYuPeng())
			{
				UI_Show_Info("提示：\n按【数字】键输入车型；\n按【紧急】键处理紧急车\n按【红X】键关闭雨棚灯");

			}
			SetYuPengState(1);
			SetYuPeng(T);
			break;
		case VK_URGENT:
			Set_WorkStation_09_Handl_Urgent_Car_Team();
			break;
		case VK_XIABAN:
			if (Getg_bLanGan())
			{
				UI_Show_Help_Info("请等车辆通过后下班!");
			}
			else if (Getg_bYuPeng())
			{
				UI_Show_Help_Info("请先关闭雨棚灯再按【下班】键！");
			}
			else
			{
				SendLaneInfo("正在下班");
				Set_WorkStation_20_EndWorkOk();
			}
			break;
		case VK_MONI:
			if (1==atoi(sys_ini.SimulateEnabledFistTuoChe) && (1==GetG_IsTuoche()))
			{
				SetG_simulateWorkState(10);
				Set_WorkStation_45_SimulateOnceOk();
			}
			else
			{
				ErrorPressKey();
			}
			break;
		case VK_CHAHAO:
			Set_WorkStation_204_FreeCar();
			break;
		case VK_Weight:
			Set_WorkStation_67_WeightMenu();
			break;
		case S_PASSLINEUP:
			break;
		default:
			ErrorPressKey();
			break;
	}
}

/*----------------------------------------------------------------------
函数名称：      void WorkStation_4_General_Validate_Car_Type_And_First_OK(int nKey)
作用：          正常收费安下数字键后跳转到这个状态验证车型。
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (3，7，10)
创建日期：      2005.10
创建人:         莫远明
最后修改日期:   2008.07
最后修改人:     王海伟
----------------------------------------------------------------------*/
void WorkStation_04_General_Validate_Car_Type_And_First_OK(int nKey)
{
	GetCarWeightInfoForWeight_InterFace();
	switch (nKey)
	{

		case VK_0:
			if(Getg_carTypeLen() ==1)
			{
				ErrorPressKey();  
				break;
			}
		case VK_6:
		case VK_7:
		case VK_8:
		case VK_9:
			if( Getg_carTypeLen() ==1 && WeightCarClassBUS!=GetWeightCarClass())
			{
				ErrorPressKey();  
				break;
			}
		case VK_1:
		case VK_2:
		case VK_3:
		case VK_4:
		case VK_5:
			
			if(Getg_carTypeLen() ==1 )
			{
				UI_SetCarType( nKey);
				UI_ShowTruck();
			}
			else if(strlen(Get_Current_Car_Type())<Getg_carTypeLen())
			{
				if(OLD312JaoKeCalculateFareMode == GetJaoKeCalculateFareMode() && WeightCarClassBUS!=GetWeightCarClass() && strlen(Get_Current_Car_Type()) >1 )
				{
					UI_Show_Help_Info("车型位数已输够！"); 
				}
				else
				{
					UI_SetCarType( nKey);
					UI_ShowTruck();				
				}
				
			}
			else
			{
				UI_Show_Help_Info("车型位数已输够！");  
			}
			
			break;
		case VK_LVSETONGDAO:
			if(Get_Weight_Is_JianMian())
			{
				HandOnceOK( nKey,4);
			}
			else
			{
				HandOnceOK( VK_RETURN,4);
			}
			break;
		case VK_YOUHUICARD:
			if(Get_Weight_Is_JianMian())
			{
				Setg_AbateType(0); 
				Set_WorkStation_23_Abate("请输入卡号");
			}
			else
			{
				HandOnceOK( VK_RETURN,4);
			}
			break;
		case VK_MOUNTHCARD:
			if(Get_Weight_Is_JianMian())
			{
				Setg_AbateType(1); 
				Set_WorkStation_23_Abate("请输入卡号");
			}
			else
			{
				HandOnceOK( VK_RETURN,4);
			}			
			break;
		case VK_CANCEL:
			if (GetG_IsTuoche())
			{
				Set_WorkStation_51_Tuo_cheMoNi_Like_work3("正常收费","拖车模拟");
			}
			else
			{
				Set_WorkStation_03_Main_Work("正常收费","等待来车");
			}
			break;
		case VK_CLOSE_YPD:
			SetYuPeng(F);
			break;
		case VK_OPEN_YPD:
			SetYuPeng(T);
			break;
		case VK_TRUCK:
			if(NotUseWeight != GetWeightFunctions())
			{
				
				if(WeightCarClassBUS==GetWeightCarClass())
				{
					if(Getg_carTypeLen() ==1 && OLD312JaoKeCalculateFareMode == GetJaoKeCalculateFareMode() && (strlen(Get_Current_Car_Type())>1 || atoi(Get_Current_Car_Type()) > 5))
					{
						UI_Show_Help_Info("吨位不能转成车型请重新输入车型！");
						break;
					}
					SetWeightCarClass(FullWeight==GetWeightFunctions()? WeightCarClassTruck:WeightCarClassTruckISNotUseWeight);
				}
				else
				{
					SetWeightCarClass(WeightCarClassBUS);					
				}
				if(WeightCarClassBUS!=GetWeightCarClass()&&Car_GetNum()==0&&GetWeightFunctions()!=FullWeight)
				{
					SetWeightCarClass(WeightCarClassBUS);	

					UI_Show_Help_Info("无法取得计重信息，请添加一辆车确认车种后转换车辆");
				}
				UI_ShowTruck();
				break;
			}
		else
		{
		echoic("修改配置文件常量表中的字段");
			UI_Show_Help_Info("计重功能没启用！");
			break;
		}
	case VK_Weight:
		Set_WorkStation_67_WeightMenu();
		break;
	default:
			HandOnceOK( nKey,4);		
			break;
	}
}

/*----------------------------------------------------------------------
函数名称：      void WorkStation_6_Closed_Road(int nKey)
作用：          临时封闭车道，按开启键开启。
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (2)
创建日期：      2005.10
创建人:         莫远明
最后修改日期:   2005.10
最后修改人:     莫远明
----------------------------------------------------------------------*/
void WorkStation_06_Closed_Road(int nKey)
{
	if (nKey == VK_OPEN)
	{
		Set_WorkStation_02_Handl_Input_Password();
	}
	else
	{
		ErrorPressKey();
	}

}
/*----------------------------------------------------------------------
函数名称：      void WorkStation_7_General_Second_OK(int nKey)
作用：          正常收费第一次确认后跳转状态，进行第二次确认或取消收费。
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (3，10)
创建日期：      2005.10
创建人:         莫远明
最后修改日期:   2005.10 ,2006-12-15
最后修改人:     莫远明
----------------------------------------------------------------------*/
int WorkStation_07_FUN_General_Second_OK_7(int Flag )
{
	int ret = 1;	
	if (1==GetG_BillPrintFlag())
	{
		if (postPrinter(T))
		{
			CaptureImg(IMG_SECOND);			
			SetG_reprintbillnum(0);
			if (Flag)
			{
				Set_WorkStation_10_Up_Parapet_Pass();
			}
			else
			{
				SetPassCar();
			}
		}
		else
		{
			setLed();
			SendMsgEI(MSGEI_PRINTER_ERROR ,MSGEI_STATUS_MSGINFO,"打印机故障");	//lzp// 打印机故障   MSGEI 事件处理
			UI_Show_Help_Info("打印机故障！");
			ret = 0;
		}
	}
	else
	{
		CaptureImg(IMG_SECOND);
		SetG_reprintbillnum(0);
		if (Flag)
		{
			Set_WorkStation_10_Up_Parapet_Pass();
		}
		else
		{
			SetPassCar();
		}
	}
	return ret;
}
/**
 * 等待二次确认，确认为现金支付
 * 
 * @param nKey
 */
void WorkStation_07_General_Second_OK(int nKey)
{
	int ShiSou = 0;
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
			GetG_ZhaoLing()[strlen(GetG_ZhaoLing())] = KeyChangCode(nKey);
			ShiSou = atoi(GetG_ZhaoLing());
			UI_Show_ZhaoLing(ShiSou);
			break;
		case   CSC_CARDENTER:
			{
				int ret;
				ret=UseCardToPay();
				switch (ret )
				{
					case PAYRET_OK://  0  //返回正常
						//说明一切正常
						break;
					case  PAYRET_READCARDERROR://  1//读卡失败
						UI_Show_Help_Info("抱歉！读卡失败，请重试!");
						break;
					case  PAYRET_READCARDKEYOLD://  1//读卡失败
						UI_Show_Help_Info("抱歉！卡密钥已过期!");
						break;
					case  PAYRET_READCARDKEYNOTFOND://  1//读卡失败
						UI_Show_Help_Info("抱歉！未找到卡信息!");
						break;
					case  PAYRET_CARDTYPEINVALID:// 2//卡类型无效。
						UI_Show_Help_Info("抱歉！此卡不是有效的可支付卡!");
						break;
					case PAYRET_CARTYPEERROR:
						UI_Show_Help_Info("抱歉，车型不符!");
						break;
					case PAYRET_PRINTERERROR:
						UI_Show_Help_Info("打印机故障，请修复打印机后再刷卡!");
						break;
					default:
						UI_Show_Help_Info("抱歉！无效卡");//未处理的返回值
						break;
				}
				echoic("这里刷卡%s",       GetCardNOByString());
			}
			break;
		case  CSC_CARDEXIT:
			echoic("卡已经被拿走了  卡号是 %s",     GetCardNOByString());
			break;
		case VK_RETURN:
			if (0==GetG_IsTuoche())
			{				
				if (0==Getg_bLanGan()||1==GetG_IsChangche())
				{
					//暂时去掉落干才能确认的判断，针对乌拉泊平凡出现不落干，会出现前一辆车落干
					WorkStation_07_FUN_General_Second_OK_7(1);
				}
				else
				{
					UI_Show_Help_Info("按键无效，请按提示进行操作。");
				}
			}
			else
			{
				WorkStation_07_FUN_General_Second_OK_7(1);
			}
			CaptureImg('0');
			break;
		case VK_DOWN:
			LogCAppLogDebug("强制落干");
			SetLanGan(F);
			break;
		case VK_QIANKUAN:
			Set_WorkStation_42_HandArrearageNumber(7);
			break;
		case VK_CANCEL:
			if(GetG_ZhaoLing()[0]==0)
			{
				if (1==atoi(sys_ini.OnceOkEnabledCancel))
				{
					Set_WorkStation_03_Main_Work("正常收费","等待来车");
				}
				else
				{
					ErrorPressKey();
				}
			}
			else
			{
				InitG_ZhaoLing();
				UI_Show_ZhaoLing(0);
			}
			break;
		case VK_CLOSE_YPD:
			SetYuPeng(F);
			break;
		case VK_OPEN_YPD:
			SetYuPeng(T);
			break;
		case VK_MONI:			
			SendLaneInfo("正在模拟");
			if (0==GetG_IsTuoche())
			{					
				Set_WorkStation_45_SimulateOnceOk();
			}
			else
			{					
				Set_WorkStation_53_SimulateOnceOkTuoche();
			}			
			break;
		case VK_Weight:
			Set_WorkStation_67_WeightMenu();
			break;
		default:
			ErrorPressKey();
			break;
	}
}

/*----------------------------------------------------------------------
函数名称：      void WorkStation_10_Up_Parapet_Pass(int nKey)
作用：          正常收费二次确认抬杆放行时工作状态。
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (3，21)
创建日期：      2005.10
创建人:         莫远明
最后修改日期:   2005.10
最后修改人:     莫远明
----------------------------------------------------------------------*/
void WorkStation_10_Up_Parapet_Pass(int nKey)
{
	switch (nKey)
	{
		case S_PASSLINEUP:
			echo_debug("WorkStation_10_Up_Parapet_Pass Start");
			if (0!=GetG_IsTuoche())
			{
				AddYCQK("被拖车");
				SetJiaoTong(F);
				SetG_IsTuoche(0);//硬托             SetG_IsTuoche(GetG_IsTuoche()-1)//软拖
			}
			echo_debug("Run Is!");
			AfterOfTransDo(1,F);
			if(0!=GetG_IsChangche())
			{
				SetG_IsChangche(0);
			}
			echo_debug("Run Is!");
			/*if(0!=GetG_IsTeZhongChe())
			{
				SetG_IsTeZhongChe(0);
			}*/
			SetJiaoTong(F);
			echo_debug("Run Is!");
			SendMsgInfo("过车消息","","普通过车");	   //qq		
			SendLaneInfo_default();
			echo_debug("Run Is!");
			SendLaneInfo("等待来车");
			echo_debug("Run Is!");
			Set_WorkStation_03_Main_Work("正常收费","等待来车");
			echo_debug("WorkStation_10_Up_Parapet_Pass End");
			break;
		case VK_CLOSE_YPD:
			SetYuPeng(F);
			break;
		case VK_OPEN_YPD:
			SetYuPeng(T);
			break;
		case VK_MONI:			
			SetG_simulateWorkState(10);
			SendLaneInfo("正在模拟");
			Set_WorkStation_46_SimulateTwoOk();			
			break;
		default:
			ErrorPressKey();
			break;
	}
}







void WorkStation_28_CarNumber_Second_OK(int nKey)
{

	switch (nKey)
	{
		
		case VK_RETURN:
			SetG_reprintbillnum(0);
			Set_WorkStation_10_Up_Parapet_Pass();
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


/*-------------------------------------------------------------------------------------------------------------------
函数名称：     WorkStation_50_DataExporter(int nKey)
作用：           用usb设备导出车道数据
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (20)
创建日期：      2008.6
最后修改日期:   2008.6
--------------------------------------------------------------------------------------------------------------------*/
int  itWorking=0;
void WorkStation_50_DataExporter(int nKey)
{
	switch (nKey)
	{
		case VK_CANCEL:
			if (0==itWorking)
			{
				Set_WorkStation_30_SelectWorkMod();
			}
			else
			{
				UI_Show_Help_Info("正在导出数据，请稍候....");
			}
			break;
		case VK_RETURN:
			itWorking=1;
			DataExporter();
			itWorking=0;
			break;
		default:
			ErrorPressKey();
			break;
	}
}


