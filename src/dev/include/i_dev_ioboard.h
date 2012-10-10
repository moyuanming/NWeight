#ifndef		_IO_BOARD_H_
#define		_IO_BOARD_H_

/*IO�������*/
#define T_LAMP_R (1<<14)  		/*�����*/
#define T_LAMP_G (1<<15)		/*������*/
#define C_LAMP_R (1<<12)		/*ͨ�к�*/
#define C_LAMP_G (1<<13)		/*ͨ����*/
#define ALARM_LAMP (1<<2)		/*������*/
#define FOG_LAMP (1<<3)			/*���*/
#define C_BAR 	 (1<<6) 		/*1̧��*/




#define OUTPUT2	 (1<<7) 

#define GuangShanUp		(1<<0)
#define GuangShanDown	(1<<1)
#define LineZhaPaiUp	(1<<2)
#define LineZhaPaiDown	(1<<3)
#define LinePassUp		(1<<4)
#define LinePassDown	(1<<5)
#define ConnError		(1<<31)
 
/*IO���붨��*/
#define LineCap     0x22	//ץ����Ȧ
#define LinePass    0x11	//ͨ����Ȧ
#define GuangShan   0xCC	//��դ�ź�

/******************************************************************************
lpIoInputFunc�������ص�����ָ������
���ܣ�
	��IO����״̬�ı�ʱ�ص��˺���
	��ʼ��ʱ����
unsigned char status��
	��ʾIO״̬ ������IO���붨�壩
******************************************************************************/
typedef void(*lpIoInputFunc)(unsigned int status);

/******************************************************************************
IO_Board_Init:�ӿڳ�ʼ��
���룺lpIoInputFunc Ϊ���� IO״̬�ı�ʱ�ĺ���ָ��
	������ lpIoInputFunc�������ص�����ָ�����ͣ�
���أ�0 ��ʾ�ɹ�
  	  -1 ��ʾϵͳ���� ���磺read() write() open()
******************************************************************************/
int IO_Board_Init(lpIoInputFunc Func);

/******************************************************************************
IO_Board_Out:IO�����������ơ����ˡ�ͨ�еơ�������
���룺 TurnOn  Ҫ�������豸������IO������壩���磺T_LAMP_R|C_LAMP_R
	   TurnOff Ҫ�رյ��豸������IO������壩���磺C_LAMP_G|C_BAR
���أ�0 ��ʾ�ɹ�
	  -1 ��ʾϵͳ���� ���磺read() write() open()
	  -100 ��ʾͨ�Ŵ���
******************************************************************************/
int IO_Board_Out(unsigned int TurnOn,unsigned int TurnOff);


/******************************************************************************
IO_Usart_Tx: ͨ��IO�崮�ڷ������ݣ����ڿ��� �����ʾ����
���룺 *tx �������ݵ�ָ��
	   len �������ݵĳ���
���أ�0 ��ʾ�ɹ�
	  -1 ��ʾϵͳ���� ���磺read() write() open()
	  -100 ��ʾͨ�Ŵ���
******************************************************************************/
int IO_Usart_Tx(char *tx ,int len);

/******************************************************************************
Vdm_line: �����ַ�����
���룺 line ��
	   coloum ��
	   nlen ����
	   *VdmChar ���ӵ��ַ�ָ��
���أ�0 ��ʾ�ɹ�
	  -1 ��ʾϵͳ���� ���磺read() write() open()
	  -100 ��ʾͨ�Ŵ���
******************************************************************************/
int	Vdm_line(unsigned char line ,unsigned char coloum,unsigned char nlen,char *VdmChar);

/*ͬ��ʱ��*/
int Sync_Vdm_Time(void);

/*�ַ����ӳ�ʼ��*/
int Vdm_init(void);

/*ͬ������*/
int IO_Board_GetInput(void);




#endif
