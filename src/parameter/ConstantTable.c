
// ***************************************************************
//  ConstantTable   version:  1.0   ·  date: 12/09/2007
//  -------------------------------------------------------------
//  常量表访问接口！
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "LocalIncludeFile.h"
struct PARAM_HEAD ConStantHead;
CONSTANT_RECORD ConstantRecordTable[MAXPAEAMRECORDS];
#define CONSTANTSTRLENGTH 87
int HrecordIndex=-1;
int ArecordIndex=-1;
int CrecordIndex=-1;
int BrecordIndex=-1;
int ErecordIndex=-1;
int FrecordIndex=-1;
int GrecordIndex=-1;
int TrecordIndex=-1;
int TrecordCount=0;
int ParseRecordConstant(char *RecordStr,CONSTANT_RECORD * RecordTableRow,int index)
{
	memset(RecordTableRow,0x00,sizeof(CONSTANT_RECORD));
	RecordTableRow->ConstRecordType = RecordStr[0];
	switch(RecordTableRow->ConstRecordType)
	{
		case 'A':
			ArecordIndex=index;
			strncpy((char *)&(RecordTableRow->RecordA),&RecordStr[1],85);	
			break;
		case 'B':
			BrecordIndex=index;
		case 'C':
			CrecordIndex=index;
		case 'E':
			ErecordIndex=index;
		case 'F':
			FrecordIndex=index;
		case 'G':
			GrecordIndex=index;
		case 'H':
			HrecordIndex=index;
			strncpy((char *)&(RecordTableRow->RecordB),&RecordStr[1],100);	
			break;
		case 'T':
			TrecordIndex=index;
			TrecordCount++;
			strncpy((char *)&(RecordTableRow->RecordT),&RecordStr[1],67);
			break;
	}
	return 0;
	
}
int GetRateFareWeightDetectedWeight(void)
{
	return 0;
}

/***********************************************************************************************************
* 计重功能开关
* 返回zhi
* #define NotUseWeight						'0' //不使用计重功能
* #define NotUseWeightUseTruckKey			'1' //不使用计重功能 但使用货车键
* #define UseWeightUseTruckKeyNotFare		'2' //使用计重功能 但不用来计算费率
* #define FullWeight						'3' //使用全部计重功能
***********************************************************************************************************/
int GetWeightFunctions()
{
	return ConstantRecordTable[GrecordIndex].RecordB.Code[0];
}
//#define OLD312CalculateFare				'0' //老312计费方式
//#define NewCalculateFare					'1' //5型车计费
//
int GetCalculateFareMode()
{
	return ConstantRecordTable[GrecordIndex].RecordB.Code[1];
}
/***********************************************************************************************************
* 计重票据样式
* 返回值
* #define OLDPrintStyle						'0' //老样式
* #define NewPrintStyle						'1' //新样式
* #define PromptPrintStyle					'2' //提示单
* #define BothNewandPromptPrintStyl			'3' //新票样和提示单
***********************************************************************************************************/
int GetPrinterMode()
{
	return ConstantRecordTable[GrecordIndex].RecordB.Code[2];
}
//#define OLD312JaoKeCalculateFareMode				'0' //老312计费方式
//#define NewJaoKeCalculateFareMode					'1' //5型车计费
int GetJaoKeCalculateFareMode(void)
{
	return ConstantRecordTable[GrecordIndex].RecordB.Code[3];
}

static int GetConstValue(int InputConstIndex,int InputValueIndex)
{
	char RateToGetTheFareWeight[5];
	RateToGetTheFareWeight[4]=0x00;
	strncpy(RateToGetTheFareWeight,ConstantRecordTable[InputConstIndex].RecordB.Num[InputValueIndex],4);
	//printf("InputConstIndex %d InputValueIndex %d RateToGetTheFareWeight %d \n",InputConstIndex,InputValueIndex,atoi(RateToGetTheFareWeight));
	return atoi(RateToGetTheFareWeight);
}
//重量修正参数
int GetRateToGetTheFareWeightFromTheDetectedWeight(void)
{	
	return GetConstValue(GrecordIndex,0);
}
//重量的取整，单位10KG
int GetRoundingTheResultToFareWeight(void)
{
	return GetConstValue(GrecordIndex,1);
}
//货车最小重量 
//Eg:0500 表示位5吨
int GetMinimumWeightForFareWeight(void)
{
	return GetConstValue(GrecordIndex,2);
}
//基本费率
//Eg：0070 表示0.07元/t/km
int GetBasicFareRate(void)
{
	return GetConstValue(GrecordIndex,3);
}
//基本费率计算重量限重 单位10KG
//Eg：2000 表示20吨
int GetLimiOfTheWeightToApplyTheBasicFareRate(void)
{
	return GetConstValue(GrecordIndex,4);
}
//最小费率
//Eg：0035 表示0.035元/t/Km
int GetMinimumFareRate(void)
{
	return GetConstValue(GrecordIndex,5);	
}
//最小费率计算重量限重 单位10KG
//Eg：4000 表示40吨
int GetLimitOfTheWeightToApplyTheMinimumFareRate(void)
{
	return GetConstValue(GrecordIndex,6);		
}
int GetMinimumFareRateOfTheParticularTruckInThousands(void)
{
	return GetConstValue(GrecordIndex,7);	
}
int GetLimitOfTheParticularTruckToApplyTheMinimumFareRate(void)
{
	return GetConstValue(GrecordIndex,8);	
}


//最大费率
//Eg：0140 表示0.14元/t/Km
int GetMaximumFareRateNotDependingOnWeight(void)
{
	return GetConstValue(GrecordIndex,9);	
}
//轻微超限
//eg：1300表示 超重30%（含30%）
int GetRateLimitOfWeightToApplyTheFirstMultiplier(void)
{
	return GetConstValue(GrecordIndex,10);		
}
//最小补偿倍数 
//eg：3000表示 按基本费率3倍补偿
int GetMultiplierOfTheFirstRateLimit(void)
{
	return GetConstValue(GrecordIndex,11);	
}
//严重超限
//Eg：eg：2000表示 超重100%（含100%）
int GetRateLimitOfWeightToApplyTheSecondMultiplier(void)
{
	return GetConstValue(GrecordIndex,12);		
}
//最大补偿倍数
//eg：6000表示 按基本费率6倍补偿
int GetMultiplierOfTheSecondRateLimit(void)
{
	return GetConstValue(GrecordIndex,13);		
}
//费额最小单位
//eg：0500 表示最小单位为5元 不足5元按5元计
int GetRoundingValue(void)
{
	return GetConstValue(GrecordIndex,14);	
}
int GetDiscountOfGreenPassageTruck(void)
{
	return GetConstValue(GrecordIndex,15);	
}
int GetDiscountOfContainerPassageTruckWithoutCSC(void)
{
	return GetConstValue(GrecordIndex,16);		
}
//
int GetWeightLimitForTruckWithAxles(int axles)
{
	char Num1[5];
	int temp;
	temp=axles-2;
	Num1[4]=0x00;
	strncpy(Num1,ConstantRecordTable[HrecordIndex].RecordB.Num[temp],4);
	return atoi(Num1);
}

/***********************************************************************************************************
* 普通货车限重
***********************************************************************************************************/
int GetAxleWeighLimt(int InputAxleNumber)
{	
	InputAxleNumber = InputAxleNumber <2  ? 2:InputAxleNumber;
	InputAxleNumber = InputAxleNumber >6  ? 6: InputAxleNumber;
	return GetConstValue(HrecordIndex,InputAxleNumber-2);
}
float GetTollFareDistance()
{
	
	float Distance = GetConstValue(HrecordIndex,18)  ;
	float Distance_Sub = GetConstValue(HrecordIndex,19);
	return Distance + (Distance_Sub/10000);
}
/***********************************************************************************************************
* 标准集装箱限重
***********************************************************************************************************/
int GetAxleContainerTruckWeighLimt(int InputAxleNumber,int Feet)
{	
	int Index=0;
	InputAxleNumber = InputAxleNumber <3  ? 3:InputAxleNumber;
	InputAxleNumber = InputAxleNumber >6  ? 6: InputAxleNumber;
	
	switch(InputAxleNumber)
	{
		case 3:
			Index = 5;
			break;
		case 4:
			Index = 6 + Feet;
			break;
		case 5:
			Index = 8 + Feet;
			break;
		case 6:
			Index = 10 + Feet;
			break;
	}		
	//printf("InputAxleNumber %d,Feet %d Index %d \n",InputAxleNumber,Feet,Index);
	return GetConstValue(HrecordIndex,Index);
}



/***********************************************************************************************************
* 等待监控确认时间 当通讯正常
***********************************************************************************************************/
int GetConstantTimeOutEntryPlazaConfirmationCOMOK()
{
	char Temp[5];	
	strncpy(Temp,ConstantRecordTable[ErecordIndex].RecordB.Num[1],4);
	Temp[4] = 0x00;
	return atoi(Temp);
}
/***********************************************************************************************************
* 等待监控确认时间 当通讯失败
***********************************************************************************************************/
int GetConstantTimeOutEntryPlazaConfirmationCOMDOWN()
{
	char Temp[5];
	
	strncpy(Temp,ConstantRecordTable[ErecordIndex].RecordB.Num[5],4);
	Temp[4] = 0x00;
	return atoi(Temp);
}

char *GetConstTableVersion()
{
	return ConStantHead.VerNo;
}


static int LoadRecordtest(char *FileName,struct PARAM_HEAD *Head,int IsFirst)
{
	FILE * FileFd;
	char HeadStr[PAEAMHEAD_LENGTH];
	char RecordStr[200];
	int i=0,j=0;
	FileFd=fopen(FileName,"r");
	if(FileFd<0)
	{
		#ifdef SYS_LOG
			writelog(logfd,"system config file not find!\n");
		#endif
		LogCParameter(LOG_ERROR,"参数表 %s 未找到",FileName);
		return 0;
	}
	TrecordCount=0;
	//lseek(FileFd,SEEK_SET,0);
	fread(HeadStr,1,PAEAMHEAD_LENGTH,FileFd);
	//read(FileFd,HeadStr,PAEAMHEAD_LENGTH);
	//HeadStr[39] = 0x00;
	if( ParseHead(HeadStr,Head,CONSTANTTABLE) || IsFirst)
	{
		
		while(!feof(FileFd))
		{
			fread(&RecordStr[i],1,1,FileFd);
			i++;

			if(i>3)
			{
				if('\n'==RecordStr[i-1])
				{
					RecordStr[i]=0x00;
					i=0;
					ParseRecordConstant(RecordStr,&ConstantRecordTable[j],j);
					j++;
					 echoic("RecordStr %s ",RecordStr);
				}
			}			
				
		}
		LogCParameter(LOG_INFOR,"载入参数表 %s ",FileName);
	}
	fclose(FileFd);
	
	return 1;
}

int LoadConstantRecord(int IsFirst)
{
	int ret = LoadRecordtest(PARACONSTANT_FILE,&ConStantHead,IsFirst);
	strncpy(GetMsgRevision()->ConstVer,ConStantHead.VerNo,2);
	if(ret)
	{
		LoadRecordFromConstantTable();//加载计重常量信息！
	}
	return ret;
}
char TFIText[100];
char* GetTFIText(int index)
{
	char msgno[10];
	int  dindex;
	memset(TFIText, 0x00, 100);
	if (index < TrecordCount)
	{
		dindex = TrecordIndex - TrecordCount +1 + index ;
		memset(msgno, 0x00, 10);
		sprintf(msgno, "%03d",  index);
		if (strncmp(ConstantRecordTable[dindex].RecordT.MsgNo, msgno, 3) == 0)
		{
			strncpy(TFIText, ConstantRecordTable[dindex].RecordT.MsgContent, 64);
		}	
	}
	else
	{
		echoic("共%d条信息，序号%d无超出范围", TrecordCount, index);
	}
	echoic("内容编号:%d,%s",index, TFIText);
	return TFIText;
}
