#include "LocalIncludeFile.h"

/*******************************************************************************/
// 欠款单号
/*******************************************************************************/
char G_ArrearageNumber[20];

void  InitG_ArrearageNumber(void)
{	
	memset(G_ArrearageNumber,'\0',20);	
}

void  SETG_ArrearageNumber_end(int value)
{	
	G_ArrearageNumber[value-1]='\0';
}



char *GetG_ArrearageNumber(void)
{	
	return G_ArrearageNumber;
}
/*******************************************************************************/
//欠款额
/*******************************************************************************/

int G_ArrearageCharge=0;
void SetG_ArrearageCharge(int value)
{	
	G_ArrearageCharge=value;
}

int GetG_ArrearageCharge(void)
{	
	return G_ArrearageCharge;
}

/*******************************************************************************/
//欠款额
/*******************************************************************************/
char G_ArrearageChargeChar[20];

void  SETG_ArrearageChargeChar_end(int value)
{	
	G_ArrearageChargeChar[value-1]='\0';
}
void InitG_ArrearageChargeChar(void)
{	
	memset(G_ArrearageChargeChar,'\0',20);	
}
void SetG_ArrearageChargeChar(char *value)
{	
	strncpy(G_ArrearageChargeChar,value,sizeof(G_ArrearageChargeChar));	
}
char *GetG_ArrearageChargeChar(void)
{	
	return G_ArrearageChargeChar;
}
void WorkStation_42_HandArrearageNumber(int nKey)
{
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
		GetG_ArrearageNumber()[strlen(GetG_ArrearageNumber())] = KeyChangCode(nKey);
		UI_Show_Input_Text(GetG_ArrearageNumber());
		if (atoi(sys_ini.MaxArrearageNumber)<strlen(GetG_ArrearageNumber()) )
		{
			ErrorShow("欠款单号到达最大长度！");
			SETG_ArrearageNumber_end(strlen(GetG_ArrearageNumber()));
			
		}
		break;
	case VK_RETURN:
		if (0==strlen(GetG_ArrearageNumber()))
		{
			ErrorShow("请输入欠款单号！");
		}
		else
		{
			if (1==atoi(sys_ini.IsInPueArrearageCharege))
			{
				Set_WorkStation_43_HandArrearageCharge();
			}
			else
			{
				if (7==GetG_BeforWzWorkstation())
				{
					WorkStation_07_FUN_General_Second_OK_7(1);
				}
			}
		}
		break;
	case VK_CANCEL:
		AddCancelCount();
		if (GetCancelCount() ==1)
		{
			Set_WorkStation_42_HandArrearageNumber(GetG_BeforWzWorkstation());
		}
		else
		{
			if (7==GetG_BeforWzWorkstation())
			{
				Set_WorkStation_07_General_Second_OK("正常收费","请核实并确认");
			}		
		}
		break;
	default:
		ErrorPressKey();
		break;
	}

}
void WorkStation_43_HandArrearageCharge(int nKey)
{
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
		
		GetG_ArrearageChargeChar()[strlen(GetG_ArrearageChargeChar())] = KeyChangCode(nKey);
		UI_Show_Input_Text( GetG_ArrearageChargeChar());
		if ((int)Get_G_Current_Actual_pay()<atoi(GetG_ArrearageChargeChar()) )
		{
			ErrorShow("欠款金额不能大于应收金额！");
			SETG_ArrearageChargeChar_end(strlen(GetG_ArrearageChargeChar()));
			
		}
		break;
	case VK_RETURN:
		if (0==strlen(GetG_ArrearageChargeChar()))
		{
			ErrorShow("请输入欠款金额！");
		}
		else
		{
			if (7==GetG_BeforWzWorkstation())
			{
				WorkStation_07_FUN_General_Second_OK_7(1);
			}
		}
		break;
	case VK_CANCEL:
		AddCancelCount();
		if (GetCancelCount() ==1)
		{
			Set_WorkStation_43_HandArrearageCharge();
		}
		else
		{
			Set_WorkStation_42_HandArrearageNumber(GetG_BeforWzWorkstation());
		}
		break;
	default:
		ErrorPressKey();
		break;
	}

}




