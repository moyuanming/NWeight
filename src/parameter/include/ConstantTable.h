#ifndef _ConstantTable_H_
#define _ConstantTable_H_
#define NotUseWeight					'0' //��ʹ�ü��ع���
#define NotUseWeightUseTruckKey			'1' //��ʹ�ü��ع��� ��ʹ�û�����
#define UseWeightUseTruckKeyNotFare		'2' //ʹ�ü��ع��� ���������������
#define FullWeight						'3' //ʹ��ȫ�����ع���
#define NotFiveClassMode				'4' //�����ڶ�λ�շ�
#define BIGFEET							1
#define SMALLFEET						0


// ����Ʊ����ʽ
//����ֵ
#define OLDPrintStyle						'0' //����ʽ
#define NewPrintStyle						'1' //����ʽ
#define PromptPrintStyle					'2' //��ʾ��
#define BothNewandPromptPrintStyl			'3' //��Ʊ������ʾ��

#define OLD312CalculateFare					'0' //��312�Ʒѷ�ʽ
#define NewCalculateFare					'1' //5�ͳ��Ʒ�

#define OLD312JaoKeCalculateFareMode				'0' //��312�Ʒѷ�ʽ
#define NewJaoKeCalculateFareMode					'1' //5�ͳ��Ʒ�

typedef struct {
	char ConstRecordType;	
	struct 
	{
		char BeginOfBSD[4];
		char OffsetBSD[2];
		char TodCashError[8];
		char Noused0[8*4];
		char Noused1[4];
		char TodIouError[4];
		char Noused2[4];
		char ActiveVideo[1];
		char Noused3[1*15];
		char VehiClassNbr[2];
		char NationNbr[1];
		char Noused4[4*2];
	}RecordA;
	struct 
	{
		char Code[20];
		char Num[20][4];
	}RecordB;	
	struct  
	{
		char MsgNo[3];
		char MsgContent[64];
	}RecordT;	
}CONSTANT_RECORD;
int GetCartridgeCapacity(void);
int GetConstantCartridgeCapacityTolerance(void);
int GetConstantFullCapacityTolerance(void);
int GetConstantEmptyCapacityTolerance(void);
int GetRoundingTheResultToFareWeight(void);
int GetRateToGetTheFareWeightFromTheDetectedWeight(void);
int GetMinimumWeightForFareWeight(void);

//��������
int GetBasicFareRate(void);

int GetLimiOfTheWeightToApplyTheBasicFareRate(void);
int GetMinimumFareRate(void);
int GetLimitOfTheWeightToApplyTheMinimumFareRate(void);
int GetMinimumFareRateOfTheParticularTruckInThousands(void);
int GetLimitOfTheParticularTruckToApplyTheMinimumFareRate(void);
int GetRateLimitOfWeightToApplyTheFirstMultiplier(void);
int GetMultiplierOfTheFirstRateLimit(void);
int GetRateLimitOfWeightToApplyTheSecondMultiplier(void);
int GetMultiplierOfTheSecondRateLimit(void);
int GetRoundingValue(void);
int GetDiscountOfGreenPassageTruck(void);
int GetWeightLimitForTruckWithAxles(int axles);
int GetAxleWeighLimt(int InputAxleNumber);
char *GetConstTableVersion(void);
int LoadConstantRecord(int IsFirst);
int GetMaximumFareRateNotDependingOnWeight(void);
int GetDiscountOfContainerPassageTruckWithoutCSC(void);
int GetConstantTimeOutEntryPlazaConfirmationCOMOK(void);
int GetConstantTimeOutEntryPlazaConfirmationCOMDOWN(void);
float GetTollFareDistance(void);
int GetWeightFunctions(void);   
int GetCalculateFareMode(void);
int GetPrinterMode(void);
int GetJaoKeCalculateFareMode(void);
int GetAxleContainerTruckWeighLimt(int InputAxleNumber,int Feet);
char *GetTFIText(int index);
#endif 
	
