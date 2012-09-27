// ***************************************************************
//  CardContext   version:  1.0   ��  date: 2009��3��9��
//   -------------------------------------------------------------
//  �ṩic����ص���Ϣ
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
		sprintf(_CardStatus,"δ����");
	}
	else if (0==strncmp( CARDSTATUS_Normal,stat,2))
	{
		sprintf(_CardStatus ,"����");
	}
	else if (0==strncmp( CARDSTATUS_Reclaim,stat,2))
	{
		sprintf(_CardStatus ,"����");
	}
	else if (0==strncmp( CARDSTATUS_Scrap,stat,2))
	{
		sprintf(_CardStatus ,"����");
	}
	else if (0==strncmp( CARDSTATUS_ReportLoss,stat,2))
	{
		sprintf(_CardStatus ,"��ʧ");
	}
	else if (0==strncmp( CARDSTATUS_LockCard,stat,2))
	{
		sprintf(_CardStatus ,"������");
	}
	return _CardStatus;
}
/**
 * ��ȡ�������
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
 * ��ȡʧЧ����
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
 * ��ȡ��������
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
 * ����֧�����Ŀ����ͣ�����˿� ��ֵ�� ��Ʊ����
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
 * ����ʹ�ÿ�֧���Ĺ���
 * 
 * @return ���ش�����롣 �ɹ����� 0  �� 
 */
int UseCardToPay(void)
{
	int LastReturn =PAYRET_OK;
	struct MSG_SVRCARDLIST *  chardINfo=NULL;
	
	echoic("�������Ϸ����ſ�  ������ %s",       GetCardNOByString());
	memset( _CardContext_CardNumber,0x00,11);
	strncpy(_CardContext_CardNumber,GetCardNOByString(),10);
	chardINfo=FindCardInParamList(GetCardNOByString());

	if (chardINfo==NULL)
	{
		SendLaneInfo("δ֪��Ƭ��δ����");  
		LastReturn=PAYRET_READCARDKEYNOTFOND;//����ʧ�ܡ� 
	}
	else
	{
			echoic("sadfsdafasdffasdfasd");
		switch (atoi(SUBSTRING(chardINfo->SvrICKind)) )
		{
			case  CARDTYPE_SVCCard:	// 	  1  //��ֵ��
				Set_WorkStation_61_ConfirmPayBy_SVCCard();
				Use_CardContext_SVCCard_Pay();
				SendLaneInfo("����ʹ�ô�ֵ��");  
				break;
			case CARDTYPE_MonthCard://   2  //��Ʊ��
				Set_WorkStation_60_ConfirmPayBy_MonthCard();
				Use_CardContext_MonthCard_Pay();
				SendLaneInfo("����ʹ����Ʊ��");  
				break;

			case  CARDTYPE_OfficialCard ://   5  ����
				Set_WorkStation_62_ConfirmPayBy_OfficialCard();
				Use_CardContext_OfficialCard_Pay();
				SendLaneInfo("����ʹ�ù���"); 
				break;
			default: 
				LastReturn=PAYRET_CARDTYPEINVALID;
				SendLaneInfo("��Ч��IC��");  
				break;
		}
	}
	return LastReturn;
}
BOOL  _IS_CardContext_MonthCard_Paid=F;
/**
 * ����Ƿ��Ѿ�֧��
 * 
 * @return 
 */
BOOL   GetIs_CardContext_MonthCard_Paid(void)
{
	return _IS_CardContext_MonthCard_Paid;
}

/**
 * �Ƿ��Ѿ�ʹ����Ʊ��֧��
 * 
 * @param b      �Ƿ�֧��
 */
void SetIs_CardContext_MonthCard_Paid(BOOL  b)
{
	_IS_CardContext_MonthCard_Paid=b;
}
BOOL  _IS_CardContext_SVCCard_Paid=F;
/**
 * ����Ƿ��Ѿ�֧��
 * 
 * @return 
 */
BOOL   GetIs_CardContext_SVCCard_Paid(void)
{
	return _IS_CardContext_SVCCard_Paid;
}

/**
 * �Ƿ��Ѿ�ʹ�ô�ֵ��֧��
 * 
 * @param b      �Ƿ�֧��
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
	sprintf(charinfo,"��ʾ��\n%s","");
	Set_CardContext_SVCCard_CanPay(F);
	_SVRList=FindCardInParamList(GetCardContext_CardNumber() );
	tempTollFare=Get_G_Current_Actual_pay();
	
	if(0!=strncmp(Get_KEYVER(),carInfo15 + 18,2))
	{
		SendLaneInfo("��Ƭ��Կ�ѹ���");  
		sprintf(charinfo,"%s��Ƭ��Կ�ѹ��ڣ�\n",charinfo );
		OK=FALSE; 
	}
	else if (_SVRList!=NULL)
	{
		echoic("adsfsd");
		if (F==GetCardIsNormal(_SVRList))
		{
	
			sprintf(charinfo,"%s�˿�Ϊ%s��\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			OK=FALSE;
		}
		else
		{
			float oldmoney=0;
			float DisRate = STRING2FLOAT(_SVRList->DisRate);
			willapy =(float)(int)(Get_G_Current_Actual_pay() * DisRate +0.5);
			
			echoic("�Ż��� %f,�Żݺ��� = %f \n", STRING2FLOAT(_SVRList->DisRate),willapy);
			oldmoney=WF_IC_ReadSVCMoney( );
			echoic("Ǯ%f",oldmoney);
			if (oldmoney>=0)
			{
				sprintf(charinfo,"%s��ǰ���:%1.0fԪ\nӦ��:%1.0fԪ,�ۿ�:%1.0f��,ʵ��%1.0fԪ\n",charinfo,oldmoney,Get_G_Current_Actual_pay(),DisRate*10,willapy);
				if (oldmoney < willapy)//������е�ǮС�ڽ�Ҫ֧����Ǯ����ʾ�²���
				{
					sprintf(charinfo,"%s���㣬�޷�֧����\n",charinfo );
					OK=FALSE;
				}
				if (FALSE==CanPayForThisCarType(_SVRList, Get_Current_Car_Type() ))
				{
					sprintf(charinfo,"%s�˿�����Ե�ǰ���͸��\n",charinfo );
					OK=FALSE;
				}
			}
			else
			{
				sprintf(charinfo,"%s��ȡʧ�ܣ������ԣ�\n",charinfo );
					OK=FALSE;
			}
		}
	}
	else
	{
		sprintf(charinfo,"%s�˿������ڣ�\n",charinfo );
		OK=FALSE;
	}
	Set_CardContext_SVCCard_CanPay(OK);
	if (OK)
	{
		Set_G_Current_Actual_pay(willapy);
		echoic("��ֵ��");
		if (tempTollFare!=Get_G_Current_Actual_pay())
		{
			sprintf(g_currentPrint.Charge,"%3.0f/%1.0f S",Get_G_Current_Actual_pay(),tempTollFare);
		}
		else
		{
			sprintf(g_currentPrint.Charge,"%3.0f S",Get_G_Current_Actual_pay());
		}
		sprintf(charinfo,"%s����ȷ�ϡ���ȷ��\n����ȡ����������\n",charinfo);
		if (0==GetG_IsTuoche())
		{

			sprintf(charinfo,"%s����ģ�⡿������ģ����",charinfo);
		}
	}
	else
	{
		sprintf(charinfo,"%s����ȡ����������",charinfo);
	}
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("��ֵ����Ϣ",GetCardContext_CardNumber(),OK,charinfo);
	
}

/**
 * ʹ��svc��֧��
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
		echoic("д��ʧ��");
		BOK=FALSE;
	}
	else
	{
		Setg_DiscountRate(Get_G_Current_Toll_Fare(),Get_G_Current_Actual_pay());
	}
	echoic("����");
	return BOK;
}
/**
 * ��õ�ǰ��ֵ���Ľ���
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
//��ȡ�Ƿ��������Ʊ��֧��
BOOL  Get_CardContext_MonthCard_CanPay(void)
{
	return _CardContext_MonthCard_CanPay; 
}
//�����ƺ����������Ʊ��֧��
void Set_CardContext_MonthCard_CanPay(BOOL _inputvalue)
{
	_CardContext_MonthCard_CanPay=_inputvalue;
}

char * Get_CardContext_MonthCard_CarType(void)
{
	return SUBSTRING( _CardToPay.MonthCard.CarType);
}

/**
 * ȡ�ó��ƺ���λ
 * 
 * @return 
 */
char * Get_CardContext_MonthCard_CarID(void)
{
	return SUBSTRING( _CardToPay.MonthCard.CarID);
}
/**
 * ʹ����Ʊ��֧��
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
	sprintf(charinfo,"��ʾ��\n%s","");
	if(0!=strncmp(Get_KEYVER(),carInfo15 + 18,2))
	{
		SendLaneInfo("��Ƭ��Կ�ѹ���");  
		sprintf(charinfo,"%s��Ƭ��Կ�ѹ��ڣ�\n",charinfo );
		OK=FALSE; 
	}
	else if (_SVRList==NULL)
	{
		OK=FALSE;
		sprintf(charinfo,"%s�˿������ڻ���δ��Ч��\n",charinfo);
	}
	else
	{
		if (OK && F==GetCardIsNormal(_SVRList))
		{
			sprintf(charinfo,"%s�˿�Ϊ%s��\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			echoic("%s %s",GetCardStatus(SUBSTRING(_SVRList->Status)),SUBSTRING(_SVRList->Status));
			OK=FALSE;
		}
		sprintf(charinfo,"%s���ƺ���:%s\n",charinfo,SUBSTRING(_SVRList->NumPlate));
		if (OK &&   atoi(SUBSTRING(_SVRList->Kind))!=atoi(Get_Current_Car_Type()))
		{
			sprintf(charinfo,"%s���Ͳ���ȷ\n",charinfo);
			echoic("���� %s",SUBSTRING(_SVRList->Kind));
			OK=FALSE;
		}
		if (OK)
		{
			sprintf( charinfo ,"%s��������:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->EnableDate)));
			sprintf( charinfo ,"%sʧЧ����:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->DisEnableDate)));
			echoic("��������:%s",SUBSTRING(_SVRList->EnableDate));
			echoic("ʧЧ����:%s",SUBSTRING(_SVRList->DisEnableDate));
			switch (GetIsCardDateLimit(_SVRList))
			{
				case 1:
					sprintf(charinfo,"%s�˿��ѹ��� \n",charinfo);
					echoic("charinfo==%s   %d",charinfo ,DiffCurrentDataTime(SUBSTRING(_SVRList->DisEnableDate)));
					OK=FALSE;
					break;
				case 2:
					sprintf(charinfo,"%s�˿�δ���� \n",charinfo);
					echoic("charinfo==%s",charinfo);
					OK=FALSE;
					break;
			}
		}
		if (OK)
		{
			HandOnceOK(VK_MOUNTHCARD,60);
			sprintf(charinfo,"%s����ȷ�ϡ���ȷ��\n",charinfo);
			if (0==GetG_IsTuoche())
			{

				sprintf(charinfo,"%s����ģ�⡿������ģ���ϳ�\n",charinfo);
			}
		}

	}
	sprintf(charinfo,"%s����ȡ����������\n",charinfo);
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("��Ʊ����Ϣ",GetCardNOByString(),OK,charinfo);
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
	sprintf(charinfo,"��ʾ��\n%s","");
	Set_CardContext_MonthCard_CanPay(F);
	_SVRList=FindCardInParamList(GetCardContext_CardNumber());
	if (_SVRList!=NULL)
	{
		echoic("adsfsd");
		if (F==GetCardIsNormal(_SVRList))
		{
	
			sprintf(charinfo,"%s�˿�Ϊ%s��\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			OK=FALSE;
		}
		else
		{
			//float oldmoney=0;
			////oldmoney=WF_IC_ReadSVCMoney( );
			//echoic("Ǯ%f",oldmoney);
			//if (oldmoney>=0)
			//{ 
			//	if (FALSE==CanPayForThisCarType(_SVRList, GetG_Current_Handl_Car_Type() ))
			//	{
			//		sprintf(charinfo,"%s�˿�����Ե�ǰ���͸��\n",charinfo );
			//		OK=FALSE;
			//	}
			//}
			//else
			//{
			//	sprintf(charinfo,"%s��ȡʧ�ܣ������ԣ�\n",charinfo );
			//		OK=FALSE;
			//}
		}
	}
	else
	{
		sprintf(charinfo,"%s�˿������ڣ�\n",charinfo );
		OK=FALSE;
	}
	 Set_CardContext_MonthCard_CanPay(OK);
	if (OK)
	{
 
		sprintf(charinfo,"%s����ȷ�ϡ���ȷ��\n����ȡ����������\n",charinfo);
		if (0==GetG_IsTuoche())
		{

			sprintf(charinfo,"%s����ģ�⡿������ģ����",charinfo);
		}
	}
	else
	{
		sprintf(charinfo,"%s����ȡ����������",charinfo);
	}
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("��Ʊ����Ϣ",GetCardContext_CardNumber(),OK,charinfo);
	return OK;	
}
 
 


BOOL _CardContext_SVCCard_CanPay=FALSE;
//��ȡ�Ƿ�����ô�ֵ��֧��
BOOL  Get_CardContext_SVCCard_CanPay(void)
{
	return _CardContext_SVCCard_CanPay; 
}
//�����ƺ�������ô�ֵ����֧��
void Set_CardContext_SVCCard_CanPay(BOOL _inputvalue)
{
	_CardContext_SVCCard_CanPay=_inputvalue;
}
 

BOOL _CardContext_OfficialCard_CanPay=FALSE;
//��ȡ�Ƿ�����ô�ֵ��֧��
BOOL  Get_CardContext_OfficialCard_CanPay(void)
{
	return _CardContext_OfficialCard_CanPay; 
}
//�����ƺ�������ô�ֵ����֧��
void Set_CardContext_OfficialCard_CanPay(BOOL _inputvalue)
{
	_CardContext_OfficialCard_CanPay=_inputvalue;
}
   BOOL  _IS_CardContext_OfficialCard_Paid=F;
/**
 * ����Ƿ��Ѿ�֧��
 * 
 * @return 
 */
BOOL   GetIs_CardContext_OfficialCard_Paid(void)
{
	return _IS_CardContext_OfficialCard_Paid;
}

/**
 * �Ƿ��Ѿ�ʹ����Ʊ��֧��
 * 
 * @param b      �Ƿ�֧��
 */
void SetIs_CardContext_OfficialCard_Paid(BOOL  b)
{
	_IS_CardContext_OfficialCard_Paid=b;
}
 
/**
 * ʹ����Ʊ��֧��
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
	sprintf(charinfo,"��ʾ��\n%s","");

	if(0!=strncmp(Get_KEYVER(),carInfo15 + 18,2))
	{
		SendLaneInfo("��Ƭ��Կ�ѹ���");  
		sprintf(charinfo,"%s��Ƭ��Կ�ѹ��ڣ�\n",charinfo );
			OK=FALSE; 
	} 
	else 	if (_SVRList==NULL)
	{
		OK=FALSE;
		sprintf(charinfo,"%s�˿������ڻ���δ��Ч��\n",charinfo);
	}
	else
	{
		if (OK && F==GetCardIsNormal(_SVRList))
		{
			sprintf(charinfo,"%s�˿�Ϊ%s��\n",charinfo,GetCardStatus(SUBSTRING(_SVRList->Status)) );
			echoic("%s %s",GetCardStatus(SUBSTRING(_SVRList->Status)),SUBSTRING(_SVRList->Status));
			OK=FALSE;
		}
		sprintf(charinfo,"%s���ƺ���:%s\n",charinfo,SUBSTRING(_SVRList->NumPlate));
	 
		if (OK &&   atoi(SUBSTRING(_SVRList->Kind))!=atoi(Get_Current_Car_Type()) )
		{
			sprintf(charinfo,"%s���Ͳ���ȷ\n",charinfo);
			echoic("���� %s",SUBSTRING(_SVRList->Kind));
			OK=FALSE;
		}
		if (OK)
		{
			sprintf( charinfo ,"%s��������:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->EnableDate)));
			sprintf( charinfo ,"%sʧЧ����:%s\n",charinfo,FormatDate(SUBSTRING(_SVRList->DisEnableDate)));
			echoic("��������:%s",SUBSTRING(_SVRList->EnableDate));
			echoic("ʧЧ����:%s",SUBSTRING(_SVRList->DisEnableDate));
			switch (GetIsCardDateLimit(_SVRList))
			{
				case 1:
					sprintf(charinfo,"%s�˿��ѹ��� \n",charinfo);
					echoic("charinfo==%s   %d",charinfo ,DiffCurrentDataTime(SUBSTRING(_SVRList->DisEnableDate)));
					OK=FALSE;
					break;
				case 2:
					sprintf(charinfo,"%s�˿�δ���� \n",charinfo);
					echoic("charinfo==%s",charinfo);
					OK=FALSE;
					break;
			}
		}
		if (OK)
		{
			HandOnceOK(VK_GONGWU,4);
			sprintf(charinfo,"%s����ȷ�ϡ���ȷ��\n",charinfo);
			if (0==GetG_IsTuoche())
			{

				sprintf(charinfo,"%s����ģ�⡿������ģ���ϳ�\n",charinfo);
			}
		}
		else
		{
			sprintf(charinfo,"%s����ȡ����������\n",charinfo);
		}
	}
	echoic("charinfo==%s",charinfo);
	UI_MsgBox("������Ϣ",GetCardNOByString(),OK,charinfo);

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
 * ��ʼ���������ġ� 
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


