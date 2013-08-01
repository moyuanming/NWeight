#include "LocalIncludeFile.h"



int g_bWeiZhangCount = 0;
void Setg_bWeiZhangCount(int inputg_bWeiZhangCount)
{	
	g_bWeiZhangCount=inputg_bWeiZhangCount;
}
int Getg_bWeiZhangCount(void)
{	
	return g_bWeiZhangCount;
} 

/*******************************************************************************/
//���Ǹ�״̬Υ�� Υ�´�������Զ����ص����״̬
/*******************************************************************************/
volatile int G_weiZhangState=0;
void SetG_weiZhangState(int  value)
{	
	G_weiZhangState=value;
}

int GetG_weiZhangState(void)
{	
	return G_weiZhangState;
}
/*******************************************************************************
//Υ������
0-	����
1-	Υ��
2-	����
3-	�󱨾�
4-   Ϊ�˷���SendMsgInfo��Ϣ�ķ��㣬����Ϣʱ����Ӧ���ַ�
******************************************************************************/
volatile int G_weiZhangType;

void SetG_weiZhangType(int  value)
{	
	G_weiZhangType=value;
}

int GetG_weiZhangType(void)
{	
	return  G_weiZhangType;
}

/*******************************************************************************/
//Υ��֮ǰ��״̬
/*******************************************************************************/
int G_BeforWzWorkstation = -1;
void SetG_BeforWzWorkstation(int value)
{	
	G_BeforWzWorkstation=value;
}

int GetG_BeforWzWorkstation(void)
{	
	return G_BeforWzWorkstation;
}
int G_BeforWzLaneState = -1;
void SetG_BeforWzLaneState(int value)
{	
	G_BeforWzLaneState=value;
}

int GetG_BeforWzLaneState(void)
{	
	return G_BeforWzLaneState;
}



BOOL WorkFlow_Peccancy(int nKey)
{
	BOOL ok=F;
	if (Getg_bWeiZhang())
	{
		WorkFlow_WeiZhang(nKey);
		ok=TRUE;
	}
	else if (nKey==VK_WEIZHANG)
	{
		Set_WorkStation_49_WeiZhang();
		SetRing(T);
		ok=TRUE;
	}
	return ok;
}
void WorkFlow_WeiZhang(int nKey)
{

		if (GetG_weiZhangState()==0)
		{
			WorkStation_49_WeiZhang(nKey);
		}
		else if (GetG_weiZhangState()==1)
		{
			WorkStation_59_WeiZhangHandl(nKey);
		}
		else if (2 == GetG_weiZhangState())
		{
			WorkStation_40_InPutWzCarType(nKey);
		}
		else if (3 == GetG_weiZhangState())
		{
			WorkStation_41_WzOK(nKey);
		}
}
void WorkStation_40_InPutWzCarType( int  nKey)
{
	switch (nKey)
	{
		case VK_1:
			wzCarType=1;
			SetG_weiZhangState(3);
			Set_WorkStation_41_WzOK("һ�ͳ�");
			break;
		case VK_2:
			wzCarType=2;
			SetG_weiZhangState(3);
			Set_WorkStation_41_WzOK("���ͳ�");
			break;
		case VK_3:
			wzCarType=3;
			SetG_weiZhangState(3);
			Set_WorkStation_41_WzOK("���ͳ�");
			break;
		case VK_4:
			wzCarType=4;
			SetG_weiZhangState(3);
			Set_WorkStation_41_WzOK("���ͳ�");
			break;
		case VK_5:
			SetG_weiZhangState(3);
			wzCarType=5;
			Set_WorkStation_41_WzOK("���ͳ�");
			break;
		case VK_6:
			SetG_weiZhangState(3);
			wzCarType=6;
			Set_WorkStation_41_WzOK("������δ֪");
			break;
		case VK_CANCEL:
			SetG_weiZhangState(0);
			UI_Show_Info("��ʾ: ��ѡ����Ȧ����ԭ��\n1. �忨������\n2. �忨δ����\n3. �󱨾�");
			Setg_CurrentLaneState(7);
			break;
		default:
			ErrorPressKey();
			break;
	}
}

void WorkStation_41_WzOK(int nKey)
{
	switch (nKey)
	{
		case VK_RETURN:
			Setg_Violation(1);
			AddMsgTotal_Violation();
			AddExitESMsgTotal_Violation();
			switch (wzCarType)
			{
				case 1:
					SendMessageWzCar(wzCarType);
					break;
				case 2:
					SendMessageWzCar(wzCarType);
					break;
				case 3:
					SendMessageWzCar(wzCarType);
					break;
				case 4:
					SendMessageWzCar(wzCarType);
					break;
				case 5:
					SendMessageWzCar(wzCarType);
					break;
			}
			SendTcoWaingMsg("������");
			SetWorkSationEndWz();
			SendExitEI(EI_Type_CK_CKTY);
			break;
		case VK_CANCEL:
			SetG_weiZhangState(2);
			Set_WorkStation_40_InPutWzCarType();
			break;
		default:
			ErrorPressKey();
			break;
	}
}
void WorkStation_49_WeiZhang(int nKey)
{
	switch (nKey)
	{
		case VK_1:
			SetG_weiZhangState(2);
			Set_WorkStation_40_InPutWzCarType();
			break;
		case VK_2:
			SetG_weiZhangType(2);
			Set_WorkStation_59_WeiZhangHandl("�忨δ����");
			SendExitEI(EI_Type_CK_CKWTY);
			break;
		case VK_3:
			SetG_weiZhangType(3);
			Set_WorkStation_59_WeiZhangHandl("�󱨾�");
			SendExitEI(EI_Type_CK_WBJ);
			break;
		default:
			ErrorPressKey();
			break;
	}
}
void WorkStation_59_WeiZhangHandl(int nKey)
{
	switch (nKey)
	{
		case VK_RETURN:
			SetWorkSationEndWz();
			if (GetG_weiZhangType()==2)
			{
				SendMsgInfo("Υ����Ϣ","","�忨δ����");
				SetG_weiZhangType(0);
			}
			else if (GetG_weiZhangType()==3)
			{
				SendMsgInfo("Υ����Ϣ","","�󱨾�");
				SetG_weiZhangType(0);
			}
			break;
		case VK_CANCEL:
			SetG_weiZhangState(0);
			UI_Show_Info("��ʾ: ��ѡ����Ȧ����ԭ��\n1. �忨������\n2. �忨δ����\n3. �󱨾�");
			Setg_CurrentLaneState(7);
			break;
		default:
			ErrorPressKey();
			UI_Show_Help_Info("������Ч���밴��ʾ���в�����");
			break;
	}
}
/******************************************************************************************************
*����Υ�³�����
******************************************************************************************************/
char tempExit[2];
void SendMessageWzCar(int wzCarType)
{	
	char tempTran[10];
	memset(tempTran,0x00,sizeof(tempTran));	
	SetG_weiZhangType(1);	
	SetExitVIMsgExitType(wzCarType);	
	sprintf(tempExit,"%d",wzCarType);	
	SetExitTRMsgExitType(Get_Current_Car_Type());	
	SetExitTRMsgMethod_Pay(MP_NotPay);	
	SetExitTRMsgViolation('1');	
	SetExitTRMsgExitClass('0');	
	SetExitTRMsgTollFare(0);	
	g_TranNo++;
	sprintf(tempTran,"%04d",g_TranNo);	
	SetExitTRMsgtranNo(tempTran);	
	SendMsgInfo("Υ����Ϣ", "","�忨������");	
	SetG_weiZhangType(0);	
	SetExitTRMsgEntryLane(GetCarNember());
	SendMessageToQueue(ID_MSGEXITTR);	
	SendMessageToQueue(ID_MSGEXITVI);	
	InitMsgExitTR();	


}
