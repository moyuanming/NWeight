#include "LocalIncludeFile.h"



/*-------------------------------------------------------------------------------------------------------------------
函数名称：     void WorkSation_56_CheckCharFold(int  nKey)
作用：          检测字符叠加
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (57)
创建日期：      2008.6
最后修改日期:   2008.6
--------------------------------------------------------------------------------------------------------------------*/
void WorkStation_56_CheckCharFold(int  nKey)
{

	switch (nKey)
	{
		case VK_RETURN:
			UI_Show_Help_Info("正在检测，请稍候……");
			Set_WorkStation_57_CheckCharFoldResult();
			break;
		case VK_CANCEL:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}

/*-------------------------------------------------------------------------------------------------------------------
函数名称：     void WorkSation_57_CheckCharFoldResult(int nKey)
作用：          字符叠加检测结果
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (31)
创建日期：      2008.6
最后修改日期:   2008.6
--------------------------------------------------------------------------------------------------------------------*/
void WorkStation_57_CheckCharFoldResult(int nKey)
{
	switch (nKey)
	{
		case VK_RETURN:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}


void WorkStation_31_SelectCheckDev(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			Set_WorkStation_32_CheckBar();
			break;
		case VK_2:

			Set_WorkStation_33_CheckPassLight();
			break;
		case VK_3:
			Set_WorkStation_34_CheckSkyLight();
			break;
		case VK_4:
			TestprintBill();
			Set_WorkStation_36_CheckPrinterResult();
			break;
		case VK_5:
			Set_WorkStation_37_CheckKeyBord();
			break;
		case VK_6:
			Set_WorkStation_44_TestLed();
			break;
		case VK_7:
			Set_WorkStation_39_CheckRing();
			break;
		case VK_8:
			Set_WorkStation_56_CheckCharFold();
			break;
		case VK_CANCEL:
			Set_WorkStation_30_SelectWorkMod();
			break;
		default:
			ErrorPressKey();
			break;
	}
}




int CheckType = 0;
void WorkStation_32_CheckBar(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			CheckType =1;

			SetLanGan(T);echoic("___");	
			SendLaneInfo_default();
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_2:
			CheckType =2;

			SetLanGan(F);echoic("___");	
			SendLaneInfo_default();
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_CANCEL:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_33_CheckPassLight(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			CheckType =3;
			SetJiaoTong(F);
			SendLaneInfo_default();
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_2:
			CheckType =4;
			SetJiaoTong(T);
			SendLaneInfo_default();
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_CANCEL:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_34_CheckSkyLight(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			CheckType =5;
			SetYuPeng(F);
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_2:
			CheckType =6;
			SetYuPeng(T);
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_CANCEL:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}


void WorkStation_35_SelectCheckResult(int nKey)
{
	switch (nKey)
	{
		case VK_RETURN:
			switch (CheckType)
			{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
			}
			Set_WorkStation_31_SelectCheckDev();
			break;
		case VK_CANCEL:
			switch (CheckType)
			{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
			}
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}



void WorkStation_36_CheckPrinterResult(nKey)
{
	switch (nKey)
	{
		case VK_RETURN:
			Set_WorkStation_31_SelectCheckDev();
			break;
		case VK_CANCEL:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_37_CheckKeyBord(int nKey)
{
	setLed();
	switch (nKey)
	{
		case  VK_0:
			UI_Show_Help_Info("当前按健为【0】键");
			break;
		case  VK_1:
			UI_Show_Help_Info("当前按健为【1】键");
			break;
		case  VK_2:
			UI_Show_Help_Info("当前按健为【2】键");
			break;
		case  VK_3:
			UI_Show_Help_Info("当前按健为【3】键");
			break;
		case  VK_4:
			UI_Show_Help_Info("当前按健为【4】键");
			break;
		case  VK_5:
			UI_Show_Help_Info("当前按健为【5】键");
			break;
		case  VK_6:
			UI_Show_Help_Info("当前按健为【6】键");
			break;
		case  VK_7:
			UI_Show_Help_Info("当前按健为【7】键");
			break;
		case  VK_8:
			UI_Show_Help_Info("当前按健为【8】键");
			break;
		case  VK_9:
			UI_Show_Help_Info("当前按健为【9】键");
			break;
		case  VK_CANCEL:
			Set_WorkStation_38_CheckKeyBordResult();
			break;
		case  VK_YOUHUICARD:
			UI_Show_Help_Info("当前按健为【优惠】键");
			break;
		case VK_MOUNTHCARD:
			UI_Show_Help_Info("当前按健为【月票】键");
			break;
		case  VK_QIANKUAN:
			UI_Show_Help_Info("当前按健为【欠费】键");
			break;
		case  VK_LVSETONGDAO:
			UI_Show_Help_Info("当前按健为【绿色通道】键");
			break;
		case  VK_RETURN:
			UI_Show_Help_Info("当前按健为【确认】键");
			break;
		case  VK_WEIZHANG:
			UI_Show_Help_Info("当前按健为【违章】键");
			break;
		case  VK_JUNCHE:
			UI_Show_Help_Info("当前按健为【军车】键");
			break;
		case  VK_GONGWU:
			UI_Show_Help_Info("当前按健为【公务车】键");
			break;
		case  VK_BEIYONG:
			UI_Show_Help_Info("当前按健为【备用1】键");
			break;
		case  VK_SHANGBAN:
			UI_Show_Help_Info("当前按健为【上班】键");
			break;
		case  VK_XIABAN:
			UI_Show_Help_Info("当前按健为【下班】键");
			break;
		case  VK_CLOSE_YPD:
			UI_Show_Help_Info("当前按健为【关闭雨棚灯】键");
			break;
		case  VK_OPEN_YPD:
			UI_Show_Help_Info("当前按健为【打开雨棚灯】键");
			break;
		case  VK_OPEN:
			UI_Show_Help_Info("当前按健为【开启车道】键");
			break;
		case  VK_CLOSE:
			UI_Show_Help_Info("当前按健为【关闭车道】键");
			break;
		/*case  VK_LANGAN:
			UI_Show_Help_Info("当前按健为【欠费】键");
			break;*/
		case  VK_MONI:
			UI_Show_Help_Info("当前按健为【模拟】键");
			break;
			/*case  VK_CHEDUI_G:
				show_Help("当前按健为【车队开启】键");	
				break;*/
		/*case  VK_CHEDUI_R:
			UI_Show_Help_Info("当前按健为【车队结束】键");*/
			break;
		case  VK_LEFT:
			UI_Show_Help_Info("当前按健为【箭头左】键");
			break;
		case  VK_RIGHT:
			UI_Show_Help_Info("当前按健为【箭头右】键");
			break;
		case  VK_UP:
			UI_Show_Help_Info("当前按健为【箭头上】键");
			break;
		case  VK_DOWN:
			UI_Show_Help_Info("当前按健为【箭头下】键");
			break;
		case  VK_URGENT:
			UI_Show_Help_Info("当前按健为【紧急】键");
			break;
		case  VK_LONGYONG:
			UI_Show_Help_Info("当前按健为【备用2】键");
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_38_CheckKeyBordResult(int nKey)
{
	switch (nKey)
	{
		case  VK_1:
			Set_WorkStation_31_SelectCheckDev();
			break;
		case  VK_2:
			Set_WorkStation_31_SelectCheckDev();
			break;
		case VK_RETURN:
			Set_WorkStation_37_CheckKeyBord();
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_39_CheckRing(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			CheckType =7;
			SetRing(T);
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_2:
			CheckType =8;
			SetRing(F);
			Set_WorkStation_35_SelectCheckResult();
			break;
		case VK_CANCEL:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}


void WorkStation_44_TestLed(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			LedShowCharge('1',5);
			break;
		case VK_2:
			LedClare(T);
			break;
		case VK_3:
			//LedSound(THANKS);
			break;
		case VK_4:
			//LedSound(WELCOME);
			break;
		case VK_5:
			//LedSound(PLEGO);
			break;
		case VK_6:
			//LedSound(GOODBYE);
			break;
		case VK_7:
			//LedSound(ITEASY);
			break;
		case VK_CANCEL:
			Set_WorkStation_31_SelectCheckDev();
			break;
		default:
			ErrorPressKey();
			break;
	}
}
