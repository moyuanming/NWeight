#include "LocalIncludeFile.h"



/*-------------------------------------------------------------------------------------------------------------------
�������ƣ�     void WorkSation_56_CheckCharFold(int  nKey)
���ã�          ����ַ�����
������          int nKey ���̼�ֵ
����ֵ��        ��
��̣�          WorkStation (57)
�������ڣ�      2008.6
����޸�����:   2008.6
--------------------------------------------------------------------------------------------------------------------*/
void WorkStation_56_CheckCharFold(int  nKey)
{

	switch (nKey)
	{
		case VK_RETURN:
			UI_Show_Help_Info("���ڼ�⣬���Ժ򡭡�");
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
�������ƣ�     void WorkSation_57_CheckCharFoldResult(int nKey)
���ã�          �ַ����Ӽ����
������          int nKey ���̼�ֵ
����ֵ��        ��
��̣�          WorkStation (31)
�������ڣ�      2008.6
����޸�����:   2008.6
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
			UI_Show_Help_Info("��ǰ����Ϊ��0����");
			break;
		case  VK_1:
			UI_Show_Help_Info("��ǰ����Ϊ��1����");
			break;
		case  VK_2:
			UI_Show_Help_Info("��ǰ����Ϊ��2����");
			break;
		case  VK_3:
			UI_Show_Help_Info("��ǰ����Ϊ��3����");
			break;
		case  VK_4:
			UI_Show_Help_Info("��ǰ����Ϊ��4����");
			break;
		case  VK_5:
			UI_Show_Help_Info("��ǰ����Ϊ��5����");
			break;
		case  VK_6:
			UI_Show_Help_Info("��ǰ����Ϊ��6����");
			break;
		case  VK_7:
			UI_Show_Help_Info("��ǰ����Ϊ��7����");
			break;
		case  VK_8:
			UI_Show_Help_Info("��ǰ����Ϊ��8����");
			break;
		case  VK_9:
			UI_Show_Help_Info("��ǰ����Ϊ��9����");
			break;
		case  VK_CANCEL:
			Set_WorkStation_38_CheckKeyBordResult();
			break;
		case  VK_YOUHUICARD:
			UI_Show_Help_Info("��ǰ����Ϊ���Żݡ���");
			break;
		case VK_MOUNTHCARD:
			UI_Show_Help_Info("��ǰ����Ϊ����Ʊ����");
			break;
		case  VK_QIANKUAN:
			UI_Show_Help_Info("��ǰ����Ϊ��Ƿ�ѡ���");
			break;
		case  VK_LVSETONGDAO:
			UI_Show_Help_Info("��ǰ����Ϊ����ɫͨ������");
			break;
		case  VK_RETURN:
			UI_Show_Help_Info("��ǰ����Ϊ��ȷ�ϡ���");
			break;
		case  VK_WEIZHANG:
			UI_Show_Help_Info("��ǰ����Ϊ��Υ�¡���");
			break;
		case  VK_JUNCHE:
			UI_Show_Help_Info("��ǰ����Ϊ����������");
			break;
		case  VK_GONGWU:
			UI_Show_Help_Info("��ǰ����Ϊ�����񳵡���");
			break;
		case  VK_BEIYONG:
			UI_Show_Help_Info("��ǰ����Ϊ������1����");
			break;
		case  VK_SHANGBAN:
			UI_Show_Help_Info("��ǰ����Ϊ���ϰࡿ��");
			break;
		case  VK_XIABAN:
			UI_Show_Help_Info("��ǰ����Ϊ���°ࡿ��");
			break;
		case  VK_CLOSE_YPD:
			UI_Show_Help_Info("��ǰ����Ϊ���ر�����ơ���");
			break;
		case  VK_OPEN_YPD:
			UI_Show_Help_Info("��ǰ����Ϊ��������ơ���");
			break;
		case  VK_OPEN:
			UI_Show_Help_Info("��ǰ����Ϊ��������������");
			break;
		case  VK_CLOSE:
			UI_Show_Help_Info("��ǰ����Ϊ���رճ�������");
			break;
		/*case  VK_LANGAN:
			UI_Show_Help_Info("��ǰ����Ϊ��Ƿ�ѡ���");
			break;*/
		case  VK_MONI:
			UI_Show_Help_Info("��ǰ����Ϊ��ģ�⡿��");
			break;
			/*case  VK_CHEDUI_G:
				show_Help("��ǰ����Ϊ�����ӿ�������");	
				break;*/
		/*case  VK_CHEDUI_R:
			UI_Show_Help_Info("��ǰ����Ϊ�����ӽ�������");*/
			break;
		case  VK_LEFT:
			UI_Show_Help_Info("��ǰ����Ϊ����ͷ�󡿼�");
			break;
		case  VK_RIGHT:
			UI_Show_Help_Info("��ǰ����Ϊ����ͷ�ҡ���");
			break;
		case  VK_UP:
			UI_Show_Help_Info("��ǰ����Ϊ����ͷ�ϡ���");
			break;
		case  VK_DOWN:
			UI_Show_Help_Info("��ǰ����Ϊ����ͷ�¡���");
			break;
		case  VK_URGENT:
			UI_Show_Help_Info("��ǰ����Ϊ����������");
			break;
		case  VK_LONGYONG:
			UI_Show_Help_Info("��ǰ����Ϊ������2����");
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
