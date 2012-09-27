/*
 * wds_thread.c
 *
 *  Created on: 2011-3-30
 *      Author: root
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "serial.h"
#include "wds_protocol.h"
#include "wds_thread.h"
#include "LocalIncludeFile.h"
int wds_isRunning = 0;
void SplitDevRecvData(unsigned char ReadChar);
int wds_read(unsigned char *buf, int nbyte) ;
void WDS_DLL_DevCheckThread(void) {
	//BOOL *p_isRunning = &m_isRunning;
	int i=0;
	while (wds_isRunning) 
	{
		echo_debug_WDS_Dll("WDS_DLL_DevCheckThread Start");
		wds_GetUpdateDateTime();
		echo_debug_WDS_Dll("Run Is!");
		wds_GetWeightStat();
		echo_debug_WDS_Dll("Run Is!");
		i=30;
		while(i--)
		{
			wds_GetCarNum();
			wds_GetTempWeightInfo();
			sleep(1);
		}
		echo_debug_WDS_Dll("WDS_DLL_DevCheckThread Start");
	}
}

static pthread_t WdsWriteComThread;
int CreateDalWDSThreadWrite(void) {
	int ret;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&WdsWriteComThread, &new_attr,
			(void *) WDS_DLL_DevCheckThread, NULL);
	pthread_attr_destroy(&new_attr);
	return ret;
}

void WDS_DLL_ReceiveThread(void) 
{
	unsigned char strRecv[512];
	int RecvLen ;	
	while (wds_isRunning) 
	{
		//echo_debug_WDS_Dll("WDS_DLL_ReceiveThread Start");
		//sem_wait(&wds_Semt);
		RecvLen =wds_read(strRecv,512);
		//echo_debug_WDS_Dll("Run Is!");
		if(RecvLen >0)
		{	
			int i=0;
			//echo_debug_WDS_Dll("RecvLen=<%d>",RecvLen);
			for(i=0;i<RecvLen;i++)
			{
				SplitDevRecvData(strRecv[i]);
			}			
		}
		//echo_debug_WDS_Dll("WDS_DLL_ReceiveThread End");
	}
	echo_debug_WDS_Dll("WDS_DLL_ReceiveThread Exit");
	/*sem_destroy(&wds_Semt);*/
}

static pthread_t WdsReadComThread;
int CreateDalWDSThreadRead(void) {
	int ret;
	pthread_attr_t new_attr;
	pthread_attr_init(&new_attr);
	pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&WdsReadComThread, &new_attr,
			(void *) WDS_DLL_ReceiveThread, NULL);
	pthread_attr_destroy(&new_attr);
	return ret;
}

void Wds_Thead_Init(int fd) {
	wds_setFD(fd);
	wds_isRunning = 1;
}
void Wds_Run(int fd) {
	wds_Timeout_Init();
	Wds_Thead_Init(fd);
	CreateDalWDSThreadRead();
	CreateDalWDSThreadWrite();
}
void Wds_Close(void) {
	wds_isRunning = 0;
}
