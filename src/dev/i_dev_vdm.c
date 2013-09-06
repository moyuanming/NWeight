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
		//	Vdm_init();
			I_DEVVDM_IsSupportChinese=F ;
			VDM_IsInit=T;//��Ӯ�ַ����Ӱ��IO��һ�𱻳�ʼ����
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
			//I_DEV_VDM_Reset();//���ﲻ��Ҫ���� ��Ϊ ��ʱ�� ���Զ����á� 
		}
	}
}



//���Ӻ����������ֱ�Ϊ ����  ��  ��  ���ȣ�������ݲ���ָ���ĳ��ȣ���˺�������ո���������
//���ݳ��Ȳ��ܳ���23���� �������ܴ��ڶ�������ֱ�ӷ��ء�
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
//ͬ��ʱ�� ����ÿ�붼�����һ�Σ�����1���Ƶ�� ���� �ӿ������д��� 
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
//�ַ��������� ÿ��Сʱ ������һ�Σ� Ϊ����һЩ�ַ�������  ��Ļ��������
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
	I_DEV_VDM_CollectNo(GetG_Number());
	I_DEV_VDM_CarType(" ");	 
	I_DEV_VDM_CarKind(0);	
	I_DEV_VDM_Cash(-1);	
	//I_DEV_VDM_TextOut("DATE   -  -       :  :  ",11,0,23);	 
}
//���ӳ���
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
	I_DEV_VDM_TextOut( CarKind_tmp,2,8,8);	
}

//�����ֽ�
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
	I_DEV_VDM_TextOut( Cash_tmp,2,15,12);	
}
//���ӳ���
void I_DEV_VDM_CarType(char *CarType)
{	
	char CarType_tmp[15] ;
	memset(CarType_tmp,0x00,15);	
	sprintf(CarType_tmp,I_DEVVDM_IsSupportChinese?CN_CARTYPE: EN_CARTYPE,CarType);	
	I_DEV_VDM_TextOut(CarType_tmp,2,0,8);	
}
//�����շ�Ա
void I_DEV_VDM_CollectNo(char *CollectNo)
{	
    char CollectNo_tmp[15];
    memset(CollectNo_tmp,0x00,15);	
    sprintf(CollectNo_tmp,I_DEVVDM_IsSupportChinese?CN_COLLECT:EN_COLLECT,CollectNo);	
    I_DEV_VDM_TextOut(CollectNo_tmp,1,15,12);	
}
//���ӳ������
void I_DEV_VDM_LaneNO(char *LaneNo)
{	
      char lane[15];
    memset(lane,0x00,15);	
    sprintf(lane,I_DEVVDM_IsSupportChinese?CN_LANENO:EN_LANENO,LaneNo);	
    I_DEV_VDM_TextOut(lane,1,8,8);	
}
//�����շ�վ
void I_DEV_VDM_ShowPlaza(char *PlazaNo)
{	
    char plaza[15];
    memset(plaza,0x00,15);	
    sprintf(plaza,I_DEVVDM_IsSupportChinese?CN_PLAZA:EN_PLAZA,PlazaNo);	
    I_DEV_VDM_TextOut(plaza,1,0,10);	
}


