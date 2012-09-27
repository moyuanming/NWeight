#include "../global/include/LocalIncludeFile.h"


#define  CarNoLen 3
char CarNember[4];
int InputLen = 0;
void InitCarNember()
{
	memset(CarNember,' ',4);
	CarNember[3] = 0x00;
	InputLen = 0;

}
void SetCarNember(char *Input)
{
	strncpy(CarNember,Input,3);
	CarNember[3] = 0x00;
}
char *GetCarNember()
{
	return CarNember;
}
void WorkStation_66_InputCarNo(nKey)
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
			if (InputLen ==CarNoLen)
			{
				UI_Show_Help_Info("�밴��ȷ�ϡ���ȷ�ϳ��ƺ���!");
			}
			else
			{		
				 nKey = KeyChangCode(nKey);	
				CarNember[InputLen++] = (char)(nKey);
				UI_Show_Input_Text(CarNember);
			}
			break;
		case VK_RETURN:
			if (InputLen ==CarNoLen)
			{			
				Set_WorkStation_07_General_Second_OK("�����շ�","���ʵ��ȷ��");
			}
			else
			{
				UI_Show_Help_Info("�����복�ƺ���!");
			}
			break;
		case VK_CANCEL:
			if(0==InputLen)
			{
				Set_WorkStation_03_Main_Work("�����շ�","�ȴ�����");
			}
			else
			{
				InitCarNember();
				UI_Show_Input_Text(CarNember);
			}			
			break;
		default:
			ErrorPressKey();
			break;
	}
}


