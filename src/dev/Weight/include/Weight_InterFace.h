#ifndef		_Weight_InterFace_H_
#define		_Weight_InterFace_H_


#define MAX_CAR_AXLE 11
typedef struct 
{
	int	AxleWeight ;//单位 10KG
	int	AxleType ;
	int TiresType;
}Wds_AxleInfo;
typedef struct 
{
	int TotalWeight; //单位 10KG
	int AxleNumber; 
	int Speed ;	
	int WeihtInfoType; //类型 是否修正过车辆信息 默认 0 没有修改
	Wds_AxleInfo AxleArry[MAX_CAR_AXLE]; //最后一组存放10轴后的合计
}Wds_CarWeightInfo;
Wds_CarWeightInfo * GetFirstCarWeightInfo(Wds_CarWeightInfo * cwi);
void RemoveFirstCarWeightInfo(void);
void ModifyAxlesNo(int inputAxesNo);
void ModfiyAxlesByWeight(int  InputWeight);
void AddAxleByIndex(int index,Wds_AxleInfo *Axle);
void RemoveAxleByIndex(int index);
void AddCarWeightInfo(Wds_CarWeightInfo *CarWeightInfo);
int GetHistoryWeight(void);
int GetHistoryAxlesNum(void);
void SetHistoryWeight(int i);
void SetHistoryAxlesNum(int i);
void AddTempCarInfo(int inputAxesNo);
void ModifyCarAxlesByNo(int inputAxesNo);
void SetNotRemoveFirstCarWeightInfo(void);
#endif

