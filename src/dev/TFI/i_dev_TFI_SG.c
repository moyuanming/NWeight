#include "LocalIncludeFile.h"
#include "i_dev_TFI_SG.h"
typedef unsigned char byte ;

static int _Cartype;
static int _Charge;

static int TFI_SG_GetCommandLen ( byte* command )
{
	return command [ 1 ] +	1 ;
}
static byte SG_BBC ( byte* command )
{
	int len = 0 ;
	int i ;
	byte bbc = 0 ;
	len = TFI_SG_GetCommandLen( command ) ;
	for ( i = 0 ; i < ( len ) ; i++ )
	{
		echo("comman%d:%2x ",i,command[i]);
		bbc ^= command[i];
	}
	echo("commanbbc:%2x ",bbc);
	command [ len ] = bbc ;
	return bbc ;
}
//00�����������á�X�ͳ�������ʾ����ͬ������
//01������������X�֣�����ʾ����ͬ������
//02������������X�֣�����ʾ����ͬ������
//03�����������XԪ������ʾ�շѽ��ͬ������
//04�����������XԪ������ʾ�շ����ͬ������
//05��������ף��һ·ƽ���ټ���
//06����������Ʊ������ͨ�С�
//07����������ѳ�����ͨ�С�
//08���������������ء�
//09: ��������ͨ��
static byte TFI_SG_LedSound(int type,int value)
{
	byte command[95];	
	byte str[20];
	byte *p ;
	int ret = 0;
	int temp = 0;
	memset ( command , 0x00 , 95 ) ;
	memset (str,0x20,20);
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x0D ;
	command [ 2 ] = 0x84 ;
	command [ 3 ] = type ;
	command [ 4 ] = 0x00 ;
	command [ 5 ] = 0x00 ;
	
	temp = value;
	sprintf((  char * )str,"%6d",temp);

	p = &command [ 6 ] ;
	strncpy ( (  char * )p , (  char * )str , 6 ) ;
	command [ 12 ] = 0xBB ;
	SG_BBC(command) ;
	
	ret = serial_write(LED_COM,command  ,TFI_SG_GetCommandLen( command )) ;
	usleep(10000*275);
	return ret;
}
static byte TFI_SG_getValue ( int v , int min , int max )
{
	int i , x ;
	i = min < max ? min : max ;
	x = min > max ? min : max ;
	return ( v < i ? i : ( v > x ? x : v ) ) ;
}
static byte * TFI_SG_show ( byte* command , int lane , int ld ,  char * str )
{
	byte *p ;
	memset ( command , 0x00 , 95 ) ;
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x27 ;
	command [ 2 ] = TFI_SG_getValue(lane,1,4)+0x80-0x01 ;
	command [ 3 ] = 0x00 ;
	command [ 4 ] = 0xFF ;
	command [ 5 ] = 0x03 ;
	p = &command [ 6 ] ;
	strncpy ( (  char * )p , str , 32 ) ;
	command [ 38 ] = 0xBB ;
	SG_BBC(command) ;
	usleep(1000);
	serial_write(LED_COM,command  ,TFI_SG_GetCommandLen( command ) ) ;
	return command;
}
//����
void   TFI_SG_clean (void  )
{
	byte command[95];	
	 
	memset ( command , 0x00 , 95 ) ;
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x07 ;
	command [ 2 ] = 0x94 ;
	command [ 3 ] = 0x00 ;
	command [ 4 ] = 0x00 ;
	command [ 5 ] = 0xBB ;
	SG_BBC(command) ;
	usleep(10000);
	serial_write(LED_COM,command  ,command[1]+1) ;
	//TFI_SG_LedSound(9,0);
	//TFI_SG_LedSound(5,0);
}

//��ʾ���
void  TFI_SG_LedShow (   int CarType , int charge )
{	
	byte command[95];
	byte str1 [ 32 ] , str2 [ 32 ] ;
	_Cartype = CarType;
	_Charge = charge;
	memset ( str1 , 0x20 , 32 ) ;
	memset ( str2 , 0x20 , 32 ) ;
	sprintf ((  char*)& str1 , " ����:%4d �ͳ�" , CarType ) ;
	sprintf ((  char*)& str2 , " ���:%4d Ԫ  " , charge ) ;
	
	TFI_SG_show ( command , 2 , 255 ,(  char*)& str1 ) ;
	TFI_SG_show ( command , 3 , 255,  (  char*)&str2 ) ;
	CreateLedSund();
	
	
	//15027745315
}
//��ͨ�� ��typeΪ00ʱͨ�е�Ϊ�죬��typeΪ01ʱͨ�е�Ϊ�̡�
void TFI_SG_SetTongXingDeng(int type)
{
	byte command[95];	
	memset ( command , 0x00 , 95 ) ;
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x07 ;
	command [ 2 ] = 0x99 ;
	command [ 3 ] = type?1:0 ;
	command [ 4 ] = 0x00 ;
	command [ 5 ] = 0x00 ;
	command [ 6 ] = 0xBB ;
	SG_BBC(command) ;
	usleep(10000);
    serial_write(LED_COM,command  ,TFI_SG_GetCommandLen( command )) ;
}
//���� 0�� 1��
void TFI_SG_SetHuangShan(int type)
{
	byte command[95];	
	memset ( command , 0x00 , 95 ) ;
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x07 ;
	command [ 2 ] = 0x98 ;
	command [ 3 ] = type?1:0 ;
	command [ 4 ] = 0x00 ;
	command [ 5 ] = 0x00 ;
	command [ 6 ] = 0xBB ;
	SG_BBC(command) ;
	usleep(10000);
    serial_write(LED_COM,command  ,TFI_SG_GetCommandLen( command )) ;
}

void LedSundthread(void )
{

	TFI_SG_LedSound(0,_Cartype);
	if(_Charge !=0)
	{
		TFI_SG_LedSound(3,_Charge*100);
	}


	_Cartype = 0;
	_Charge = 0;
}

static pthread_t LedSund;
int CreateLedSund(void)
{
	int ret;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&LedSund, &new_attr, (void *)LedSundthread, NULL);
	pthread_attr_destroy(&new_attr);
	return ret;
}
