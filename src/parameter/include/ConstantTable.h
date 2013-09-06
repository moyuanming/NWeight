#ifndef _ConstantTable_H_
#define _ConstantTable_H_
#define NotUseWeight					'0' //不使用计重功能
#define NotUseWeightUseTruckKey			'1' //不使用计重功能 但使用货车键
#define UseWeightUseTruckKeyNotFare		'2' //使用计重功能 但不用来计算费率
#define FullWeight						'3' //使用全部计重功能
#define NotFiveClassMode				'4' //按现在吨位收费
#define BIGFEET							1
#define SMALLFEET						0


// 计重票据样式
//返回值
#define OLDPrintStyle						'0' //老样式
#define NewPrintStyle						'1' //新样式
#define PromptPrintStyle					'2' //提示单
#define BothNewandPromptPrintStyl			'3' //新票样和提示单

#define OLD312CalculateFare					'0' //老312计费方式
#define NewCalculateFare					'1' //5型车计费

#define OLD312JaoKeCalculateFareMode				'0' //老312计费方式
#define NewJaoKeCalculateFareMode					'1' //5型车计费

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

//基本费率
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
	
