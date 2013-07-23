#include "LocalIncludeFile.h"
BOOL VDM_IsInit=F;
BOOL I_DEVVDM_IsSupportChinese;
 
void I_DEV_VDM_Init(void)
{
	if (EnabledVDM()==T)
	{
		echo_ct("VDM <%s> Init",GetVDMDLL());
		if (strncmp(GetVDMDLL(),"RHY",3)==0)
		{
			Vdm_init();
			I_DEVVDM_IsSupportChinese=F ;
			VDM_IsInit=T;//瑞华赢字符叠加板和IO板一起被初始化了
		}
		else if (strncmp(GetVDMDLL(),"SAT",3)==0)
		{
			 VDM_SAT_Init();
			 I_DEVVDM_IsSupportChinese=VDM_SAT_SupportChinese();
			 VDM_IsInit=T;
		}
		else 
		{
			echo_ct("unknow vdm dll is  <%s>",GetVDMDLL());
		}
		if (VDM_IsInit)
		{
			//I_DEV_VDM_Reset();//这里不需要重置 因为 计时器 会自动重置。 
		}
	}
}



//叠加函数，参数分别为 内容  行  列  长度，如果内容不足指定的长度，则此函数补充空格来填满。
//内容长度不能超过23个。 行数不能大于二。负责直接返回。
void I_DEV_VDM_TextOut(char *text,unsigned char l,unsigned char c,unsigned char  len)
{
	char text_toshow[30];
	char text_tmp[300];
	memset(text_tmp,0x00,300);
	memset(text_toshow,0x00,30);
	sprintf(text_tmp,"%s                              ",text);
	strncpy(text_toshow,text_tmp,len);
	text_toshow[len]=0;
	if (EnabledVDM()==T)
	{
		if (strncmp(GetVDMDLL(),"RHY",3)==0)
		{
			Vdm_line(l,c,len, text_toshow);
		}
		else if (strncmp(GetVDMDLL(),"SAT",3)==0)
		{
			VDM_SAT_TextOut(text_toshow,l,c ,len);
		}
		else 
		{
			echo_ct("unknow vdm dll is  <%s>",GetVDMDLL());
		}
	}
}
//同步时间 这里每秒都会调用一次，大于1秒的频率 的在 接口中自行处理。 
void I_DEV_VDM_SyncTime(void)
{	
	if (EnabledVDM()==T)
	{
		if (strncmp(GetVDMDLL(),"RHY",3)==0)
		{
			Sync_Vdm_Time();
		}
		else if (strncmp(GetVDMDLL(),"SAT",3)==0)
		{
			VDM_SAT_SyncTime();
		}
		else 
		{
			echo_ct("unknow vdm dll is  <%s>",GetVDMDLL());
		}

	}
}

static pthread_t __I_DEV_VDM_Reset_T;
//字符叠加重置 每个小时 会重置一次， 为避免一些字符叠加器  屏幕会有乱码
void  I_DEV_VDM_Reset(void)
{
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&__I_DEV_VDM_Reset_T, &new_attr, (void *)I_DEV_VDM_Reset_T, NULL);
	pthread_attr_destroy(&new_attr);

}

void I_DEV_VDM_Reset_T(void)
{	
	if (strncmp(GetVDMDLL(),"RHY",3)==0)
	{
		int i =0;
		for( i=0;i<24;i++)
		{	
			I_DEV_VDM_TextOut("    ",i,0,24);	
		}
	}
	else if (strncmp(GetVDMDLL(),"SAT",3)==0)
	{
		VDM_SAT_Clear();
	}
	
	I_DEV_VDM_ShowPlaza(GetLanConfigStationNo());	
	I_DEV_VDM_LaneNO(GetLanConfigLaneNo());	
	I_DEV_VDM_CollectNo("      ");	
	I_DEV_VDM_CarType(" ");	
	I_DEV_VDM_CarKind(0);	
	I_DEV_VDM_Cash(-1);	
	//I_DEV_VDM_TextOut("DATE   -  -       :  :  ",11,0,23);	 
}
//叠加车种
void I_DEV_VDM_CarKind(int CarKind)
{	
	char CarKind_tmp[10];
	memset(CarKind_tmp,0x00,10);
	 
	 
	if(CarKind>0)
	{	
		sprintf(CarKind_tmp,I_DEVVDM_IsSupportChinese?CN_CARKIND:EN_CARKIND,CarKind);	
	}
	else
	{	
		sprintf(CarKind_tmp,I_DEVVDM_IsSupportChinese?CN_CARKIND_S:EN_CARKIND_S,"   ");	
	}
	I_DEV_VDM_TextOut( CarKind_tmp,1,8,8);	
}

//叠加现金
void I_DEV_VDM_Cash(int value)
{	
	char Cash_tmp[15];
	memset(Cash_tmp,0x00,15);    ;
	if (value>0)
	{
		sprintf(Cash_tmp,I_DEVVDM_IsSupportChinese?CN_CASH:EN_CASH,value);	
	}
	else
	{	
		sprintf(Cash_tmp,I_DEVVDM_IsSupportChinese?CN_CASH_S:EN_CASH_S,"   ");	
	}
	I_DEV_VDM_TextOut( Cash_tmp,1,15,12);	
}
//叠加车型
void I_DEV_VDM_CarType(char *CarType)
{	
	char CarType_tmp[15] ;
	memset(CarType_tmp,0x00,15);	
	sprintf(CarType_tmp,I_DEVVDM_IsSupportChinese?CN_CARTYPE: EN_CARTYPE,CarType);	
	I_DEV_VDM_TextOut(CarType_tmp,1,0,8);	
}
//叠加收费员
void I_DEV_VDM_CollectNo(char *CollectNo)
{	
    char CollectNo_tmp[15];
    memset(CollectNo_tmp,0x00,15);	
    sprintf(CollectNo_tmp,I_DEVVDM_IsSupportChinese?CN_COLLECT:EN_COLLECT,CollectNo);	
    I_DEV_VDM_TextOut(CollectNo_tmp,0,15,12);	
}
//叠加车道编号
void I_DEV_VDM_LaneNO(char *LaneNo)
{	
      char lane[15];
    memset(lane,0x00,15);	
    sprintf(lane,I_DEVVDM_IsSupportChinese?CN_LANENO:EN_LANENO,LaneNo);	
    I_DEV_VDM_TextOut(lane,0,8,8);	
}
//叠加收费站
void I_DEV_VDM_ShowPlaza(char *PlazaNo)
{	
    char plaza[15];
    memset(plaza,0x00,15);	
    sprintf(plaza,I_DEVVDM_IsSupportChinese?CN_PLAZA:EN_PLAZA,PlazaNo);	
    I_DEV_VDM_TextOut(plaza,0,0,10);	
}


