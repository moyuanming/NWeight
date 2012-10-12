#include "LocalIncludeFile.h"
#include "i_dev_ioboard.h"

char oldbt;
unsigned char  oldStatus;
time_t CurrenttimeUP ;
time_t CurrenttimeDown ;
//初始化，程序启动时使用
int  I_DEV_IOBoard_Init(void)
{
	if(T==EnabledIOBoard())
	{		
		echoic("IO Lib Call  I_DEV_IOBoard_Callback!");
		return IO_Board_Init(I_DEV_IOBoard_Callback);
	}	
	return 0;
}
//程序退出时使用
void I_DEV_IOBoard_Exit(void)
{
	
}

/*IO输入量处理函数，请自行分析 例如：线圈*/
void I_DEV_IOBoard_Callback(unsigned char Input)
{
 
	switch (Input)
	{
	case GuangShanUp:

		echoic("光栅到达");
		break;
	case GuangShanDown:

		echoic("光栅离开");
		break;
	case LineZhaPaiUp:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_UP, 0, 0);
		echoic("抓拍线圈到达");
		break;
	case LineZhaPaiDown:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_DOWN, 0, 0);
		echoic("抓拍线圈离开");

		break;
	case LinePassUp:
		PostMessage(UI_Get_From_Handl(), MSG_BAR_UP, 0, 0);
		echoic("通过线圈到达");

		break;
	case LinePassDown:
		PostMessage(UI_Get_From_Handl(), MSG_BAR_DOWN, 0, 0);
		echoic("通过线圈离开");
		break;
	case ConnError:
		//	fprintf(stderr,"%s通信错误%s\n",GCor,PCor);
		break;
	}
}

void I_DEV_IOBoard_CommandSender(int bFlag ,int command1,int command2)
{
	int temp1,temp2;
	if ( bFlag )
	{
		temp1 = command1;
		temp2 = command2;
	}
	else
	{
		temp1 = command2;
		temp2 = command1;
	}
	if (EnabledIOBoard()==T)
	{
		echoic("IO Lib Call  IO_Board_Out(%0x,%0X)!",temp1,temp2);
		IO_Board_Out(temp1,temp2);
	}
}
 
/* 以下为 iO板控制部分的代码 */
/******************************************************************************
 函 数 名： get_crc
 描    述： CRC校验函数的原始实现方法；它的原理是原始数据表达式t(x)乘以标准多
            项式的最高阶次r，然后除以g(x)，求出余式y(x)即是原始数据的校验码；
            CRC校验所用的多项式算法是模二运算，加减不进位或借位，所以可用异或
            运算来代替；根据异或运算的交换率，可知y(x1+x2)=y(x1)+y(x2)，依据
            这个规则，可以将数据串拆分为单个字节来处理，单个字节也可以拆分为
            N个比特来处理
 输    入： ninit_checksum，CRC校验的初始值，为零时不能检测出数据块起始的零字符，所以常
            用CRC的最大值初始化；
            ncrc_type，标准多项式的特征值，如0x131表示g(x)=x^8+X^5+X^4+X^0，此处要
            写入标准多项式的特征值的反转码，如0x8C
            cdata，原始数据
            nlength，原始数据的长度
 输    出： 无
 返 回 值： 原始数据的校验码，有效数字与标准多项式的特征码一致
 全局变量： 无
 调用模块： 无
 作    者：
 创建日期： 2007.12.4
 其    他：
 历    史：
******************************************************************************/

unsigned int get_crc(unsigned int ninit_checksum, unsigned int ncrc_type, const unsigned char cdata[], unsigned int nlength)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	flag;
	unsigned int	current;
	unsigned int	nchecksum;
	nchecksum = ninit_checksum;
	for(i = 0; i < nlength; i++)
	{
		// As the data in byte, so the current only infect low byte
		current = (nchecksum ^ cdata[i]) & 0xFF;
		for(j = 0; j < 8; j++)
		{
			// Check from bit0 to bit8, only use for right Cyclic
			flag = current & 0x01;
			current = current >> 1;
			if(flag != 0)
			{
				// Xor the crc type
				// the type code may be 0x8c, 0xA001, 0x8408, 0xEDB88320
				current = current ^ ncrc_type;
			}
			// Watch the middle value
			//printf("%08X\t", current);
		}
		// Checksum xor the new data's crc data
		nchecksum = (nchecksum >> 8) ^ current;
	}

	return nchecksum;
}


