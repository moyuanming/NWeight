// ***************************************************************
//  systemContext   version:  1.0   ��  date: 5/5/2008
//  -------------------------------------------------------------
//  �������ź�״̬��������Ϣ
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
#include "LocalIncludeFile.h"

/******************************/
// ������Ƿ񱻴򿪹�
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
//��������״ֵ̬
/*******************************************************************************/
//������� ������־
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
// ����״ֵ̬
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
//Υ�±�־
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
