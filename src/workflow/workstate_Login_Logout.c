#include "LocalIncludeFile.h"


/******************************************************************
函数名称：      void LoginSuccess(char * userType)
作用：          登录成功后所要做的工作。
参数：          char * userType  收费员类型
返回值：        无
创建日期：      2008.5
创建人:         王海伟
最后修改日期:   2008.5
最后修改人:     王海伟
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
	SendMsgInfo("上班消息", "","开始上班");	
	SendLaneInfo("登录成功");	


	UI_ShowLoginTime(FALSE);
	memset(MsgHour->tmGreen,'0',sizeof(MsgHour->tmGreen));
	SendLaneInfo_default();
	UI_Set_From_Title(); 
	SendMsgInfo("登录消息","","登录成功");

	OpenMoneyBox();
}
/******************************************************************
函数名称：      void LoginOutSuccess()
作用：          下班确认后所要做的工作。
参数：          无
返回值：        无
创建日期：      2008.5
创建人:         王海伟
最后修改日期:   2008.5
最后修改人:     王海伟
******************************************************************/
static void LoginOutSuccess(void)
{	
	SendMessageToQueue(ID_MSGEXITES);	
	InitMsgExitES();	
	InitUserNumAndNameAndOnJobDateTime();	
	Setg_workStatus(WORKSTAUS_XIABAN);	
	SendLaneInfo("等待上班");	
	Setg_bYuPengOpened(F);	
	OpenMoneyBox();
	SetG_weiZhangType(4);
	SendMsgInfo("下班消息","","处于下班状态");	
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
		SendLaneInfo("正在登录");
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
void GetUserNumberFromStatffCard()
{
	char * cardinfo;	
	cardinfo=ReadStaffCard();
	if (cardinfo!=NULL)
	{			
		SetG_Number(substring(cardinfo,6));
		UI_Show_Input_Text( GetG_Number());
		SetInput_Number_Count(6);		
	}
	else
	{
		UI_Show_Help_Info("抱歉!请重试或换卡");
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
				SendLaneInfo("非法用户试图登录");//三次登录失败 会 响警铃 监控也应该提示 非法用户登录
				SendMsgEI(MSGEI_IDCARD_INVALID,MSGEI_STATUS_EVENT_OCCURRED,"非法用户企图登录");
			}
			InitG_Number();
			UI_Show_UserNumber_Text("");
			if (UsedCar)
			{
				UI_Show_Help_Info("抱歉!您的身份卡无效!");
			}
			else
			{
				UI_Show_Help_Info("工号输入错误, 重新输入工号!");
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
				UI_Show_Help_Info("手动登录被限制，请使用身份卡登录!");
			}			
			break;
		case   CSC_CARDENTER :
			if (LT_OnlyHand != GetHowToLogin())
			{		
				GetUserNumberFromStatffCard();	
				ValidateUserNumber(TRUE);			
			}
			else 
			{
				UI_Show_Help_Info("身份卡被限制使用!请手动登录！");
			}			
			break;
		case CSC_CARDEXIT:
			UI_Show_Help_Info("身份卡已经被拿开!");
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
			SendLaneInfo("等待上班");
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
		UI_Show_Help_Info("按键无效，请按提示进行操作。");
		break;
	}
}
/*----------------------------------------------------------------------
函数名称：      void WorkStation_1_Handl_Input_Number(int nKey)
作用：          员工工号输入正确后或封闭车道开启后跳转到这个状态，处理员
				工输入的密码，密码输入三次不正确自动报警。
参数：          int nKey 键盘键值
返回值：        无
后继：          WorkStation (1,3,6)
创建日期：      2005.10
创建人:         莫远明
最后修改日期:   2008.5
最后修改人:     王海伟
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
				UI_Show_Help_Info("请按【确认】键确认密码!");
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
						SendMsgInfo("登录消息","","登录成功");
						Set_WorkStation_03_Main_Work(trim(Getg_szName()),"车道已开启");
					}
					else
					{
						if (0==strcmp(GetG_collectTypeStr(),"收费员"))
						{
							LoginSuccess();									
							Set_WorkStation_03_Main_Work(trim(Getg_szName()),"登陆成功！");
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
					UI_Show_Help_Info("密码输入错误, 重新输入密码!");
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
		Set_WorkStation_03_Main_Work("正常收费","等待来车");
		SendLaneInfo("等待来车");
		SendMsgInfo("正常收费","","等待来车");
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
		SendMsgInfo("上班消息","","开始上班");
		UI_ShowLoginTime(FALSE);
		UI_Set_From_Title(); 
		Set_WorkStation_03_Main_Work(trim(Getg_szName()),"登陆成功！");		
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
		UI_Show_Help_Info("正在关闭车道软件，请稍候……");
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

