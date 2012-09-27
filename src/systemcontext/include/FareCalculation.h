#ifndef _FareCalculation_H_
#define _FareCalculation_H_
int FareWithoutWeightSystem(char *InputEnNetNo,char *InputEnPlazaNo,char *InputVehiClass);
int FareForCarAndBus(char *InputEnNetNo,char *InputEnPlazaNo,char *InputVehiClass);
int FareForTrucks(float weightNum,int axesNum,float distance);

float FareCalculation_WeightTollFare(void);
float FareCalculation_WeightLimitTollFare(void);
float FareCalculation_OverloadFare(void);

int G_Calculate_Final_Fare(void);
void SetG_WeightFare(int value);
int GetG_WeightFare(void);

//ºÏ≤‚÷ÿ¡ø–ﬁ’˝
float TheDetectingCorrection(float weightNum);
void LoadRecordFromConstantTable(void);
#endif

