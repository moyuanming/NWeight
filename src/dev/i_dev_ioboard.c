//sfdjkfsf
#include "LocalIncludeFile.h"

io_board_t  * io_board;
char oldbt;
unsigned char  oldStatus;
time_t CurrenttimeUP ;
time_t CurrenttimeDown ;

io_board_t * GetIo_board()
{
	return io_board;
}
//��ʼ������������ʱʹ��
int  I_DEV_IOBoard_Init(void)
{
	if(T==EnabledIOBoard())
	{
		io_board=IOBoard_init();	//��ʼ������
		if ( io_board== NULL )
		{
			return -1;
		}
	}	
	return 0;
}
//�����˳�ʱʹ��
void I_DEV_IOBoard_Exit(void)
{
	IOBoard_exit(io_board);
}

/*IO�������������������з��� ���磺��Ȧ*/
void I_DEV_IOBoard_Callback(unsigned char Input)
{
	char bt;
	if (oldStatus!=Input)
	{
		bt=(char)Input;
		ReadDeviceStatus_Loop(2, bt, oldbt );//������Ȧ
		ReadDeviceStatus_Loop(3, bt, oldbt );//�뿪��Ȧ
		oldStatus=Input;
		oldbt=oldStatus;
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
		IO_Board_Out(io_board,temp1,temp2);
	}
}
/*һ��Ϊ�߼����Ʋ���*/
  void ReadDeviceStatus_Loop(int i, char bt, char oldbt)
{
	int a=0,   b=0;
	a   =(bt	&	(1<<i));	//��ǰ
	b   =(oldbt & (1<<i));	//����

	if ( a!=b)
	{
		switch (i )
		{
			case 2:

				if (a!=0 )
				{
					PostMessage(UI_Get_From_Handl(),MSG_BAR_UP,0,0);
					CurrenttimeUP = time(NULL);
				}
				else
				{
					CurrenttimeDown = time(NULL);
					if ((CurrenttimeDown-CurrenttimeUP) >=1)
					{
						PostMessage(UI_Get_From_Handl(),MSG_BAR_DOWN,0,0);
					}
				}
				break;
			case 3:
				PostMessage(UI_Get_From_Handl(),((a!=0)?MSG_PIC_UP:MSG_PIC_DOWN),0,0);
				break;
		}
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

/******************************************************************************
 �� �� ���� get_crc8
 ��    ���� 8λCRCУ�麯����ʵ�ַ���
 ��    �룺 cdata��ԭʼ����
            nlength��ԭʼ���ݵĳ���
 ��    ���� ��
 �� �� ֵ�� ԭʼ���ݵ�У���룬��Ч����8λ
 ȫ�ֱ����� ��
 ����ģ�飺 ��
 ��    �ߣ�
 �������ڣ� 2007.12.4
 ��    ����
 ��    ʷ��
******************************************************************************/
unsigned int get_crc8(unsigned char cdata[], unsigned int nlength)
{
	unsigned int	nchecksum;

	nchecksum = get_crc(0x00, CRC8, cdata, nlength);

	return nchecksum;
}
//spi��ѯ�߳� ���ڼ����Ȧ
void *SpiThred(void *args)
{
	static unsigned char ReadChar,OldChar;
	static unsigned char ReadIO[2]={0xE0,0xE1};
	io_board_t *io;
	io=(io_board_t *)args;
	OldChar = 0x00;
	while(1)
	{
      sem_wait(&(io->IO_Semt));

      write(io->IO_fd,ReadIO,2);

      IO_DELAY;

    read(io->IO_fd,&ReadChar,1);

     sem_post(&(io->IO_Semt));

		usleep(100000);
		if(ReadChar&0xf0)
		{
			printf("/tRead GPIO IN Error!!!!!!! %02x\n",ReadChar);
			continue; /*������*/
		}

		if(ReadChar != OldChar)
		{
			OldChar = ReadChar;
			Analyse_Gpio_in(ReadChar);
		}
	}
}
//���ڳ�ʼ��io��
io_board_t  * IOBoard_init()
{
	io_board_t * io;

	io = malloc(sizeof(io_board_t));
	io->IO_fd=open("/dev/io_board", O_RDWR);

	if(io->IO_fd < 0)
	{
		fprintf(stderr,"Open /dev/io_board Error!!\n");
		return NULL;
	}

	if(sem_init(&(io->IO_Semt),0,1) <0)
		return NULL;

	if(pthread_create(&(io->Thread_io), NULL, &SpiThred, (void *) io) < 0)
		return NULL;

	return io;
}
//�˳�������io����ص����ݡ�
int IOBoard_exit(io_board_t *io)
{
	close(io->IO_fd);
	sem_destroy(&io->IO_Semt);
	free(io);
	return 0;
}
unsigned char pc_val,pd_val;//�⼸������Ӧ��Ϊȫ�֣������������ƹرվ���ʱ����������������
//����io�壬Ҫ�򿪵� |  ��Set ,����� | ��CLR
int IO_Board_Out(io_board_t *io,unsigned int SET,unsigned int CLR)
{
	unsigned char  tmp;
	static unsigned char pc_old = ~(RL_1 | RL_2);
	static unsigned char pd_old = 0xff;
	unsigned char send[6]={	WRITE_CMD,WRITE_IO,WRITE_IO_SIZE,M16_PC,00,0x0c};
	char read_io[3]={0x00,0x00,0x00};
	pc_val |= (SET&0xff);
	pc_val &= ~(CLR&0xff);
	if(pc_val != pc_old)
	{
		send[3] = M16_PC;
		tmp = pc_val;
		send[4] = pc_val & 0xf3;
		tmp = ~tmp;
		tmp = tmp & 0xc;
		send[4] += tmp;

		pc_old = pc_val;
		send[5]=get_crc8(&send[3],2);
		sem_wait(&io->IO_Semt);
err_PC:
		write(io->IO_fd,send,6);
		usleep(50);
		read(io->IO_fd,read_io,2);
	//	usleep(1000);
		if(strcmp(read_io,"OK")!=0)
		{
			fprintf(stderr,"IO OUT PC READ IS : %s\n",read_io);
			goto err_PC;
		}
		sem_post(&io->IO_Semt);
	}
	tmp = (SET>>8);
	pd_val |= tmp;
	tmp = (CLR>>8);
	pd_val &= ~tmp;
	if(pd_val != pd_old)
	{
		send[3] = M16_PD;
		send[4] = ~pd_val;
		pd_old = pd_val;
		send[5]=get_crc8(&send[3],2);
		sem_wait(&io->IO_Semt);
err_PD:
		write(io->IO_fd,send,6);
		usleep(50);
		read(io->IO_fd,read_io,2);
		if(strcmp(read_io,"OK")!=0)
		{
			fprintf(stderr,"IO OUT PD READ IS :%s\n",read_io);
			goto err_PD;
		}
		sem_post(&io->IO_Semt);
	}
	return 0;
}
int  IO_Usart_Tx(io_board_t *io , unsigned char *tx ,int len)
{
	static unsigned char Usart_send[3] =  { WRITE_CMD,WRITE_USART,0};
	unsigned char crc8,nlen;
	char read_io[3]={ 0x00,0x00,0x00};
#define TX_SIZE 30
	sem_wait(&io->IO_Semt);
	while(len>0)
	{
		if(len > TX_SIZE)			nlen = TX_SIZE;
		else 		nlen = len;

		Usart_send[2]= nlen+1;

		crc8 = get_crc8(tx,nlen);
err_Usart:
		write(io->IO_fd,Usart_send,3);
		write(io->IO_fd,tx,nlen);
		write(io->IO_fd,&crc8,1);
		usleep(1500*Usart_send[2]);
		read(io->IO_fd,read_io,2);	//Usart_send[2]);
//		usleep(1000*Usart_send[2]);
		if(strcmp(read_io,"OK")!=0)
		{
			/*������*/
			fprintf(stderr,"IO_Usart READ IS : %s\n",read_io);
			goto err_Usart;
		}
		tx += nlen;
		len -= nlen;
	}
	sem_post(&io->IO_Semt);
	return 1;
}

/*IO�������������������з���*/
void Analyse_Gpio_in(unsigned char in)
{
	I_DEV_IOBoard_Callback(in);
}

