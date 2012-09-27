// ***************************************************************
//  CarKind   version:  1.0   ��  date:  11/7/2008
//  -------------------------------------------------------------
//  ������Ϣ���ʽӿڣ�
//  -------------------------------------------------------------
//  author����־��
// ------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************

#include "LocalIncludeFile.h"

struct PARAM_HEAD  CarKindHead;
/*****************************************************************************
*�����ñ��е�һ�м�¼ �� �ṹ�������һ��Ԫ����
*****************************************************************************/
int ParseCarKindRecord(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&CarKindRecord[Rowindex],RecordStr,sizeof(struct CARKIND_PARA));	
	return 0;
}

/*************************************************************************
*�������������ļ����ڴ���
*************************************************************************/
int LoadCarKindRecord(int IsFirst)
{	
	int ret = LoadRecord(PARACARKINDLIST_FILE,&CarKindHead ,LENGHT_CARKIND_PARA,ParseCarKindRecord,FRAE,IsFirst);	
	SetG_Lane_carKindCount(atoi(CarKindHead.Recordcount ));
	return ret;
}

/***********************************************************************
*��Ӧ���ֵ��շѼ��㷽ʽ
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
//��ü۸�������
float   GetCarKindChargeComputeMethod_byindex(int  index)
{   
	char  CMethod[40];
	memset(CMethod,0x00,40);
	strncpy(CMethod,CarKindRecord[index].carKindChargeComputeMethod,sizeof(CarKindRecord[index].carKindChargeComputeMethod));
	//echoic("GetCarKindChargeComputeMethod_byindex:::%s %f",CMethod,atof(CMethod));
	return atof(CMethod);
}
char   CarKeyName[9];
//ȡ��ָ�������ļ�����
char  *   GetCarKindKeyName(int  index)
{   
	memset(    CarKeyName,0x00,9);
	strncpy(    CarKeyName,CarKindRecord[index].carkindHandl,sizeof(CarKindRecord[index].carkindHandl));
	return     CarKeyName;  
}
char   CarKindNameByIndex[9];
//���ָ�������ĳ�������
char  *   GetCarKindNameByIndex(int  index)
{   
	memset(    CarKindNameByIndex,0x00,9);
	strncpy(    CarKindNameByIndex,CarKindRecord[index].carKindExplian,sizeof(CarKindRecord[index].carKindExplian));
	return     CarKindNameByIndex;  
}

 //���ָ�������ĳ���֧����ʽ
char   GetCarKindCharge(int  index)
{   
	//echoic("index %d ,  carkindcharge %s %c ",index,CarKindRecord[index].carKindCharge,CarKindRecord[index].carKindCharge[0]);
    return   CarKindRecord[index].carKindCharge[0]; 
}

//���ָ�������ĳ����ַ�
char     GetCarKindChar(int  index)
{   
	 return CarKindRecord[index].carKineNumber[0]; 
}
char     GetNeedAskTCO(int  index)
{   
	 return CarKindRecord[index].AskTCO; 
}
//����������ó���intֵ
int      GetCarKindInt(int  index)
{   
	char carkin[3];
	memset(carkin ,0x00,3);
	strncpy(carkin,CarKindRecord[index].carKindId,sizeof(CarKindRecord[index].carKindId));
	 return atoi(carkin);
}
char   CarKindName[9];  
//���ñ��м�ֵ��Ӧ���֣��ú����ɼ�ֵ��ó���
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
//���������Ҫ��ʾ�ĳ��ֺͰ�����ʾ�ַ���
char *GetCarKeyNames(void)
{   
	int i;
	memset(charKindMSG,0x00,400);
	sprintf(charKindMSG,"��ʾ��\n");
	for (i=0;i<atoi(CarKindHead.Recordcount );i++)
	{
		if (0!=strncmp("0 ", CarKindRecord[i].keyboardValue,sizeof(CarKindRecord[i].keyboardValue)))
		{
			if (0!=strncmp("        ", CarKindRecord[i].carkindHandl,sizeof(CarKindRecord[i].carkindHandl)))
			{
				sprintf(charKindMSG,"%s����%s��������%s\n",trim(charKindMSG), trim(GetCarKindKeyName(i)),trim(GetCarKindNameByIndex(i)));
			
			}
		}
	}
	return  charKindMSG;
} 

/*********************************************************************
*�ó����Ƿ����һ��ȷ��
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
*�ɳ��ֶ�Ӧ�ļ�ֵ��ȡͼƬ����
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
*Ʊ�ݱ�ǣ��Ƿ���Ʊ��
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
*Ʊ�ݱ�ǣ��Ƿ���Ʊ��
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
//ʹ���������Ʊ�ݴ�ӡ��ǡ� 
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
