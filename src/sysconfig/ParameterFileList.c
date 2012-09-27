// ***************************************************************
//  ParameterFileList   version:  1.0   ·  date: 12/28/2007
//  -------------------------------------------------------------
//  配置参数列表
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"

struct ParameterFileList CurrentParameterFileList;
struct ParameterFileList *GetParameterFileList(void)
{	
    return &CurrentParameterFileList;
}

void InitParameterFileList(void )
{	
    memset((char *)&CurrentParameterFileList,' ',sizeof(struct ParameterFileList));	
}

void LoadGetParameterFileList(void)
{	
	echoic("正在装载参数表信息...");
    LoadIniFile(FILENAME_PARAMETER_FILE_LIST);	
    InitParameterFileList();	
    strcpy(CurrentParameterFileList.COLLECT,readItemInIniFile("COLLECT"));	
    strcpy(CurrentParameterFileList.FARELIST,readItemInIniFile("FARELIST"));	
    strcpy(CurrentParameterFileList.YHKLIST,readItemInIniFile("YHKLIST"));	
	strcpy(CurrentParameterFileList.YHRATE,readItemInIniFile("YHRATE"));    
	strcpy(CurrentParameterFileList.YPKLIST,readItemInIniFile("YPKLIST"));  
	strcpy(CurrentParameterFileList.CARKIND_CONF,readItemInIniFile("CARKIND_CONF"));    
	strcpy(CurrentParameterFileList.JOUCODE,readItemInIniFile("JOUCODE"));  
	strcpy(CurrentParameterFileList.SVRCARDLIST,readItemInIniFile("SVRCARDLIST"));  
	strcpy(CurrentParameterFileList.CONSTANT,readItemInIniFile("CONSTANT")); 
	echoic("装载参数表信息完成");
}

