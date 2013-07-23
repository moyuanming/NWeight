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
//00：报出：您好、X型车（与显示车型同步）。
//01：报出：总重X吨（与显示总重同步）。
//02：报出：超重X吨（与显示超重同步）。
//03：报出：金额X元（与显示收费金额同步）。
//04：报出：余额X元（与显示收费余额同步）。
//05：报出：祝您一路平安再见。
//06：报出：月票车，请通行。
//07：报出：免费车，请通行。
//08：报出：车辆闯关。
//09: 报出：请通行
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
//清屏
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

//显示金额
void  TFI_SG_LedShow (   int CarType , int charge )
{	
	byte command[95];
	byte str1 [ 32 ] , str2 [ 32 ] ;
	_Cartype = CarType;
	_Charge = charge;
	memset ( str1 , 0x20 , 32 ) ;
	memset ( str2 , 0x20 , 32 ) ;
	sprintf ((  char*)& str1 , " 车型:%4d 型车" , CarType ) ;
	sprintf ((  char*)& str2 , " 金额:%4d 元  " , charge ) ;
	
	TFI_SG_show ( command , 2 , 255 ,(  char*)& str1 ) ;
	TFI_SG_show ( command , 3 , 255,  (  char*)&str2 ) ;
	CreateLedSund();
	
	
	//15027745315
}
//交通灯 当type为00时通行灯为红，当type为01时通行灯为绿。
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
//黄闪 0关 1开
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
