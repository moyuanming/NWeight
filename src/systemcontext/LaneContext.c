// ***************************************************************
//  systemContext   version:  1.0   ·  date: 5/5/2008
//  -------------------------------------------------------------
//  车道上下文信息！
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
#include "LocalIncludeFile.h"

/*******************************************************************************/
//车道车型数量 在读配置表的时候得到；
/*******************************************************************************/
char G_SaveBeforTipOne[20];
void InitG_SaveBeforTipOne(void)
{	
    memset(G_SaveBeforTipOne,0x00,20);	
}
char *GetG_SaveBeforTipOne()
{	
	return G_SaveBeforTipOne;
}
void SetG_SaveBeforTipOne(char * inputG_SaveBeforTipOne)
{	
	    strcpy(G_SaveBeforTipOne,inputG_SaveBeforTipOne);	
}

/*******************************************************************************/
//
/*******************************************************************************/

char G_SaveBeforTipTwo[20];
void InitG_SaveBeforTipTwo(void)
{	
    memset(G_SaveBeforTipTwo,0x00,20);	
}
char *GetG_SaveBeforTipTwo()
{	
	return G_SaveBeforTipTwo;
}
void SetG_SaveBeforTipTwo(char * inputG_SaveBeforTipTwo)
{	
    strcpy(G_SaveBeforTipTwo,inputG_SaveBeforTipTwo);	
}


/*******************************************************************************/
//车种数量 在读配置表的时候得到
/*******************************************************************************/

int G_Lane_carKindCount;	
void SetG_Lane_carKindCount(int value)
{	
	G_Lane_carKindCount=value;
}

int GetG_Lane_carKindCount(void)
{	
	return  G_Lane_carKindCount;
}
/*******************************************************************************/
//当前车道车型表ID
/*******************************************************************************/

int G_Current_LaneCarTypeTableID = 0;
void SetG_Current_LaneCarTypeTableID(int value)
{	
	G_Current_LaneCarTypeTableID=value;
}

int GetG_Current_LaneCarTypeTableID(void)
{	
	return  G_Current_LaneCarTypeTableID;
}
/*******************************************************************************/
//车种表ID
/*******************************************************************************/
int G_Current_CarKindID=0;
void SetG_Current_CarKindID(int value)
{	
	G_Current_CarKindID=value;
}

int GetG_Current_CarKindID(void)
{	
	return  G_Current_CarKindID;
}
 
int G_IsTuoche = 0;
void SetG_IsTuoche(int value)
{	
	G_IsTuoche=value;
}

int GetG_IsTuoche(void)
{	
	return  G_IsTuoche;
}
int G_IsChangche = 0;
void SetG_IsChangche(int value)
{
	G_IsChangche = value;
}
int GetG_IsChangche(void)
{
	return G_IsChangche;
}

int G_IsTeZhongChe = 0;
void SetG_IsTeZhongChe(int value)
{
	G_IsTeZhongChe = value;
	SetWeightCarClass(G_IsTeZhongChe?WeightCarClassTruck:WeightCarClassTruckSpecialVehicles);
}
int GetG_IsTeZhongChe(void)
{
	return G_IsTeZhongChe;
}
/*******************************************************************************/
//
/*******************************************************************************/
int G_IsTuoCheUp = 0;
void SetG_IsTuoCheUp(int value)
{	
	G_IsTuoCheUp=value;
}

int GetG_IsTuoCheUp(void)
{	
	return  G_IsTuoCheUp;
}

