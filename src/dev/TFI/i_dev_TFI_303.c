#include "LocalIncludeFile.h"


struct Led_protocol G_Led_protocol;
int is_Led_303_init = 0;
static void TFI_303_Init(void)
{
	if(is_Led_303_init==0)
	{
		//显示器显示车型1，金额为 25元（不是025），语音报价
		G_Led_protocol.ShowChargeAndSound[0] = 0x0A;
		G_Led_protocol.ShowChargeAndSound[1] = 0x46;
		G_Led_protocol.ShowChargeAndSound[2] = 0x0B;
		G_Led_protocol.ShowChargeAndSound[3] = 0x00;



		//清屏
		G_Led_protocol.ClearAndSound[0] = 0x0A;
		G_Led_protocol.ClearAndSound[1] = 0x46;
		G_Led_protocol.ClearAndSound[2] = 0x0D;
		G_Led_protocol.ClearAndSound[3] = 0x00;
		//
		G_Led_protocol.ClearNotSound[0] = 0x0A;
		G_Led_protocol.ClearNotSound[1] = 0x46;
		G_Led_protocol.ClearNotSound[2] = 0x15;
		G_Led_protocol.ClearNotSound[3] = 0x00;

		//你好
		G_Led_protocol.Hello[0] = 0x0A;
		G_Led_protocol.Hello[1] = 0x46;
		G_Led_protocol.Hello[2] = 0x0E;
		G_Led_protocol.Hello[3] = 0x00;

		//谢谢
		G_Led_protocol.Thanks[0] = 0x0A;
		G_Led_protocol.Thanks[1] = 0x46;
		G_Led_protocol.Thanks[2] = 0x0F;
		G_Led_protocol.Thanks[3] = 0x00;

		//欢迎光临
		G_Led_protocol.WelCome[0] = 0x0A;
		G_Led_protocol.WelCome[1] = 0x46;
		G_Led_protocol.WelCome[2] = 0x10;
		G_Led_protocol.WelCome[3] = 0x00;

		//别客气
		G_Led_protocol.ItEasy[0] = 0x0A;
		G_Led_protocol.ItEasy[1] = 0x46;
		G_Led_protocol.ItEasy[2] = 0x11;
		G_Led_protocol.ItEasy[3] = 0x00;

		//请慢走
		G_Led_protocol.PleGo[0] = 0x0A;
		G_Led_protocol.PleGo[1] = 0x46;
		G_Led_protocol.PleGo[2] = 0x12;
		G_Led_protocol.PleGo[3] = 0x00;

		//走好
		G_Led_protocol.Go[0] = 0x0A;
		G_Led_protocol.Go[1] = 0x46;
		G_Led_protocol.Go[2] = 0x13;
		G_Led_protocol.Go[3] = 0x00;

		//再见
		G_Led_protocol.GoodBye[0] = 0x0A;
		G_Led_protocol.GoodBye[1] = 0x46;
		G_Led_protocol.GoodBye[2] = 0x14;
		G_Led_protocol.GoodBye[3] = 0x00;

		//走好
		G_Led_protocol.Go[0] = 0x0A;
		G_Led_protocol.Go[1] = 0x46;
		G_Led_protocol.Go[2] = 0x13;
		G_Led_protocol.Go[3] = 0x00;
		is_Led_303_init = 1;
	}
}
void TFI_303_clean (BOOL IsSound )
{
	TFI_303_Init();
	if(IsSound && 1==atoi(sys_ini.LedSoundEnabled))
	{	
		TFI_303_SoundOuther(atoi(sys_ini.GoodBeySay));	
	}
	else
	{	
		TFI_303_SoundOuther(CLEARNOTSOUND);	
	}
}
void TFI_303_SoundOuther (int Type )
{
	switch(Type)
    {	
    case HELLO:
        serial_write(LED_COM,G_Led_protocol.Hello,4);	
        break;
    case THANKS:
        serial_write(LED_COM,G_Led_protocol.Thanks,4);	
        break;
    case WELCOME:
        serial_write(LED_COM,G_Led_protocol.WelCome,4);	
        break;
    case ITEASY:
        serial_write(LED_COM,G_Led_protocol.ItEasy,4);	
        break;
    case PLEGO:
        serial_write(LED_COM,G_Led_protocol.PleGo,4);	
        break;
    case GO:
        serial_write(LED_COM,G_Led_protocol.Go,4);	
        break;
    case GOODBYE:
        serial_write(LED_COM,G_Led_protocol.GoodBye,4);	
        break;
    case CLEARANDSOUND:
        serial_write(LED_COM,G_Led_protocol.ClearAndSound,4);	
        break;
    case CLEARNOTSOUND:
        //serial_write(LED_COM,G_Led_protocol.ClearNotSound,4);	
        break;
    }
}
void  TFI_303_LedShow (int CarType , int charge )
{
	unsigned char strCharge[5];
	int ret ;
	TFI_303_Init();
	G_Led_protocol.ShowChargeNotSound[0] = 0x0a;
	G_Led_protocol.ShowChargeNotSound[1] = 0x46;
	if(0==charge)
	{	
		G_Led_protocol.ShowChargeNotSound[3] = 0x0D;
		serial_write(LED_COM,G_Led_protocol.ShowChargeNotSound,3);	
		return ;//0元不需要报价
	}
	memset(strCharge,0x00,5);	
	sprintf(strCharge,"%04d",charge);	
	if(1==atoi(sys_ini.LedSoundEnabled))
	{	
		G_Led_protocol.ShowChargeAndSound[2] = 0x0B;
		G_Led_protocol.ShowChargeAndSound[3] = CarType;
		G_Led_protocol.ShowChargeAndSound[4] = strCharge[0];
		G_Led_protocol.ShowChargeAndSound[5] = strCharge[1];
		G_Led_protocol.ShowChargeAndSound[6] = strCharge[2];
		G_Led_protocol.ShowChargeAndSound[7] = strCharge[3];
		G_Led_protocol.ShowChargeAndSound[8] = 0x00;
		ret= serial_write(LED_COM,G_Led_protocol.ShowChargeAndSound,9);	
	}
	else
	{	
		G_Led_protocol.ShowChargeNotSound[2] = 0x0c;
		G_Led_protocol.ShowChargeNotSound[3] = CarType;
		G_Led_protocol.ShowChargeNotSound[4] = strCharge[0];
		G_Led_protocol.ShowChargeNotSound[5] = strCharge[1];
		G_Led_protocol.ShowChargeNotSound[6] = strCharge[2];
		G_Led_protocol.ShowChargeNotSound[7] = strCharge[3];
		G_Led_protocol.ShowChargeNotSound[8] = 0x00;
		ret=serial_write(LED_COM,G_Led_protocol.ShowChargeNotSound,9);	
	}
	/*serial_write(LED_COM,"seeeee",6);	
	serial_write(LED_COM,"s0001e",6);	*/
}
