#include "LocalIncludeFile.h"
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
		Vdm_line(GetIo_board(),l,c,len, text_toshow);
	}
}
void I_DEV_VDM_SyncTime(void)
{	
	if (EnabledVDM()==T)
	{
		Sync_Vdm_Time(GetIo_board());
	}
}
//字符叠加
void  Sync_Vdm_Time(io_board_t *io)
{
	static unsigned char send[11] =  {WRITE_CMD,WRITE_VDM,8,VDM_DATA_TIME,1,2,3,4,5,6,0xcc};
	char read_Vdm_Time[3]={0x00,0x00,0x00};
	time_t t;
	struct tm *rtc_time;
	t = time(NULL);
	rtc_time = localtime(&t);
	rtc_time->tm_year &=0xff;
	rtc_time->tm_year -=100;
	send[4]=rtc_time->tm_year;
	send[5]=rtc_time->tm_mon+1;
	send[6]=rtc_time->tm_mday;
	send[7]=rtc_time->tm_hour;
	send[8]=rtc_time->tm_min;
	send[9]=rtc_time->tm_sec;
	send[10]=get_crc8(&send[3],7);
	sem_wait(&io->IO_Semt);
err_Vdm_Time:
	write(io->IO_fd,send,11);
	usleep(50);
	read(io->IO_fd,read_Vdm_Time,2);
	if(strcmp(read_Vdm_Time,"OK")!=0)
	{

		goto err_Vdm_Time;
	}
	sem_post(&io->IO_Semt);

}

int	Vdm_line(io_board_t *io ,unsigned char line ,unsigned char coloum,
	unsigned char nlen,char *VdmChar)
{
	unsigned char Vdm_line_send[40];// =  WRITE_CMD,WRITE_VDM,0,VDM_LINE,0,0,0};
	char read_Vdm_line[3]={ 0x00,0x00,0x00};
	if( line >2 && coloum>24 && nlen>24)
		return -1;

	Vdm_line_send[0] = WRITE_CMD;
	Vdm_line_send[1] = WRITE_VDM;
	Vdm_line_send[2]= 4 + nlen + 1;
	Vdm_line_send[3] = VDM_LINE;
	Vdm_line_send[4] = line;
	Vdm_line_send[5] = coloum;
	Vdm_line_send[6] = nlen;

	memcpy(&Vdm_line_send[7],VdmChar,nlen);
	Vdm_line_send[nlen+7] = get_crc8(&Vdm_line_send[3],(nlen+4));
	sem_wait(&io->IO_Semt);
err_Vdm_Line:
	write(io->IO_fd,Vdm_line_send,(8+nlen));
	usleep(1000*nlen);
	read(io->IO_fd,read_Vdm_line,2);
	if(strcmp(read_Vdm_line,"OK")!=0)
	{
		goto err_Vdm_Line;
	}
	sem_post(&io->IO_Semt);

	return 0;


}
//字符叠加重置
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
//叠加车种
void I_DEV_VDM_CarKind(int CarKind)
{	
	char CarKind_tmp[10];
	memset(CarKind_tmp,0x00,10);	;
	if(CarKind>0)
	{	
		sprintf(CarKind_tmp,"K:%c ",GetCarKindChar(CarKind));	
	}
	else
	{	
		sprintf(CarKind_tmp,"K:%s","   ");	
	}
	I_DEV_VDM_TextOut( CarKind_tmp,1,8,7);	
}
//叠加现金
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
//叠加车型
void I_DEV_VDM_CarType(char *CarType)
{	
     char CarType_tmp[10] ;
    memset(CarType_tmp,0x00,10);	
   sprintf(CarType_tmp,"T:%s",CarType);	
   I_DEV_VDM_TextOut(CarType_tmp,1,0,5);	
}
//叠加收费员
void I_DEV_VDM_CollectNo(char *CollectNo)
{	
    char CollectNo_tmp[10];
    memset(CollectNo_tmp,0x00,10);	
    sprintf(CollectNo_tmp,"C:%s",CollectNo);	
    I_DEV_VDM_TextOut(CollectNo_tmp,0,15,9);	
}
//叠加车道编号
void I_DEV_VDM_LaneNO(char *LaneNo)
{	
      char lane[10];
    memset(lane,0x00,10);	
    sprintf(lane,"L:%s",LaneNo);	
    I_DEV_VDM_TextOut(lane,0,8,7);	
}
//叠加收费站
void I_DEV_VDM_ShowPlaza(char *PlazaNo)
{	
    char plaza[10];
    memset(plaza,0x00,10);	
    sprintf(plaza,"P:%s",PlazaNo);	
    I_DEV_VDM_TextOut(plaza,0,0,8);	
}


