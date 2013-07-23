#include "LocalIncludeFile.h"
#include "i_dev_ioboard.h"

char oldbt;
unsigned char  oldStatus;
time_t CurrenttimeUP ;
time_t CurrenttimeDown ;
//初始化，程序启动时使用
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
//程序退出时使用
void I_DEV_IOBoard_Exit(void)
{
	
}
time_t CurrenttimeUP ;
time_t CurrenttimeDown ;
/*IO输入量处理函数，请自行分析 例如：线圈*/
void I_DEV_IOBoard_Callback(unsigned char Input)
{
 
	switch (Input)
	{
	case GuangShanUp:

		echoic("光栅到达");
		break;
	case GuangShanDown:

		echoic("光栅离开");
		break;
	case LineZhaPaiUp:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_UP, 0, 0);
		echoic("抓拍线圈到达");
		break;
	case LineZhaPaiDown:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_DOWN, 0, 0);
		echoic("抓拍线圈离开");
		break;
	case LinePassUp:
		PostMessage(UI_Get_From_Handl(), MSG_BAR_UP, 0, 0);
		CurrenttimeUP = time(NULL);
		echoic("通过线圈到达");
		break;
	case LinePassDown:
		CurrenttimeDown = time(NULL);
		if ((CurrenttimeDown-CurrenttimeUP) >=1)
		{
			PostMessage(UI_Get_From_Handl(), MSG_BAR_DOWN, 0, 0);
		}
		echoic("通过线圈离开");
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
			I_DEV_IO_SAT_Out(temp1,temp2);
		}
	}
}
 