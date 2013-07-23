#include "LocalIncludeFile.h"
typedef unsigned char byte ;
#define HNMaxCommandLen 103
/********************************************************************************************
语音板
********************************************************************************************/
#define ISD1700_XIEXIE	"0AA0AF"	//谢谢
#define ISD1700_NINHAO	"09809D"	//你好
#define ISD1700_QINGFU	"09E0A4"	//请付
#define ISD1700_YUAN	"0A50A9"	//元
#define ISD1700_DUN		"0D80DC"	//吨
#define ISD1700_CHEXIN	{"0B00B6","0B70BE","0BF0C7","0C80CF","0D00D7"}	//车型
#define ISD1700_GW		{"103107","010014","015019","01A01F","020025","02602B","02C031","032037","03803B","03C041"} //0-9
#define ISD1700_SHI		"042047"	//十
#define ISD1700_QIAN	"14814C"	//千
#define ISD1700_WAN		"14D150"	//万
#define ISD1700_LIAN	"13C13F"	//两
#define ISD1700_DOT		"10810D"	//.
#define ISD1700_SW		{"190196","15415A","15B162","16316A","16B171","172179","17A181","182188","18918F"} //10-90
#define ISD1700_BW		{"04804C","04D053","054059","05A05F","060064","065069","06A06E","06F073","074078"}	//100-900
#define ISD1700_QW		{"07907F","080086","08708C","08D092","093097","10E112","113118","11911D","11E123"}	//1000-9000
#define ISD1700_WW		{"124128","12912F","130135","13613B"} //10000-40000
#define ISD1700_QP		"STOPSTOP"	//清除
void ISD1700_SendCommand(char *cmd)
{
	byte temp[20];
	memset ( temp , 0x00 , 20 ) ;
	sprintf((  char * )temp,"ISD:%sE",cmd);
	echoic("COMMAND=%s LEN=%d",temp,strlen((  char * )temp));
	serial_write(LED_COM,temp,strlen((  char * )temp));
}
void ISD1700_Clear(void )
{
	//ISD1700_SendCommand(ISD1700_QP);
	//ISD1700_SendCommand(ISD1700_XIEXIE);
}
void ISD1700_SZ(int value)
{
	int q=0,b=0,s=0,g=0,w=0;
	char *ww[4]	= ISD1700_WW;
	char *qw[9] = ISD1700_QW;
	char *bw[9] = ISD1700_BW;
	char *gw[10] = ISD1700_GW;
	char *sw[9]	=	ISD1700_SW;
	int zs=0,xs=0,xs1=0,xs2=0,is0=0;
	zs = value/100;
	xs = value - zs*100;
	w = zs/10000;
	q = (zs-w*10000)/1000;
	b = (zs-w*10000-q*1000)/100;
	s = (zs-w*10000-q*1000-b*100)/10;
	g = (zs-w*10000-q*1000-b*100-s*10);
	xs1 = xs/10;
	xs2 = xs-xs1*10;
	echoic("value=%d zs=%d xs=%d",value,zs,xs);
	if(zs<50000)
	{
		if(w>0)
		{
			ISD1700_SendCommand(ww[w-1]);
			echoic("%d万",w);
			is0 = 1;
		}
		if(q>0)
		{
			ISD1700_SendCommand(qw[q-1]);
			echoic("%d千",q);
			is0 = 1;
		}
		else if(is0)
		{
			ISD1700_SendCommand(gw[0]);
			echoic("零");
			is0=0;
		}
		if(b>0)
		{
			ISD1700_SendCommand(bw[b-1]);
			echoic("%d百",b);
			is0 = 1;
		}
		else if(is0)
		{
			ISD1700_SendCommand(gw[0]);
			echoic("零");
			is0=0;
		}
		if(s>0)
		{
			ISD1700_SendCommand(sw[s-1]);
			echoic("%d十",s);
			is0 = 1;
		}
		else if(is0&&g>0)
		{
			ISD1700_SendCommand(gw[0]);
			echoic("零");
			is0=0;
		}
		if(g>0)
		{
			ISD1700_SendCommand(gw[g]);
			echoic("%d",g);
		}
		if(xs>0)
		{
			ISD1700_SendCommand(ISD1700_DOT);
			echoic("点");
			ISD1700_SendCommand(gw[xs1]);
			echoic("%d",xs1);
			if(xs2>0)
			{
				ISD1700_SendCommand(gw[xs2]);
				echoic("%d",xs2);
			}
		}
	}
}
void ISD1700_BJ(int CarType , int charge)
{
	char *cx[5] = ISD1700_CHEXIN;
	int weight = 0;
	weight =GetFareContext_CarWeight()*100;
	if((weight%10)>=5)
	{
		weight += 10;
	}
	weight -= (weight%10);
	ISD1700_SendCommand(ISD1700_QP);	//清除
	ISD1700_SendCommand(ISD1700_NINHAO);//你好
	if(CarType>0&&CarType<6)
	{
		ISD1700_SendCommand(cx[CarType-1]);//几型车
	}
	if(WeightCarClassBUS!=GetWeightCarClass()&&WeightCarClassTruckISNotUseWeight!=GetWeightCarClass()&&weight>0)
	{
		ISD1700_SZ(weight);
		ISD1700_SendCommand(ISD1700_DUN);
	}
	if(charge>0&&charge<50000)
	{
		ISD1700_SendCommand(ISD1700_QINGFU);
		ISD1700_SZ(charge*100);
		ISD1700_SendCommand(ISD1700_YUAN);
		ISD1700_SendCommand(ISD1700_XIEXIE);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
static int TFI_HN_GetCommandLen ( byte* command )
{
	return command [ 2 ] ;
}
static byte HN_BBC ( byte* command )
{
	int len = 0 ;
	int i ;
	byte bbc = 0 ;
	len = TFI_HN_GetCommandLen( command )-1 ;
	for ( i = 0 ; i < ( len ) ; i++ )
	{
		echo("comman%d:%2x ",i,command[i]);
		bbc ^= command[i];
	}
	echo("commanbbc:%2x ",bbc);
	command [ len ] = bbc ;
	return bbc ;
}
static byte getValue ( int v , int min , int max )
{
	int i , x ;
	i = min < max ? min : max ;
	x = min > max ? min : max ;
	return ( v < i ? i : ( v > x ? x : v ) ) ;
}
static byte * show ( byte* command , int lane , int ld ,  char * str )
{
	int len = 0 ,maxlen=(lane==0?96:16) ;
	byte *p ;
	len = strlen ( str ) ;
	command [ 0 ] = 0xFF ;
	command [ 1 ] = 0xDC ;
	command [ 2 ] = (lane==0?103:23) ;
	command [ 3 ] = 'D' ;
	command [ 4 ] = getValue(ld,0,0xff) ;
	command [ 5 ] = getValue(lane,0,6) ;
	p = &command [ 6 ] ;
	strncpy ((char*) p , str , len<=maxlen?len:maxlen ) ;
	HN_BBC(command) ;
	echoic("LED_COM = %d",LED_COM);
	usleep(1000*100);
	serial_write(LED_COM,command  ,TFI_HN_GetCommandLen( command ) ) ;
	return command;
}
void   TFI_HN_clean ( )
{
	byte command[HNMaxCommandLen];
	byte str1 [ HNMaxCommandLen ] ;
	memset ( command , 0x00 , HNMaxCommandLen ) ;

	sprintf ( (char*)str1 , "                  新疆高速              欢迎您！  计重收费              试运行！") ;
	//sprintf ( str1 , "                  新疆高速              欢迎您！ 2012年5月28日零点正式开通计重收费 ！") ;
	show ( command , 0 , 255, (char*)str1 ) ;
	usleep(1000*100);
	ISD1700_Clear();
}


void  TFI_HN_LedShow (   int CarType , int charge )
{	
	byte command[HNMaxCommandLen];
	byte str1 [ HNMaxCommandLen ] ;
	memset ( command , 0x00 , HNMaxCommandLen ) ;
	if(FullWeight == GetWeightFunctions())
	{
		sprintf ( (char *)str1 , "车    型:%4s%1d型金    额:%5d元承载标准:%5.0f吨车货总重:%5.1f吨超标准比:%5.0f％",
			GetWeightCarClass()==WeightCarClassBUS?"客":"货",
			CarType,
			charge,
			GetWeightContext_WeightLimit_ByTon(),
			GetFareContext_CarWeight(),
			GetWeightContext_OverLoadWeightRate());
	}
	else
	{
		sprintf ((  char * ) str1 , "车    型:%4s%1d型金    额:%5d元计重金额:%5d元承载标准:%5.0f吨车货总重:%5.1f吨超标准比:%5.0f％",
			GetWeightCarClass()==WeightCarClassBUS?"客":"货",
			CarType,
			charge,
			GetG_WeightFare(),
			GetWeightContext_WeightLimit_ByTon(),
			GetFareContext_CarWeight(),
			GetWeightContext_OverLoadWeightRate());
	}
	show ( command , 0 , 255,(char *) str1 ) ;
	ISD1700_BJ(CarType,charge);
}

