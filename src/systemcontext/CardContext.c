// ***************************************************************
//  CardContext   version:  1.0   ·  date: 2009年3月9日
//   -------------------------------------------------------------
//  提供ic卡相关的信息
//  -------------------------------------------------------------
// ***************************************************************
#include "LocalIncludeFile.h"
struct ICCARD   _CardToPay ;
BOOL GetCardIsNormal(	struct MSG_SVRCARDLIST * _inputcardisnormal)
{
	BOOL r=F;
	if (0==strncmp( CARDSTATUS_Normal,_inputcardisnormal->Status,strlen(CARDSTATUS_Normal)))
	{
		r=T;
	}
	return r;
}
char  _CardStatus[10];
char * GetCardStatus(char * stat)
{
	if (0==strncmp( CARDSTATUS_Unfulfilment,stat,2))
	{
		sprintf(_CardStatus,"未制作");
	}
	else if (0==strncmp( CARDSTATUS_Normal,stat,2))
	{
		sprintf(_CardStatus ,"正常");
	}
	else if (0==strncmp( CARDSTATUS_Reclaim,stat,2))
	{
		sprintf(_CardStatus ,"回收");
	}
	else if (0==strncmp( CARDSTATUS_Scrap,stat,2))
	{
		sprintf(_CardStatus ,"报废");
	}
	else if (0==strncmp( CARDSTATUS_ReportLoss,stat,2))
	{
		sprintf(_CardStatus ,"挂失");
	}
	else if (0==strncmp( CARDSTATUS_LockCard,stat,2))
	{
		sprintf(_CardStatus ,"黑名单");
	}
	return _CardStatus;
}
/**
 * 获取结余次数
 * 
 * @return 
 */
int  Get_CardContext_MonthCard_Balance(void)
{
	return atoi(SUBSTRING(_CardToPay.MonthCard.BlanceCount));
}
int  Get_CardContext_MonthCard_Count(void)
{
	return atoi(SUBSTRING(_CardToPay.MonthCard.Count));
}

char  _disenabledate[15];
/**
 * 获取失效日期
 * 
 * @return 
 */
char * Get_CardContext_DisEnableDate(void)
{
	struct MSG_SVRCARDLIST * tmp ;
	memset(_disenabledate,0x00,15);
	tmp = FindCardInParamList( GetCardNOByString() );
	if (tmp!=NULL)
	{
		strncpy(_disenabledate,tmp->DisEnableDate,14);
	}
	return _disenabledate;
}
char  _enabledate[15];
/**
 * 获取启用日期
 * 
 * @return 
 */
char * Get_CardContext_EnableDate(void)
{
	struct MSG_SVRCARDLIST * tmp ;
	memset(_enabledate,0x00,15);
	tmp = FindCardInParamList( GetCardNOByString() );
	if (tmp!=NULL)
	{
		strncpy(_enabledate,tmp->EnableDate,14);
	}
	return _enabledate;
}

/**
 * 返回支付卡的卡类型，如记账卡 储值卡 月票卡等
 * 
 * @return 
 */
int Get_CardContext_PayCardType(void)
{
	return atoi(SUBSTRING(_CardToPay.CardType));
}
char _CardContext_CardNumber[11];
char * GetCardContext_CardNumber(void)
{
	return _CardContext_CardNumber;
}
/**
 * 处理使用卡支付的过程
 * 
 * @return 返回错误代码。 成功返回 0  。 
 */
int UseCardToPay(void)
{
	int LastReturn =PAYRET_OK;
	struct MSG_SVRCARDLIST *  chardINfo=NULL;
	
	echoic("读卡器上放了张卡  卡号是 %s",       GetCardNOByString());
	memset( _CardContext_CardNumber,0x00,11);
	strncpy(_CardContext_CardNumber,GetCardNOByString(),10);
	chardINfo=FindCardInParamList(GetCardNOByString());

	if (chardINfo==NULL)
	{
		SendLaneInfo("未知卡片或未启用");  
		LastReturn=PAYRET_READCARDKEYNOTFOND;//读卡失败。 
	}
	else
	{
			echoic("sadfsdafasdffasdfasd");
		switch (atoi(SUBSTRING(chardINfo->SvrICKind)) )
		{
			case  CARDTYPE_SVCCard:	// 	  1  //储值卡
				Set_WorkStation_61_ConfirmPayBy_SVCCard();
				Use_CardContext_SVCCard_Pay();
				SendLaneInfo("正在使用储值卡");  
				break;
			case CARDTYPE_MonthCard://   2  //月票卡
				Set_WorkStation_60_ConfirmPayBy_MonthCard();
				Use_CardContext_MonthCard_Pay();
				SendLaneInfo("正在使用月票卡");  
				break;

			case  CARDTYPE_OfficialCard ://   5  公务卡
				Set_WorkStation_62_ConfirmPayBy_OfficialCard();
				Use_CardContext_OfficialCard_Pay();
				SendLaneInfo("正在使用公务卡"); 
				break;
			default: 
				LastReturn=PAYRET_CARDTYPEINVALID;
				SendLaneInfo("无效的IC卡");  
				break;
		}
	}
	return LastReturn;
}
BOOL  _IS_CardContext_MonthCard_Paid=F;
/**
 * 获得是否已经支付
 * 
 * @return 
 */
BOOL   GetIs_CardContext_MonthCard_Paid(void)
{
	return _IS_CardContext_MonthCard_Paid;
}

/**
 * 是否已经使用月票卡支付
 * 
 * @param b      是否支付
 */
void SetIs_CardContext_MonthCard_Paid(BOOL  b)
{
	_IS_CardContext_MonthCard_Paid=b;
}
BOOL  _IS_CardContext_SVCCard_Paid=F;
/**
 * 获得是否已经支付
 * 
 * @return 
 */
BOOL   GetIs_CardContext_SVCCard_Paid(void)
{
	return _IS_CardContext_SVCCard_Paid;
}

/**
 * 是否已经使用储值卡支付
 * 
 * @param b      是否支付
 */
void SetIs_CardContext_SVCCard_Paid(BOOL  b)
{
	_IS_CardContext_SVCCard_Paid=b;
}
void   Use_CardContext_SVCCard_Pay(void)
{
	BOOL OK=TRUE;
	char charinfo[400];
	struct MSG_SVRCARDLIST * _SVRList;
	float tempTollFare;
	float willapy = 0; 
	char *carInfo15 = Get15File();
	memset(charinfo,0x00,400);
	sprintf(charinfo,"提示：\n%s","");
	Set_CardContext_SVCCard_CanPay(F);
	_SVRList=FindCardInParamList(GetCardContext_CardNumber() );
	tempTollFare=Get_G_Current_Actual_pay();
	
	if(0!=strncmp(Get_KEYVER(),carInfo15 + 18,2))
	{
		SendLaneInfo("卡片密钥已过期");  
		sprintf(charinfo,"%s卡片密钥已过期！\n",charinfo );
		OK=FALSE; 
	}
	else if (_SVRList!=NULL)
	{
		echoic("adsfsd");
		if (F==GetCardIsNormal(_SVRList))
		{
	
			sprintf(charinfo,"%s此卡为%s卡\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			OK=FALSE;
		}
		else
		{
			float oldmoney=0;
			float DisRate = STRING2FLOAT(_SVRList->DisRate);
			willapy =(float)(int)(Get_G_Current_Actual_pay() * DisRate +0.5);
			
			echoic("优惠率 %f,优惠后金额 = %f \n", STRING2FLOAT(_SVRList->DisRate),willapy);
			oldmoney=WF_IC_ReadSVCMoney( );
			echoic("钱%f",oldmoney);
			if (oldmoney>=0)
			{
				sprintf(charinfo,"%s当前余额:%1.0f元\n应收:%1.0f元,折扣:%1.0f折,实收%1.0f元\n",charinfo,oldmoney,Get_G_Current_Actual_pay(),DisRate*10,willapy);
				if (oldmoney < willapy)//如果卡中的钱小于将要支付的钱就提示月不足
				{
					sprintf(charinfo,"%s余额不足，无法支付！\n",charinfo );
					OK=FALSE;
				}
				if (FALSE==CanPayForThisCarType(_SVRList, Get_Current_Car_Type() ))
				{
					sprintf(charinfo,"%s此卡不针对当前车型付款！\n",charinfo );
					OK=FALSE;
				}
			}
			else
			{
				sprintf(charinfo,"%s读取失败，请重试！\n",charinfo );
					OK=FALSE;
			}
		}
	}
	else
	{
		sprintf(charinfo,"%s此卡不存在！\n",charinfo );
		OK=FALSE;
	}
	Set_CardContext_SVCCard_CanPay(OK);
	if (OK)
	{
		Set_G_Current_Actual_pay(willapy);
		echoic("储值卡");
		if (tempTollFare!=Get_G_Current_Actual_pay())
		{
			sprintf(g_currentPrint.Charge,"%3.0f/%1.0f S",Get_G_Current_Actual_pay(),tempTollFare);
		}
		else
		{
			sprintf(g_currentPrint.Charge,"%3.0f S",Get_G_Current_Actual_pay());
		}
		sprintf(charinfo,"%s按【确认】键确认\n按【取消】键返回\n",charinfo);
		if (0==GetG_IsTuoche())
		{

			sprintf(charinfo,"%s按【模拟】键处理模拟拖",charinfo);
		}
	}
	else
	{
		sprintf(charinfo,"%s按【取消】键返回",charinfo);
	}
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("储值卡信息",GetCardContext_CardNumber(),OK,charinfo);
	
}

/**
 * 使用svc卡支付
 * 
 * @return 
 */
BOOL Use_CardContext_SVCCard_PayByCard(void)
{
	int ok=0;
	int BOK=TRUE;
	float writemoney;
	writemoney=Get_G_Current_Actual_pay();
	ok= WF_IC_WriteSVCMoney(writemoney);
	if (ok!=T)
	{
		echoic("写入失败");
		BOK=FALSE;
	}
	else
	{
		Setg_DiscountRate(Get_G_Current_Toll_Fare(),Get_G_Current_Actual_pay());
	}
	echoic("返回");
	return BOK;
}
/**
 * 获得当前储值卡的结余
 * 
 * @return 
 */
float Get_CardContext_SVC_Balance(void)
{
	return  atof(SUBSTRING(_CardToPay.SCVCard.Balance));
}
float Get_CardContext_SVC_BeforeBalance(void)
{
	return  atof(SUBSTRING(_CardToPay.SCVCard.BeforeBalance));
}
float Get_CardContext_SVC_UsedCash(void)
{
	return  atof(SUBSTRING(_CardToPay.SCVCard.UsedCash));
}

 

BOOL _CardContext_MonthCard_CanPay=FALSE;
//获取是否可以用月票卡支付
BOOL  Get_CardContext_MonthCard_CanPay(void)
{
	return _CardContext_MonthCard_CanPay; 
}
//设置似乎否可以用月票卡支付
void Set_CardContext_MonthCard_CanPay(BOOL _inputvalue)
{
	_CardContext_MonthCard_CanPay=_inputvalue;
}

char * Get_CardContext_MonthCard_CarType(void)
{
	return SUBSTRING( _CardToPay.MonthCard.CarType);
}

/**
 * 取得车牌后三位
 * 
 * @return 
 */
char * Get_CardContext_MonthCard_CarID(void)
{
	return SUBSTRING( _CardToPay.MonthCard.CarID);
}
/**
 * 使用月票卡支付
 */
void  Use_CardContext_MonthCard_Pay(void)
{
	BOOL OK=TRUE;
	char charinfo[400];
	struct MSG_SVRCARDLIST * _SVRList;
	char *carInfo15 = Get15File();
	_SVRList=FindCardInParamList(GetCardContext_CardNumber() );
	echoic("%s",(char*)_SVRList);
	memset(charinfo,0x00,400);
	sprintf(charinfo,"提示：\n%s","");
	if(0!=strncmp(Get_KEYVER(),carInfo15 + 18,2))
	{
		SendLaneInfo("卡片密钥已过期");  
		sprintf(charinfo,"%s卡片密钥已过期！\n",charinfo );
		OK=FALSE; 
	}
	else if (_SVRList==NULL)
	{
		OK=FALSE;
		sprintf(charinfo,"%s此卡不存在或尚未生效！\n",charinfo);
	}
	else
	{
		if (OK && F==GetCardIsNormal(_SVRList))
		{
			sprintf(charinfo,"%s此卡为%s卡\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			echoic("%s %s",GetCardStatus(SUBSTRING(_SVRList->Status)),SUBSTRING(_SVRList->Status));
			OK=FALSE;
		}
		sprintf(charinfo,"%s车牌号码:%s\n",charinfo,SUBSTRING(_SVRList->NumPlate));
		if (OK &&   atoi(SUBSTRING(_SVRList->Kind))!=atoi(Get_Current_Car_Type()))
		{
			sprintf(charinfo,"%s车型不正确\n",charinfo);
			echoic("车型 %s",SUBSTRING(_SVRList->Kind));
			OK=FALSE;
		}
		if (OK)
		{
			sprintf( charinfo ,"%s启用日期:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->EnableDate)));
			sprintf( charinfo ,"%s失效日期:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->DisEnableDate)));
			echoic("启用日期:%s",SUBSTRING(_SVRList->EnableDate));
			echoic("失效日期:%s",SUBSTRING(_SVRList->DisEnableDate));
			switch (GetIsCardDateLimit(_SVRList))
			{
				case 1:
					sprintf(charinfo,"%s此卡已过期 \n",charinfo);
					echoic("charinfo==%s   %d",charinfo ,DiffCurrentDataTime(SUBSTRING(_SVRList->DisEnableDate)));
					OK=FALSE;
					break;
				case 2:
					sprintf(charinfo,"%s此卡未启用 \n",charinfo);
					echoic("charinfo==%s",charinfo);
					OK=FALSE;
					break;
			}
		}
		if (OK)
		{
			HandOnceOK(VK_MOUNTHCARD,60);
			sprintf(charinfo,"%s按【确认】键确认\n",charinfo);
			if (0==GetG_IsTuoche())
			{

				sprintf(charinfo,"%s按【模拟】键处理模拟拖车\n",charinfo);
			}
		}

	}
	sprintf(charinfo,"%s按【取消】键返回\n",charinfo);
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("月票卡信息",GetCardNOByString(),OK,charinfo);
	Set_CardContext_MonthCard_CanPay(OK);
	if (OK==FALSE)
	{
		switch (GetICYPKERRGO ())
		{
			case   ICYPKERRGO_GOTO_normal:
				HandOnceOK(VK_RETURN,4);
				break;
			case  ICYPKERRGO_Wait_Cancel:
			default:
				break;
		}
	}
}
BOOL Use_CardContext_MonthCard_PayByCard(void)
{
	 BOOL OK=TRUE;
	char charinfo[400];
	struct MSG_SVRCARDLIST * _SVRList;
	memset(charinfo,0x00,400);
	sprintf(charinfo,"提示：\n%s","");
	Set_CardContext_MonthCard_CanPay(F);
	_SVRList=FindCardInParamList(GetCardContext_CardNumber());
	if (_SVRList!=NULL)
	{
		echoic("adsfsd");
		if (F==GetCardIsNormal(_SVRList))
		{
	
			sprintf(charinfo,"%s此卡为%s卡\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			OK=FALSE;
		}
		else
		{
			//float oldmoney=0;
			////oldmoney=WF_IC_ReadSVCMoney( );
			//echoic("钱%f",oldmoney);
			//if (oldmoney>=0)
			//{ 
			//	if (FALSE==CanPayForThisCarType(_SVRList, GetG_Current_Handl_Car_Type() ))
			//	{
			//		sprintf(charinfo,"%s此卡不针对当前车型付款！\n",charinfo );
			//		OK=FALSE;
			//	}
			//}
			//else
			//{
			//	sprintf(charinfo,"%s读取失败，请重试！\n",charinfo );
			//		OK=FALSE;
			//}
		}
	}
	else
	{
		sprintf(charinfo,"%s此卡不存在！\n",charinfo );
		OK=FALSE;
	}
	 Set_CardContext_MonthCard_CanPay(OK);
	if (OK)
	{
 
		sprintf(charinfo,"%s按【确认】键确认\n按【取消】键返回\n",charinfo);
		if (0==GetG_IsTuoche())
		{

			sprintf(charinfo,"%s按【模拟】键处理模拟拖",charinfo);
		}
	}
	else
	{
		sprintf(charinfo,"%s按【取消】键返回",charinfo);
	}
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("月票卡信息",GetCardContext_CardNumber(),OK,charinfo);
	return OK;	
}
 
 


BOOL _CardContext_SVCCard_CanPay=FALSE;
//获取是否可以用储值卡支付
BOOL  Get_CardContext_SVCCard_CanPay(void)
{
	return _CardContext_SVCCard_CanPay; 
}
//设置似乎否可以用储值卡卡支付
void Set_CardContext_SVCCard_CanPay(BOOL _inputvalue)
{
	_CardContext_SVCCard_CanPay=_inputvalue;
}
 

BOOL _CardContext_OfficialCard_CanPay=FALSE;
//获取是否可以用储值卡支付
BOOL  Get_CardContext_OfficialCard_CanPay(void)
{
	return _CardContext_OfficialCard_CanPay; 
}
//设置似乎否可以用储值卡卡支付
void Set_CardContext_OfficialCard_CanPay(BOOL _inputvalue)
{
	_CardContext_OfficialCard_CanPay=_inputvalue;
}
   BOOL  _IS_CardContext_OfficialCard_Paid=F;
/**
 * 获得是否已经支付
 * 
 * @return 
 */
BOOL   GetIs_CardContext_OfficialCard_Paid(void)
{
	return _IS_CardContext_OfficialCard_Paid;
}

/**
 * 是否已经使用月票卡支付
 * 
 * @param b      是否支付
 */
void SetIs_CardContext_OfficialCard_Paid(BOOL  b)
{
	_IS_CardContext_OfficialCard_Paid=b;
}
 
/**
 * 使用月票卡支付
 */
void  Use_CardContext_OfficialCard_Pay(void)
{
	BOOL OK=TRUE;
	char charinfo[400];
	struct MSG_SVRCARDLIST * _SVRList;
	char *carInfo15 = Get15File();
	_SVRList=FindCardInParamList(GetCardContext_CardNumber() );
	echoic("%s",(char*)_SVRList);
	memset(charinfo,0x00,400);
	sprintf(charinfo,"提示：\n%s","");

	if(0!=strncmp(Get_KEYVER(),carInfo15 + 18,2))
	{
		SendLaneInfo("卡片密钥已过期");  
		sprintf(charinfo,"%s卡片密钥已过期！\n",charinfo );
			OK=FALSE; 
	} 
	else 	if (_SVRList==NULL)
	{
		OK=FALSE;
		sprintf(charinfo,"%s此卡不存在或尚未生效！\n",charinfo);
	}
	else
	{
		if (OK && F==GetCardIsNormal(_SVRList))
		{
			sprintf(charinfo,"%s此卡为%s卡\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			echoic("%s %s",GetCardStatus(SUBSTRING(_SVRList->Status)),SUBSTRING(_SVRList->Status));
			OK=FALSE;
		}
		sprintf(charinfo,"%s车牌号码:%s\n",charinfo,SUBSTRING(_SVRList->NumPlate));
	 
		if (OK &&   atoi(SUBSTRING(_SVRList->Kind))!=atoi(Get_Current_Car_Type()) )
		{
			sprintf(charinfo,"%s车型不正确\n",charinfo);
			echoic("车型 %s",SUBSTRING(_SVRList->Kind));
			OK=FALSE;
		}
		if (OK)
		{
			sprintf( charinfo ,"%s启用日期:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->EnableDate)));
			sprintf( charinfo ,"%s失效日期:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->DisEnableDate)));
			echoic("启用日期:%s",SUBSTRING(_SVRList->EnableDate));
			echoic("失效日期:%s",SUBSTRING(_SVRList->DisEnableDate));
			switch (GetIsCardDateLimit(_SVRList))
			{
				case 1:
					sprintf(charinfo,"%s此卡已过期 \n",charinfo);
					echoic("charinfo==%s   %d",charinfo ,DiffCurrentDataTime(SUBSTRING(_SVRList->DisEnableDate)));
					OK=FALSE;
					break;
				case 2:
					sprintf(charinfo,"%s此卡未启用 \n",charinfo);
					echoic("charinfo==%s",charinfo);
					OK=FALSE;
					break;
			}
		}
		if (OK)
		{
			HandOnceOK(VK_GONGWU,4);
			sprintf(charinfo,"%s按【确认】键确认\n",charinfo);
			if (0==GetG_IsTuoche())
			{

				sprintf(charinfo,"%s按【模拟】键处理模拟拖车\n",charinfo);
			}
		}
		else
		{
			sprintf(charinfo,"%s按【取消】键返回\n",charinfo);
		}
	}
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("公务卡信息",GetCardNOByString(),OK,charinfo);

	Set_CardContext_OfficialCard_CanPay(OK);
	if (OK==FALSE)
	{
		switch (GetICYPKERRGO ())
		{
			case   ICYPKERRGO_GOTO_normal:
				HandOnceOK(VK_RETURN,4);
				break;
			case  ICYPKERRGO_Wait_Cancel:
			default:
				break;
		}
	}
}
BOOL Use_CardContext_OfficialCard_PayByCard(void)
{
 
	BOOL BOK=TRUE;
	 
	return BOK;
}
 
 
 
/**
 * 初始化卡上下文。 
 */
void  InitCardContext(void)
{
	_CardContext_MonthCard_CanPay=FALSE;
	memset((char*)&_CardToPay,'0',sizeof(struct ICCARD));
	memset( _CardContext_CardNumber,0x00,11);
	_IS_CardContext_MonthCard_Paid=FALSE;
	_IS_CardContext_SVCCard_Paid=FALSE;
	_IS_CardContext_OfficialCard_Paid=FALSE;
	_CardContext_SVCCard_CanPay=FALSE;
		_CardContext_OfficialCard_CanPay=FALSE;
 
}


