// ***************************************************************
//  FareRecordTable   version:  1.0   ·  date:  29/5/2008
//  -------------------------------------------------------------
//  费率表访问接口！
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"

struct PARAM_HEAD FareHead;
struct MSG_FARELIST  FareRecordTable[MAXPAEAMRECORDS];
#define FAREREADSTRLENGTH 126
int RowsCount = 0;
int ParseRecordFare(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&FareRecordTable[Rowindex],RecordStr,sizeof(struct MSG_FARELIST));
	RowsCount = atoi(FareHead.Recordcount); 
	return 0;
}


int LoadFareRecord(int IsFirst)
{	
	int ret = LoadRecord(PARAFARELIST_FILE,&FareHead,FAREREADSTRLENGTH,ParseRecordFare,FRAE,IsFirst);	
	strncpy(GetMsgRevision()->FareListVer,FareHead.VerNo,2);	
	return ret;

}
char tempVerNo[3];
char * GetFareVersion(void)
{	
	memset(tempVerNo,0x00,sizeof(tempVerNo));	
	strncpy(tempVerNo,FareHead.VerNo,sizeof(FareHead.VerNo));	
	return tempVerNo;
}

 

/*****************************************************************
从惠率表读出 对应车型的  惠率值
*********************************************************************/
int  GetFareValue_extracted(int InputVehiClass,   int i, char * FareSum )
{
	int FareValue;
	switch (InputVehiClass)
	{
		case 0:
			strncpy(FareSum,FareRecordTable[i].Type1Fare,10);   
			FareValue = atoi(FareSum);  
			break;
		case 1:
			strncpy(FareSum,FareRecordTable[i].Type2Fare,10);   
			FareValue = atoi(FareSum);  
			break;
		case 2:
			strncpy(FareSum,FareRecordTable[i].Type3Fare,10);   
			FareValue = atoi(FareSum);  
			break;
		case 3:
			strncpy(FareSum,FareRecordTable[i].Type4Fare,10);   
			FareValue = atoi(FareSum);  
			break;
		case 4:
			strncpy(FareSum,FareRecordTable[i].Type5Fare,10);   
			FareValue = atoi(FareSum);  
			break;
		case 5:
			strncpy(FareSum,FareRecordTable[i].Type6Fare,10);   
			FareValue = atoi(FareSum);  
			break;
		case 6:
			strncpy(FareSum,FareRecordTable[i].Type7Fare,10);   
			FareValue = atoi(FareSum);  
			break;
		default:
			FareValue=-1;
			break;
	}
	return FareValue;
}
int GetFareValue(int InputVehiClass)
{	
	int FareValue=-1;
	int i ;
	char FareSum[5];
	char  lanenox[4];
	char lanenoa[4];
	memset(lanenoa,0x00,4);
	memset(lanenox,0x00,4);
	strncpy(lanenoa,GetLanConfigLaneNo(),3);
	strncpy(lanenox,(char*)&lanenoa[1],2);
	FareSum[4]=0x00;
	  
	for (i=0;i<RowsCount;i++)
	{
		char nowfarelane[4];
		memset(nowfarelane,0x00,4);
		strncpy(nowfarelane,   (char*)&FareRecordTable[i].ExitLaneNo[1],2);
		echoic("当前车道号%s 当前费率的车道号:%s i=<%d>,count=<%d>",lanenox,nowfarelane,i,RowsCount);
		if (atoi(lanenox) >=atoi(nowfarelane) || i==0)
		{
			echoic("OK");
			FareValue= GetFareValue_extracted(InputVehiClass, i, FareSum);

		}
	}
	echoic("读取到费率%d",FareValue);
	return FareValue;
}

