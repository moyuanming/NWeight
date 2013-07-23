#include "LocalIncludeFile.h"
#include "i_dev_TFI_CJ.h"

typedef unsigned char byte ;

//#define  OLDCJTFI
#ifdef OLDCJTFI

#define STX                 0x02           //  ��ʼ��־
#define ETX                 0x03           //  ������־
#define DISP_CHECK			0x01           //  LED��ʾ�Լ�
#define DISP_OUT_LED		0x02           // ����LED 
#define DISP_OUT_AUDIO		0x03            // ��������
#define ACK                 0x04           //  ������ȷ
#define NCK                 0x15           //  ���մ���
static byte BBC ( byte* command )
{
	int i ;
	byte bbc = 0 ;
	command[0] = STX;
	command[2] = 13;
	for ( i = 1 ; i < 16 ; i++ )
	{
		bbc ^= command[i];
	}
	command [ 16 ] = bbc ;
	command[17] = ETX;
	return bbc ;
}
#endif

void   TFI_CJ_clean ( void)
{
	#ifdef OLDCJTFI
	byte command[20];	
	int ret = 0;
	int i = 0;
	memset ( command , 0x00 , 20 ) ;
	command[1] = DISP_OUT_LED;   //������
	for (i=3;i<15;++i) 
	{           //���ݣ������ʾʱ��������Ϊ��
        command[i] = ' ';
    }
    command[15] = 0;
	BBC(command);
	ret = serial_write(LED_COM,command  ,18) ;
	#else
	byte command[20];
	memset ( command , 0x00 , 0x00 ) ;
	//0x97	����	AA 04 97 BB
	//0x98	������������лл��ף��һ·ƽ����	AA 04 98 BB
	//0x99	����	AA 04 99 BB
	//0xA0	лл	AA 04 A0 BB
	//0xA1	��ӭ����	AA 04 A1 BB
	//0xA2	�����	AA 04 A2 BB
	//0xA3	������	AA 04 A3 BB
	//0xA4	�ߺ�	AA 04 A4 BB
	//0xA5	�ټ�	AA 04 A5 BB
	command[0] = 0xAA;
	command[1] = 0x04;
	command[2] = 0x97;
	command[3] = 0xBB;
	serial_write(LED_COM,command  ,4) ;
	#endif
}

void  TFI_CJ_LedShow (   int CarType , int charge )
{	
	#ifdef OLDCJTFI
	byte command[20];	
	int ret = 0;
	memset ( command , 0x00 , 20 ) ;
	command[1] = DISP_OUT_LED;   //������
	sprintf(&command[3],"% 4d% 4d% 4d",CarType,charge,0);
	if(charge)
	{
		command[15] = CarType;
	}
	BBC(command);
	ret = serial_write(LED_COM,command  ,18) ;
	#else
	byte command[20];	
	memset ( command , 0x00 , 20 ) ;
	//�����ʾ����ʾ 1 �ͳ� ��� 25Ԫ ����ʾ��������1�ͳ� �ɷ�25Ԫ
	//AA 0B 95 31 30 32 35 30 30 30 BB 
	if(CarType>0&&CarType<10&&charge>0)
	{
		command[0] = 0xAA;
		command[1] = 0x0B;
		command[2] = 0x95;//95���� 95������
		sprintf((char*)&command[3],"%d%03d%03d",CarType,charge,0);
		command[10] = 0xBB;
		serial_write(LED_COM,command  ,11) ;
	}
	#endif	
}

