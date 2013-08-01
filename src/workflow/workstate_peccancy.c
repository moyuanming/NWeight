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
//由那个状态违章 违章处理完后将自动返回到这个状态
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
//违章类型
0-	正常
1-	违章
2-	后退
3-	误报警
4-   为了发送SendMsgInfo消息的方便，发消息时它对应空字符
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
//违章之前的状态
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
			Set_WorkStation_41_WzOK("一型车");
			break;
		case VK_2:
			wzCarType=2;
			SetG_weiZhangState(3);
			Set_WorkStation_41_WzOK("二型车");
			break;
		case VK_3:
			wzCarType=3;
			SetG_weiZhangState(3);
			Set_WorkStation_41_WzOK("三型车");
			break;
		case VK_4:
			wzCarType=4;
			SetG_weiZhangState(3);
			Set_WorkStation_41_WzOK("四型车");
			break;
		case VK_5:
			SetG_weiZhangState(3);
			wzCarType=5;
			Set_WorkStation_41_WzOK("五型车");
			break;
		case VK_6:
			SetG_weiZhangState(3);
			wzCarType=6;
			Set_WorkStation_41_WzOK("其他或未知");
			break;
		case VK_CANCEL:
			SetG_weiZhangState(0);
			UI_Show_Info("提示: 请选择线圈报警原因\n1. 冲卡并逃逸\n2. 冲卡未逃逸\n3. 误报警");
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
			SendTcoWaingMsg("闯道车");
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
			Set_WorkStation_59_WeiZhangHandl("冲卡未逃逸");
			SendExitEI(EI_Type_CK_CKWTY);
			break;
		case VK_3:
			SetG_weiZhangType(3);
			Set_WorkStation_59_WeiZhangHandl("误报警");
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
				SendMsgInfo("违章消息","","冲卡未逃逸");
				SetG_weiZhangType(0);
			}
			else if (GetG_weiZhangType()==3)
			{
				SendMsgInfo("违章消息","","误报警");
				SetG_weiZhangType(0);
			}
			break;
		case VK_CANCEL:
			SetG_weiZhangState(0);
			UI_Show_Info("提示: 请选择线圈报警原因\n1. 冲卡并逃逸\n2. 冲卡未逃逸\n3. 误报警");
			Setg_CurrentLaneState(7);
			break;
		default:
			ErrorPressKey();
			UI_Show_Help_Info("按键无效，请按提示进行操作。");
			break;
	}
}
/******************************************************************************************************
*发送违章车数据
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
	SendMsgInfo("违章消息", "","冲卡并逃逸");	
	SetG_weiZhangType(0);	
	SetExitTRMsgEntryLane(GetCarNember());
	SendMessageToQueue(ID_MSGEXITTR);	
	SendMessageToQueue(ID_MSGEXITVI);	
	InitMsgExitTR();	


}
