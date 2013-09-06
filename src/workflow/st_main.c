#include "LocalIncludeFile.h"
#include "Version.h"
static BOOL KeyDown = T;
BOOL U_SBtn_Flag=0;
int IC_UpdateTime = 0;
int is_init_all = T;
int AutoIndex = 0;

int CDCWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		case MSG_CREATE:
			UI_Set_From_Handl( hWnd);
			UI_LoadRes();
			

			break;
		case MSG_PAINT:
			if(is_init_all==T)
			{
				U_SBtn_Flag=1;
				UI_InitFrom(hWnd);
				UI_Set_Device_State(0,0);
				sem_post(&Device_semt);
				SendLaneInfo("等待上班");
				is_init_all = F;
				if (GetUseAutoMan()==T)
				{
					SetTimer(hWnd, 10, 10);
				}
				else 
				{
					SetTimer(hWnd, 100, 100);
				}
			}
			break;
		case MSG_TIMER:
			 
			if(GetMoneyTimer()<=3)
			{
				CloseMoneyBox();
			}
			if (Getg_bWeiZhang())
			{
				Setg_bWeiZhangCount(Getg_bWeiZhangCount()+1);
				if (Getg_bWeiZhangCount()>=atoi(sys_ini.RushCancelTime))
				{
					Setg_Violation(1);
					AddMsgTotal_Violation();
					SendMessageWzCar(0);
					SetWorkSationEndWz();
					SetVideoAlarm(F);
					Setg_bWeiZhangCount(0);
					Setg_bWeiZhang(F);
				}
			}
			if ( GetCanTestPrinter( ))
			{
				TestPrintState();
			}
//			WF_TestICReader();
			updateTime( );
			CheckHourSend();
			SendTCOMsg(MSGTCO_NETWORK,"OK");
			AutoManHandl();
			break;
		case MSG_KEYDOWN:
			if (KeyDown)
			{
				WorkStation(KeyTran(wParam));
				echoic("wParam = <%d><%d>",wParam,KeyTran(wParam));
				KeyDown = F;
			}
			break;
		case MSG_KEYUP:
			KeyDown = T;
			break;
	case MSG_BAR_UP:
		echoic("MSG_BAR_UPMSG_BAR_UPMSG_BAR_UPMSG_BAR_UPMSG_BAR_UP");
			G_CurrentSystemDevStatus.TongGuoLine = 1;
			PassLineUP();
			break;
		case MSG_BAR_DOWN:
			G_CurrentSystemDevStatus.TongGuoLine = 0;
			PassLineDown();
			break;
		case MSG_PIC_UP:
			G_CurrentSystemDevStatus.ZhuaPaiLine = 1;
			InLineUP();
			break;
		case MSG_PIC_DOWN:
			G_CurrentSystemDevStatus.ZhuaPaiLine = 0;
			InLineDown();
			break;
		case MSG_REMOTECONTROL:
			WorkStation(KeyTran(wParam));
			break;
		case MSG_CLOSE:
			DestroyMainWindow (hWnd);
			PostQuitMessage (hWnd);
			return 0;
		case MSG_CRADENENT:
			if (GetEnableIC())
			{
				SetCardNO(lParam);//必须先赋予卡号
				switch (wParam)
				{
					case  CSC_CARDENTER ://				1201  //卡进入读卡器可读范围
						SetCardExist(T);
						break;
					case CSC_CARDEXIT:
						SetCardExist(F);
						break;
				}
				SetCardInReader(T);
				WorkStation(wParam);
				SetCardInReader(F);
			}
			break;
	}
	return DefaultMainWinProc (hWnd, message, wParam, lParam);
}
static void InitCreateInfo (PMAINWINCREATE pCreateInfo)
{
	pCreateInfo->dwStyle = WS_CAPTION | WS_BORDER | WS_SYSMENU;
	pCreateInfo->dwStyle &= ~WS_CAPTION;
	pCreateInfo->dwStyle &= ~WS_BORDER;
	pCreateInfo->dwStyle &= ~WS_SYSMENU;
	pCreateInfo->dwExStyle = WS_EX_NONE | WS_EX_USEPRIVATECDC;
	pCreateInfo->spCaption = "车道控制器";
	pCreateInfo->hMenu = 0;
	//pCreateInfo->hCursor = GetSystemCursor (IDC_ARROW);
	pCreateInfo->hIcon = 0;
	pCreateInfo->MainWindowProc = CDCWinProc;
	pCreateInfo->lx = 0;
	pCreateInfo->ty = 0;
	pCreateInfo->rx = UI_DISPLAY_RESOLUTION == DISPPLAY_640_480 ? 640:800;
	pCreateInfo->by = UI_DISPLAY_RESOLUTION == DISPPLAY_640_480 ? 480:600;;
	pCreateInfo->iBkColor =WND_BACK_COLOR;
	pCreateInfo->dwAddData = 0;
	pCreateInfo->hHosting = HWND_DESKTOP;
}

int  ZeroClockSyncTime_Hour=-1;
int ClearConut = 0;
BOOL DeleteOldMessage = FALSE;
void updateTime( void )
{
	char szInfo[80];

	//显示当前日期和时间
	struct tm *rtc_time;
	time_t t = time(NULL);
	rtc_time = localtime(&t);
	sprintf(szInfo, "%04d-%02d-%02d %02d:%02d:%02d",
			rtc_time->tm_year+1900, rtc_time->tm_mon+1, rtc_time->tm_mday,
			rtc_time->tm_hour, rtc_time->tm_min, rtc_time->tm_sec
		   );
	if ( rtc_time->tm_hour!=ZeroClockSyncTime_Hour)
	{
		//字符叠加每小时校正一次时间和内容。
		//上面两行字符有时出现意外字符。
		if (3==GetWorkState()|| -1== ZeroClockSyncTime_Hour)
		{
			I_DEV_VDM_Reset();
			I_DEV_VDM_CollectNo(GetG_Number());
			ZeroClockSyncTime_Hour= rtc_time->tm_hour;
		}
	}
	if(3==rtc_time->tm_hour )
	{
		if(DeleteOldMessage)
		{
			DB_DelteOldMessage(GetDataSaveDays());
			DeleteOldMessage = FALSE;
		}
	}
	else
	{
		DeleteOldMessage = TRUE;
	}
	I_DEV_VDM_SyncTime();
	UI_ShowNowTime(szInfo);
	if (1==g_nHelpTimer &&  ClearConut++ >5)
	{
		g_nHelpTimer=0;
		ClearConut = 0;
		UI_Show_Help_Info("");
	}
}
int MiniGUIMain (int args, const char* arg[])
{
	HWND hMainWnd;
	MSG Msg;
	MAINWINCREATE CreateInfo;	
	
	DoSysCmd("date >> CurrentVer");
	DoSysCmd("echo \""PROVER"\" >> CurrentVer");
	init();
	InitCreateInfo (&CreateInfo);
	hMainWnd = CreateMainWindow (&CreateInfo);
	if (hMainWnd == HWND_INVALID)
		return -1;
	ShowWindow (hMainWnd, SW_SHOWNORMAL);
	SetCursorPos (805, 605) ;
	while ( GetMessage (&Msg, hMainWnd) )
	{
		TranslateMessage (&Msg);
		DispatchMessage (&Msg);
	}
	I_DEV_IOBoard_Exit();
	MainWindowThreadCleanup (hMainWnd);
	system_close();
	exit(0);

	return 0;
}

