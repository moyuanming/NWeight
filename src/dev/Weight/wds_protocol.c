#include "LocalIncludeFile.h"
#include <stdlib.h>
#include <time.h>
#include "carlist.h"
#include "serial.h"
#include "wds_protocol.h"
#define MAX_BUFFER 5
#define WDS_TIMEOUT 5
static const unsigned short
		crctab[256] = { 0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6,
				0x70E7, 0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE,
				0xF1EF, 0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7,
				0x62D6, 0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF,
				0xE3DE, 0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4,
				0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC,
				0xD58D, 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695,
				0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D,
				0xC7BC, 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802,
				0x3823, 0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A,
				0xB92B, 0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33,
				0x2A12, 0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B,
				0xAB1A, 0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60,
				0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68,
				0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51,
				0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59,
				0x8F78, 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E,
				0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046,
				0x6067, 0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F,
				0xF35E, 0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277,
				0x7256, 0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C,
				0xC50D, 0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424,
				0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D,
				0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615,
				0x5634, 0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A,
				0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882,
				0x28A3, 0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB,
				0xBB9A, 0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3,
				0x3A92, 0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8,
				0x8DC9, 0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0,
				0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9,
				0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1,
				0x1EF0 };

#define CalcCRC(crc16,data) (crc16=(crctab[((crc16>>8)&0xff)^(data&0xff)]^(crc16<<8)))

typedef struct bit {
	unsigned a :1;
	unsigned b :1;
	unsigned c :1;
	unsigned d :1;
	unsigned e :1;
	unsigned f :1;
	unsigned g :1;
	unsigned h :1;
} TBit;
typedef union bitchar {
	TBit bit;
	unsigned char c;
} TBitChar;

static int wds_fd;
static int wds_is_delete_car = 0;
void wds_setFD(int pfd) {
	wds_fd = pfd;
}

static time_t wds_WDS_Timeout;
WDS_Status_Event_Func wds_status_func = NULL;
void wds_Set_Status_Event_Func(WDS_Status_Event_Func func)
{
	wds_status_func = func;
}

void Wds_Init(PTWdsProtocol ptwds) {
	//ptwds->msg_data = (unsigned char *) malloc(sizeof(unsigned char));
	ptwds->order_type = 0;
	ptwds->msg_length = 0;
}
PTWdsProtocol wds_Create(void) {
	PTWdsProtocol result = (PTWdsProtocol) malloc(sizeof(TWdsProtocol));
	Wds_Init(result);
	return result;
}
void wds_Destroy(PTWdsProtocol ptwds) {
	if (ptwds != NULL) {
		/*if (ptwds->msg_data != NULL) {
			free(ptwds->msg_data);
		}*/
		free(ptwds);
	}
}
int wds_Length(PTWdsProtocol ptwds) {
	if (ptwds != NULL) {
		return ptwds->msg_length;
	}
	return 0;
}

void wds_insert(PTWdsProtocol ptwds, unsigned char data) {
	/*if (ptwds != NULL) {
	if ((ptwds->msg_length % MAX_BUFFER) == 0 && ptwds->msg_length
	>= MAX_BUFFER) {
	ptwds ->msg_data = (unsigned char *) realloc(ptwds->msg_data,
	sizeof(unsigned char) * ((ptwds->msg_length / MAX_BUFFER)
	+ 1) * MAX_BUFFER);
	}
	ptwds ->msg_data[ptwds->msg_length] = data;
	ptwds->msg_length++;
	}*/
}
void wds_copy(PTWdsProtocol ptwds, unsigned char * data, int length) {
	int i = 0;
	for (i = 0; i < length; i++) {
		wds_insert(ptwds, data[i]);
	}
}
unsigned char * wds_Data(PTWdsProtocol ptwds) {
	if (ptwds != NULL) {
		return ptwds->msg_data;
	}
	return NULL;
}
int wds_write(unsigned char *buf, int nbyte) {
	int i = 0;
	int c = 0;
	for (i = 0; i < nbyte; i++, buf++) {
		c = Serial_Write(wds_fd, buf, 1);
		echo_wds("%02X ", (int) (*(buf)));
	}
	return c;
}
unsigned short wds_getCRC(PTWdsProtocol ptwds) {
	unsigned short crc16 = 0;
	unsigned char i = 0;
	CalcCRC(crc16,0xFF);
	CalcCRC(crc16,ptwds->order_type);
	CalcCRC(crc16,(ptwds->msg_length + 5));
	for (i = 0; i < ptwds->msg_length; i++) {
		CalcCRC(crc16,ptwds->msg_data[i]);
	}
	return crc16;
}
sem_t wds_Semt;
void wds_Init_SEM()
{
	sem_init (&wds_Semt, 0, 1);
}
void wds_Destroy_SEM()
{
	sem_destroy(&wds_Semt);
}
void wds_Wait_SEM()
{


	echo_debug_WDS_Dll("wds_Wait_SEM Start <%d>",wds_Semt);
	sem_wait(&wds_Semt);
	echo_debug_WDS_Dll("wds_Wait_SEM End <%d>",wds_Semt);
}
void wds_Post_SEM()
{
	echo_debug_WDS_Dll("wds_Post_SEM Start <%d>",wds_Semt);
	sem_post(&wds_Semt);
	echo_debug_WDS_Dll("wds_Post_SEM End <%d>",wds_Semt);
}
void wds_Timeout_Init()
{
	wds_WDS_Timeout = time(NULL);
}
static void wds_Timeout_Status(void )
{
	time_t temptime = time(NULL) -wds_WDS_Timeout;
	//echoic("%ld - %ld = %ld",time(NULL),wds_WDS_Timeout,temptime);
	if(temptime>=WDS_TIMEOUT )
	{
		if(wds_is_delete_car==1)
		{
			wds_is_delete_car = 0;
		}
		if(temptime%WDS_TIMEOUT==0)
		{
			if(wds_status_func!=NULL)
			{
				LogCDev(LOG_DEBUG,"TimeOut");
				LogCDev(LOG_INFOR,"通讯超时");
				wds_status_func(5);
			}
		}
	}
}
void wds_Send(PTWdsProtocol ptwds) {
	echo_debug_WDS_Dll("Send Begin");
	wds_Wait_SEM();
	echo_debug_WDS_Dll("Send wds_Wait_SEM");
	unsigned short crc16;
	unsigned char t1 = 0, t2 = 0, s = 0xFF, l = ptwds->msg_length + 5;
	crc16 = wds_getCRC(ptwds);
	t1 = (unsigned char) (crc16 >> 8);
	t2 = (unsigned char) (crc16 & 0xff);
	echo_debug_WDS_Dll("Run Is!");
	wds_write(&s, 1);
	wds_write(&(ptwds->order_type), 1);
	wds_write(&l, 1);
	if (ptwds->msg_length > 0) {
		wds_write(ptwds->msg_data, ptwds->msg_length);
	}
	echo_debug_WDS_Dll("Run Is!");
	wds_write(&t1, 1);
	wds_write(&t2, 1);
	wds_Timeout_Status();
	usleep(60000);
	echo_debug_WDS_Dll("Run Is!");
	wds_Post_SEM();
	echo_debug_WDS_Dll("Send End");
}
int wds_read(unsigned char *buf, int nbyte) 
{
	int c = 0;
	c = Serial_Read(wds_fd, buf, nbyte);
	return c;
}


void wds_Call(PTWdsProtocol ptwds) {
	wds_Wait_SEM();
	echo_wds("Set Time");
	wds_WDS_Timeout = time(NULL);
	unsigned char * data = NULL;
	TBitChar Status;
	int c = Car_GetNum(), tempc = 0;
	int speed = 0,  i = 0, weight = 0, space = 0;
	int axlenum = 0;
	int TempCarNum = 0;
	if (ptwds != NULL) 
	{
		data = wds_Data(ptwds);
		LogCDev(LOG_DEBUG,"R %d",ptwds->order_type);
		switch (ptwds->order_type) {
		case 1://-------车辆信息处理-------------
			Car_SetCarOverload(c, data[7]);
			speed = data[8];
			speed = (speed << 8) + data[9];
			Car_SetCarSpeed(c, speed/10);
			Car_SetCarAcceleration(c, data[10]/10);
			axlenum = data[11];
			echo_wds("Overload:%d;Speed:%d;Acceleration:%d;",Car_GetCarOverload(c),Car_GetCarSpeed(c),Car_GetCarAcceleration(c));
			LogCDev(LOG_DEBUG,"R %d N:%d;O:%d;S:%d;A:%d;",ptwds->order_type,c,Car_GetCarOverload(c),Car_GetCarSpeed(c),Car_GetCarAcceleration(c));
			LogCDev(LOG_INFOR,"%d车;是否超限:%d;车速:%d;加速度:%d;",c,Car_GetCarOverload(c),Car_GetCarSpeed(c),Car_GetCarAcceleration(c));
			if (axlenum > 0 && axlenum<=15) {
				for (i = 0; i < axlenum; i++) {
					weight = data[13 + 2 * i];
					weight = (weight << 8) + data[13 + 2 * i + 1];
					if (i == 0) {
						space = 0;
					} else {
						space = data[13 + 3 * axlenum + 2 * i - 2];
						space = (space << 8) + data[13 + 3 * axlenum + 2 * i
								- 2 + 1];
					}
					Car_SetCarAxlesWeight(c, i, weight*10);
					Car_SetCarAxlesType(c, i, data[13 + 2 * axlenum + i]);
					Car_SetCarAxlesSpace(c, i, space);
					echo_wds("Weight:%d;Type:%d;Space:%d;",Car_GetCarAxlesWeight(c,i),Car_GetCarAxlesType(c,i),Car_GetCarAxlesSpace(c,i));
					LogCDev(LOG_DEBUG,"R %d C:%d;A:%d;W:%d;T:%d;S:%d;",ptwds->order_type,c,i,Car_GetCarAxlesWeight(c,i),Car_GetCarAxlesType(c,i),Car_GetCarAxlesSpace(c,i));
					LogCDev(LOG_INFOR,"%d车;%d轴;轴重:%d;轴型:%d;轴距:%d;",c,i,Car_GetCarAxlesWeight(c,i),Car_GetCarAxlesType(c,i),Car_GetCarAxlesSpace(c,i));
				}
			}
			while((Car_GetNum()-10)>0)
			{
				Car_QueuePop();
				SetHistoryWeight(Car_GetCarWeight(0));
				SetHistoryAxlesNum(Car_GetCarAxlesNum(0));
			}
			CarList_Change();
			wds_Post_SEM();
			wds_DropFirstInfo();
			break;
		case 3://-------临时数据-------------
			if(wds_is_delete_car==1)
			{
				wds_Post_SEM();
				break;
			}
			TempCarNum = TempCar_GetCarAxlesNum();
			TempCar_CarAxlesClear();
			TempCar_SetCarOverload( data[7]);
			speed = data[8];
			speed = (speed << 8) + data[9];
			TempCar_SetCarSpeed( speed);
			TempCar_SetCarAcceleration(data[10]);
			axlenum = data[11];
			echo_wds("TEMP Overload:%d;Speed:%d;Acceleration:%d;",TempCar_GetCarOverload(),TempCar_GetCarSpeed(),TempCar_GetCarAcceleration());
			LogCDev(LOG_DEBUG,"R %d O:%d;S:%d;A:%d;",ptwds->order_type,TempCar_GetCarOverload(),TempCar_GetCarSpeed(),TempCar_GetCarAcceleration());
			if (axlenum > 0 && axlenum<=15) {
				for (i = 0; i < axlenum; i++) {
					weight = data[13 + 2 * i];
					weight = (weight << 8) + data[13 + 2 * i + 1];
					if (i == 0) {
						space = 0;
					} else {
						space = data[13 + 3 * axlenum + 2 * i - 2];
						space = (space << 8) + data[13 + 3 * axlenum + 2 * i
								- 2 + 1];
					}
					TempCar_SetCarAxlesWeight( i, weight*10);
					TempCar_SetCarAxlesType( i, data[13 + 2 * axlenum + i]);
					TempCar_SetCarAxlesSpace( i, space);
					echo_wds("TEMP Weight:%d;Type:%d;Space:%d;",TempCar_GetCarAxlesWeight(i),TempCar_GetCarAxlesType(i),TempCar_GetCarAxlesSpace(i));
					LogCDev(LOG_DEBUG,"R %d W:%d;T:%d;S:%d;",ptwds->order_type,TempCar_GetCarAxlesWeight(i),TempCar_GetCarAxlesType(i),TempCar_GetCarAxlesSpace(i));
				}
			}
			if(TempCarNum != TempCar_GetCarAxlesNum())
			{
				CarList_Change();
			}
			wds_Post_SEM();
			break;
		case 4://-------车辆数---------------
			tempc = data[7];
			LogCDev(LOG_DEBUG,"R %d C:%d;",ptwds->order_type,tempc);
			wds_Post_SEM();
			if(tempc>0)
			{
				LogCDev(LOG_INFOR,"来车:%d辆;",tempc);
				wds_GetFirstWeightInfo();
			}
			break;
		case 5://-------处理设备状态-------------
			Status.c = (data[7]);
			LogCDev(LOG_DEBUG,"R %d S:%d;",ptwds->order_type,Status.c);
			if(Status.c>0)
			{
				LogCDev(LOG_INFOR,"错误状态:%d;",ptwds->order_type,Status.c);
			}
			wds_Post_SEM();
			/*
			 1	1	Bending plate sensor failure称台传感器故障
			 2	2	Optical grating failure光栅故障
			 3	4	Induction loop failure线圈故障
			 4	8	Reserved保留
			 5	16	Any communication failure or doesn’t receive any command from PC for 1 minute通讯故障或1分内没有收到车道计算机任何命令
			 6	32	Optical grating blocked by something else (dust, snow, ...)and long vehicle that more than 15 Axles光栅被遮挡(灰尘，冰雪..)以及被长车遮挡（>=15轴）
			 7	64	Wheel type sensor failure轮胎识别器故障
			 8	128	Reserved保留
			 */
			if (Status.bit.a == 1) {
				//Bending plate sensor failure称台传感器故障
				echo_wds("Bending plate sensor failure称台传感器故障");
				if(wds_status_func!=NULL)
				{
					wds_status_func(1);
				}
			}
			if (Status.bit.b == 1) {
				//Optical grating failure光栅故障
				echo_wds("Optical grating failure光栅故障");
				if(wds_status_func!=NULL)
				{
					wds_status_func(2);
				}
			}
			if (Status.bit.c == 1) {
				//Induction loop failure线圈故障
				echo_wds("Induction loop failure线圈故障");
				if(wds_status_func!=NULL)
				{
					wds_status_func(3);
				}
			}
			if (Status.bit.d == 1) {
				//Reserved保留
				echo_wds("Reserved保留");
				if(wds_status_func!=NULL)
				{
					wds_status_func(4);
				}
			}
			if (Status.bit.e == 1) {
				//Any communication failure or doesn’t receive any command from PC for 1 minute通讯故障或1分内没有收到车道计算机任何命令
				echo_wds("Any communication failure or doesn’t receive any command from PC for 1 minute通讯故障或1分内没有收到车道计算机任何命令");
				if(wds_status_func!=NULL)
				{
					wds_status_func(5);
				}
			}
			if (Status.bit.f == 1) {
				//Optical grating blocked by something else (dust, snow, ...)and long vehicle that more than 15 Axles光栅被遮挡(灰尘，冰雪..)以及被长车遮挡（>=15轴）
				//wds_GetFirstWeightInfo();
				echo_wds("Optical grating blocked by something else (dust, snow, ...)and long vehicle that more than 15 Axles光栅被遮挡(灰尘，冰雪..)以及被长车遮挡（>=15轴）");
				if(wds_status_func!=NULL)
				{
					wds_status_func(6);
				}
			}
			if (Status.bit.g == 1) {
				//Wheel type sensor failure轮胎识别器故障
				echo_wds("Wheel type sensor failure轮胎识别器故障");
				if(wds_status_func!=NULL)
				{
					wds_status_func(7);
				}
			}
			if (Status.bit.h == 1) {
				//Reserved保留
				echo_wds("Reserved保留");
				if(wds_status_func!=NULL)
				{
					wds_status_func(8);
				}
			}

			break;
		case 6://-------处理倒车-------------
			LogCDev(LOG_INFOR,"倒车;");
			Car_StackPop();
			CarList_Change();
			wds_Post_SEM();
			break;
		case 7://--------较时----------------
			wds_Post_SEM();
			switch (data[7]) {
			case 0://更新时间失败
				echo_wds("更新时间失败");
				break;
			case 1://更新时间成功
				echo_wds("更新时间成功");
				break;
			}
			break;
		case 8://-------删除第一条----------
			LogCDev(LOG_INFOR,"秤台删车成功;");
			wds_Post_SEM();
			wds_is_delete_car = 0;
			switch (data[7]) {
			case 0://删除失败
				//wds_DropFirstInfo();
				echo_wds("删除失败");
				break;
			case 1://删除成功
				echo_wds("删除成功");
				break;
			}
			break;
		default:
			LogCDev(LOG_INFOR,"未知命令;");
			wds_Post_SEM();
			break;
		}
	}
	
	else
	{
		wds_Post_SEM();
		echo_wds("ERROE");
	}
}
static volatile int SplitCount = 0;
static volatile int ProtocolLen = 0;
TWdsProtocol CurrentProtocol;

void SplitDevRecvData(unsigned char ReadChar)
{
	//echo_debug_WDS_Dll("SplitCount = <%d> ReadChar= <%02X>",SplitCount,ReadChar);
	if( 0 == SplitCount  && 0xFF !=ReadChar  ) return ; //开头必须是FF打头的命令才能接收
	
	SplitCount++;

	if(2==SplitCount)
	{
		CurrentProtocol.order_type = ReadChar;
	}
	else if(3 == SplitCount)
	{
		CurrentProtocol.msg_length = ReadChar-5;
		ProtocolLen = ReadChar;
	}
	else if(1!=SplitCount)
	{
		CurrentProtocol.msg_data[SplitCount-4] = ReadChar;
		if(ProtocolLen==SplitCount)
		{
			unsigned short crc16 = wds_getCRC(&CurrentProtocol);
			unsigned char  t1 = (unsigned char) (crc16 >> 8);
			unsigned char  t2 = (unsigned char) (crc16 & 0xff);
			echo_debug_WDS_Dll("Recv Data=<%2x><%02x><%02x><%02x><%02x>",CurrentProtocol.msg_data[0],CurrentProtocol.msg_data[ProtocolLen-5],t1,CurrentProtocol.msg_data[ProtocolLen-4],t2);
			if(CurrentProtocol.msg_data[ProtocolLen-5]==t1
				&&CurrentProtocol.msg_data[ProtocolLen-4]==t2)
			{
				wds_Call(&CurrentProtocol);
			}
			else
			{
				LogCDev(LOG_DEBUG,"CRC ERROR");
				LogCDev(LOG_INFOR,"收到错误指令");
			}
			SplitCount = 0;
		}
		
	}
}

void wds_SendCommand(int type) 
{
	LogCDev(LOG_DEBUG,"S %d",type);
	PTWdsProtocol pp = wds_Create();
	pp->order_type = type;
	wds_Send(pp);
	wds_Destroy(pp);
}
void wds_GetFirstWeightInfo(void) {
	if(wds_is_delete_car==0)
	{
		wds_is_delete_car = 1;
		TempCar_CarAxlesClear();
		wds_SendCommand(1);
	}
}
void wds_GetTempWeightInfo(void) {
	if(wds_is_delete_car==0)
	{
		wds_SendCommand(3);
	}
}
void wds_GetCarNum(void) {
	if(wds_is_delete_car==0)
	{
		wds_SendCommand(4);
	}
}
void wds_GetWeightStat(void) {
	wds_SendCommand(5);
}
void wds_GetUpdateDateTime(void) {
	LogCDev(LOG_DEBUG,"S 7");
	struct tm *rtc_timeer;
	time_t Currenttime;
	PTWdsProtocol pp = wds_Create();
	pp->order_type = 7;
	Currenttime = time(NULL);
	rtc_timeer = localtime(&Currenttime);
	pp->msg_data[0] =	(unsigned short) (((rtc_timeer->tm_year + 1900)
			- (rtc_timeer->tm_year + 1900) % 256) / 256);
	pp->msg_data[1] =	(unsigned short) (rtc_timeer->tm_year + 1900) % 256;
	pp->msg_data[2] =	 (unsigned short) rtc_timeer->tm_mon + 1;
	pp->msg_data[3] =	(unsigned short) rtc_timeer->tm_mday;
	pp->msg_data[4] =	(unsigned short) rtc_timeer->tm_hour;
	pp->msg_data[5] =	(unsigned short) rtc_timeer->tm_min;
	pp->msg_data[6] =	(unsigned short) rtc_timeer->tm_sec;
	pp->msg_length = 7;
	wds_Send(pp);
	wds_Destroy(pp);
}
void wds_DropFirstInfo(void) {
	LogCDev(LOG_INFOR,"发送删车指令");
	wds_SendCommand(8);
}
