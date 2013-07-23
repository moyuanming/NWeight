#ifndef __i_dev_vdm_H__
#define __i_dev_vdm_H__
void I_DEV_VDM_SyncTime(void);
void I_DEV_VDM_Init(void);
void I_DEV_VDM_TextOut(char *text,unsigned char x,unsigned char y,unsigned char  len);
void I_DEV_VDM_Reset(void);
void I_DEV_VDM_Reset_T(void);
void I_DEV_VDM_Cash(int value);
void I_DEV_VDM_CarKind(int CarKind);
void I_DEV_VDM_CarType(char *CarType);
void I_DEV_VDM_CollectNo(char *CollectNo);
void I_DEV_VDM_LaneNO(char *LaneNo);
void I_DEV_VDM_ShowPlaza(char *PlazaNo);
#define EN_CARKIND		"K:%d "
#define EN_CARKIND_S	"K:%s "
#define EN_CASH			"M:%-5d"
#define EN_CASH_S		"M:%s"
#define EN_CARTYPE		"T:%s"
#define EN_COLLECT		"C:%s"
#define EN_LANENO		"L:%s"
#define EN_PLAZA		"P:%s"

#define CN_CARKIND		"车种:%d "
#define CN_CARKIND_S	"车种:%s "
#define CN_CASH			"费额:%-5d"
#define CN_CASH_S		"费额:%s"
#define CN_CARTYPE		"车型:%s"
#define CN_COLLECT		"工号:%s"
#define CN_LANENO		"车道:%s"
#define CN_PLAZA		"站名:%s"
#endif 