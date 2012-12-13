#include "LocalIncludeFile.h"
void Set_WorkStation(int Index)
{
	SetWorkState(Index);    
	UI_Set_From_Title();
}
void Set_WorkStation_00_Wait_Begin_Work()
{   
	UI_Show_Info("提示：\n上班请按【上班】键。");
	UI_WorkMode1("关闭");
	UI_WorkMode2("关闭");
	UI_Set_From_Title();
	UI_SetFromColor(F);
	UI_ShowLoginTime(T);    
	UI_ShowOperatorInfo( "","");  
	UI_Set_From_Title(); 
	Setg_bReLogin(F);   
	SetCloseDev();  
	Set_WorkStation(0); 
	Setg_CurrentLaneState(10);  
	SendLaneInfo_default(); 
	UI_Out_ClearHistory();
}

void Set_WorkStation_01_Handl_Input_Number()
{   
	UI_Show_Info("提示：\n请输入6位上班工号，\n按【确认】键确认，\n按【取消】键取消。");
	UI_Draw_Login_UserNmber( "工号");  
	UI_Show_UserNumber_Text("");  
	UI_Show_Login_UserPwd(""); 
	InitInput_Number_Count();
	SetInputLen( 0);
	InitG_Number();
	Set_WorkStation(1);
	Setg_CurrentLaneState(0);
	SetYuPengState(0);
}
void Set_WorkStation_02_Handl_Input_Password()
{   
	char temp[200];
	memset(temp,'\0',200);  
	sprintf(temp,"提示：\n%s－%s，\n请输入4-6位密码，\n按【确认】键确认，\n按【取消】键取消。", GetG_collectTypeStr(),trim(Getg_szName()));   
	UI_Draw_Login_UserPwd( "密码");  
	UI_Show_Login_UserPwd("");  
	InitInput_Number_Count();   
	InitInput_Password_Count( );    
	SetInputLen(0); 
	IntiG_Password();
	UI_Show_Info(temp); 
	Set_WorkStation(2); 
	Setg_CurrentLaneState(0);   

}

/**
 * 设置3状态的扩展状态，负责初始化的时 设置状态前的初始化工作。 
 * 
 * @param left
 * @param right
 */
void Set_WorkStation_03_Main_Work_extracted1(char * left, char * right)
{
	char temp[30];
	memset(temp,0x00,30);
	InitCarTypeKindCharge();
	BeforeOfTransDo();

	UI_ShowOperatorInfo(left,right);
	if (Getg_Ring())
	{
		SetRing(F); 
	}
	SetG_Urgent_Car_Team_Enabled(F);    
	Setg_bReLogin( T);  
	SetInputLen(0); 
	SetsecondLogin( T); 
	 

}
void Set_WorkStation_03_Main_Work_extracted2(void)
{
	Setg_CurrentLaneState(1);   
	SetRingVoide(F);    
	InitCardContext();
	SendLaneInfo_default();
	UI_Clear_Login_And_Input();
}

void Set_WorkStation_03_Main_Work(char *left,char *right)
{   	
	ClearCPHM();
	Set_WorkStation_03_Main_Work_extracted1(left, right);
	if(!GetYuPengState())
	{
		UI_Show_Info("提示：\n按【绿↓】键打开雨棚灯\n按【下班】键下班");
	}
	else
	{
		if(Getg_bYuPeng())
		{
			UI_Show_Info("提示：\n按【数字】键输入车型；\n按【紧急】键处理紧急车\n按【红X】键关闭雨棚灯");
		}
		else
		{
			UI_Show_Info("提示：\n按【数字】键输入车型；\n按【紧急】键处理紧急车\n按【绿↓】键打开雨棚灯\n按【下班】键下班");
		}
	}
	
	UI_WorkMode1("运营");
	UI_WorkMode2("人工");
	Set_WorkStation(3); 
	Set_WorkStation_03_Main_Work_extracted2();	
	
}

void Set_WorkStation_04_General_Validate_Car_Type_And_First_OK()
{   
	UI_ShowOperatorInfo("正常收费","请确认车种");	
	UI_Show_Info("提示：\n按【货车】键处理货车\n按【确认】键确认\n按【取消】键取消\n公务、军车、优惠车、月票车、农用车、绿色通道请按对应按键");	
	UI_Clear_Login_And_Input();
	Set_WorkStation(4);
	Setg_CurrentLaneState(11);
}
void Set_WorkStation_204_FreeCar()
{   
	InitG_AbateNumber();
	UI_ShowOperatorInfo("输入车牌号：","");	
	UI_Show_Info("提示：\n按【数字】输入车牌号后3位，\n输入后按【确认】键确认,\n按【取消】键重新输入。");	
	Set_WorkStation(204);
}
void Set_WorkStation_06_Closed_Road()
{   
	UI_ClearCarKind(); 
	UI_ClearCarType(); 
	UI_ClearCarMoney(); 
	UI_ShowOperatorInfo("车道已封闭","等待开启");
	SetYuPeng(F);	
	UI_Show_Info("提示：\n车道处于暂时关闭状态，\n按【开启】键打开车道。");
	Set_WorkStation(6); 
	Setg_CurrentLaneState(2);   
}

void Set_WorkStation_07_General_Second_OK(char *left,char *rihgt)
{   
	char charge[10];
	char temp[200];
	char tmpxxx[100];
	char *carnumber = GetCarNember();
	G_Calculate_Final_Fare();
	memset(tmpxxx,0x00,100);
	UI_ShowOperatorInfo(left,rihgt);
	InitG_SaveBeforTipOne();
	InitG_SaveBeforTipTwo();
	SetG_SaveBeforTipOne(left);
	SetG_SaveBeforTipTwo(rihgt);	
	UI_Show_Info("7状态，对应位置");
	Set_WorkStation(7);
	Setg_CurrentLaneState(12);
	SendLaneInfo(left);
	memset(charge,'\0',10); 
	sprintf(charge,"%1.0f",Get_G_Current_Actual_pay());    
	memset(temp,'\0',200); 
	UI_Show_WeightData(); 
	memset(temp,'\0',200); 
	sprintf(tmpxxx,"车牌号：%s \n",GetCPHM(temp));
	if (GetEnableIC())
	{
		sprintf(tmpxxx,"持卡车辆请刷卡\n");
	}
	if(' '!=carnumber[0])
	{
		sprintf(tmpxxx,"车牌号：%s \n",carnumber);
	}
	if (0==GetG_IsTuoche())
	{
		sprintf(temp,"提示：\n车种：%s 收费：%s 元 ，\n%s按【确认】键抬杆放行，\n按【模拟】键处理拖车模拟、更改车型、车种。\n按【计重】键调整车辆信息、设置特种车辆、转换货车",Getg_CurrentCarKindExplain(),charge,tmpxxx);    
		UI_Show_Info(temp);    
	}
	else
	{
		sprintf(temp,"提示：\n车种：%s 收费：%s 元 ，\n%s按【确认】键确认,\n按【模拟】键更改车型、车种。\n按【计重】键调整车辆信息、设置特种车辆、转换货车",Getg_CurrentCarKindExplain(),charge,tmpxxx);   
		UI_Show_Info(temp);    
	}
	InitG_ZhaoLing();
}

void Set_WorkStation_09_Handl_Urgent_Car_Team()
{   	
	UI_ShowOperatorInfo("车队类型","紧急车队");	
	UI_Show_Info("提示：\n按【确认】键抬杆放行，\n按【取消】键取消。");
	Set_WorkStation(9); 
	Setg_CurrentLaneState(14);  
}
void Set_WorkStation_10_Up_Parapet_Pass()
{   
	SetPassCar();
	UI_ShowOperatorInfo("正常收费","车辆正在通过！");	
	UI_Show_Info("提示：\n车辆正在通过，\n按【模拟】进行模拟操作。");
	Set_WorkStation(10);    
	SetroadCridState('4');   
	Setg_CurrentLaneState(4);   
	UI_Clear_Login_And_Input();
}
void Set_WorkStation_13_Urgent_Car_Team_Passing()
{   
	SetPassCar();   
	SetInputLen(0); 
	SetG_Urgent_Car_Team_Enabled(T);    
	SetG_Car_Pass_Count(0); 
	Init_Current_Car_Type();   
	UI_ClearCarKind(); 
	UI_ClearCarType(); 
	UI_ClearCarMoney();    
	UI_ShowOperatorInfo("紧急车队","正在通过");	
	UI_Show_Info("提示：\n紧急车队正在通过！\n如果确认车队已经通过。\n按【紧急】键继续下面的操作");
	Set_WorkStation(13);    
	Setg_CurrentLaneState(16);  
}


void Set_WorkStation_16_Handl_Urgent_Car_Team_End()
{   
	UI_ShowOperatorInfo("结束紧急车队","请确认或取消");	
	UI_Show_Info("提示：\n按【确认】键确认结束，\n按【取消】键取消结束。");
	Set_WorkStation(16);    
	Setg_CurrentLaneState(16);  
}

void Set_WorkStation_20_EndWorkOk()
{   
	UI_ShowOperatorInfo("下班操作","请确认");	
	UI_Show_Info("提示：\n按【确认】键确认，\n按【取消】键返回。");
	Set_WorkStation(20);    
	Setg_CurrentLaneState(17);  
	SendMsgInfo("准备下班","","等待确认下班");	//qq
	SendLaneInfo("准备下班");
}

void Set_WorkStation_49_WeiZhang(void)
{   
	if (!Getg_bWeiZhang())
	{
		CaptureImg(IMG_SECOND);
		SetG_CurrentInfoTemp(GetG_CurrentInfo());   
		SetG_BeforWzWorkstation(GetWorkState());    
		Setg_bWeiZhang(TRUE);   
		SetG_weiZhangState(0);  
		UI_Show_Info("提示: 请选择线圈报警原因\n1. 闯道\n2. 倒车\n3. 误报警"); 
		SetG_BeforWzLaneState(Getg_CurrentLaneState()); 
		Setg_CurrentLaneState(7);   
	}
}
void Set_WorkStation_59_WeiZhangHandl(char *weiZhangType)
{   
	char tempInfo[150];
	Setg_bWeiZhang( TRUE);  
	SetG_weiZhangState(1);  
	sprintf(tempInfo,"提示：违章类型＝%s\n按【确认】键确认\n按【取消】取消。%c",weiZhangType,'\0'); 
	UI_Show_Info(tempInfo); 
	Setg_CurrentLaneState(7); 
}

void Set_WorkStation_23_Abate(char *Type)
{  	
	
	UI_Draw_Input_Text(Type); 
	UI_Show_Input_Text("");  
	SetInputLen(0); 
	InitG_AbateNumber(); 
	UI_Show_Info("提示：\n按【数字】键输入卡号，\n按【取消】键取消。");
	Set_WorkStation(23);    
	Setg_CurrentLaneState(9);   
	SetRingVoide(T);    
}

void Set_WorkStation_30_SelectWorkMod()
{   
	UI_ShowOperatorInfo( "","");	
	UI_Show_Info("提示：\n请选择工作模式：\n1：模拟收费    2：设备检测\n3：导出数据    4：关闭车道软件\n5：修改车到配置 按【取消】键退出登陆");
	Set_WorkStation(30);    
	Setg_CurrentLaneState(30);  
	SetYuPeng(F);   
	SetJiaoTong(F); 
	SetLanGan(F);   echoic("___");	
	SetRing(F); 
	SendLaneInfo_default(); 
}
void Set_WorkStation_31_SelectCheckDev()
{   	
	UI_ShowOperatorInfo("设备检测","请选择设备");
	UI_Show_Info("提示：\n1:检测栏杆机\n2:检测通行灯\n3:检测雨棚灯\n4:检测打印机\n5:检测收费键盘\n6:检测金额显示器\n7:检测报警器\n8:检测字符叠加;按取消键返回");
	Set_WorkStation(31);    
	Setg_CurrentLaneState(18);  
}
void Set_WorkStation_32_CheckBar()
{   
	UI_ShowOperatorInfo("设备检测","栏杆");	
	UI_Show_Info("提示：\n栏杆检测请选择：\n1：抬杆检测\n2：落杆检测\n按【取消】键取消。");
	Set_WorkStation(32);    
	Setg_CurrentLaneState(19);  
}
void Set_WorkStation_33_CheckPassLight()
{   
	UI_ShowOperatorInfo("设备检测","通行灯");	
	UI_Show_Info("提示：\n通行灯检测请选择：\n1：红灯检测\n2：绿灯检测\n按【取消】键取消。");
	Set_WorkStation(33);    
	Setg_CurrentLaneState(20);  
}
void Set_WorkStation_34_CheckSkyLight()
{   
	UI_ShowOperatorInfo("设备检测","雨棚灯");	
	UI_Show_Info("提示：\n雨棚灯检测请选择：\n1：红灯检测\n2：绿灯检测\n按【取消】键取消。");
	Set_WorkStation(34);    
	Setg_CurrentLaneState(21);  
}
void Set_WorkStation_35_SelectCheckResult()
{    
	UI_ShowOperatorInfo("设备检测","检测结果");
	UI_Show_Info("提示：\n设备响应正确\n    则按【确认】键返回。\n    设备响应错误,\n    则按【取消】键返回，\n    待检查设备后重新检测。");
	Set_WorkStation(35);    
	Setg_CurrentLaneState(26);  
}

void Set_WorkStation_36_CheckPrinterResult()
{   
	UI_ShowOperatorInfo( "打印机检测","检测结果");
	UI_Show_Info("提示：\n打印机打出票据正常，\n   则按【确认】键返回，\n   打印机票据错误或未打印,\n   则按【取消】键返回，\n   待检查设备后重新检测。");
	Set_WorkStation(36);    
	Setg_CurrentLaneState(22);  
}

void Set_WorkStation_37_CheckKeyBord()
{  
	UI_ShowOperatorInfo( "键盘检测","正在检测");	
	UI_Show_Info("提示：\n请按键盘进行按键检测\n    按【取消】键进行下一步。");
	Set_WorkStation(37);    
	Setg_CurrentLaneState(23);  
}
void Set_WorkStation_38_CheckKeyBordResult()
{
	UI_ShowOperatorInfo( "键盘检测","检测结果"); 
	UI_Show_Info("提示：\n【取消】键检测正常，\n    按健全部检测正常，\n    按【1】键返回。\n    按键检测出错，\n    按【2】键返回，\n    按【确认】键继续测试。");
	Set_WorkStation(38);    
	Setg_CurrentLaneState(27);  
}

void Set_WorkStation_39_CheckRing()
{ 
	UI_ShowOperatorInfo( "设备检测","报警器");  	
	UI_Show_Info("提示：\n报警器检测请选择：\n1：报警检测\n2：关闭报警检测\n按【取消】键取消。");
	Set_WorkStation(39);    
	Setg_CurrentLaneState(25);
}

void Set_WorkStation_40_InPutWzCarType()
{   
	UI_Show_Info("提示：请输入闯道车类型\n  1：一型车\n  2：二型车\n  3：三型车\n  4：四型车\n  5：五型车\n  6：其他车型\n  按【取消】键返回。");
	Set_WorkStation(40);    
	Setg_CurrentLaneState(28);  
}

void Set_WorkStation_41_WzOK(char *CarType)
{   
	char temp[200];
	memset(temp,'\0',200);  
	sprintf(temp,"提示：\n闯道车类型：%s\n按【确认】键确认，\n按【取消】键返回。",CarType);    
	Setg_CurrentLaneState(29);  
	UI_Show_Info(temp);    
}

void Set_WorkStation_42_HandArrearageNumber(int BefWorkStation)
{   
	char * Info = "提示：\n请按数字键输入1－%d位的欠款单号\n按【确认】键确认，\n按【取消】键返回。";
	char temp[200];
	UI_Draw_Input_Text( "欠款单号");  
	UI_Show_Input_Text("");  
	InitG_ArrearageNumber();  	
	UI_Show_Info(Info);
	Set_WorkStation(42);    
	memset(temp,'\0',200);  
	sprintf(temp,Info, atoi(sys_ini.MaxArrearageNumber));   
	UI_Show_Info(temp);    
	SetG_BeforWzWorkstation(BefWorkStation); 
	SetWorkState( 42);  
}
void Set_WorkStation_43_HandArrearageCharge()
{   
	char temp[200];
	char tempNumber[50];
	char * Info =/* 43 */"提示：\n欠款单号：%s\n请按【数字】键输入欠款金额\n按【确认】键确认，\n按【取消】键返回。";
	UI_Draw_Input_Text( "欠款金额");  
	UI_Show_Input_Text("");  
	memset(tempNumber,'0',50);  
	InitG_ArrearageChargeChar();    
	strcpy(tempNumber + atoi(sys_ini.MaxArrearageNumber) - strlen(GetG_ArrearageNumber()),GetG_ArrearageNumber());  
	memset(temp,'\0',200);  
	sprintf(temp,Info /*promptInformation[43]*/,tempNumber); 
	UI_Show_Info(temp);    
	SetWorkState ( 43); 
}


void SetWorkSationEndWz()
{   
	SetWorkState   (GetG_BeforWzWorkstation() );    
	Setg_bWeiZhang( F); 
	SetG_weiZhangState(-1); 
	UI_Show_Info(GetG_CurrentInfoTemp());  
	SetRing(F); 
	Setg_CurrentLaneState(GetG_BeforWzLaneState()); 
	if (7==GetWorkState())
	{
		Set_WorkStation_03_Main_Work("正常收费","等待来车");    
	}
	Setg_bWeiZhangCount(0); 
}
void Set_WorkStation_44_TestLed(void)
{   
	UI_ShowOperatorInfo( "设备检测","金额显示器");  

	Setg_CurrentLaneState(31);  
}

void Set_WorkStation_45_SimulateOnceOk()
{   
	UI_ShowMenu("模拟菜单","提示：\n请选择模拟类型：%s","1、更改车型\n2、更改车种\n3、拖车模拟");
	Set_WorkStation(45);    
	Setg_CurrentLaneState(8);   
}
/*****************************************************
两次拖车模拟后，不能再进行拖车模拟时跳入的状态。
By:王海伟
******************************************************/
void Set_WorkStation_53_SimulateOnceOkTuoche()
{   
	UI_ShowMenu("模拟菜单","提示：\n请选择模拟类型：%s","1、更改车型\n2、更改车种");
	Set_WorkStation(53);    
	Setg_CurrentLaneState(8);   
}
void Set_WorkStation_46_SimulateTwoOk()
{   
	UI_ShowMenu("模拟菜单","提示：\n请选择模拟类型：%s","1、过车模拟\n2、重打票据");
	Set_WorkStation(46);    
	Setg_CurrentLaneState(8);   
}

void Set_WorkStation_47_FavourCardOK(char *left,char *rihgt,char *startData,char *endData)
{   
	char Temp[250];
	UI_ShowOperatorInfo( left,rihgt);    
	InitG_SaveBeforTipOne();    
	InitG_SaveBeforTipTwo();    
	SetG_SaveBeforTipOne(left);  
	SetG_SaveBeforTipTwo(rihgt);    
	memset(Temp,0x00,250);  

	sprintf(Temp,"提示：\n车种：%s 收费：%d 元，\n生效日期:%s,失效日期%s\n按【确认】键确认\n按【模拟】键更改车型、车种。",Getg_CurrentCarKindExplain(),(int)Get_G_Current_Actual_pay(),startData,endData);   
	
	UI_Show_Info(Temp);	
	SetWorkState(47);   
	Setg_CurrentLaneState(12);  
}
void Set_WorkStation_48_VK_OK()
{   
	char * Info =/* 48 */"提示：\n工号输入正确\n请按【确认】键确认。";
	UI_Show_Info(Info);
	Set_WorkStation(48);    
	Setg_CurrentLaneState(0);   
}
void Set_WorkStation_52_VKABATE_OK()
{   
	UI_Show_Info("提示：\n按【确认】键确认卡号,\n按【取消】键取消已输入卡号。");
	Set_WorkStation(52);    
	Setg_CurrentLaneState(12);  
}

void  Set_WorkStation_50_DataExporter(void)
{   
	UI_Show_Info("提示：\n按【数字】键输入车型。");
	Set_WorkStation(50);   
	UI_Show_Info("提示：\n请将您的可移动存储设备插入USB口。确认设备正常工作后：\n按【确认】键开始导出，\n按【取消】键退出此操作！");    
}
void Set_WorkStation_51_Tuo_cheMoNi_Like_work3(char *left,char *right)
{   
	Set_WorkStation_03_Main_Work_extracted1(left, right);
	UI_Show_Info("提示：\n按【数字】键输入车型。");
	Set_WorkStation(51);    
	Set_WorkStation_03_Main_Work_extracted2();
}
void Set_WorkStation_56_CheckCharFold()
{   
	UI_ShowOperatorInfo( "设备检测","字符叠加");	
	UI_Show_Info("提示：\n正在进行字符叠加检测……	\n    按【取消】键返回测试界面\n    按【确认】键查看检测结果。");
	Set_WorkStation(56);    
	Setg_CurrentLaneState(56);  
}

void Set_WorkStation_57_CheckCharFoldResult()
{   
	UI_ShowOperatorInfo( "字符叠加检测","检测结果");  	
	UI_Show_Info("提示：\n按【确认】键返回。");
	Set_WorkStation(57);    
	Setg_CurrentLaneState(57);  
}
void Set_WorkStation_60_ConfirmPayBy_MonthCard(void)
{
	Set_WorkStation(60);
}
void Set_WorkStation_61_ConfirmPayBy_SVCCard(void)
{
	Set_WorkStation(61);
}

void Set_WorkStation_62_ConfirmPayBy_OfficialCard(void)
{
	Set_WorkStation(62);
}
void Set_WorkStation_63_IC_Moni_SVC(void)
{
	Set_WorkStation(63);
	UI_Show_Info("提示：\n选择模拟类型：\n1、拖车模拟\n按【取消】键返回。");
}
void Set_WorkStation_64_IC_Moni_Month(void)
{
	Set_WorkStation(64);
	UI_Show_Info("提示：\n选择模拟类型：\n1、拖车模拟\n按【取消】键返回。");
}
void Set_WorkStation_65_IC_Moni_Official(void)
{
	Set_WorkStation(65);
	UI_Show_Info("提示：\n选择模拟类型：\n1、拖车模拟\n按【取消】键返回。");
}

void Set_WorkStation_66_InputCarNo(char *left)
{   
	char charge[10];
	char temp[200];
	UI_Draw_Input_Text( left);	
	UI_Show_Input_Text("");
	Set_WorkStation(66);
	Setg_CurrentLaneState(12);	
	SendLaneInfo(left);
	memset(charge,'\0',10); 
	sprintf(charge,"%1.0f",Get_G_Current_Actual_pay());    
	memset(temp,'\0',200);  	
	sprintf(temp,"提示：\n车种：%s 收费：%s 元，\n按【数字】输入车牌号后3位，\n输入后按【确认】键确认,\n按【取消】键重新输入。",Getg_CurrentCarKindExplain(),charge);    
	UI_Show_Info(temp);  

}

void Set_WorkStation_67_WeightMenu()
{
	if (NotUseWeight != GetWeightFunctions())
	{
		SetLastWorkState(GetWorkState());
		Set_WorkStation(67);
		SetG_WeightMenuStues(-1);
		UI_Show_Info("提示：\n请按【数字】键选择菜单\n按【取消】键取消。");
		Draw_MenuCZ_GUI();
	}
	else
	{
		echoic("修改配置文件常量表中的字段");
		UI_Show_Help_Info("计重功能没启用！");
	}
}
  

void Set_WorkStation_68_WeightMenuCC()
{
	Draw_MenuHide();
	InitG_CarAxlesNum();
	switch(GetG_WeightMenuStues())
	{
		case 3:
			break;
		case 4: 
			GetG_CarAxlesNum()[0]='2';
			break;
	}
	UI_Show_Info("提示：\n请输入当前车轴数\n按【确认】键确认,\n按【取消】键取消。");
	UI_Draw_Input_Text( "当前车轴数"); 
	UI_Show_Input_Text(GetG_CarAxlesNum());
	Set_WorkStation(68);
}



