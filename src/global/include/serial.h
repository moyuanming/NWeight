#ifndef __SERIAL_H__
#define __SERIAL_H__




void Serial_Set_Speed(int fd, int speed);
int Serial_Set_Parity(int fd, int databits, int stopbits, int parity);
int Serial_Open(unsigned char *dev,int bps) ;
int Serial_Close(int fd);
int Serial_Read(int fd, unsigned char *byReadBuf, int nReadLen);
int Serial_Write(int fd, unsigned char *byWriteBuf, int nWriteLen);

#endif
