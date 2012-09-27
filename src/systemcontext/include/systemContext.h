#ifndef __systemContext_H__

#define __systemContext_H__


#define	  	STATE01			1	//	等待上班状态
#define	  	STATE02			2	//	等待登录状态
#define	  	STATE03			3	//	等待车型录入
#define	  	STATE04			4	//	等待记重信息
#define	  	STATE05			5	//	等待车牌录入
#define	  	STATE06			6	//	等待输入车种
#define	  	STATE07			7	//	等待车队离开
#define	  	STATE08			8	//	等待发卡
#define	  	STATE09			9	//	等待模拟功能选择状态
#define	  	STATE10			10	//	等待选择卡箱操作项
#define	  	STATE11			11	//	等待车辆离开
#define	  	STATE12			12	//	等待交易确认
#define	  	STATE13			13	//	等待下班
#define	  	STATE14			14	//	等待录入车种
#define	  	STATE15			15	//	等待读通行卡
#define	  	STATE16			16	//	等待输入付款方式
#define	  	STATE17			17	//	等待付款
#define	  	STATE18			18	//	等待公务卡
#define	  	STATE19			19	//	等待功能键
#define	  	STATE20			20	//	等待监控确认
#define	  	STATE21			21	//	等待手工输入记重信息
#define	  	STATE22			22	//	等待手工录入入口站信息
#define	  	STATE23			23	//	等待优惠卡并确认
#define	  	STATE24			24	//	等待计重类型选择状态
#define	  	STATE25			25	//	读卡完毕确认
#define	  	STATE26			26	//
#define	  	STATE27			27	//
#define	  	STATE28			28	//
#define	  	STATE29			29	//
#define	  	STATE30			30	// 支付方式处更改车
#define 	STATE31 		 31

#define		WORKMODECLOSE		'0'
#define		WORKMODEYY			'1'
#define		WORKMODEMONI		'3'
#define		WORKMODETEST		'4'

void SetWorkState(int value);
void SetLastWorkState(int value);
int GetWorkState(void);
int GetLastWorkState(void);
char * GetMsgTitle(void);
 


void SetWorkMode(char InputWorkModeCode );
char * GetWorkMode(void);
char GetWorkModeCode(void);
void SetWorkType(char * InputWorkType);
char * GetWorkType(void);

char * GetPayTypeDec(void);
void SetPayTypeDec(char *InputPayTypeDec);

int Get_Current_Car_Type_Index(void);

void Setg_CurrentCarKindIndex(int value);
int Getg_CurrentCarKindIndex(void);
 

void Setg_DiscountRate(float tollFare,float actualFare);
int Getg_DiscountRate(void);
void SetBillNumber(void);
int GetCurrentWorkPassCarCount(void);
void SetCurrentWorkPassCarCount(int InputCurrentWorkPassCarCount);
int AddCurrentWorkPassCarCount(void);
void Setg_CurrentCarKindExplain(char * value);
char * Getg_CurrentCarKindExplain(void);
void Setg_CurrentCarTypeStand(int value);
char * Getg_CurrentCarTypeStand(void);
void SetEixtTRInfo(int carTypeIndex,int carKindIndex);

/*
 * 结算日期
 * 作业号
 * 同一个结算日期内每上一次班作业号++
 * 当结算日期变化时作业号设置为 1
 *
 */
struct StructSystemContextSettlementDateAndJobNo
{
	char SettlementDate[8];
	char JobNo[2];
};
void LoadSystemContextSettlementDateAndJobNo(void);
char *CreateSettlementDate(void);
void SetSettlementDate(void);
char *GetSettlementDate(void);
void InitJobNo(void);
void AddJobNo(void);
int GetJobNo(void);

/*
 *未上班时记录违章信息数量
 *
*/

void InitViolCount(void);
void AddViolCount(void);
int GetViolCount(void);
void InitOnJobDateTime(void);
char *GetOnJobDateTime(void);
void SetOnJobDateTime(char *jbtimetime);
void BeforeOfTransDo(void);
void AfterOfTransDo(int value,BOOL urgen);
int GetNewCarCount(void);
void ReSetCarCount(void);
void Setg_DisputeType(int value);
int Getg_DisputeType(void);
void Setg_Violation(int value);
int Getg_Violation(void);
//交易记录号
int CurrentTranNO;
void InitSystemContextCurrentTranNO(void);
void AddSystemContextCurrentTranNO(void);
char  *GetSystemContextCurrentTranNO(void);

void SendMessageWzCar(int wzCarType);
//指示号

void InitSystemContextDuplicatedIndexNo(void);
void AddSystemContextDuplicatedIndexNo(void);
char GetSystemContextDuplicatedIndexNo(void);


void SetSystemContextSihtNo(char InputSystemContextSihtNo);
char GetSystemContextSihtNo(void);


void InitSystemContextIsIOU(void);
int GetSystemContextIsIOU(void);
void SetSystemContextIsIOU(void);
char *GetSystemIOUNO(void);
void SetSystemIOUNO(char *InputSystemIOUNO);
/******************************************************************************************************
* 使用储值卡
******************************************************************************************************/
void InitSystemContextIsSVC(void);
int GetSystemContextIsSVC(void);
void SetSystemContextIsSVC(void);
long GetEixtEsWorkTime(char * Bs_time,char * EixtEstime);

void SetSystemContextTFITextIndex(char *InputSystemContext);
char *GetSystemContextTFITextIndex(void);
char *GetSystemContextTFIText(void);
void LoadTFIText(void);
void InitUserNumAndNameAndOnJobDateTime(void);

void Set_AllKindData(void);
void TransDoTuoche(void);
//线程

void InitCarTypeKindCharge(void);
void Setg_CurrentLaneState(int value);
int Getg_CurrentLaneState(void);
#endif


