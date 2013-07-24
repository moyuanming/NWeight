#include "LocalIncludeFile.h"
BOOL IO_SAT_IsInit=F;
#define JiaoTong_R 2+2
#define JiaoTong_G 3+2
#define ShenGuang  5+2
#define YUPENG_R   7+2
#define YUPENG_G   8+2
#define LANGAN     14+2
sem_t IO_SAT_Semt;
unsigned char sta[20] ={0x0a,'S','0','0','1','0','0','0','0','1','0','0','0','0','0','0','1','0',0x0d,0x00};
#define  SETSTA(__NEW__,__OLD__)  sta[(__NEW__)]=((TurnOn & (__OLD__))==0)? ((TurnOff & (__OLD__))==0?sta[(__NEW__)]:'0'):'1'


int  I_DEV_IO_SAT_Init(void)
{
	int x=IO_SAT_IsInit;
	if (IO_SAT_IsInit==F )
	{
		sem_init(&IO_SAT_Semt, 0, 1);
		serial_initbit7_JI(Get_IOBoardCOM(),Get_IOBoardCOMSpeed());
		CreateIO_STAThreadWrite();
		IO_SAT_IsInit=T;
	}
	return x;
}

static pthread_t IO_STAhread;
int CreateIO_STAThreadWrite(void) {
	int ret;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&IO_STAhread, &new_attr,
		(void *) IO_STA_ReceiveThread, NULL);
	pthread_attr_destroy(&new_attr);
	return ret;
}
int IO_STA_isRunning=1;
BOOL CanRead=T;
void IO_STA_ReceiveThread(void) 
{
	unsigned char starecv[15];
	int x;
	while (IO_STA_isRunning) 
	{
		if (CanRead==T)
		{
			sem_wait(&IO_SAT_Semt);
			{
				memset(starecv,0x00,sizeof(starecv));
				x=serial_read(Get_IOBoardCOM(), starecv,sizeof(starecv));
				if (starecv[0]==0x0a)
				{
					x=serial_read(Get_IOBoardCOM(), &starecv[1],sizeof(starecv)-1);
					if (starecv[1]=='E')
					{
						I_DEV_IO_SAT_Callback(starecv); 
					}
				}
			}
			sem_post(&IO_SAT_Semt);
		}
		usleep(1000);
	}
	sem_destroy(&IO_SAT_Semt); 
}
BOOL  sta_QianXianquan=-1;
BOOL  sta_HouXianquan=-1;

BOOL  sta_QianXianquan_OLD=-1;
BOOL  sta_HouXianquan_OLD=-1;
void I_DEV_IO_SAT_Callback(unsigned char *Inputstrs)
{
	unsigned char Input=0x00 ;
	BOOL  needout=F;
	if (Inputstrs[0]==0x0a && Inputstrs[1]=='E')
	{
		//前线圈， 即专拍线圈。 
		if (sta_QianXianquan==-1)
		{
			sta_QianXianquan=Inputstrs[6]==1?T:F; 
			Input=sta_QianXianquan?LineZhaPaiUp:LineZhaPaiDown;
		}
		else if (sta_QianXianquan==T && Inputstrs[6]=='0')
		{
			Input=LineZhaPaiDown;
			sta_QianXianquan=F;
		}
		else if (sta_QianXianquan==F  && Inputstrs[6]=='1')
		{
			Input=LineZhaPaiUp;
			sta_QianXianquan=T;
		}
		if (sta_QianXianquan_OLD!=sta_QianXianquan)
		{
			I_DEV_IOBoard_Callback(Input);
			needout=T;
			sta_QianXianquan_OLD=sta_QianXianquan;
		}



		//通过线圈， 即 后线圈 
		if (sta_HouXianquan==-1)
		{
			sta_HouXianquan=Inputstrs[5]==1?T:F; 
			Input=sta_HouXianquan?LinePassUp:LinePassDown;
		}
		else if (sta_HouXianquan==T && Inputstrs[5]=='0')
		{
			Input=LinePassDown;
			sta_HouXianquan=F;
		}
		else if (sta_HouXianquan==F  && Inputstrs[5]=='1')
		{
			Input=LinePassUp;
			sta_HouXianquan=T;
		}
		if (sta_HouXianquan_OLD!=sta_HouXianquan)
		{
			sta_HouXianquan_OLD=sta_HouXianquan;
			needout=T;
			I_DEV_IOBoard_Callback(Input);
		}
		if (needout)
		{
			echo_ct("STA::%s",Inputstrs);
			needout=F;
		}
	}
}

int  I_DEV_IO_SAT_Out(unsigned int TurnOn,unsigned int TurnOff)
{
	int result;
	CanRead=F;
	sem_wait(&IO_SAT_Semt);
	{
		SETSTA(JiaoTong_R,C_LAMP_R);
		SETSTA(JiaoTong_G,C_LAMP_G);
		SETSTA(YUPENG_R,T_LAMP_R);
		SETSTA(YUPENG_G,T_LAMP_G);
		SETSTA(ShenGuang,ALARM_LAMP);
		SETSTA(LANGAN,C_BAR);
		result=serial_write(Get_IOBoardCOM(), sta,sizeof(sta));
		//usleep(1000);
	}
	sem_post(&IO_SAT_Semt);
	CanRead=T;
	return result;
}
