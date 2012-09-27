
// ***************************************************************
//  FareCalculation   version:  1.0   ·  date: 12/09/2007
//  -------------------------------------------------------------
//  费率计算接口！
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "LocalIncludeFile.h"

//初始化变量，这些变量是用来保存计算过程中的中间值的。
//Rate to get the fare weight from the detected weight
//检测重量的修正比例100%
float RateFareWeightDetectedWeight=0;


//基本费率计算重量限重 单位10KG
//Eg：2000 表示20吨
float LimitOfTheWeightBasicFareRate=0; 		
//最小费率计算重量限重 单位10KG
//Eg：4000 表示40吨
float LimitOfTheWeightMinimumFareRate=0;	


float LimitOfTheParticularTruck=0;			//特殊货车总重计算基准点//14.0
float LimitOfTheParticularFare=0;			//特殊货车计算费率 0.043 



float MaximumFareRate=0;					//最大费率1.4

float BasicFareRate=0;						//基本费率0.07
float MinimumFareRate=0;					//最小费率0.04
float TheFirstMultiplier=0;					//第一个划分超限界限百分比 1.3
float TheSecondMultiplier=0;				//第二个划分超限界限百分比 2.0
float TheFirstRateLimit=0;					//第一个超限界限的调节系数数值 3.0
float TheSecondRateLimit=0;					//第二个超限界限的调节系数数值 6.0
float TheMaxRateLimit=0;					//最大超限界限的调节系数数值 12
float RoundingValue=0;						//通行费取证单位 5
float MinimumWeightForFareWeight = 0;      //费率计算最小吨位

float DiscountOfGreenPassageTruck=0;		//绿色通道优惠折扣率 0.25

float DiscountOfContainerPassageTruckWithoutCSC=0;//无优惠卡的标准集装箱车优惠折扣率 0.15
void LoadRecordFromConstantTable(void)
{
	//以下信息从常量表里，开头为'G'的记录中读取的，它是一些预先订好的数值
	MinimumWeightForFareWeight =(float)GetMinimumWeightForFareWeight()/100;
	RateFareWeightDetectedWeight=(float)GetRateToGetTheFareWeightFromTheDetectedWeight()/1000;
	LimitOfTheWeightBasicFareRate=(float)GetLimiOfTheWeightToApplyTheBasicFareRate()/100;	
	LimitOfTheParticularTruck=(float)GetLimitOfTheParticularTruckToApplyTheMinimumFareRate()/100;
	LimitOfTheWeightMinimumFareRate=(float)GetLimitOfTheWeightToApplyTheMinimumFareRate()/100;//35
	MinimumFareRate=(float)GetMinimumFareRate()/10000;//0.04
	BasicFareRate=(float)GetBasicFareRate()/10000;//0.07	
	MaximumFareRate=(float)GetMaximumFareRateNotDependingOnWeight()/100;//1.4
	TheFirstMultiplier=(float)GetRateLimitOfWeightToApplyTheFirstMultiplier()/1000;//1.3
	TheSecondMultiplier=(float)GetRateLimitOfWeightToApplyTheSecondMultiplier()/1000;//2.0
	TheFirstRateLimit=(float)GetMultiplierOfTheFirstRateLimit()/100;//3.0
	TheSecondRateLimit=(float)GetMultiplierOfTheSecondRateLimit()/100;//6.0
	TheMaxRateLimit = (float)GetMaximumFareRateNotDependingOnWeight()/100;
	RoundingValue=(float)GetRoundingValue()/100;//5
	DiscountOfGreenPassageTruck=(float)GetDiscountOfGreenPassageTruck()/1000;
	DiscountOfContainerPassageTruckWithoutCSC=(float)GetDiscountOfContainerPassageTruckWithoutCSC()/1000;
	LimitOfTheParticularFare =(float) GetMinimumFareRateOfTheParticularTruckInThousands()/1000;
}
//费率的最后取整
static int RoundToFinalFare(float FareBeforeRound)
{
	int FinalFare = (int)(FareBeforeRound *100);
	if(0==FinalFare)
	{
		return 0;
	}
	if(FinalFare % 500 <= 250)
	{
		FinalFare -= (FinalFare % 500);
		FinalFare = FinalFare ==0 ? 5:FinalFare;
	}
	else
	{
		FinalFare += 500 - (FinalFare % 500);
	}
	/**************************************************************
	*     *  修改 低于5元的费率为 5元  080224 马彦宏  缸窑                                                              .
	****************************************************************/
	FinalFare=FinalFare/100 ;
	if (FinalFare<5 )
	{
		FinalFare=5;
	}
	return FinalFare ;
}
/*************************************************************************************
* 正常部分费率计算
* 基本费率取0.07元/吨千米，以收费站实际测量确定的车货总重为依据，
* 小于20吨（含）的车辆，按基本费率计收车辆通行费；
* 20吨至40吨（含）的车辆，20吨（含）以下部分，按基本费率计收，20吨以上部分，按0.07元/吨千米线性递减至0.035元/吨千米计收；
* 40吨以上的部分按0.035元/吨千米计收。计费不足5元按5元计。
**************************************************************************************/
static float FarePartI(float WeightNum,float distance)
{
	float PartFare = 0;
	float UseBasicFareRateOfWeight = 0;
	float UseLinearDecOfWeight = 0;
	float UseMiniFareRateOfWeight = 0;
	/*if(GetWeightContext_IsOverLoad()==0)
	{*/
	echoic("FareI :<%f><%f>",WeightNum,distance);
	if(WeightNum>LimitOfTheWeightMinimumFareRate)
	{
		UseMiniFareRateOfWeight = WeightNum - LimitOfTheWeightMinimumFareRate;		
		UseLinearDecOfWeight = LimitOfTheWeightMinimumFareRate - LimitOfTheWeightBasicFareRate;
		UseBasicFareRateOfWeight = LimitOfTheWeightBasicFareRate;
	}
	else if(WeightNum>LimitOfTheWeightBasicFareRate)
	{
		UseLinearDecOfWeight = WeightNum - LimitOfTheWeightBasicFareRate;
		UseBasicFareRateOfWeight = LimitOfTheWeightBasicFareRate;
	}
	else
	{
		UseBasicFareRateOfWeight = WeightNum;
	}
	PartFare = UseBasicFareRateOfWeight*BasicFareRate*distance;
	//(0.07-((0.07-0.035)/(40-20))*4)*80.3*4
	PartFare +=((BasicFareRate+(BasicFareRate-((BasicFareRate-MinimumFareRate)/(LimitOfTheWeightMinimumFareRate - LimitOfTheWeightBasicFareRate))*UseLinearDecOfWeight))/2)*distance*UseLinearDecOfWeight;
	PartFare +=UseMiniFareRateOfWeight*MinimumFareRate*distance;
	/*}
	else
	{
		PartFare = WeightNum*distance*BasicFareRate;
	}	*/
	echoic("PartFare :<%f><%f>",WeightNum,PartFare);
	return PartFare;
}

/*************************************************************************************
* < WeightNum
* 轻微超限部分 <130
* 总轴重超过该车对应的公路承载能力认定标准30%（含）以下的车辆，
* 未超过公路承载能力认定标准部分重量按正常车辆基本费率收费标准计算，超限部分重量暂按基本费率计收
**************************************************************************************/
static float FarePartII(float WeightNum,float distance)
{	
	echoic("FarePartII :<%f><%f>",WeightNum,distance);
	return 0;//WeightNum*BasicFareRate*distance;
}
/*************************************************************************************
* 严重超限部分  130 -200 
* 总轴重超过该车对应的公路承载能力认定标准30%～100%（含）的车辆。
* 该车车货总重中超过公路承载能力认定标准30%(含)以下的重量部分，按第1）款计收；
* 超过公路承载能力认定标准30%以上的重量部分，按基本费率的3倍线性递增至6倍计收
**************************************************************************************/
static float FarePartIII_I(float WeightNum,float distance,float WeightLimit)
{
	//0.07*(3+((6-3)/(WeightLimit*200-limit*130)*w)
	float FareRate = FareRate = BasicFareRate * (
		(TheFirstRateLimit + WeightNum * (TheSecondRateLimit - TheFirstRateLimit) / 
		((TheSecondMultiplier - TheFirstMultiplier) * WeightLimit))
		);
		return  WeightNum * distance * (FareRate + (TheFirstRateLimit * BasicFareRate)) / 2;
}
/*************************************************************************************
* 轻微超限部分  >200 
* 总轴重超过该车对应的公路承载能力认定标准100%以上的车辆:
* 该车车货总重中超过公路承载能力认定标准30%(含)以下的重量部分，按第1）款计收；
* 超过公路承载能力认定标准30%以上的重量部分，按基本费率的6倍计收
**************************************************************************************/
static float FarePartIII_II(float WeightNum,float distance )
{
	return WeightNum*distance*BasicFareRate*MaximumFareRate;
}
static volatile float _WeightTollFare;
float FareCalculation_WeightTollFare()
{
	return RoundToFinalFare(_WeightTollFare);
}
static volatile float _WeightLimitTollFare;
float FareCalculation_WeightLimitTollFare()
{
	return _WeightLimitTollFare;
}
static volatile float _OverloadFare;
float FareCalculation_OverloadFare()
{
	return _OverloadFare;
}
static float  BigTrucksFareForTrucks(float weightNum,int axesNum,float distance)
{

	float FareI = 0;	
	FareI = weightNum*distance*BasicFareRate;	
	_WeightTollFare = 0;
	_WeightTollFare = FareI;
	return _WeightTollFare;
}

static float  NomalFareForTrucks(float weightNum,int axesNum,float distance)
{
	float NormalWeight =0;
	float LowOverloadWeight =0;
	float HighOverloadWeight_I =0;
	float HighOverloadWeight_II =0;
	float WeightLimit =0;
	float FareI = 0;
	float FareII =0;
	float FareIII_I =0;
	float FareIII_II =0;	

	_WeightTollFare = 0;
	_WeightLimitTollFare = 0;
	_OverloadFare = 0;

	WeightLimit = (float)GetAxleWeighLimt(axesNum)/100;

	if(weightNum >WeightLimit*TheSecondMultiplier)
	{
		HighOverloadWeight_II = weightNum - WeightLimit*TheSecondMultiplier;
		HighOverloadWeight_I = WeightLimit*(TheSecondMultiplier-TheFirstMultiplier);
		LowOverloadWeight = WeightLimit *(TheFirstMultiplier-1);
		NormalWeight = WeightLimit + LowOverloadWeight;
		LowOverloadWeight = 0;
	}
	else if (weightNum >WeightLimit*TheFirstMultiplier)
	{
		HighOverloadWeight_I = weightNum - WeightLimit *TheFirstMultiplier;
		LowOverloadWeight = WeightLimit *(TheFirstMultiplier-1);
		NormalWeight = WeightLimit + LowOverloadWeight;
		LowOverloadWeight = 0;
	}
	else
	{
		NormalWeight = weightNum ;//>MinimumWeightForFareWeight ?weightNum:MinimumWeightForFareWeight;
	}

	FareI = FarePartI(NormalWeight,distance);
	FareII = FarePartII(LowOverloadWeight,distance);
	FareIII_I = FarePartIII_I(HighOverloadWeight_I,distance,WeightLimit);
	FareIII_II = FarePartIII_II(HighOverloadWeight_II,distance);
	echoic("FareI :<%f><%f>",NormalWeight,FareI);
	echoic("FareII :<%f><%f>",LowOverloadWeight,FareII);
	echoic("FareIII_I :<%f><%f>",HighOverloadWeight_I,FareIII_I);
	echoic("FareIII_II :<%f><%f>",HighOverloadWeight_II,FareIII_II);
	_WeightTollFare = FareI+FareII+FareIII_I+FareIII_II;
	_WeightLimitTollFare = FareI;
	_OverloadFare = FareII+FareIII_I+FareIII_II;
	return  _WeightTollFare ;
}

//检测重量修正
float TheDetectingCorrection(float weightNum)
{
	float DetectResult=0;
	weightNum=RateFareWeightDetectedWeight*weightNum;
	DetectResult=(float)(int)(weightNum*10)/10;
	if(DetectResult<LimitOfTheWeightBasicFareRate)
	{
		DetectResult=LimitOfTheWeightBasicFareRate;
	}
	return DetectResult;
}
int FareForBigTrucks(float weightNum,int axesNum,float distance)
{
	return RoundToFinalFare( BigTrucksFareForTrucks(weightNum,axesNum,distance));
}
int FareForTrucks(float weightNum,int axesNum,float distance)
{
	return RoundToFinalFare(NomalFareForTrucks(weightNum,axesNum,distance));
}
//老312按吨位计费
static int FareT(int InputVehiClass,int Xy10,float Dy10)
{

	float FareValue;
	FareValue = InputVehiClass*Xy10;
	if(InputVehiClass>10)
	{
		//FareValue-=(InputVehiClass-10)*(10-8);
		FareValue=(InputVehiClass-10)*Dy10+Xy10*10;
	}
	return (int)FareValue;
}
int G_WeightFare = 0;
void SetG_WeightFare(int value)
{
	G_WeightFare = value;
	echoic("################################SET %d",G_WeightFare);
}
int GetG_WeightFare(void)
{
	echoic("################################GET %d",G_WeightFare);
	return G_WeightFare;
}

int G_Calculate_Final_Fare()
{
	int FiveCarTollFare,WeightFare;
	if(NewCalculateFare==GetCalculateFareMode())
	{
		if(WeightCarClassBUS == GetWeightCarClass() && OLD312JaoKeCalculateFareMode == GetJaoKeCalculateFareMode())
		{
			FiveCarTollFare = FareT(atoi(Get_Current_Car_Type()),Get_XIAOYU_10T(),Get_DAYU_10T());	
		}
		else
		{
			FiveCarTollFare = GetFareValue(Get_Current_Car_Type_Index());
		}
		
	}
	else
	{
		FiveCarTollFare = FareT(atoi(Get_Current_Car_Type()),Get_XIAOYU_10T(),Get_DAYU_10T());		
	}
	if(WeightCarClassBIGTruckVehicles == GetWeightCarClass())
	{
		WeightFare = FareForBigTrucks(GetFareContext_CarWeight(),GetFareContext_CarAxleNumber(),GetTollFareDistance());
	}
	else
	{
		WeightFare = FareForTrucks(GetFareContext_CarWeight(),GetFareContext_CarAxleNumber(),GetTollFareDistance());
	}
	echoic("################################ %d",WeightFare);
	SetG_WeightFare(WeightFare);
	if(FullWeight == GetWeightFunctions())
	{
		if(WeightCarClassTruck == GetWeightCarClass())
		{
			Set_G_Current_Toll_Fare(WeightFare);
		}
		else
		{
			Set_G_Current_Toll_Fare(FiveCarTollFare);
		}
		switch (GetCarKindChar(Getg_CurrentCarKindIndex()))
		{
			case CARKIND_SHOUFEI:
				if(WeightCarClassBUS == GetWeightCarClass()||WeightCarClassTruckISNotUseWeight == GetWeightCarClass())
				{
					Set_G_Current_Toll_Fare(FiveCarTollFare);
					Set_G_Current_Actual_pay(FiveCarTollFare);
				}
				else
				{
					Set_G_Current_Actual_pay(WeightFare);
				}				
				break;
			case CARKIND_YHC:	
				if(WeightCarClassBUS == GetWeightCarClass()||WeightCarClassTruckISNotUseWeight == GetWeightCarClass())
				{
					Set_G_Current_Toll_Fare(FiveCarTollFare);
					Set_G_Current_Actual_pay(GetFactMoney(FiveCarTollFare,GetYHRate(GetYHCode(GetG_AbateNumber())),GetAdjustMode(GetYHCode(GetG_AbateNumber())),GetCarryMode(GetYHCode(GetG_AbateNumber()))));
					Setg_DiscountRate(Get_G_Current_Actual_pay(),Get_G_Current_Toll_Fare());	
				}
				else
				{					
					Set_G_Current_Actual_pay(GetFactMoney(WeightFare,GetYHRate(GetYHCode(GetG_AbateNumber())),GetAdjustMode(GetYHCode(GetG_AbateNumber())),GetCarryMode(GetYHCode(GetG_AbateNumber()))));
					Setg_DiscountRate(Get_G_Current_Actual_pay(),Get_G_Current_Toll_Fare());					
				}
				break;
			default:
				Set_G_Current_Actual_pay(0);
				break;
		}
	}
	else
	{
		Set_G_Current_Toll_Fare(FiveCarTollFare);
		switch (GetCarKindChar(Getg_CurrentCarKindIndex()))
		{
		case CARKIND_SHOUFEI:
			Set_G_Current_Actual_pay(FiveCarTollFare);
			break;
		case CARKIND_YHC:		
			Set_G_Current_Actual_pay(GetFactMoney(FiveCarTollFare,GetYHRate(GetYHCode(GetG_AbateNumber())),GetAdjustMode(GetYHCode(GetG_AbateNumber())),GetCarryMode(GetYHCode(GetG_AbateNumber()))));
			Setg_DiscountRate(Get_G_Current_Actual_pay(),Get_G_Current_Toll_Fare());	
			break;
		default:
			Set_G_Current_Actual_pay(0);
			break;
		}
	}
	return 0 ;
}


