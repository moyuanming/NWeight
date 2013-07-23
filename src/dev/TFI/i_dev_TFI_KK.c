#include "LocalIncludeFile.h"
typedef unsigned char byte ;
static int TFI_KK_GetCommandLen ( byte* command )
{
	return command [ 1 ] ;
}
//static byte BBC ( byte* command )
//{
//	int len = 0 ;
//	int i ;
//	byte bbc = 0 ;
//	len = TFI_KK_GetCommandLen( command ) ;
//	for ( i = 0 ; i < ( len ) ; i++ )
//	{
//		bbc ^= command[i];
//	}
//	command [ len ] = bbc ;
//	return bbc ;
//}
static byte getValue ( int v , int min , int max )
{
	int i , x ;
	i = min < max ? min : max ;
	x = min > max ? min : max ;
	return ( v < i ? i : ( v > x ? x : v ) ) ;
}
static byte * show ( byte* command , int lane , int sd , int sj , int mode , char * str )
{
	int len = 0 ;
	byte *p ;
	command [ 0 ] = 0xAA ;
	len = strlen ( str ) ;
	command [ 1 ] = len + 4 + 3 ;
	command [ 2 ] = 0x80 + getValue ( lane , 0 , 3 ) ;
	command [ 3 ] = sd ;
	command [ 4 ] = sj ;
	command [ 5 ] = getValue ( mode , 1 , 6 ) ;
	p = &command [ 6 ] ;
	strncpy ( (  char * )p , str , len ) ;
	p = p + len ;
	*p = 0xBB ;
	serial_write(LED_COM,command  ,TFI_KK_GetCommandLen( command ) ) ;

	return command;
}
void   TFI_KK_clean ( void)
{
	byte command[95];	
	memset ( command , 0x00 , 95 ) ;
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x07 ;
	command [ 2 ] = 0x94 ;
	command [ 3 ] = 0x00 ;
	command [ 4 ] = 0x00 ;
	command [ 5 ] = 0x00 ;
	command [ 6 ] = 0xBB ;
	serial_write(LED_COM,command  ,7) ;
	
}

static byte getSoundVolume ( int volume )
{
	return getValue ( volume , 0 , 3 ) + 0x30 ;
}
/*
 * 0 谢谢
 * 1 谢谢合作，请走好
 * 2 您好，月票
 * 3 您好，免费车
 */
void TFI_KK_SoundOuther ( int Type )
{
	byte command[95];	
	int i ;
	memset ( command , 0x00 , 95 ) ;
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x0A ;
	command [ 2 ] = 0x4B ;
	command [ 3 ] = getValue ( Type , 0 , 3 ) ;
	command [ 4 ] = 0x00 ;
	command [ 5 ] = 0x00 ;
	command [ 6 ] = 0x00 ;
	command [ 7 ] = 0x00 ;
	command [ 8 ] = 0x30 ;
	command [ 9 ] = 0xBB ;
	
	serial_write(LED_COM,command , TFI_KK_GetCommandLen( command )) ;
	for(i = 0;i<TFI_KK_GetCommandLen( command );i++ )
	{
		echoic("TFI=<%x>",command[i]);
	}
}
void TFI_KK_Sound ( byte* command , int CarType , int charge , int volume )
{
	byte str [ 5 ] ;
	int i;
	sprintf ( (  char * )str , "%d%04d" , getValue ( CarType , 0 , 9 ) , charge ) ;
	command [ 0 ] = 0xAA ;
	command [ 1 ] = 0x0A ;
	command [ 2 ] = 0x4A ;
	strncpy ((  char * )&command [ 3 ] , (  char * )str , 5 ) ;
	command [ 8 ] = getSoundVolume ( volume ) ;
	command [ 9 ] = 0xBB ;
	
	serial_write(LED_COM,command , TFI_KK_GetCommandLen( command )) ;

	for(i = 0;i<TFI_KK_GetCommandLen( command );i++ )
	{
		echoic("TFI=<%x>",command[i]);
	}
}
void  TFI_KK_LedShow (   int CarType , int charge )
{	
	byte command[95];
	char  str1 [ 90 ] , str2 [ 90 ] ;
	memset ( command , 0x00 , 95 ) ;
	TFI_KK_Sound ( command , CarType , charge , 3 ) ;
	sprintf ( str1 , " 车型:%4d 型车" , CarType ) ;
	sprintf ( str2 , " 金额:%4d 元  " , charge ) ;
	show ( command , 1 , 0 , 0 , 3 , str1 ) ;
	usleep(1000*11);
	show ( command , 2 , 0 , 0 , 3 , str2 ) ;
	//15027745315
}

