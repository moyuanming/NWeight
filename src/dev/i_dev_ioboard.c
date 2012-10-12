#include "LocalIncludeFile.h"
#include "i_dev_ioboard.h"

char oldbt;
unsigned char  oldStatus;
time_t CurrenttimeUP ;
time_t CurrenttimeDown ;
//��ʼ������������ʱʹ��
int  I_DEV_IOBoard_Init(void)
{
	if(T==EnabledIOBoard())
	{		
		echoic("IO Lib Call  I_DEV_IOBoard_Callback!");
		return IO_Board_Init(I_DEV_IOBoard_Callback);
	}	
	return 0;
}
//�����˳�ʱʹ��
void I_DEV_IOBoard_Exit(void)
{
	
}

/*IO�������������������з��� ���磺��Ȧ*/
void I_DEV_IOBoard_Callback(unsigned char Input)
{
 
	switch (Input)
	{
	case GuangShanUp:

		echoic("��դ����");
		break;
	case GuangShanDown:

		echoic("��դ�뿪");
		break;
	case LineZhaPaiUp:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_UP, 0, 0);
		echoic("ץ����Ȧ����");
		break;
	case LineZhaPaiDown:
		PostMessage(UI_Get_From_Handl(), MSG_PIC_DOWN, 0, 0);
		echoic("ץ����Ȧ�뿪");

		break;
	case LinePassUp:
		PostMessage(UI_Get_From_Handl(), MSG_BAR_UP, 0, 0);
		echoic("ͨ����Ȧ����");

		break;
	case LinePassDown:
		PostMessage(UI_Get_From_Handl(), MSG_BAR_DOWN, 0, 0);
		echoic("ͨ����Ȧ�뿪");
		break;
	case ConnError:
		//	fprintf(stderr,"%sͨ�Ŵ���%s\n",GCor,PCor);
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
 
/* ����Ϊ iO����Ʋ��ֵĴ��� */
/******************************************************************************
 �� �� ���� get_crc
 ��    ���� CRCУ�麯����ԭʼʵ�ַ���������ԭ����ԭʼ���ݱ��ʽt(x)���Ա�׼��
            ��ʽ����߽״�r��Ȼ�����g(x)�������ʽy(x)����ԭʼ���ݵ�У���룻
            CRCУ�����õĶ���ʽ�㷨��ģ�����㣬�Ӽ�����λ���λ�����Կ������
            ���������棻�����������Ľ����ʣ���֪y(x1+x2)=y(x1)+y(x2)������
            ������򣬿��Խ����ݴ����Ϊ�����ֽ������������ֽ�Ҳ���Բ��Ϊ
            N������������
 ��    �룺 ninit_checksum��CRCУ��ĳ�ʼֵ��Ϊ��ʱ���ܼ������ݿ���ʼ�����ַ������Գ�
            ��CRC�����ֵ��ʼ����
            ncrc_type����׼����ʽ������ֵ����0x131��ʾg(x)=x^8+X^5+X^4+X^0���˴�Ҫ
            д���׼����ʽ������ֵ�ķ�ת�룬��0x8C
            cdata��ԭʼ����
            nlength��ԭʼ���ݵĳ���
 ��    ���� ��
 �� �� ֵ�� ԭʼ���ݵ�У���룬��Ч�������׼����ʽ��������һ��
 ȫ�ֱ����� ��
 ����ģ�飺 ��
 ��    �ߣ�
 �������ڣ� 2007.12.4
 ��    ����
 ��    ʷ��
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


