#include "LocalIncludeFile.h"

int GetFareContext_CarAxleNumber()
{
	int ret =2;
	if(GetWeightContext_DevAxleNumber()>6)
	{
		ret = 6;
	}
	else if(GetWeightContext_DevAxleNumber()<2)
	{
		ret = 2;
	}
	else
	{
		ret = GetWeightContext_DevAxleNumber();
	}
	return ret ; 
}
float volatile FareContext_CarWeight = 0;
float GetFareContext_CarWeight()
{
	int DetectedWeight ;
	float FDetectedWeight,carweight ;
	DetectedWeight = GetRateToGetTheFareWeightFromTheDetectedWeight();
	FDetectedWeight =  (float)DetectedWeight/1000;
	carweight = GetWeightContext_DevWeight();
	FareContext_CarWeight = carweight*FDetectedWeight;
	if(WeightCarClassTruckSpecialVehicles==GetWeightCarClass())
	{
		FareContext_CarWeight = FareContext_CarWeight/2;
	}
	echoic("GetFareContext_CarWeight<%d><%f><%f><%f>",DetectedWeight,FDetectedWeight,carweight,FareContext_CarWeight);
	return FareContext_CarWeight;
}
float G_Current_Actual_pay=0;
void Init_G_Current_Actual_pay()
{
	G_Current_Actual_pay=0;
	I_DEV_VDM_Cash((int)G_Current_Actual_pay);
}
void Set_G_Current_Actual_pay(float value)
{	
	G_Current_Actual_pay=value;
	UI_SetCarMoney((short)G_Current_Actual_pay);
	LedShowCharge(Get_Current_Car_Type()[0],(int)G_Current_Actual_pay);
	I_DEV_VDM_Cash((int)value);
}
float Get_G_Current_Actual_pay(void)
{	
	return G_Current_Actual_pay;
}

float G_Current_Toll_Fare=0;
void Set_G_Current_Toll_Fare(float value)
{	
	G_Current_Toll_Fare=value;
}
float Get_G_Current_Toll_Fare(void)
{	
	return G_Current_Toll_Fare;
}
