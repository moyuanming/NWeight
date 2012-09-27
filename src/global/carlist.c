#include <stdlib.h>
#include "list.h"
#include "carlist.h"
#include "LocalIncludeFile.h"
typedef struct axle {
	int type;
	int weight;
	int Space;
} TAxle;
typedef TAxle * PTAxle;
typedef struct car {
	PTList axles;
	int Overload;
	int Speed;
	int Acceleration;
} TCar;
typedef TCar * PTCar;

PTList CarList = NULL;
PTCar TempCar = NULL;
CarList_Change_Event_Func CarList_Change_Event = NULL;

void Set_CarList_Change_Event(CarList_Change_Event_Func func) {
	CarList_Change_Event = func;
}
void CarList_Change(void) {
	if (CarList_Change_Event != NULL) {
		CarList_Change_Event();
	}

}

PTAxle Axle_Create(void) {
	PTAxle axle = (PTAxle) malloc(sizeof(TAxle));
	axle->Space = 0;
	axle->type = 0;
	axle->weight = 0;
	return axle;
}
void Axle_Destroy(PTAxle axle) {

	if (axle != NULL) {

		free(axle);
		axle = NULL;

	}

}
PTAxle Axle_Add(PTCar car) {
	PTAxle axle = Axle_Create();
	PTListItem pli = Queue_Push(car->axles, (void *) axle);
	pli->destroy_func = (TItem_Destroy_Func) Axle_Destroy;
	return axle;
}
PTCar Car_Create(void) {
	PTCar car = (PTCar) malloc(sizeof(TCar));

	car->axles = List_Create();
	car->Acceleration = 0;
	car->Overload = 0;
	car->Speed = 0;
	return car;
}
void Car_Destroy(PTCar car) {

	if (car != NULL) {

		List_Destroy(car->axles);

		free(car);
		car = NULL;

	}
}
void CarListInit(void) {
	if (CarList == NULL) {
		CarList = List_Create();
	}
}
void CarListDestroy() {
	if (CarList != NULL) {
		List_Destroy(CarList);
	}
	if(TempCar!=NULL){
		Car_Destroy(TempCar);
	}
}
PTCar Car_Add(void) {
	PTCar car = Car_Create();
	PTListItem pli = Queue_Push(CarList, (void *) car);
	pli->destroy_func = (TItem_Destroy_Func) Car_Destroy;
	return car;
}
int Car_Insert(int carnum) {
	int c = List_GetIndex(CarList, carnum);
	if (c < 0 && CarList->length != carnum) {
		return FALSE;
	}
	PTCar car = Car_Create();
	PTListItem pli = List_Insert(CarList, (void *) car, carnum);
	pli->destroy_func = (TItem_Destroy_Func) Car_Destroy;
	return TRUE;
}
void Car_Delete(int carnum) {
	List_Delete(CarList, carnum);
}
PTCar Car_Get(int i) {
	CarListInit();
	PTListItem pli = List_GetItem(CarList, i);
	if (pli != NULL) {
		return (PTCar) pli->item;
	}
	return NULL;
}
int Axle_Insert(int carnum, int i) {
	PTCar car = Car_Get(carnum);
	if (car == NULL) {
		return FALSE;
	}
	int c = List_GetIndex(car->axles, i);
	if (c < 0 && car->axles->length != i) {
		return FALSE;
	}
	PTAxle axle = Axle_Create();
	PTListItem pli = List_Insert(car->axles, (void *) axle, i);
	pli->destroy_func = (TItem_Destroy_Func) Axle_Destroy;
	return TRUE;
}
void Axle_Delete(int carnum, int i) {
	PTCar car = Car_Get(carnum);
	if (car == NULL) {
		return;
	}
	List_Delete(car->axles, i);
}
PTAxle Car_GetAxles(PTCar car, int i) {
	if (car != NULL) {
		PTListItem pli = List_GetItem(car->axles, i);
		if (pli != NULL) {
			return ((PTAxle) pli->item);
		}
	}
	return NULL;
}
int Car_GetAxlesType(PTAxle axle) {
	if (axle == NULL)
		return 0;
	return axle->type;
}
void Car_SetAxlesType(PTAxle axle, int Type) {
	if (axle == NULL)
		return;
	axle->type = Type;
}
int Car_GetAxlesSpace(PTAxle axle) {
	if (axle == NULL)
		return 0;
	return axle->Space;
}
void Car_SetAxlesSpace(PTAxle axle, int Space) {
	if (axle == NULL)
		return;
	axle->Space = Space;
}
int Car_GetAxlesWeight(PTAxle axle) {
	if (axle == NULL)
		return 0;
	return axle->weight;
}
void Car_SetAxlesWeight(PTAxle axle, int Weight) {
	
	if (axle == NULL)
		return;
	axle->weight = Weight;
}
int Car_GetAxlesNum(PTCar car) {
	if (car == NULL)
		return 0;
	return car->axles->length;
}
int Car_GetOverload(PTCar car) {
	if (car == NULL)
		return 0;
	return car->Overload;
}
void Car_SetOverload(PTCar car, int Overload) {
	if (car == NULL)
		return;
	car->Overload = Overload;
}
int Car_GetSpeed(PTCar car) {
	if (car == NULL)
		return 0;
	return car->Speed;
}
void Car_SetSpeed(PTCar car, int Speed) {
	if (car == NULL)
		return;
	car->Speed = Speed;
}
int Car_GetAcceleration(PTCar car) {
	if (car == NULL)
		return 0;
	return car->Acceleration;
}
void Car_SetAcceleration(PTCar car, int Acceleration) {
	if (car == NULL)
		return;
	car->Acceleration = Acceleration;
}
int Car_GetNum() {
	if (CarList == NULL)
		return 0;
	return CarList->length;
}
PTAxle Car_SetAxles(PTCar car, int i) {
	
	PTListItem pli = List_GetItem(car->axles, i);
	
	if (pli == NULL && i == Car_GetAxlesNum(car)) {
	
		return Axle_Add(car);
	} else {
	
		return (PTAxle) pli->item;
	}
	
	return NULL;
}
PTCar Car_Set(int i) {
	
	CarListInit();
	PTListItem pli = List_GetItem(CarList, i);
	
	if (pli == NULL && i == Car_GetNum()) {
	
		return Car_Add();
	} else {
	
		return (PTCar) pli->item;
	}
	
	return NULL;
}
int Car_GetCarOverload(int carnum) {
	return Car_GetOverload(Car_Get(carnum));
}
void Car_SetCarOverload(int carnum, int Overload) {
	Car_SetOverload(Car_Set(carnum), Overload);
}
int Car_GetCarSpeed(int carnum) {
	return Car_GetSpeed(Car_Get(carnum));
}
void Car_SetCarSpeed(int carnum, int Speed) {
	Car_SetSpeed(Car_Set(carnum), Speed);
}
int Car_GetCarAcceleration(int carnum) {
	return Car_GetAcceleration(Car_Get(carnum));
}
void Car_SetCarAcceleration(int carnum, int Acceleration) {
	Car_SetAcceleration(Car_Set(carnum), Acceleration);
}
int Car_GetCarAxlesNum(int carnum) {
	return Car_GetAxlesNum(Car_Get(carnum));
}

int Car_GetCarAxlesType(int carnum, int i) {
	return Car_GetAxlesType(Car_GetAxles(Car_Get(carnum), i));
}
void Car_SetCarAxlesType(int carnum, int i, int type) {
	Car_SetAxlesType(Car_SetAxles(Car_Set(carnum), i), type);
}

int Car_GetCarAxlesWeight(int carnum, int i) {
	return Car_GetAxlesWeight(Car_GetAxles(Car_Get(carnum), i));
}
void Car_SetCarAxlesWeight(int carnum, int i, int Weight) {
	Car_SetAxlesWeight(Car_SetAxles(Car_Set(carnum), i), Weight);
}

int Car_GetCarAxlesSpace(int carnum, int i) {
	return Car_GetAxlesSpace(Car_GetAxles(Car_Get(carnum), i));
}
void Car_SetCarAxlesSpace(int carnum, int i, int Space) {
	Car_SetAxlesSpace(Car_SetAxles(Car_Set(carnum), i), Space);
}
void Car_AxlesClear(PTCar car) {
	List_Destroy(car->axles);
	car->axles = List_Create();
}
void Car_CarAxlesClear(int carnum) {
	Car_AxlesClear(Car_Get(carnum));
}

void Car_QueuePop(void) {
	CarListInit();
	Queue_Pop(CarList);
}
void Car_StackPop(void) {
	CarListInit();
	Stack_Pop(CarList);
}
void Car_QueuePush(void) {
	CarListInit();
	Queue_Push(CarList, (void *)Car_Create());
}
void Car_StackPush(void) {
	CarListInit();
	Stack_Push(CarList, (void *)Car_Create());
}

int Car_GetCarListAxlesNum(void) {
	int num = 0;
	PTCar car = NULL;
	PTListItem pli = CarList->first;
	while (pli != NULL) {
		car = (PTCar) (pli->item);
		if (car != NULL) {
			num += car->axles->length;
		}
		pli = pli->next;
	}
	return num;
}
int Car_GetWeight(PTCar car) {
	if (car == NULL) {
		return 0;
	}
	if (car->axles == NULL) {
		return 0;
	}
	int weight = 0;
	PTAxle axle = NULL;
	PTListItem pli = car->axles->first;
	while (pli != NULL) {
		axle = (PTAxle) (pli->item);
		if (car != NULL) {
			weight += axle->weight;
		}
		pli = pli->next;
	}
	return weight;
}
int Car_GetCarWeight(int carnum) {
	return Car_GetWeight(Car_Get(carnum));
}
int Car_GetCarListWeight(void) {
	int weight = 0;
	PTListItem pli = CarList->first;
	while (pli != NULL) {
		weight += Car_GetWeight((PTCar) (pli->item));
		pli = pli->next;
	}
	return weight;
}


////////////////////////////////////////////////////
int TempCar_GetCarOverload(){
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetOverload(TempCar);
}
void TempCar_SetCarOverload( int Overload) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	Car_SetOverload(TempCar, Overload);
}
int TempCar_GetCarSpeed() {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetSpeed(TempCar);
}
void TempCar_SetCarSpeed( int Speed) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	Car_SetSpeed(TempCar, Speed);
}
int TempCar_GetCarAcceleration() {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetAcceleration(TempCar);
}
void TempCar_SetCarAcceleration( int Acceleration) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	Car_SetAcceleration(TempCar, Acceleration);
}
int TempCar_GetCarAxlesNum() {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetAxlesNum(TempCar);
}
int TempCar_GetCarAxlesType( int i) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetAxlesType(Car_GetAxles(TempCar, i));
}
void TempCar_SetCarAxlesType( int i, int type) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	Car_SetAxlesType(Car_SetAxles(TempCar, i), type);
}
int TempCar_GetCarAxlesWeight( int i) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetAxlesWeight(Car_GetAxles(TempCar, i));
}
void TempCar_SetCarAxlesWeight( int i, int Weight) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	Car_SetAxlesWeight(Car_SetAxles(TempCar, i), Weight);
}
int TempCar_GetCarAxlesSpace( int i) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetAxlesSpace(Car_GetAxles(TempCar, i));
}
void TempCar_SetCarAxlesSpace( int i, int Space) {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	Car_SetAxlesSpace(Car_SetAxles(TempCar, i), Space);
}
void TempCar_CarAxlesClear() {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	Car_AxlesClear(TempCar);
}
int TempCar_GetCarWeight() {
	if(TempCar == NULL)
	{
		TempCar = Car_Create();
	}
	return Car_GetWeight(TempCar);
}
