#include "LocalIncludeFile.h"


/*******************************************************************************/
//��ʶ���Ǹ�����״̬���е�ģ����� ��ͬ�Ĺ���״̬����ģ����ɺ󽫻ص�ʲô״̬
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
//�ش�Ʊ�ݴ���
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
		SendMsgInfo("�쳣��Ϣ","","��Ȧ�쳣");	   
		SendMsgInfo("ģ����Ϣ","","����ģ��");	
		SetLanGan(F);
		SetExitTRMsgPassageLoopError('1');
		AddYCQK("����ģ��");
		SetExitTRMsgDisputeType('1');
		SendExitEI(EI_Type_MN_GCMN);
		SetNotRemoveFirstCarWeightInfo();
	case S_PASSLINEUP:			
		SetJiaoTong(F);		
		if (0!=GetG_IsTuoche())
		{
			AddYCQK("���ϳ�");
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
		SendMsgInfo("������Ϣ","","��ͨ����");	   
		Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");		
		SendLaneInfo_default();
		SendLaneInfo("�ȴ�����");
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
				SendMsgInfo("ģ����Ϣ","","�ش�Ʊ��");
				AddYCQK("�ش�Ʊ��");
				SetExitTRMsgDisputeType('5');
				SendExitEI(EI_Type_MN_CDPJ);
			}
			else
			{
				UI_Show_Help_Info("�ش�Ʊ�ݴ�������!");
			}

		}
		else
		{
			UI_Show_Help_Info("��ѳ�û��Ʊ�ݣ�");
			setLed();
		}
		break;
	default:
		ErrorPressKey();
		break;
	}
}

