#ifndef __CARDCONTEXT_H__
#define __CARDCONTEXT_H__
#define PAYRET_OK  0  //��������
#define PAYRET_READCARDERROR  1//����ʧ��
#define PAYRET_CARDTYPEINVALID 2//��������Ч�� 
#define PAYRET_CARTYPEERROR 3//���ͺ�����ĳ����޷�ƥ��
#define PAYRET_PRINTERERROR 4//��ӡ������
#define PAYRET_READCARDKEYOLD  5//����ʧ��
#define PAYRET_READCARDKEYNOTFOND  6//����ʧ��
#define CARDSTATUS_Unfulfilment 	  "00"	//δ����
#define CARDSTATUS_Normal   		  "01"//	����
#define CARDSTATUS_Reclaim  		  "02"//	����
#define CARDSTATUS_Scrap  			  "03"//	����
#define CARDSTATUS_ReportLoss 		  "04"//��ʧ
#define CARDSTATUS_LockCard  		  "05" //���� �Ͻ�������
char * GetCardStatus(char * stat);
int UseCardToPay(void);
int Get_CardContext_PayCardType(void);
 char * GetCardContext_CardNumber(void);
int  Get_CardContext_MonthCard_Balance(void);
char * Get_CardContext_EnableDate(void);
char * Get_CardContext_DisEnableDate(void);
int  Get_CardContext_MonthCard_Count(void);
char * Get_CardContext_MonthCard_CarType(void);
BOOL  Get_CardContext_MonthCard_CanPay(void);
void  Set_CardContext_MonthCard_CanPay(BOOL _inputvalue);
void        Use_CardContext_SVCCard_Pay(void);
void Use_CardContext_SVCCard_Pay_extracted(float tempTollFare);
float Get_CardContext_SVC_UsedCash(void);
float Get_CardContext_SVC_BeforeBalance(void);
void   Use_CardContext_SVCCard_Pay(void);
void  Use_CardContext_MonthCard_Pay(void);
BOOL Use_CardContext_MonthCard_PayByCard(void);
float Get_CardContext_SVC_Balance(void);
void  InitCardContext(void);
struct ICCARD  *Get_CardContext(void);
BOOL   GetIs_CardContext_MonthCard_Paid(void);
void SetIs_CardContext_MonthCard_Paid(BOOL  b);
BOOL   GetIs_CardContext_SVCCard_Paid(void);
void SetIs_CardContext_SVCCard_Paid(BOOL  b);
BOOL  Get_CardContext_SVCCard_CanPay(void);
void  Set_CardContext_SVCCard_CanPay(BOOL _inputvalue);
BOOL Use_CardContext_SVCCard_PayByCard(void);

BOOL  Get_CardContext_OfficialCard_CanPay(void);
void Set_CardContext_OfficialCard_CanPay(BOOL _inputvalue);
 
void  Use_CardContext_OfficialCard_Pay(void);
BOOL Use_CardContext_OfficialCard_PayByCard(void);
BOOL   GetIs_CardContext_OfficialCard_Paid(void);
void SetIs_CardContext_OfficialCard_Paid(BOOL  b);
 
#endif 
