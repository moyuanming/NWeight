// ***************************************************************
//  CarKind   version:  1.0   ·  date:  11/7/2008
//  -------------------------------------------------------------
//  车种信息访问接口！
//  -------------------------------------------------------------
//  author：刘志鹏
// ------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************

#include "LocalIncludeFile.h"

struct PARAM_HEAD  CarKindHead;
/*****************************************************************************
*读配置表中的一行记录 到 结构体数组的一个元素中
*****************************************************************************/
int ParseCarKindRecord(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&CarKindRecord[Rowindex],RecordStr,sizeof(struct CARKIND_PARA));	
	return 0;
}

/*************************************************************************
*加载整个配置文件到内存中
*************************************************************************/
int LoadCarKindRecord(int IsFirst)
{	
	int ret = LoadRecord(PARACARKINDLIST_FILE,&CarKindHead ,LENGHT_CARKIND_PARA,ParseCarKindRecord,FRAE,IsFirst);	
	SetG_Lane_carKindCount(atoi(CarKindHead.Recordcount ));
	return ret;
}

/***********************************************************************
*对应车种的收费计算方式
***********************************************************************/
float   GetCarKindChargeComputeMethod(int  keyboardvalue)
{	
    float  ComputeMethod=0.0;
	char  CMethod[3];
	int i;
	char KeyValue[2];
	sprintf(KeyValue,"%d",keyboardvalue);	
	for(i=0;i<atoi(CarKindHead.Recordcount );i++)
	{	
		if(0==strncmp(KeyValue, CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{	
			strncpy(CMethod,CarKindRecord[i].carKindChargeComputeMethod,sizeof(CarKindRecord[i].carKindChargeComputeMethod));	
			ComputeMethod=atof(CMethod);	
		}
	}

	return  ComputeMethod;
}
//获得价格计算乘数
float   GetCarKindChargeComputeMethod_byindex(int  index)
{   
	char  CMethod[40];
	memset(CMethod,0x00,40);
	strncpy(CMethod,CarKindRecord[index].carKindChargeComputeMethod,sizeof(CarKindRecord[index].carKindChargeComputeMethod));
	//echoic("GetCarKindChargeComputeMethod_byindex:::%s %f",CMethod,atof(CMethod));
	return atof(CMethod);
}
char   CarKeyName[9];
//取得指定索引的键名称
char  *   GetCarKindKeyName(int  index)
{   
	memset(    CarKeyName,0x00,9);
	strncpy(    CarKeyName,CarKindRecord[index].carkindHandl,sizeof(CarKindRecord[index].carkindHandl));
	return     CarKeyName;  
}
char   CarKindNameByIndex[9];
//获得指定索引的车种名称
char  *   GetCarKindNameByIndex(int  index)
{   
	memset(    CarKindNameByIndex,0x00,9);
	strncpy(    CarKindNameByIndex,CarKindRecord[index].carKindExplian,sizeof(CarKindRecord[index].carKindExplian));
	return     CarKindNameByIndex;  
}

 //获得指定索引的车种支付方式
char   GetCarKindCharge(int  index)
{   
	//echoic("index %d ,  carkindcharge %s %c ",index,CarKindRecord[index].carKindCharge,CarKindRecord[index].carKindCharge[0]);
    return   CarKindRecord[index].carKindCharge[0]; 
}

//获得指定索引的车种字符
char     GetCarKindChar(int  index)
{   
	 return CarKindRecord[index].carKineNumber[0]; 
}
char     GetNeedAskTCO(int  index)
{   
	 return CarKindRecord[index].AskTCO; 
}
//根据索引获得车种int值
int      GetCarKindInt(int  index)
{   
	char carkin[3];
	memset(carkin ,0x00,3);
	strncpy(carkin,CarKindRecord[index].carKindId,sizeof(CarKindRecord[index].carKindId));
	 return atoi(carkin);
}
char   CarKindName[9];  
//配置表中键值对应车种，该函数由键值获得车种
char *GetCarKindName(int  keyboardvalue)
{	
	char KeyValue[2];
	int i;
	memset(CarKindName,' ',9);	
	CarKindName[9]='\0';
	sprintf(KeyValue,"%d",keyboardvalue);	
	for(i=0;i<atoi(CarKindHead.Recordcount );i++)
	{	
		if(0==strncmp(KeyValue, CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{	
			strncpy(CarKindName,CarKindRecord[i].carKindExplian,sizeof(CarKindRecord[i].carKindExplian));	
		}
	}
	return  CarKindName;
} 

char   charKindMSG[400]; 
//获得所有需要显示的车种和按键提示字符串
char *GetCarKeyNames(void)
{   
	int i;
	memset(charKindMSG,0x00,400);
	sprintf(charKindMSG,"提示：\n");
	for (i=0;i<atoi(CarKindHead.Recordcount );i++)
	{
		if (0!=strncmp("0 ", CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{
			if (0!=strncmp("        ", CarKindRecord[i].carkindHandl,sizeof(CarKindRecord[i].carkindHandl)))
			{
				sprintf(charKindMSG,"%s按【%s】键处理%s\n",trim(charKindMSG), trim(GetCarKindKeyName(i)),trim(GetCarKindNameByIndex(i)));
			
			}
		}
	}
	return  charKindMSG;
} 

/*********************************************************************
*该车种是否采用一次确认
*********************************************************************/
int  GetOnceOk(int  keyboardval)
{	
    int  IsOnceOk=-1;
	char OnceOk[2];
	int i;
	char KeyValue[2];
	memset(OnceOk,' ',2);	
	OnceOk[2]='\0';
	sprintf(KeyValue,"%d",keyboardval);	
	for(i=0;i<atoi(CarKindHead.Recordcount );i++)
	{	
		if(0==strncmp(KeyValue, CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{	
			strncpy(OnceOk,CarKindRecord[i].onceOk,sizeof(CarKindRecord[i].onceOk));
			IsOnceOk=atoi(OnceOk);	     
		}
	}
	return  IsOnceOk;
}


/*********************************************************************
*由车种对应的键值获取图片索引
*********************************************************************/
int GetImageIndex(int  keyboardvalue)
{	
	int index=-1;
	char KeyValue[2];
	char strindex[2];
	int i;
	strindex[2]='\0';
	sprintf(KeyValue,"%d",keyboardvalue);	
	for(i=0;i<atoi(CarKindHead.Recordcount );i++)
	{	
		if(0==strncmp(KeyValue, CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{	
			strncpy(strindex,CarKindRecord[i].imageIndex,sizeof(CarKindRecord[i].imageIndex));	
			index=atoi(strindex);	
		}
	}
	return  index;
}


/****************************************************************
*票据标记，是否有票据
*****************************************************************/
int  GetBillFlag(int  keyboardvalue)
{	
	int Flag=-1;
	char KeyValue[2];
	int i;
	sprintf(KeyValue,"%d",keyboardvalue);	
	for(i=0;i<atoi(CarKindHead.Recordcount );i++)
	{	
		if(0==strncmp(KeyValue, CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{	
			Flag=atoi(CarKindRecord[i].BillFlag);	
		}
	}
	return  Flag;
}


/****************************************************************
*票据标记，是否有票据
*****************************************************************/
int  GetCarKindIndex(int  keyboardvalue)
{	
	int Flag=-1;
	char KeyValue[2];
	int i;
	sprintf(KeyValue,"%d",keyboardvalue);	
	for(i=0;i<atoi(CarKindHead.Recordcount );i++)
	{	
		if(0==strncmp(KeyValue, CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{	
			Flag=i ;
			break;
		}
	}
	return  Flag;
}
//使用索引获得票据打印标记。 
int GetBillFlagbyIndex(int index)
{	
	if('1' == CarKindRecord[index].BillFlag[0] )
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
