#include "LocalIncludeFile.h"
 
struct currentSystemdevStatus G_CurrentSystemDevStatus;
 
 
 
struct Information_Node  *G_Head_Information_Node;
 
struct BILLPARAM g_currentPrint;
 
BOOL ftp_send_flag=T;

char G_CurrentInfo[350];
char G_CurrentInfoTemp[350];



#define KeyNumber ((3+6+4+1+1) +5*(5*5) +(2*5*(2+8+2+2))+3 + 5*4*2) +(2*5*7) +(5*5)+10

int KeyValue[KeyNumber]={
	VK_SHANGBAN,VK_8,VK_8,VK_8,VK_8,VK_8,VK_8,VK_RETURN,VK_8,VK_8,VK_8,VK_8,VK_RETURN,VK_OPEN_YPD,VK_CLOSE_YPD,
	VK_1,VK_1,VK_TRUCK,VK_RETURN  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_2,VK_1,VK_TRUCK,VK_RETURN  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_3,VK_1,VK_TRUCK,VK_RETURN  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_4,VK_1,VK_TRUCK,VK_RETURN  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_5,VK_1,VK_TRUCK,VK_RETURN  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 

	VK_1,VK_1,VK_TRUCK,VK_JUNCHE  ,VK_0,VK_0,VK_1,VK_RETURN,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_2,VK_1,VK_TRUCK,VK_JUNCHE  ,VK_0,VK_0,VK_1,VK_RETURN,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,
	VK_3,VK_1,VK_TRUCK,VK_JUNCHE  ,VK_0,VK_0,VK_1,VK_RETURN,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_4,VK_1,VK_TRUCK,VK_JUNCHE  ,VK_0,VK_0,VK_1,VK_RETURN,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,
	VK_5,VK_1,VK_TRUCK,VK_JUNCHE  ,VK_0,VK_0,VK_1,VK_RETURN,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 

	VK_1,VK_1,VK_TRUCK,VK_GONGWU  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_2,VK_1,VK_TRUCK,VK_GONGWU  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,
	VK_3,VK_1,VK_TRUCK,VK_GONGWU  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_4,VK_1,VK_TRUCK,VK_GONGWU  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_5,VK_1,VK_TRUCK,VK_GONGWU  ,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 

	VK_1,VK_1,VK_TRUCK,VK_LONGYONG    ,VK_0,VK_0,VK_1,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_2,VK_1,VK_TRUCK,VK_LONGYONG    ,VK_0,VK_0,VK_2,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_3,VK_1,VK_TRUCK,VK_LONGYONG    ,VK_0,VK_0,VK_3,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_4,VK_1,VK_TRUCK,VK_LONGYONG    ,VK_0,VK_0,VK_4,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_5,VK_1,VK_TRUCK,VK_LONGYONG    ,VK_0,VK_0,VK_5,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 

	VK_1,VK_1,VK_TRUCK,VK_LVSETONGDAO ,VK_0,VK_0,VK_1,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_2,VK_1,VK_TRUCK,VK_LVSETONGDAO ,VK_0,VK_0,VK_2,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_3,VK_1,VK_TRUCK,VK_LVSETONGDAO ,VK_0,VK_0,VK_4,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_4,VK_1,VK_TRUCK,VK_LVSETONGDAO ,VK_0,VK_0,VK_5,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_5,VK_1,VK_TRUCK,VK_LVSETONGDAO ,VK_0,VK_0,VK_6,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,


	VK_1,VK_1,VK_TRUCK,VK_YOUHUICARD ,VK_0,VK_0,VK_7,VK_7,VK_5,VK_6,VK_5,VK_5,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,  
	VK_2,VK_1,VK_TRUCK,VK_YOUHUICARD  ,VK_0,VK_0,VK_7,VK_7,VK_5,VK_6,VK_5,VK_5,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,  
	VK_3,VK_1,VK_TRUCK,VK_YOUHUICARD  ,VK_0,VK_0,VK_7,VK_7,VK_5,VK_6,VK_5,VK_5,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,  
	VK_4,VK_1,VK_TRUCK,VK_YOUHUICARD  ,VK_0,VK_0,VK_7,VK_7,VK_5,VK_6,VK_5,VK_5,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,   
	VK_5,VK_1,VK_TRUCK,VK_YOUHUICARD  ,VK_0,VK_0,VK_7,VK_7,VK_5,VK_6,VK_5,VK_5,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,   


	VK_1,VK_1,VK_TRUCK,VK_MOUNTHCARD  ,VK_0,VK_0,VK_0,VK_1,VK_1,VK_3,VK_9,VK_9,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN, 
	VK_2,VK_1,VK_TRUCK,VK_MOUNTHCARD  ,VK_0,VK_0,VK_0,VK_1,VK_1,VK_3,VK_9,VK_9,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,  
	VK_3,VK_1,VK_TRUCK,VK_MOUNTHCARD  ,VK_0,VK_0,VK_0,VK_1,VK_1,VK_3,VK_9,VK_9,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,   
	VK_4,VK_1,VK_TRUCK,VK_MOUNTHCARD  ,VK_0,VK_0,VK_0,VK_1,VK_1,VK_3,VK_9,VK_9,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,  
	VK_5,VK_1,VK_TRUCK,VK_MOUNTHCARD  ,VK_0,VK_0,VK_0,VK_1,VK_1,VK_3,VK_9,VK_9,VK_RETURN,VK_RETURN,MSG_BAR_UP,MSG_BAR_DOWN,  


	VK_CLOSE_YPD,VK_XIABAN, VK_RETURN

} ;
  
 int Index = 0;
void AutoManHandl()
{
	if(GetUseAutoMan()	)
	{
		if(Index>KeyNumber)
		{
			Index = 0;
		}
		if(KeyValue[Index] == MSG_BAR_UP)
		{
			G_CurrentSystemDevStatus.TongGuoLine = 1;
			PassLineUP();
			Index++;
		}
		else if(KeyValue[Index] == MSG_BAR_DOWN)
		{
			G_CurrentSystemDevStatus.TongGuoLine = 0;
			PassLineDown();
			Index++;
		}
		else
		{
			WorkStation(KeyValue[Index++]);
		}
		
	}
}
