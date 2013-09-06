#include "LocalIncludeFile.h"
Wds_CarWeightInfo CurrentCarWeight;
void GetCarWeightInfoForWeight_InterFace()
{	
	if(NULL ==GetFirstCarWeightInfo(&CurrentCarWeight))
	{
		InitWeightContextData();
	}
	echoic("CurrentCarWeight->TotalWeight<%d>,CurrentCarWeight->AxleNumber<%d>,CurrentCarWeight->Speed<%d>",CurrentCarWeight.TotalWeight,CurrentCarWeight.AxleNumber,CurrentCarWeight.Speed);
}
int GetWeightContext_DevAxleNumber()
{
	return CurrentCarWeight.AxleNumber;
}

/*************************************************************************************
* 计重设备获取的顿数 
**************************************************************************************/
static volatile float GetDevWeight = 0;
float  GetWeightContext_DevWeight()
{

	GetDevWeight = CurrentCarWeight.TotalWeight;
	
	return GetDevWeight/1000;
}

/*************************************************************************************
* 限重 根据轴数计算出限重 单位10 kg
**************************************************************************************/
int GetWeightContext_WeightLimit(void)
{
	int WeightLimit = 0;
	if (GetFareContext_CarAxleNumber()>0)
	{		
		WeightLimit = GetAxleWeighLimt(GetFareContext_CarAxleNumber())*10;
	}
	return WeightLimit;
}
/*************************************************************************************
*取得限重 ， 单位是 吨，                                     
**************************************************************************************/
static volatile float WeightLimit = 0;
float  GetWeightContext_WeightLimit_ByTon(void)
{
	
	WeightLimit=GetWeightContext_WeightLimit();
	return  WeightLimit/ 1000;
}
BOOL OverLoad30(void)
{
	int Over = GetWeightContext_OverLoadWeightRate();
	return Over<=30;
}
BOOL Get_Weight_Is_JianMian()
{

	if(FullWeight == GetWeightFunctions())
	{
	
		return OverLoad30();
	}
	else
	{
		return TRUE;
	}
	
}
/**************************************************************
*  取得设备返回的指定轴重量    单位 10kg                      . 
***************************************************************/
float GetWeightContext_DevWeight_Axes(int IndexOfAxes)
{

	if(IndexOfAxes>GetWeightContext_DevAxleNumber())
	{
		return 0;
	}
	else
	{
		return CurrentCarWeight.AxleArry[IndexOfAxes].AxleWeight;
	}
	
}
/*************************************************************************************
* 超重 重量
**************************************************************************************/
static volatile float OverWeightLimit = 0;
int GetWeightContext_OverLoadWeight()
{

	if(GetFareContext_CarWeight()>GetWeightContext_WeightLimit_ByTon())
	{
		OverWeightLimit =  GetFareContext_CarWeight() - GetWeightContext_WeightLimit_ByTon();
	}
	else
	{
		OverWeightLimit = 0;
	}
	echoic("OverWeightLimit<%f>",OverWeightLimit);
	
	return	OverWeightLimit ;
}

/*************************************************************************************
* 超重 比例
**************************************************************************************/
static volatile float OverLoadWeightRate = 0;
float GetWeightContext_OverLoadWeightRate ()
{

	float _weight,_weightLimit;
	_weight = Rounding(GetFareContext_CarWeight());
	_weightLimit = Rounding(GetWeightContext_WeightLimit_ByTon());
	if(0==_weight || 0== _weightLimit || _weight <=_weightLimit)
	{
		 OverLoadWeightRate = 0;
	}
	else
	{	
		echoic("_weight<%f>,_weightLimit<%f>",_weight,_weightLimit);
		OverLoadWeightRate = _weight /_weightLimit;
		echoic("_weight<%f>,_weightLimit<%f><%f><%f><%f>",_weight,_weightLimit,OverLoadWeightRate,Rounding(OverLoadWeightRate), OverLoadWeightRate*100-100);
		OverLoadWeightRate = OverLoadWeightRate*100-100;
	}
	return	Rounding(OverLoadWeightRate);
}
/*************************************************************************************
* 速度 
**************************************************************************************/
int GetWeightContext_Speed ()
{
	return	CurrentCarWeight.Speed;;
}
/*************************************************************************************
* 加速度 
**************************************************************************************/
int GetWeightContext_AcceleSpeed ()
{	
	return CurrentCarWeight.Speed;
}
/*************************************************************************************
* 受否超限
**************************************************************************************/
int GetWeightContext_IsOverLoad()
{
	if(GetFareContext_CarWeight() >(GetWeightContext_WeightLimit_ByTon()))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void InitWeightContextData()
{	
	CurrentCarWeight.AxleNumber = 0;
	CurrentCarWeight.TotalWeight = 0;
	CurrentCarWeight.WeihtInfoType = 0;
	CurrentCarWeight.Speed = 0;
}

void SetMsg_TR_WeightInfo()
{
	int i;
	SetExitTRMsgWeightCarClass(GetWeightCarClass());
	SetExitTRMsgFWeightTotal(GetFareContext_CarWeight());
	SetExitTRMsgFAxleCount(GetFareContext_CarAxleNumber());
	SetExitTRMsgFFareBase(GetBasicFareRate());


	SetExitTRMsgWeightLimit(GetWeightContext_WeightLimit_ByTon());
	SetExitTRMsgOverloadWeight(GetWeightContext_OverLoadWeight());
	SetExitTRMsgOverloadFare((FareCalculation_OverloadFare()));

	SetExitTRMsgWeightTollFare((FareCalculation_WeightTollFare()));
	SetExitTRMsgWeightLimitTollFare((FareCalculation_WeightLimitTollFare()));


	SetExitTRMsgFlagOverWeight(GetWeightContext_IsOverLoad());
	SetExitTRMsgRateFareWeight(GetRateToGetTheFareWeightFromTheDetectedWeight());
	SetExitTRMsgOverLoadWeightRate(GetWeightContext_OverLoadWeightRate());
	SetExitTRMsgDetectWeightTotal(GetWeightContext_DevWeight());
	SetExitTRMsgDetectAxleCount(GetWeightContext_DevAxleNumber());




	for (i=0;i<CurrentCarWeight.AxleNumber;i++)
	{
		SetExitTRMsgDetectAxleGorup(GetWeightContext_DevWeight_Axes(i),i);
	}


}

void SetMsg_ES_HT_WeightInfo()
{
	int Fist = (GetRateLimitOfWeightToApplyTheFirstMultiplier()-1000)/10;
	int Second =(GetRateLimitOfWeightToApplyTheSecondMultiplier()-1000)/10;
	int Rate = GetWeightContext_OverLoadWeightRate();

	//移除车辆计重信息



	RemoveFirstCarWeightInfo();
	if(WeightCarClassBUS ==GetWeightCarClass())
	{
		return;
	}
	SetExitESMsgWeightCount(1);
	SetExitESMsgWeightFareTotal(Get_G_Current_Actual_pay());
	if(0==Rate)
	{
		SetExitESMsgUnOverloadWeightCount(1);
		SetExitESMsgUnOverloadWeightFareTotal(Get_G_Current_Actual_pay());
	}
	else if(Rate >0 && Rate <=Fist)
	{
		SetExitESMsgOverloadWeight30Count(1);
		SetExitESMsgOverloadWeight30FareTotal(Get_G_Current_Actual_pay());
	}
	else if(Rate >Fist && Rate <=Second)
	{
		SetExitESMsgOverloadWeight30_100Count(1);
		SetExitESMsgOverloadWeight30_100FareTotal(Get_G_Current_Actual_pay());
	}
	else if(Rate >Second )
	{
		SetExitESMsgOverloadWeight100Count(1);
		SetExitESMsgOverloadWeight100FareTotal(Get_G_Current_Actual_pay());
	}
	
}

