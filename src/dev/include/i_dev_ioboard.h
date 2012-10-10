#ifndef		_IO_BOARD_H_
#define		_IO_BOARD_H_

/*IO输出定义*/
#define T_LAMP_R (1<<14)  		/*顶棚红*/
#define T_LAMP_G (1<<15)		/*顶棚绿*/
#define C_LAMP_R (1<<12)		/*通行红*/
#define C_LAMP_G (1<<13)		/*通行绿*/
#define ALARM_LAMP (1<<2)		/*报警灯*/
#define FOG_LAMP (1<<3)			/*雾灯*/
#define C_BAR 	 (1<<6) 		/*1抬杆*/




#define OUTPUT2	 (1<<7) 

#define GuangShanUp		(1<<0)
#define GuangShanDown	(1<<1)
#define LineZhaPaiUp	(1<<2)
#define LineZhaPaiDown	(1<<3)
#define LinePassUp		(1<<4)
#define LinePassDown	(1<<5)
#define ConnError		(1<<31)
 
/*IO输入定义*/
#define LineCap     0x22	//抓拍线圈
#define LinePass    0x11	//通过线圈
#define GuangShan   0xCC	//光栅信号

/******************************************************************************
lpIoInputFunc：声明回调函数指针类型
功能：
	在IO输入状态改变时回调此函数
	初始化时传入
unsigned char status：
	表示IO状态 （参照IO输入定义）
******************************************************************************/
typedef void(*lpIoInputFunc)(unsigned int status);

/******************************************************************************
IO_Board_Init:接口初始化
输入：lpIoInputFunc 为处理 IO状态改变时的函数指针
	（参照 lpIoInputFunc：声明回调函数指针类型）
返回：0 表示成功
  	  -1 表示系统错误 例如：read() write() open()
******************************************************************************/
int IO_Board_Init(lpIoInputFunc Func);

/******************************************************************************
IO_Board_Out:IO输出驱动雨棚灯、栏杆、通行灯、报警等
输入： TurnOn  要开启的设备（参照IO输出定义）例如：T_LAMP_R|C_LAMP_R
	   TurnOff 要关闭的设备（参照IO输出定义）例如：C_LAMP_G|C_BAR
返回：0 表示成功
	  -1 表示系统错误 例如：read() write() open()
	  -100 表示通信错误
******************************************************************************/
int IO_Board_Out(unsigned int TurnOn,unsigned int TurnOff);


/******************************************************************************
IO_Usart_Tx: 通过IO板串口发送数据（用于控制 金额显示器）
输入： *tx 发送数据的指针
	   len 发送数据的长度
返回：0 表示成功
	  -1 表示系统错误 例如：read() write() open()
	  -100 表示通信错误
******************************************************************************/
int IO_Usart_Tx(char *tx ,int len);

/******************************************************************************
Vdm_line: 控制字符叠加
输入： line 行
	   coloum 列
	   nlen 长度
	   *VdmChar 叠加的字符指针
返回：0 表示成功
	  -1 表示系统错误 例如：read() write() open()
	  -100 表示通信错误
******************************************************************************/
int	Vdm_line(unsigned char line ,unsigned char coloum,unsigned char nlen,char *VdmChar);

/*同步时间*/
int Sync_Vdm_Time(void);

/*字符叠加初始化*/
int Vdm_init(void);

/*同步输入*/
int IO_Board_GetInput(void);




#endif
