/************************************************************************/
/* 卡读写 fuxl 2008.5.30											    */
/************************************************************************/
#include "LocalIncludeFile.h"
#include "imf.h"
struct DAL_CSC_VAR dal_csc_var;
static int iOpenCardFlag=0;
/************************************************************************/
/* 天线初始化 liujl 2008.6.10                                           */
/************************************************************************/
int WF_IC_Init(HWND pWnd)
{
	
	dal_csc_var.bIsInit = TRUE;
	if(-1==I_DEV_IC_Init(pWnd))
	{			
		dal_csc_var.bIsInit = FALSE;
		return -1;
	}

	return 0;
}
void WF_TestICReader(void)
{
	if (dal_csc_var.bIsInit==FALSE)
	{
		if (TRUE==GetEnableIC())
		{
			echoic("启用了IC卡");
			WF_IC_Init(UI_Get_From_Handl());

		}
	}
}
/************************************************************************/
/* 重置信号 liujl 2008.6.10                                             */
/************************************************************************/
int WF_IC_GOpenCard(void)
{
	if(iOpenCardFlag==0)
	{
		iOpenCardFlag = 1;
		return I_DEV_IC_OpenCard();
	}

	return 0;
}

/************************************************************************/
/* 置信号 liujl 2008.6.10                                               */
/************************************************************************/
int WF_IC_GCloseCard(void)
{
	if(iOpenCardFlag==1)
	{
		iOpenCardFlag = 0;
		return I_DEV_IC_CloseCard();
	}
	return 0;
}
 
 
int WF_IC_TESTIC_STATE(void)
{
	int iReturn=0 ;
	int iTimes=0;
	do
	{
		iReturn = WF_IC_GOpenCard();
		iTimes++;
		if (iReturn != 0)
		{
			usleep(10*(iTimes+1));
		}
	} while (iTimes<9 && iReturn!=0);

	return iReturn;
}
float WF_IC_ReadSVCMoney( void)
{
	float iRet=-1;	
	char * tempcardinfo;
	char tmpvalue[17];
	int a;
	tempcardinfo=Get15File();
	if (tempcardinfo!=NULL)
	{			
		memset(tmpvalue,0x00,17);
		memcpy(tmpvalue,(char*)&tempcardinfo[12*2],16);
		echoic("卡内金额字段=%s",tmpvalue);
		a=atol(tmpvalue );
		iRet=a;//加钱之前的数字
		echoic("卡内的钱%f",iRet);
	}	
	return iRet;
}

BOOL  WF_IC_WriteBase(void)
{	
	if ( T == ReadyCard(GetHexCardNumber()) && T == EXTERNAL_AUTHENTICATE())
	{
		return T;
	}	
	return F ;
}
BOOL  WF_IC_WriteSVCMoney(  float addnumber )
{
	BOOL iRet=F;
	
	char * tempcardinfo=Get15File();
	char tmpvalue[17];
	char svcb[7];
	char svcob[7];
	float newnumber;
	float  a;
	if (tempcardinfo!=NULL)
	{			
		memset(tmpvalue,0x00,17);
		memcpy(tmpvalue,(char*)&tempcardinfo[12*2],16);			
		a=atof(tmpvalue );			
		memset(svcob,0x00,7);
		sprintf( svcob,"%06.0f",a);
		a=a-addnumber;
		newnumber=a;			
		sprintf(tmpvalue,"%016.0f",newnumber);			
		memcpy((char*)&tempcardinfo[12*2],tmpvalue,16);
		echoic("tempcardinfo:%s", tempcardinfo);
		iRet=   WriteCardInfo(tempcardinfo);
		memset(svcb,0x00,7);
		sprintf( svcb,"%06.0f",newnumber);
		SetExitTRMsgSVCBalance(svcb );
		SetExitTRMsgSVCOldBalance ( svcob);
	}
	
	return iRet;
}

char _ReadStaffCard[7];
char * ReadStaffCard(void)
{
	
	char * tempcardinfo=Get15File();
	char * tempcardinfo16=Get16File();		
	memset(_ReadStaffCard,0x00,7);
	if (tempcardinfo!=NULL && tempcardinfo16!=NULL && GetProType(tempcardinfo)==4)
	{		
		memset(_ReadStaffCard,0x00,7);
		memcpy(_ReadStaffCard, Read(tempcardinfo16,52,3),6);			
	}
	return _ReadStaffCard;
}
 
BOOL  WF_IC_WriteYPK(void)
{
	BOOL iRet=F;	
	char * tempcardinfo=Get15File();
	char tmpvalue[17];
	float  a;
	if (tempcardinfo!=NULL)
	{		
		memset(tmpvalue,0x00,17);
		memcpy(tmpvalue,(char*)&tempcardinfo[12*2],16);
		a=atof(tmpvalue );
	}
	return iRet;
}
