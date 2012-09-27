#ifndef __CarList_H__
#define __CarList_H__

//#ifndef NULL
//#define NULL 0
//#endif




typedef void (*CarList_Change_Event_Func)(void);
void CarListInit(void);
void CarListDestroy(void);
void Car_QueuePop(void);
void Car_StackPop(void);

int Car_GetNum(void);
int Car_GetCarOverload(int carnum);
void Car_SetCarOverload(int carnum, int Overload);
int Car_GetCarSpeed(int carnum);
void Car_SetCarSpeed(int carnum, int Speed);
int Car_GetCarAcceleration(int carnum);
void Car_SetCarAcceleration(int carnum, int Acceleration);
int Car_GetCarAxlesNum(int carnum);
int Car_GetCarAxlesType(int carnum, int i);
void Car_SetCarAxlesType(int carnum, int i, int type);
int Car_GetCarAxlesWeight(int carnum, int i);
void Car_SetCarAxlesWeight(int carnum, int i, int weight);
int Car_GetCarAxlesSpace(int carnum, int i);
void Car_SetCarAxlesSpace(int carnum, int i, int Space);
void Car_CarAxlesClear(int carnum);
void Car_QueuePush(void);
void Car_StackPush(void);

int Car_Insert(int carnum);
int Axle_Insert(int carnum,int i);
void Axle_Delete(int carnum,int i);
void Car_Delete(int carnum);

int Car_GetCarListAxlesNum(void);
int Car_GetCarWeight(int carnum);
int Car_GetCarListWeight(void);

void Set_CarList_Change_Event(CarList_Change_Event_Func func) ;
void CarList_Change(void) ;

////TempCar
int TempCar_GetCarOverload(void);
void TempCar_SetCarOverload( int Overload);
int TempCar_GetCarSpeed(void);
void TempCar_SetCarSpeed( int Speed);
int TempCar_GetCarAcceleration(void);
void TempCar_SetCarAcceleration( int Acceleration);
int TempCar_GetCarAxlesNum(void) ;
int TempCar_GetCarAxlesType( int i);
void TempCar_SetCarAxlesType( int i, int type) ;
int TempCar_GetCarAxlesWeight( int i);
void TempCar_SetCarAxlesWeight( int i, int Weight);
int TempCar_GetCarAxlesSpace( int i);
void TempCar_SetCarAxlesSpace( int i, int Space) ;
void TempCar_CarAxlesClear(void);
int TempCar_GetCarWeight(void);
#endif
