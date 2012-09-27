#ifndef _APPConfig_H_
#define _APPConfig_H_


/*********�����Ǵ�RHY_Design��ֲ������   �й� �������� �ı���***********************************/
#define LANETYPE_SRV    '8'
#define LANETYPE_TCO    'B'
#define LANETYPE_EXIT   '1'
#define LANETYPE_ENTRY  '7'
#define LANETYPE_CCM    'F'
#define LANETYPE_OPE    'E'
#define LANETYPE_IOU    'I'
#define LANETYPE_TOD    'C'
/*+++�����Ǵ�RHY_Design��ֲ������++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**/
char *GetLanConfigNetNo(void);
void SetLanConfigNetNo(char *InputNetNo);
int GetDataSaveDays(void);
char *GetLanConfigStationNo(void);
char *GetLanConfigPlazaNo(void);
void SetLanConfigPlazaNo(char * InputPlazaNo);
char *GetLanConfigPlazaType(void);
void SetLanConfigPlazaType(char * InputPlazaType);
char *GetLanConfigPlazaDesc(void);
void SetLanConfigPlazaDesc(char *InputPlazaDesc);
char * GetLanConfigLaneNo(void);
void SetLanConfigLaneNo(char *InputLaneNo);
char GetLanConfigLaneType(void);
void SetLanConfigLaneType(char *InputLaneType);
void SetLanConfigLaneMod(char * InputLaneMode);
char GetLanConfigLaneMod(void);
int LanLanConfigTypeIsExitType(void);
void SetUseAutoMan(int inputautoman);
int GetUseAutoMan(void);
void SetICYPKERRGO(int inputICYPKERRGO);
int GetICYPKERRGO(void);
#define  ICYPKERRGO_GOTO_normal  1 //ֱ����Ϊ������
#define  ICYPKERRGO_Wait_Cancel  0 //�ȴ�ȡ��
char * GetKeyMap(void);
int GetHowToLogin(void);
void SetHowToLogin(int inputhowtologin);
void SetEnableTCOCALL(BOOL inputEnableTCOCALL);
void SetKeyMap(char * InputKeyMap);
void LoadLanConfig(void);
char * GetLanConfigVersionNo(void);
void SetLanConfigVisionNo(char * version);
struct LaneConfig * GetCurrentLanConfig(void);
char *GetLanConfigPicType(void);
void Setg_carTypeLen(int value);
int Getg_carTypeLen(void);
void Setg_stationName(char * value);
char * Getg_stationName(void);
void Setg_userPasswordLen(int value);
int Getg_userPasswordLen(void);
void Setg_userNumberLen(int value);
int Getg_userNumberLen(void);
char * GetBillTitle(void);
void SetBillTitle(char * InputBillTitle);
int Get_XIAOYU_10T(void);
float Get_DAYU_10T(void);




#define LT_HandAndIC  0
#define LT_OnlyHand 1
#define LT_OnlyIC  2
#endif
