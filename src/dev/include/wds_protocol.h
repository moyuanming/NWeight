#ifndef __WDS_PROTOCOL_H__
#define __WDS_PROTOCOL_H__
//#ifndef NULL
//#define NULL 0
//#endif
#include <semaphore.h>
//sem_t wds_Semt;
typedef struct wds_protocol {
	unsigned char msg_data[512];
	unsigned char order_type;
	unsigned char msg_length;
} TWdsProtocol;
typedef TWdsProtocol * PTWdsProtocol;
typedef void (*WDS_Status_Event_Func)(int);
void wds_setFD(int pfd);
void wds_GetFirstWeightInfo(void);
void wds_GetTempWeightInfo(void);
void wds_GetCarNum(void);
void wds_GetWeightStat(void);
void wds_GetUpdateDateTime(void);
void wds_DropFirstInfo(void);
void wds_Set_Status_Event_Func(WDS_Status_Event_Func func);
void wds_Init_SEM(void);
void wds_Destroy_SEM(void);
void wds_Timeout_Init(void);
void wds_Wait_SEM(void);
void wds_Post_SEM(void);
#endif
