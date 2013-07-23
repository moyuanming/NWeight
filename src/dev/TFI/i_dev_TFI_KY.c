#include "LocalIncludeFile.h"
#include "i_dev_TFI_KY.h"
typedef unsigned char byte ;

void replace(byte* str,byte oldc,byte newc)
{
    byte* p = str;
    while(*p)
    {
        if(*p==oldc)
        {
            *p =  newc;
        }
        p++;
    }
}
void   TFI_KY_clean (void)
{
	byte command[20];	
	memset ( command , 0x00 , 20 ) ;
	command[0] = '<';
	command[1] = 'Y';
	command[2] = '>';
	serial_write(LED_COM,command  ,3) ;
}

void  TFI_KY_LedShow (   int CarType , int charge )
{	
	byte command[20];	
	memset ( command , 0x00 , 20 ) ;
	sprintf((char *)&command,"<V2%4d>",CarType);
	replace(command,' ','*');
	serial_write(LED_COM,command  ,8) ;
	usleep(10);
	sprintf((char *)&command,"<M%5d>",charge);
	replace(command,' ','*');
	serial_write(LED_COM,command  ,8) ;
	
}

