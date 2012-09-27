#ifndef		IO_Board_Test_H
#define		IO_Board_Test_H


#define WRITE_CMD		0xF0
#define WRITE_IO		0xF1
#define WRITE_USART		0xF2
#define WRITE_VDM 		0xF3
#define WRITE_IO_SIZE		3

#define READ_CMD	0xE0
#define READ_IO 	0xE1

#define M16_PA	0x0a
#define M16_PB	0x0b
#define M16_PC	0x0c
#define M16_PD	0x0d

#define VDM_LINE		120
#define VDM_RESET		108
#define VDM_DATA_TIME	100



#define IO_MAX_SIZE		32


#define SPI_IO_MASK     1<<0
#define SPI_VDM_MASK    1<<1
#define SPI_USART_MASK  1<<2
typedef struct
{
	int IO_fd;
	sem_t IO_Semt;
	pthread_t Thread_io;
#if 0
	unsigned char IO_SET;
	unsigned char IO_CLR;
	
	unsigned char read_io;
	unsigned char Vdm_time[6];
	unsigned char *Vdm_char;
	unsigned char vmd_line;
	unsigned char vdm_coloum;
	unsigned char vmd_size;
	unsigned char *Usart_tx;
	unsigned char Usart_rx[30];
	unsigned int mask;
#endif
}io_board_t; 


#define PIND4	(1<<12)
#define PIND5	(1<<13)
#define PIND6	(1<<14)
#define PIND7	(1<<15)

#define PINC2	(1<<2)
#define PINC3	(1<<3)
#define PINC5	(1<<5)
#define PINC6	(1<<6)





//303代码的定义。 
/*以下带过零检测控制*/
#define T_LAMP_R PIND7  /*顶棚红*/
#define T_LAMP_G PIND6	/*顶棚绿*/
#define C_LAMP_R PIND5	/*通行红*/
#define C_LAMP_G PIND4	/*通行绿*/
 
 //辽宁代码
// #define T_LAMP_R PIND4  /*顶棚红*/
// #define T_LAMP_G PIND5  /*顶棚绿*/
 //#define C_LAMP_R PIND6  /*通行红*/
 //#define C_LAMP_G PIND7  /*通行绿*/
 
#define ALARM_LAMP PINC2	/*报警灯*/
#define FOG_LAMP PINC3		/*雾气灯*/
/*以下为继电器输出开关量*/
#define RL_1 PINC6
#define RL_2 PINC5





/*IO延时时间*/
#define IO_DELAY do{usleep(1000);}while(0)

#define		CRC8		0x80
#define		CRC16		0xA001
#define		CRC16_CCITT	0x8408
#define		CRC32		0xEDB88320unsigned int get_crc8(unsigned char cdata[], unsigned int nlength);
unsigned int get_crc(unsigned int ninit_checksum, unsigned int ncrc_type, const unsigned char cdata[], unsigned int nlength);
io_board_t  * IOBoard_init(void);
int IOBoard_exit(io_board_t *io);
io_board_t * GetIo_board(void);
int IO_Board_Out(io_board_t *io,unsigned int SET,unsigned int CLR);
void  Sync_Vdm_Time(io_board_t *io);
int	Vdm_line(io_board_t *io ,unsigned char line ,unsigned char coloum, 
	unsigned char nlen,char *VdmChar);
int  IO_Usart_Tx(io_board_t *io ,unsigned  char *tx ,int len);
void Analyse_Gpio_in(unsigned char in);
unsigned int get_crc8(unsigned char cdata[], unsigned int nlength);

#endif
