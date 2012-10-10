#include "LocalIncludeFile.h"

void InLineUP()
{
    Setg_bZhuaPaiXianQuan(T);
    CaptureImg(IMG_FIRST);
}

void InLineDown()
{
    Setg_bZhuaPaiXianQuan(F);
}
void PassLineUP(void)
{
	echo_debug("PassLineUP Start");
	echo_debug("Run Is!");
    Setg_bTongGuoXianQuan(TRUE);
	echo_debug("Run Is!");
    if((0==GetG_IsTuoche()||0==GetG_IsChangche())&&(FALSE==Getg_bJiaoTong()||FALSE==Getg_bLanGan()))
    {
        SetRingVoide(T);
        Set_WorkStation_49_WeiZhang();
        SetRing(T);
    }
    else
    {
		echo_debug("Run Is!");
        WorkStation(S_PASSLINEUP);
		echo_debug("Run Is!");
    }
	echo_debug("PassLineUP End");
}

void PassLineDown(void)
{
	echo_debug("PassLineDown Start");
	Setg_bTongGuoXianQuan(F);
	echo_debug("Run Is!");
	if (10==GetWorkState()||46==GetWorkState())
	{
		PassLineUP();
	}
	echo_debug("Run Is!");
    if(0!=GetG_IsTuoche())//如果不等于0，说明拖车没有处理完。 直接返回。
    {
		echo_debug("Run Is!");
        return;
    }
	echo_debug("Run Is!");
	if(GetG_Urgent_Car_Team_Enabled())
    {
        char temp[100];
		echo_debug("Run Is!");
        AddG_Car_Pass_Count();
		echo_debug("Run Is!");
        memset(temp,'\0',100);
        sprintf(temp,"提示：\n车队已通过%d辆车，\n按【紧急键】键结束紧急车队。",GetG_Car_Pass_Count());
        UI_Show_Info(temp);
		echo_debug("Run Is!");
		return;
    }
	if(0!=GetG_IsChangche()&&!(10==GetWorkState()||46==GetWorkState()))
	{
		echo_debug("Run Is!");
		SetRingVoide(T);
		echo_debug("Run Is!");
        Set_WorkStation_49_WeiZhang();
		echo_debug("Run Is!");
        SetRing(T);
	}
	++YaxianquanNum;
	YaxianquanNum=0;
	echo_debug("Run Is!");
    SetLanGan(F);echoic("___");
	SetJiaoTong(F);
	echo_debug("Run Is!");
    SendLaneInfo_default();
	echo_debug("Run Is!");
	if(46==GetWorkState())
	{
		echo_debug("Run Is!");
		Set_WorkStation_03_Main_Work("正常收费","等待来车");
		echo_debug("Run Is!");
	}

	echo_debug("PassLineDown End!");
    /*if(GetWorkState()==3||GetWorkState()==4|| GetWorkState()==7||51==GetWorkState()||10==GetWorkState()||46==GetWorkState())
    {
			++YaxianquanNum;
			YaxianquanNum=0;
            SetLanGan(F);echoic("___");
			SetJiaoTong(F);
            SendLaneInfo_default();
			if(46==GetWorkState())
			{
				Set_WorkStation_03_Main_Work("正常收费","等待来车");					
			}
    }
    else
    {
        if(GetG_Urgent_Car_Team_Enabled())
        {
            char temp[100];
            AddG_Car_Pass_Count();
            memset(temp,'\0',100);
            sprintf(temp,"提示：\n车队已通过%d辆车，\n按【紧急键】键结束紧急车队。",GetG_Car_Pass_Count());
            UI_Show_Info(temp);
        }
    }*/
}

void SetYuPeng(BOOL  bFlag)
{
    if(Getg_bYuPeng() != bFlag)
    {
        Setg_bYuPeng(bFlag);

        if(bFlag)
        {
            G_CurrentSystemDevStatus.YuPeng  = 1;
            SendMsgGR(MSGGR_CANOPY_ON);
			//SetG_BillPrintFlag(4);
			SetG_weiZhangType(4);
            SendMsgInfo("顶棚灯消息","","雨棚灯打开");
            SendLaneInfo_default();
            Setg_bYuPengOpened(T);
        }
        else
        {
            G_CurrentSystemDevStatus.YuPeng  = 0;
            SendMsgGR(MSGGR_CANOPY_OFF);
            //SetG_BillPrintFlag(4);
            SetG_weiZhangType(4);
            SendMsgInfo("顶棚灯消息","","雨棚灯关闭");
            SendLaneInfo_default();
        }
		I_DEV_IOBoard_CommandSender(bFlag,T_LAMP_G,T_LAMP_R);
        
    }
}
void SetPassCar()
{
	if(1!=GetG_IsTuoche())
	{
		//LogCAppLogDebug("Open Jiao Tong Open LanGan");
		I_DEV_IOBoard_CommandSender(T,C_LAMP_G|C_BAR,C_LAMP_R);
		Setg_bJiaoTong(T);
		Setg_bLanGan(T);
		G_CurrentSystemDevStatus.LanGan = 1;
		G_CurrentSystemDevStatus.JIaoTong = 1;;
		SendLaneInfo("正在过车");
	}
    else
    {
        SetG_IsTuoche(GetG_IsTuoche()+1);
    }
}
void SetJiaoTong(BOOL bFlag)
{
    if(Getg_bJiaoTong() != bFlag)
    {
        Setg_bJiaoTong(bFlag);
		G_CurrentSystemDevStatus.JIaoTong = (bFlag?1:0);
		if(IsRichTFI())
		{
			echo("Setg_bJiaoTong <%d>",bFlag);
			TFI_SetTongXingDeng(bFlag);
		}
		else
		{
			I_DEV_IOBoard_CommandSender(bFlag,C_LAMP_G,C_LAMP_R);
		}
        
    }
}
void SetLanGan(BOOL bFlag)
{
	Setg_bLanGan(bFlag);
	G_CurrentSystemDevStatus.LanGan = (bFlag?1:0);
	I_DEV_IOBoard_CommandSender(bFlag,C_BAR,0);
    
}
BOOL COM_RINGVOIDE = F;
void SetRingVoide(BOOL  bFla)
{
	echoic("打开视频报警\n");
	return;
	if (COM_RINGVOIDE!=bFla)
	{
		COM_RINGVOIDE =bFla;
		I_DEV_IOBoard_CommandSender(bFla,OUTPUT2,0);
	}
}

void  SetMoney(BOOL bFlag)
{
	if (COM_RINGVOIDE!=bFlag)
	{
		COM_RINGVOIDE =bFlag;
		//I_DEV_IOBoard_CommandSender(bFlag,RL_2,0);
	}
}
int MoneyTimer = 0;
int GetMoneyTimer()
{
	if(MoneyTimer<=3)
	{
		MoneyTimer++;
	}
	return MoneyTimer;
}
void OpenMoneyBox(void)
{
#ifdef MONEYBOX
	echoic("打开钱箱\n");
	MoneyTimer = 0;
	I_DEV_IOBoard_CommandSender(F,OUTPUT2,0);
#endif
}
void CloseMoneyBox(void)
{
#ifdef MONEYBOX
	echoic("关闭钱箱\n");
	I_DEV_IOBoard_CommandSender(T,OUTPUT2,0);
#endif
}
void SetRing(BOOL bFlag)
{
    if(Getg_Ring() !=bFlag )
    {
        Setg_Ring(bFlag);
		G_CurrentSystemDevStatus.Ring =(bFlag?1:0);
		if(IsRichTFI())
		{
			echo("SetRing <%d>",bFlag);
		 	TFI_SetHuangShan(bFlag);
		}
		else
		{
			I_DEV_IOBoard_CommandSender(bFlag,ALARM_LAMP,0);
		}
		
    }
}
void SetCloseDev()
{
    I_DEV_IOBoard_CommandSender(T,T_LAMP_R|C_LAMP_R|OUTPUT2,T_LAMP_G|C_LAMP_G|C_BAR|FOG_LAMP |ALARM_LAMP);
    I_DEV_IOBoard_CommandSender(F,OUTPUT2,0);

    sleep(1);
}
int  getJiaoTongDengState(void)
{
    int ret;
    if(Getg_bJiaoTong())
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

char  *GetJiaoTongDengState_Str(void)
{
    if(1==getJiaoTongDengState())
    {
        return "1";
    }
    else
    {
        return "0";
    }
}

int  getGetPrintState(void)
{
    return 1;// autio(g_printfState);
}

int getLanGanState(void)
{
    int ret;
    if(Getg_bLanGan())
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

char  *GetLanGanState_Str(void)
{
    if(1==getLanGanState())
    {
        return "1";
    }
    else
    {
        return "0";
    }
}

int getTongGuoXianQuan(void)
{
    int ret;
    if(Getg_bTongGuoXianQuan())
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
int  getZhuaPaiXianQuan()
{
    int ret;
    if(Getg_bZhuaPaiXianQuan())
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

