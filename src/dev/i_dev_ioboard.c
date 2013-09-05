#include "LocalIncludeFile.h"
#include "i_dev_ioboard.h"

char oldbt;
unsigned char  oldStatus;
time_t CurrenttimeUP ;
time_t CurrenttimeDown ;
//��ʼ������������ʱʹ��
int  I_DEV_IOBoard_Init(void)
{
	int result=0;
	if(T==EnabledIOBoard())
	{		
		if (strncmp(GetIOBoardDLL(),"RHY",3)==0)
		{
			result=  IO_Board_Init((lpIoInputFunc)I_DEV_IOBoard_Callback);
		}
		else if (strncmp(GetIOBoardDLL(),"SAT",3)==0)
		{
			result =I_DEV_IO_SAT_Init();
		}
	}	
	return result;
}
//�����˳�ʱʹ��
void I_DEV_IOBoard_Exit(void)
{
	
}
time_t CurrenttimeUP ;
time_t CurrenttimeDown ;
/*IO�������������������з��� ���磺��Ȧ*/
void I_DEV_IOBoard_Callback(unsigned char Input)
{
 
	switch (Input)
	{
	case GuangShanUp:

		echoic("��դ����");
		break;
	case GuangShanDown:

		echoic("��դ�뿪");
		break;
	case LineZhaPaiUp:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_UP, 0, 0);
		echoic("ץ����Ȧ����");
		break;
	case LineZhaPaiDown:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_DOWN, 0, 0);
		echoic("ץ����Ȧ�뿪");
		break;
	case LinePassUp:
		PostMessage(UI_Get_From_Handl(), MSG_BAR_UP, 0, 0);
		CurrenttimeUP = time(NULL);
		echoic("ͨ����Ȧ����");
		break;
	case LinePassDown:
		CurrenttimeDown = time(NULL);
		if ((CurrenttimeDown-CurrenttimeUP) >=1)
		{
			PostMessage(UI_Get_From_Handl(), MSG_BAR_DOWN, 0, 0);
		}
		echoic("ͨ����Ȧ�뿪");
		break;
	 default:
		break ;

	}
}

void I_DEV_IOBoard_CommandSender(int bFlag ,int command1,int command2)
{
	int temp1,temp2;
	if ( bFlag )
	{
		temp1 = command1;
		temp2 = command2;
	}
	else
	{
		temp1 = command2;
		temp2 = command1;
	}
	if (EnabledIOBoard()==T)
	{
		echoic("IO Lib Call  IO_Board_Out(%0x,%0X)!",temp1,temp2);

		if (strncmp(GetIOBoardDLL(),"RHY",3)==0)
		{
			IO_Board_Out(temp1,temp2);  
		}
		else if (strncmp(GetIOBoardDLL(),"SAT",3)==0)
		{
			I_DEV_IO_SAT_Out(temp2,temp1);
		}
	}
}
 