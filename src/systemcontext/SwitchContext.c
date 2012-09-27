// ***************************************************************
//  systemContext   version:  1.0   ·  date: 5/5/2008
//  -------------------------------------------------------------
//  开关量信号状态上下文信息
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
#include "LocalIncludeFile.h"

/******************************/
// 雨棚灯是否被打开过
/******************************/
BOOL   g_bYuPengOpened=F;
void Setg_bYuPengOpened(BOOL  value)
{	
	g_bYuPengOpened=value;
}
int Getg_bYuPengOpened(void)
{	
	return g_bYuPengOpened;
}
/*******************************************************************************/
//车道工作状态值
/*******************************************************************************/
//车道封闭 开启标志
volatile BOOL  g_bCheDaoStatus = TRUE;

void Setg_bCheDaoStatus(BOOL  value)
{	
	g_bCheDaoStatus=value;
}


int Getg_bCheDaoStatus(void)
{	
	return g_bCheDaoStatus;
}

/*******************************************************************************/
// 工作状态值
/*******************************************************************************/
volatile BOOL  g_bReLogin = FALSE;

void Setg_bReLogin(BOOL  value)
{	
	g_bReLogin=value;
}


int Getg_bReLogin(void)
{	
	return g_bReLogin;
}

/*******************************************************************************/
//违章标志
/*******************************************************************************/

volatile BOOL   g_bWeiZhang = FALSE;

void Setg_bWeiZhang(BOOL  value)
{	
	g_bWeiZhang=value;
}


int Getg_bWeiZhang(void)
{	
	return g_bWeiZhang;
}

/*******************************************************************************/
//
/*******************************************************************************/
