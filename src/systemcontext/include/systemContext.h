#ifndef __systemContext_H__

#define __systemContext_H__


#define	  	STATE01			1	//	�ȴ��ϰ�״̬
#define	  	STATE02			2	//	�ȴ���¼״̬
#define	  	STATE03			3	//	�ȴ�����¼��
#define	  	STATE04			4	//	�ȴ�������Ϣ
#define	  	STATE05			5	//	�ȴ�����¼��
#define	  	STATE06			6	//	�ȴ����복��
#define	  	STATE07			7	//	�ȴ������뿪
#define	  	STATE08			8	//	�ȴ�����
#define	  	STATE09			9	//	�ȴ�ģ�⹦��ѡ��״̬
#define	  	STATE10			10	//	�ȴ�ѡ���������
#define	  	STATE11			11	//	�ȴ������뿪
#define	  	STATE12			12	//	�ȴ�����ȷ��
#define	  	STATE13			13	//	�ȴ��°�
#define	  	STATE14			14	//	�ȴ�¼�복��
#define	  	STATE15			15	//	�ȴ���ͨ�п�
#define	  	STATE16			16	//	�ȴ����븶�ʽ
#define	  	STATE17			17	//	�ȴ�����
#define	  	STATE18			18	//	�ȴ�����
#define	  	STATE19			19	//	�ȴ����ܼ�
#define	  	STATE20			20	//	�ȴ����ȷ��
#define	  	STATE21			21	//	�ȴ��ֹ����������Ϣ
#define	  	STATE22			22	//	�ȴ��ֹ�¼�����վ��Ϣ
#define	  	STATE23			23	//	�ȴ��Żݿ���ȷ��
#define	  	STATE24			24	//	�ȴ���������ѡ��״̬
#define	  	STATE25			25	//	�������ȷ��
#define	  	STATE26			26	//
#define	  	STATE27			27	//
#define	  	STATE28			28	//
#define	  	STATE29			29	//
#define	  	STATE30			30	// ֧����ʽ�����ĳ�
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
 * ��������
 * ��ҵ��
 * ͬһ������������ÿ��һ�ΰ���ҵ��++
 * ���������ڱ仯ʱ��ҵ������Ϊ 1
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
 *δ�ϰ�ʱ��¼Υ����Ϣ����
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
//���׼�¼��
int CurrentTranNO;
void InitSystemContextCurrentTranNO(void);
void AddSystemContextCurrentTranNO(void);
char  *GetSystemContextCurrentTranNO(void);

void SendMessageWzCar(int wzCarType);
//ָʾ��

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
* ʹ�ô�ֵ��
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
//�߳�

void InitCarTypeKindCharge(void);
void Setg_CurrentLaneState(int value);
int Getg_CurrentLaneState(void);
#endif


