#ifndef __i_dev_ICR_JY2_H__
#define __i_dev_ICR_JY2_H__
void ICR_JY2_Init(char *ProtNumber, int Bdps);
void ICR_JY2_MIFRequest(void);
int  ICR_JY2_ReadBlock(int blockid,char* buffer);
int  ICR_JY2_WriteBlock(int blockid,char* buffer);
#endif 