#include "LocalIncludeFile.h"
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
	//	echoic("CALL IO LIB Vdm_line()");
		Vdm_line(l,c,len, text_toshow);
	}
}
void I_DEV_VDM_SyncTime(void)
{	
	if (EnabledVDM()==T)
	{
		//echoic("CALL IO LIB Sync_Vdm_Time()");
		Sync_Vdm_Time();
	}
}


//�ַ���������
void I_DEV_VDM_Reset(void)
{	
	int i =0;
	for( i=0;i<24;i++)
	{	
		I_DEV_VDM_TextOut("  ",i,0,24);	
	}
	I_DEV_VDM_ShowPlaza(GetLanConfigStationNo());	
	I_DEV_VDM_LaneNO(GetLanConfigLaneNo());	
	I_DEV_VDM_CollectNo(" ");	
	I_DEV_VDM_CarType(" ");	
	I_DEV_VDM_CarKind(0);	
	I_DEV_VDM_Cash(-1);	
	I_DEV_VDM_TextOut("DATE   -  -       :  :  ",11,0,23);	 
}
//���ӳ���
void I_DEV_VDM_CarKind(int CarKind)
{	
	char CarKind_tmp[10];
	memset(CarKind_tmp,0x00,10);	;
	if(CarKind>0)
	{	
		sprintf(CarKind_tmp,"K:%d ",CarKind);	
	}
	else
	{	
		sprintf(CarKind_tmp,"K:%s","   ");	
	}
	I_DEV_VDM_TextOut( CarKind_tmp,1,8,7);	
}
//�����ֽ�
void I_DEV_VDM_Cash(int value)
{	
	char Cash_tmp[10];
	memset(Cash_tmp,0x00,10);    ;
	if (value>0)
	{
		if (Get_CardContext_SVCCard_CanPay())
		{
			sprintf(Cash_tmp,"M:%d S",value); 
		}
		else if (Get_CardContext_MonthCard_CanPay())
		{
			sprintf(Cash_tmp,"M:%d M",value);   
		}
		else
		{
			sprintf(Cash_tmp,"M:%d   ",value);	
		}
	}
	else
	{	
		sprintf(Cash_tmp,"M:%s","   ");	
	}
	I_DEV_VDM_TextOut( Cash_tmp,1,15,8);	
}
//���ӳ���
void I_DEV_VDM_CarType(char *CarType)
{	
	char CarType_tmp[10] ;
	memset(CarType_tmp,0x00,10);	
	sprintf(CarType_tmp,"T:%s",CarType);	
	I_DEV_VDM_TextOut(CarType_tmp,1,0,5);	
}
//�����շ�Ա
void I_DEV_VDM_CollectNo(char *CollectNo)
{	
    char CollectNo_tmp[10];
    memset(CollectNo_tmp,0x00,10);	
    sprintf(CollectNo_tmp,"C:%s",CollectNo);	
    I_DEV_VDM_TextOut(CollectNo_tmp,0,15,9);	
}
//���ӳ������
void I_DEV_VDM_LaneNO(char *LaneNo)
{	
      char lane[10];
    memset(lane,0x00,10);	
    sprintf(lane,"L:%s",LaneNo);	
    I_DEV_VDM_TextOut(lane,0,8,7);	
}
//�����շ�վ
void I_DEV_VDM_ShowPlaza(char *PlazaNo)
{	
    char plaza[10];
    memset(plaza,0x00,10);	
    sprintf(plaza,"P:%s",PlazaNo);	
    I_DEV_VDM_TextOut(plaza,0,0,8);	
}


