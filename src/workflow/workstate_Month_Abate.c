#include "LocalIncludeFile.h"




static int Validate_Abate_Number(char *abateNumber)
{	
	int ret = -1;
	if(0==Getg_AbateType())
	{	
		if(1==CheckYHKCardNumber(abateNumber))
		{	
			Validate_Car_Kind(VK_YOUHUICARD);
			G_Calculate_Final_Fare();
			ret=1;
		}
	}
	else if(1==CheckCardNumber(abateNumber))
	{	
		Validate_Car_Kind(VK_MOUNTHCARD);		
		G_Calculate_Final_Fare();	
		ret=1;		
	}
	return  ret ;
}


void WorkStation_23_Abate(int nKey)
{
	int MaxLengh;
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
		
		 GetG_AbateNumber()[strlen( GetG_AbateNumber())] = KeyChangCode(nKey);
		 UI_Show_Input_Text(GetG_AbateNumber());
		if (0==Getg_AbateType())
		{
			MaxLengh = atoi(sys_ini.AbateMaxLengh);
		}
		else
		{
			MaxLengh = atoi(sys_ini.MonthCardMaxLengh);
		}
		if (MaxLengh== strlen(GetG_AbateNumber()) )
		{
			Set_WorkStation_52_VKABATE_OK();
		}
		break;
	case VK_CANCEL:
		AddCancelCount();
		if (GetCancelCount() ==1)
		{
			if(0==Getg_AbateType())
			{
				Set_WorkStation_23_Abate("�������Żݳ�����");
			}
			else				
			{
				Set_WorkStation_23_Abate("��������Ʊ������");
			}
		}
		else
		{
			Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
		}
		break;
	default:
		ErrorPressKey();
		break;
	}
}

void WorkStation_204_FreeCar(int nKey)
{
	char temp[500];
	static int is_return =F;
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
		if(strlen( GetG_AbateNumber())<3)
		{
			GetG_AbateNumber()[strlen( GetG_AbateNumber())] = KeyChangCode(nKey);
			UI_Show_Input_Text(GetG_AbateNumber());
		}
		else if(is_return==F)
		{
			UI_Show_Help_Info("�밴��ȷ�ϡ���ȷ�ϳ��ƺ��룡");
		}
		else
		{
			ErrorPressKey();
		}
		break;
	case VK_RETURN:
		
		if(strlen( GetG_AbateNumber())<=3&&is_return==F)
		{
			sprintf(temp,"��ʾ��\n��˶���Ϣ��\n%s\n����ȷ�ϡ������ء�\n�������񡿼�ֱ�ӷ���\n����ȡ������ȡ����",GetCarInfo(GetG_AbateNumber()));
			UI_Show_Info(temp);
			is_return=T;
		}
		else if(is_return==T)
		{
			AddCancelCount();
			InitG_AbateNumber();
			Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
			is_return=F;
		}
		else
		{
			UI_Show_Help_Info("���������λ���ƺ��ٰ���ȷ�ϡ�����");
		}
		break;
	case VK_GONGWU:
		if(strlen( GetG_AbateNumber())<=3&&is_return==T)
		{
			if(GetCarInfoStaue()==T)
			{
				UI_SetCarType( VK_1);
				HandOnceOK(nKey,4);
				InitG_AbateNumber();
				is_return=F;
			}
			else
			{
				UI_Show_Help_Info("δ�鵽�����밴��ȷ�ϡ������ء��򰴡�ȡ������ȡ����");
			}
		}
		else
		{
			ErrorPressKey();
		}
		
		break;
	case VK_CANCEL:
		if(strlen( GetG_AbateNumber())>0)
		{
			Set_WorkStation_204_FreeCar();
		}
		else
		{
			AddCancelCount();
			InitG_AbateNumber();
			Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
		}
		is_return=F;
		break;
	default:
		ErrorPressKey();
		break;
	}
}
void WorkStation_47_FavourCardOK(int nKey)
{
	switch (nKey)
	{
	case VK_RETURN:	//����ģ��
		WorkStation_07_FUN_General_Second_OK_7(1);			
		break;
	case VK_CANCEL:
		if (1==atoi(sys_ini.OnceOkEnabledCancel))
		{
			Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
		}
		else
		{
			ErrorPressKey();
		}
		break;
	case VK_CLOSE_YPD:
		SetYuPeng(F);
		break;
	case VK_OPEN_YPD:
		SetYuPeng(T);
		break;
	case VK_MONI:		
		if (0==GetG_IsTuoche())
		{
			SendLaneInfo("����ģ��");
			Set_WorkStation_45_SimulateOnceOk();
		}
		else
		{
			SendLaneInfo("����ģ��");
			Set_WorkStation_53_SimulateOnceOkTuoche();
		}	
		break;
	default:
		ErrorPressKey();
		break;
	}
}
void WorkStation_52_Abate_OK(int nKey)
{
	int ret;
	char tempNetNo[3];
	char tempPlazaNo[3];
	memset(tempNetNo,0x00,sizeof(tempNetNo));
	memset(tempPlazaNo,0x00,sizeof(tempPlazaNo));
	switch (nKey)
	{
	case VK_RETURN:
		ret = Validate_Abate_Number(GetG_AbateNumber());
		if (-1==ret)
		{
			char tempInfo[250];
			HandOnceOK(VK_RETURN,4);
			sprintf(tempInfo,"��ʾ��\n����������󣬰��շѳ�����\n����ȷ�ϡ���̧�ˣ�"
				"\n����Ƿ�������Ƿ�\n����ģ�⡿�������ϳ�ģ�⡢���ĳ��͡����֡�");
			UI_Show_Info(tempInfo);
		}
		else
		{
			char temp[20];
			char tempInfo[250];
			time_t Currenttime = time(NULL);
			memset(temp,'\0',20);
			memset(tempInfo,'\0',250);
			strcpy(temp,GetG_AbateNumber());
			strncpy(tempNetNo,GetLanConfigNetNo(),2);
			strncpy(tempPlazaNo,GetLanConfigPlazaNo(),2);
			if (0==Getg_AbateType())
			{
				if (ValidateYHCarEndDate(GetG_AbateNumber(),Currenttime))
				{
					UI_ClearAbateChargeEditC();
					HandOnceOK(VK_RETURN,4);
					sprintf(tempInfo,"��ʾ��\n�ÿ����ѵ��ڣ����շѳ�����\n����ȷ�ϡ���̧�ˣ�"
						"\n����Ƿ�������Ƿ�\n����ģ�⡿�������ϳ�ģ�⡢���ĳ��͡����֡�");
					UI_Show_Info(tempInfo);
				}
				else if (ValidateYHCarStartDate(GetG_AbateNumber(),Currenttime))
				{
					UI_ClearAbateChargeEditC();
					HandOnceOK(VK_RETURN,4);
					sprintf(tempInfo,"��ʾ��\n�ÿ���δ���ã����շѳ�������Ч���ڣ�%s��\n����ȷ�ϡ���̧�ˣ�"
						"\n����Ƿ�������Ƿ�\n����ģ�⡿�������ϳ�ģ�⡢���ĳ��͡����֡�",
						GetYHCarStartDate(GetG_AbateNumber()));
					UI_Show_Info(tempInfo);
				}
				else
				{
					Set_WorkStation_47_FavourCardOK(temp,"���ʵ��ȷ��",GetYHCarStartDate(GetG_AbateNumber()),GetYHCarEndDate(GetG_AbateNumber()));
				}
			}
			else
			{
				if (ValidateYPKCarEndDate(GetG_AbateNumber(),Currenttime))
				{

					UI_ClearAbateChargeEditC();
					HandOnceOK(VK_RETURN,4);
					sprintf(tempInfo,"��ʾ��\n�ÿ����ѵ��ڣ����շѳ�����ʧЧ���ڣ�%s��\n����ȷ�ϡ���̧��"
						"\n����Ƿ�������Ƿ��\n����ģ�⡿�������ϳ�ģ�⡢���ĳ��͡����֡�",
						GetYPKCarEndDate(GetG_AbateNumber()));
					UI_Show_Info(tempInfo);
				}
				else if (ValidateYPKCarStartDate(GetG_AbateNumber(),Currenttime))
				{
					UI_ClearAbateChargeEditC();
					HandOnceOK(VK_RETURN,4);
					sprintf(tempInfo,"��ʾ��\n�ÿ���δ���ã����շѳ�����\n����ȷ�ϡ���̧��"
						"\n����Ƿ�������Ƿ��\n����ģ�⡿�������ϳ�ģ�⡢���ĳ��͡����֡�");
					UI_Show_Info(tempInfo);
				}
				else
				{
					Set_WorkStation_47_FavourCardOK(temp,"���ʵ��ȷ��",GetYPKCarStartTime(GetG_AbateNumber()),GetYPKCarEndDate(GetG_AbateNumber()));
				}
			}

		}
		break;
	case VK_CANCEL:
		AddCancelCount();
		if (GetCancelCount() ==1)
		{
			if(0==Getg_AbateType())
			{
				Set_WorkStation_23_Abate("�������Żݳ�����");
			}
			else				
			{
				Set_WorkStation_23_Abate("��������Ʊ������");
			}
		}
		else
		{
			Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
		}
		break;
	default:
		ErrorPressKey();
		break;
	}
}

