#include "LocalIncludeFile.h"


/******************************************************************
�������ƣ�      void LoginSuccess(char * userType)
���ã�          ��¼�ɹ�����Ҫ���Ĺ�����
������          char * userType  �շ�Ա����
����ֵ��        ��
�������ڣ�      2008.5
������:         ����ΰ
����޸�����:   2008.5
����޸���:     ����ΰ
******************************************************************/
static void LoginSuccess(void)
{	
	char tempBillNumber[9];
	tempBillNumber[8]=0x00;
	g_TranNo=1;
	Setg_workStatus(WORKSTAUS_NORMAL);	
	SetOnJobDateTime(GetMsgHead()->YYYYMMDDHHMMSS);	
	SetExitBSMsgcollectortype(GetG_collectType());	
	sprintf(tempBillNumber,"%08d",GetbillCount()+1);	
	SetExitBSMsgWorkStatus(Getg_workStatus());	
	SetExitBSMsgBeginSTicketNo(tempBillNumber);	
	SetExitESMsgBS_TicketNo(tempBillNumber);	
	SendMessageToQueue(ID_MSGEXITBS);	        
	SetG_weiZhangType(4);	
	SendMsgInfo("�ϰ���Ϣ", "","��ʼ�ϰ�");	
	SendLaneInfo("��¼�ɹ�");	


	UI_ShowLoginTime(FALSE);
	memset(MsgHour->tmGreen,'0',sizeof(MsgHour->tmGreen));
	SendLaneInfo_default();
	UI_Set_From_Title(); 
	SendMsgInfo("��¼��Ϣ","","��¼�ɹ�");

	OpenMoneyBox();
}
/******************************************************************
�������ƣ�      void LoginOutSuccess()
���ã�          �°�ȷ�Ϻ���Ҫ���Ĺ�����
������          ��
����ֵ��        ��
�������ڣ�      2008.5
������:         ����ΰ
����޸�����:   2008.5
����޸���:     ����ΰ
******************************************************************/
static void LoginOutSuccess(void)
{	
	SendMessageToQueue(ID_MSGEXITES);	
	InitMsgExitES();	
	InitUserNumAndNameAndOnJobDateTime();	
	Setg_workStatus(WORKSTAUS_XIABAN);	
	SendLaneInfo("�ȴ��ϰ�");	
	Setg_bYuPengOpened(F);	
	OpenMoneyBox();
	SetG_weiZhangType(4);
	SendMsgInfo("�°���Ϣ","","�����°�״̬");	
}


void WorkStation_00_Wait_Begin_Work(int nKey)
{
	switch (nKey)
	{
//  case VK_0:
//  	TFI_HFW_LedShow(2, 5);
//  	break;
//  case VK_1:
//  	TFI_HFW_LedShow(1, 12345);
//  	break;
//  case VK_2:
//  	TFI_HFW_LedShow(2, 20);
//  	break;
//  case VK_3:
//  	TFI_HFW_SetHuangShan(T);
//  	break;
//  case VK_4:
//  	TFI_HFW_SetHuangShan(F);
//  	break;
//  case VK_5:
//  	SetJiaoTong(T);
//  	break;
//  case VK_6:
//  	SetJiaoTong(F);
//  	break;
	case VK_SHANGBAN:
		SendLaneInfo("���ڵ�¼");
		Set_WorkStation_01_Handl_Input_Number();
		ReadBillNumber();
		break;
	case S_PASSLINEUP:
		AddTotalTraffic();
		YaxianquanNum = 0;
		break;
	default:
		echoic("%d", nKey);
		ErrorPressKey();
		break;
	}
}
 
static void ValidateUserNumber(BOOL UsedCar) 
{
	if (strlen(GetG_Number())==Getg_userNumberLen())
	{
		AddInput_Number_Count();
		if(UserNumberExist(GetG_Number()))
		{
			Set_WorkStation_48_VK_OK();
		}
		else
		{
			if(GetInput_Number_Count()>=3)
			{
				SetRing(T);
				SendLaneInfo("�Ƿ��û���ͼ��¼");//���ε�¼ʧ�� �� �쾯�� ���ҲӦ����ʾ �Ƿ��û���¼
				SendMsgEI(MSGEI_IDCARD_INVALID,MSGEI_STATUS_EVENT_OCCURRED,"�Ƿ��û���ͼ��¼");
			}
			InitG_Number();
			UI_Show_UserNumber_Text("");
			if (UsedCar)
			{
				UI_Show_Help_Info("��Ǹ!������ݿ���Ч!");
			}
			else
			{
				UI_Show_Help_Info("�����������, �������빤��!");
			}
		}
	}
}

void WorkStation_01_Handl_Input_Number(int nKey)
{
	echoic("key=<%d>",nKey);
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
			if (LT_OnlyIC!=GetHowToLogin())
			{				
				SetG_NumberByChar(KeyChangCode(nKey));
				UI_Show_UserNumber_Text(GetG_Number());
				ValidateUserNumber(FALSE);
			}
			else
			{
				UI_Show_Help_Info("�ֶ���¼�����ƣ���ʹ����ݿ���¼!");
			}			
			break;
		 
		case VK_CANCEL:
			AddCancelCount();
			if (GetCancelCount() ==1)
			{
				Set_WorkStation_01_Handl_Input_Number();
			}
			else
			{
				UI_Clear_Login_And_Input();
				Set_WorkStation_00_Wait_Begin_Work();
			}
			SendLaneInfo("�ȴ��ϰ�");
			break;
		default:
			ErrorPressKey();
			break;
	}

}
void WorkStation_48_VK_OK(int nKey)
{
	switch (nKey)
	{
	case VK_RETURN:
		Set_WorkStation_02_Handl_Input_Password();
		break;
	case VK_CANCEL:		
		Set_WorkStation_01_Handl_Input_Number();			
		break;
	default:
		ErrorPressKey();
		UI_Show_Help_Info("������Ч���밴��ʾ���в�����");
		break;
	}
}
/*----------------------------------------------------------------------
�������ƣ�      void WorkStation_1_Handl_Input_Number(int nKey)
���ã�          Ա������������ȷ����ճ�����������ת�����״̬������Ա
				����������룬�����������β���ȷ�Զ�������
������          int nKey ���̼�ֵ
����ֵ��        ��
��̣�          WorkStation (1,3,6)
�������ڣ�      2005.10
������:         ĪԶ��
����޸�����:   2008.5
����޸���:     ����ΰ
----------------------------------------------------------------------*/
void WorkStation_02_Handl_Input_Password(int nKey)
{
	char temp[7];
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
			if (strlen(GetG_Password()) ==Getg_userPasswordLen())
			{
				UI_Show_Help_Info("�밴��ȷ�ϡ���ȷ������!");
			}
			else
			{				
				SetG_PasswordByChar(KeyChangCode(nKey));
				strncpy(temp,"*********",strlen(GetG_Password()));
				temp[strlen(GetG_Password())] = '\0';
				UI_Show_Login_UserPwd(temp);
			}
			break;
		case VK_CANCEL:
			AddCancelCount();
			if (1 == GetCancelCount())
			{
				Set_WorkStation_02_Handl_Input_Password();
			}
			else
			{
				if (Getg_bReLogin())
				{
					Set_WorkStation_06_Closed_Road();
				}
				else
				{
					Set_WorkStation_01_Handl_Input_Number();
				}
			}
			break;
		case VK_RETURN:
			{
				
				AddInput_Password_Count();
				if (UserExist(GetG_Number(),GetG_Password()))
				{
					UI_SetFromColor(T);	
					UI_Clear_Login_And_Input();
					I_DEV_VDM_CollectNo(GetG_Number());					
					if (Getg_bReLogin())
					{
						SetYuPeng(T);
						SetG_weiZhangType(4);
						SendMsgInfo("��¼��Ϣ","","��¼�ɹ�");
						Set_WorkStation_03_Main_Work(trim(Getg_szName()),"�����ѿ���");
					}
					else
					{
						if (0==strcmp(GetG_collectTypeStr(),"�շ�Ա"))
						{
							LoginSuccess();									
							Set_WorkStation_03_Main_Work(trim(Getg_szName()),"��½�ɹ���");
						}
						else
						{
							Set_WorkStation_30_SelectWorkMod();
						}
					}

				}
				else
				{
					IntiG_Password();
					UI_Show_Login_UserPwd( "");
					UI_Show_Help_Info("�����������, ������������!");
					setLed();
					if (3==GetInput_Password_Count())
					{
						SetRing(T);
					}
				}
			}
			break;
		default:
			ErrorPressKey();
			break;
	}
}
void WorkStation_20_EndWorkOk(int nKey)
{
	switch (nKey)
	{
	case VK_RETURN:
		LoginOutSuccess();		
		Set_WorkStation_00_Wait_Begin_Work();
		break;
	case VK_CANCEL:
		Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
		SendLaneInfo("�ȴ�����");
		SendMsgInfo("�����շ�","","�ȴ�����");
		break;
	default:
		ErrorPressKey();
		break;
	}
}

void WorkStation_30_SelectWorkMod(int nKey)
{
	
	switch (nKey)
	{
	case VK_1:			
		Setg_workStatus(WORKSTAUS_SIMULATRO );
		SendLaneInfo_default();
		SendMessageToQueue(ID_MSGEXITBS);
		SetG_weiZhangType(4);
		SendMsgInfo("�ϰ���Ϣ","","��ʼ�ϰ�");
		UI_ShowLoginTime(FALSE);
		UI_Set_From_Title(); 
		Set_WorkStation_03_Main_Work(trim(Getg_szName()),"��½�ɹ���");		
		break;
	case VK_2:
		Setg_workStatus(WORKSTAUS_SETTEST);
		UI_Set_From_Title(); 
		Set_WorkStation_31_SelectCheckDev();
		break;
	case VK_3:
		Setg_workStatus(WORKSTAUS_EXPORTDATA );
		UI_Set_From_Title(); 
		Set_WorkStation_50_DataExporter();
		break;
	case VK_4:
		UI_Show_Help_Info("���ڹرճ�����������Ժ򡭡�");
		system("killall emrc_main");
		break;
	case VK_5:
		SetWorkStation_200_SetConfig();
		break;
	case VK_CANCEL:
		Set_WorkStation_00_Wait_Begin_Work();
		break;
	default:
		ErrorPressKey();
		break;
	}
}

