#include "carlist.h"
#include "wds_protocol.h"
#include "Weight_InterFace.h"
#include "LocalIncludeFile.h"
Wds_CarWeightInfo * GetFirstCarWeightInfo(Wds_CarWeightInfo * cwi) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	LogCDev(LOG_INFOR,"取车计费 开始");
	wds_Wait_SEM();
	int i = 0;
	if (cwi == NULL && Car_GetNum() <= 0) 
	{
		LogCDev(LOG_INFOR,"取车计费 无车");
		wds_Post_SEM();
		return NULL;
	}
	cwi->AxleNumber = Car_GetCarAxlesNum(0);
	cwi->Speed = Car_GetCarSpeed(0);
	cwi->TotalWeight = Car_GetCarWeight(0);
	cwi->AxleArry[10].AxleType = 0;
	cwi->AxleArry[10].AxleWeight = 0;
	LogCDev(LOG_INFOR,"取车计费 轴数:%d;车速:%d;总重:%d;",cwi->AxleNumber,cwi->Speed,cwi->TotalWeight);
	for (i = 0; i < cwi->AxleNumber; i++) {
		if (i >= MAX_CAR_AXLE - 1) {
			cwi->AxleArry[10].AxleType += Car_GetCarAxlesType(0, i);
			cwi->AxleArry[10].AxleWeight += Car_GetCarAxlesWeight(0, i);
			LogCDev(LOG_INFOR,"取车计费 10轴;轴型:%d;轴重:%d;",cwi->AxleArry[10].AxleType,cwi->AxleArry[10].AxleWeight);
		} else {
			cwi->AxleArry[i].AxleType = Car_GetCarAxlesType(0, i);
			cwi->AxleArry[i].AxleWeight = Car_GetCarAxlesWeight(0, i);
			LogCDev(LOG_INFOR,"取车计费 %d轴;轴型:%d;轴重:%d;",i,cwi->AxleArry[i].AxleType,cwi->AxleArry[i].AxleWeight);
		}
	}	
	echoic("cwi->TotalWeight<%d>,cwi->AxleNumber<%d>,cwi->Speed<%d>",cwi->TotalWeight,cwi->AxleNumber,cwi->Speed);
	wds_Post_SEM();
	LogCDev(LOG_INFOR,"取车计费 结束");
	return cwi;

}
void Finishing(void) {
	if (0 == Car_GetCarAxlesNum(1)) {
		Car_Delete(1);
	}
	if (1 == Car_GetCarAxlesNum(1)) {
		Axle_Insert(1, 1);
		Car_SetCarAxlesWeight(1,1,Car_GetCarAxlesWeight(1,0));
		Car_SetCarAxlesWeight(1,0,Car_GetCarAxlesWeight(0,Car_GetCarAxlesNum(0)-1)/2);
		Car_SetCarAxlesWeight(0,Car_GetCarAxlesNum(0)-1,Car_GetCarAxlesWeight(0,Car_GetCarAxlesNum(0)-1)/2);
	}
}
int HistoryWeight = 0;
int HistoryAxlesNum = 0;
void SetHistoryWeight(int i)
{
	HistoryWeight = i;
}
void SetHistoryAxlesNum(int i)
{
	HistoryAxlesNum = i;
}
int GetHistoryWeight(void)
{
	return HistoryWeight;
}
int GetHistoryAxlesNum(void)
{
	return HistoryAxlesNum;
}
int isRemoveFirstCarWeightInfo = 0;
void SetNotRemoveFirstCarWeightInfo(void)
{
	isRemoveFirstCarWeightInfo = 1;
}
void RemoveFirstCarWeightInfo(void)
{
	LogCDev(LOG_INFOR,"删车 开始");
	if(isRemoveFirstCarWeightInfo!=0)
	{
		isRemoveFirstCarWeightInfo = 0;
		LogCDev(LOG_INFOR,"删车 模拟降杆不删车");
		return;
	}
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	wds_Wait_SEM();
	echo_debug_WDS_Dll("Run Is!");
	HistoryWeight = Car_GetCarWeight(0);
	echo_debug_WDS_Dll("Run Is!");
	HistoryAxlesNum = Car_GetCarAxlesNum(0);
	echo_debug_WDS_Dll("Run Is!");
	echoic("RemoveFirstCarWeightInfo");
	Car_QueuePop();
	echo_debug_WDS_Dll("Run Is!");
	CarList_Change();
	echo_debug_WDS_Dll("Run Is!");
	wds_Post_SEM();
	LogCDev(LOG_INFOR,"删车 结束");
}
void ModifyAxlesNo(int inputAxesNo) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	LogCDev(LOG_INFOR,"修正车辆信息 轴数:%d",inputAxesNo);
	wds_Wait_SEM();
	if (Car_GetNum() > 0) {
		if (inputAxesNo > Car_GetCarListAxlesNum() || inputAxesNo <= 0) {
			wds_Post_SEM();
			return;
		}
		int i = 0, j = 0;
		int c = Car_GetCarAxlesNum(0);
		if (c > inputAxesNo)//轴数小于当前轴数 拆车
		{
			Car_Insert(1);
			Car_SetCarOverload(1, Car_GetCarOverload(0));
			Car_SetCarSpeed(1, Car_GetCarSpeed(0));
			Car_SetCarAcceleration(1, Car_GetCarAcceleration(0));
			for (i = inputAxesNo; i < c; i++) {
				Car_SetCarAxlesWeight(1, j, Car_GetCarAxlesWeight(0,
						inputAxesNo));
				Car_SetCarAxlesType(1, j, Car_GetCarAxlesType(0, inputAxesNo));
				Car_SetCarAxlesSpace(1, j, Car_GetCarAxlesSpace(0, inputAxesNo));
				Axle_Delete(0, inputAxesNo);
				j++;
			}
		} else if (c < inputAxesNo)//轴数大于当前轴数 向后面车扩展
		{
			for (i = c; i < inputAxesNo; i++) {
				if (0 == Car_GetCarAxlesNum(1)) {
					Car_Delete(1);
				}
				Car_SetCarAxlesWeight(0, i, Car_GetCarAxlesWeight(1, 0));
				Car_SetCarAxlesType(0, i, Car_GetCarAxlesType(1, 0));
				Car_SetCarAxlesSpace(0, i, Car_GetCarAxlesSpace(1, 0));
				Axle_Delete(1, 0);
			}
		}
		Finishing();
	}
	CarList_Change();
	wds_Post_SEM();
}
void ModfiyCarAxlesByWeight(int cn, int InputWeight) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	wds_Wait_SEM();
	int i = 0, j = 0, k = 0, c = 0;
	int tempWeight = 0;
	int carnum = cn;

	c = Car_GetCarAxlesNum(0);
	for (i = 0; i < c; i++) {
		if (carnum == cn) {
			tempWeight += Car_GetCarAxlesWeight(cn, i);
		}
		if (tempWeight >= InputWeight && carnum == cn) {
			Car_SetCarAxlesWeight(cn, i, Car_GetCarAxlesWeight(cn, i)
					- (tempWeight - InputWeight));
			carnum = cn + 1;
			Car_Insert(carnum);
			Car_SetCarOverload(carnum, Car_GetCarOverload(cn));
			Car_SetCarSpeed(carnum, Car_GetCarSpeed(cn));
			if (tempWeight - InputWeight != 0) {
				Car_SetCarAcceleration(carnum, Car_GetCarAcceleration(cn));
				Car_SetCarAxlesWeight(carnum, j, tempWeight - InputWeight);
				Car_SetCarAxlesType(carnum, j, Car_GetCarAxlesType(cn, i));
				Car_SetCarAxlesSpace(carnum, j, Car_GetCarAxlesSpace(cn, i));
				j++;
			}
			k = i + 1;
		} else if (carnum == cn + 1) {
			Car_SetCarAxlesWeight(carnum, j, Car_GetCarAxlesWeight(cn, k));
			Car_SetCarAxlesType(carnum, j, Car_GetCarAxlesType(cn, k));
			Car_SetCarAxlesSpace(carnum, j, Car_GetCarAxlesSpace(cn, k));
			Axle_Delete(cn, k);
			j++;
		}
	}
	Finishing();
	CarList_Change();
	wds_Post_SEM();
}
void ModfiyAxlesByWeight(int InputWeight) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	wds_Wait_SEM();
	int i = 0;
	int tempWeight = 0;
	int axle = 0;
	if (Car_GetNum() > 0) {
		if (InputWeight > Car_GetCarListWeight() || InputWeight <= 0) {
			wds_Post_SEM();
			return;
		}
		if (InputWeight <= Car_GetCarWeight(0)) {//拆车
			ModfiyCarAxlesByWeight(0, InputWeight);
		} else {
			do {
				tempWeight += Car_GetCarWeight(i);
				axle += Car_GetCarAxlesNum(i++);
			} while (tempWeight < InputWeight);
			ModifyAxlesNo(axle);//合并轴
			ModfiyCarAxlesByWeight(0, InputWeight);//拆分重量
		}
	}
	CarList_Change();
	wds_Post_SEM();
}
void AddAxleByIndex(int index, Wds_AxleInfo *Axle) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	wds_Wait_SEM();
	Axle_Insert(0, index);
	Car_SetCarAxlesType(0, index, Axle->TiresType);
	Car_SetCarAxlesWeight(0, index, Axle->AxleWeight);
	CarList_Change();
	wds_Post_SEM();
}
void RemoveAxleByIndex(int index) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	wds_Wait_SEM();
	Axle_Delete(0, index);
	CarList_Change();
	wds_Post_SEM();
}
void AddCarWeightInfo(Wds_CarWeightInfo *CarWeightInfo) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	wds_Wait_SEM();
	Car_Insert(0);
	Car_SetCarSpeed(0, CarWeightInfo->Speed);
	int i = 0;
	for (i = 0; i < CarWeightInfo->AxleNumber; i++) {
		if (i < MAX_CAR_AXLE) {
			Car_SetCarAxlesType(0, i, CarWeightInfo->AxleArry[i].TiresType);
			Car_SetCarAxlesWeight(0, i, CarWeightInfo->AxleArry[i].AxleWeight);
		} else {
			Axle_Insert(0, i);
		}
	}
	CarList_Change();
	wds_Post_SEM();
}
void AddTempCarInfo(int inputAxesNo)
{
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	LogCDev(LOG_INFOR,"添加车辆信息 轴数:%d",inputAxesNo);
	wds_Wait_SEM();
	Car_StackPush();
	
	Car_SetCarSpeed(0, 0);
	
	Car_SetCarAcceleration(0, 0);
	
	int i =0;
	for(i=0;i<inputAxesNo;i++)
	{
	
		Car_SetCarAxlesWeight(0, i, 0);
	
		Car_SetCarAxlesType(0, i, 1);
	
		Car_SetCarAxlesSpace(0, i, 0);
	
	}
	
	CarList_Change();
	wds_Post_SEM();
}

void ModifyCarAxlesByNo(int inputAxesNo) {
	echo_debug_WDS_Dll("wds_Wait_SEM  Call!!!-----------");
	LogCDev(LOG_INFOR,"修正车辆轴数 轴数:%d",inputAxesNo);
	wds_Wait_SEM();
	if (Car_GetNum() > 0 && inputAxesNo>1 ) {
		int i=0,Weight=0;
		int c = Car_GetCarAxlesNum(0);
		if(c<inputAxesNo)//加轴
		{
			Weight = Car_GetCarAxlesWeight(0,c-1);
			for(i=c;i<inputAxesNo;i++)
			{
				Axle_Insert(0,i);
				Car_SetCarAxlesWeight(0, i, 0);
				Car_SetCarAxlesType(0, i, Car_GetCarAxlesType(0, c-1));
				Car_SetCarAxlesSpace(0, i, Car_GetCarAxlesSpace(0, c-1));
			}
		}
		else if(c>inputAxesNo)//合轴
		{
			for(i=c-1;i>=inputAxesNo;i--)
			{
				Weight += Car_GetCarAxlesWeight(0,i);
				Axle_Delete(0,i);
			}
			Weight += Car_GetCarAxlesWeight(0,i);
			Car_SetCarAxlesWeight(0,i,Weight);
		}
	}
	CarList_Change();
	wds_Post_SEM();
}
