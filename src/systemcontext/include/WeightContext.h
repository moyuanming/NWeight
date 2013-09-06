#ifndef __WeightContext_H__
#define __WeightContext_H__
#define AXES_MAX 60//本软件能够处理的最大轴数  不能超过100

#define Rounding(_F_) (int)((_F_ * (100)) + (0.5)) / (100.0)

void GetCarWeightInfoForWeight_InterFace(void);

BOOL Get_Weight_Is_JianMian(void);
int GetWeightContext_DevAxleNumber(void);
float  GetWeightContext_DevWeight(void);
int GetWeightContext_WeightLimit(void);
float  GetWeightContext_WeightLimit_ByTon(void);
float GetWeightContext_DevWeight_Axes(int IndexOfAxes);
int GetWeightContext_OverLoadWeight(void);
float GetWeightContext_OverLoadWeightRate (void);
int GetWeightContext_Speed (void);
int GetWeightContext_AcceleSpeed (void);
int GetWeightContext_IsOverLoad(void);
void InitWeightContextData(void);
void SetMsg_ES_HT_WeightInfo(void);
void SetMsg_TR_WeightInfo(void);
BOOL OverLoad30(void);
















#endif

