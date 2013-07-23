#ifndef __i_dev_IO_SAT_H__
#define __i_dev_IO_SAT_H__
int  I_DEV_IO_SAT_Init(void);
void I_DEV_IO_SAT_Callback(unsigned char *Inputstrs);
int  I_DEV_IO_SAT_Out(unsigned int TurnOn,unsigned int TurnOff);
int CreateIO_STAThreadWrite(void) ;
void IO_STA_ReceiveThread(void) ;
#endif