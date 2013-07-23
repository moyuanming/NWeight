#include "LocalIncludeFile.h"
#include "tfi_lib.h"
/* 石河子公路局 玛纳斯收费站 老费显协议 */
/* 显示费额  0A  46  C1  F1  F2  F3  0D */
unsigned char ShowCmd[7] = {0x0A,0x46,0x01,0x00,0x00,0x05,0x0D};	
void  TFI_MNS_LedShow ( char CarType , int charge )
{
	unsigned char C_charge[3] ;
	sprintf((  char * )C_charge,"%03d",charge);
	ShowCmd[2]=CarType;
	ShowCmd[3]=C_charge[0];
	ShowCmd[4]=C_charge[1];
	ShowCmd[5]=C_charge[2];
	echoic("MNSTFIShow <%0x %0x %0x %0x %0x %0x %0x>",
		ShowCmd[0],
		ShowCmd[1],
		ShowCmd[2],
		ShowCmd[3],
		ShowCmd[4],
		ShowCmd[5],
		ShowCmd[6]);
	serial_write(LED_COM,ShowCmd,7);	
}
/*清屏命令：0A  B  0D*/
unsigned char ClearCmd[3] = {0x0A,  0x0B,  0x0D};
void   TFI_MNS_clean ( void)
{
	/*ClearCmd[0] = 0x0A;
	ClearCmd[1] = 0x0b;
	ClearCmd[2] = 0x0d;
	echoic("MNSTFICleard <%0x %0x %0x >",
		ClearCmd[0],
		ClearCmd[1],
		ClearCmd[2]);
	serial_write(LED_COM,ClearCmd,3);*/
	echoic("MNSTFICleard ");
	TFI_MNS_LedShow('0',0);

}

void  TFI_MNS_NEW_LedShow ( char CarType , int charge )
{
	char Temp[10] ;
	int iCartype = (int)CarType - 48;
	memset(Temp,0x00,10);

	LedTfi_CheXing(iCartype); 	
	sprintf(Temp,"%d",charge);
	LedTfi_JinE(Temp);
}

void   TFI_MNS_New_clean (void)
{
	LedTfi_BMP();
}