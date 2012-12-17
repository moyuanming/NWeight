
// ***************************************************************
//  ConstantTable   version:  1.0   ��  date: 12/09/2007
//  -------------------------------------------------------------
//  ��������ʽӿڣ�
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
* ���ع��ܿ���
* ����zhi
* #define NotUseWeight						'0' //��ʹ�ü��ع���
* #define NotUseWeightUseTruckKey			'1' //��ʹ�ü��ع��� ��ʹ�û�����
* #define UseWeightUseTruckKeyNotFare		'2' //ʹ�ü��ع��� ���������������
* #define FullWeight						'3' //ʹ��ȫ�����ع���
***********************************************************************************************************/
int GetWeightFunctions()
{
	return ConstantRecordTable[GrecordIndex].RecordB.Code[0];
}
//#define OLD312CalculateFare				'0' //��312�Ʒѷ�ʽ
//#define NewCalculateFare					'1' //5�ͳ��Ʒ�
//
int GetCalculateFareMode()
{
	return ConstantRecordTable[GrecordIndex].RecordB.Code[1];
}
/***********************************************************************************************************
* ����Ʊ����ʽ
* ����ֵ
* #define OLDPrintStyle						'0' //����ʽ
* #define NewPrintStyle						'1' //����ʽ
* #define PromptPrintStyle					'2' //��ʾ��
* #define BothNewandPromptPrintStyl			'3' //��Ʊ������ʾ��
***********************************************************************************************************/
int GetPrinterMode()
{
	return ConstantRecordTable[GrecordIndex].RecordB.Code[2];
}
//#define OLD312JaoKeCalculateFareMode				'0' //��312�Ʒѷ�ʽ
//#define NewJaoKeCalculateFareMode					'1' //5�ͳ��Ʒ�
int GetJaoKeCalculateFareMode()
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
//������������
int GetRateToGetTheFareWeightFromTheDetectedWeight(void)
{	
	return GetConstValue(GrecordIndex,0);
}
//������ȡ������λ10KG
int GetRoundingTheResultToFareWeight(void)
{
	return GetConstValue(GrecordIndex,1);
}
//������С���� 
//Eg:0500 ��ʾλ5��
int GetMinimumWeightForFareWeight(void)
{
	return GetConstValue(GrecordIndex,2);
}
//��������
//Eg��0070 ��ʾ0.07Ԫ/t/km
int GetBasicFareRate(void)
{
	return GetConstValue(GrecordIndex,3);
}
//�������ʼ����������� ��λ10KG
//Eg��2000 ��ʾ20��
int GetLimiOfTheWeightToApplyTheBasicFareRate(void)
{
	return GetConstValue(GrecordIndex,4);
}
//��С����
//Eg��0035 ��ʾ0.035Ԫ/t/Km
int GetMinimumFareRate(void)
{
	return GetConstValue(GrecordIndex,5);	
}
//��С���ʼ����������� ��λ10KG
//Eg��4000 ��ʾ40��
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


//������
//Eg��0140 ��ʾ0.14Ԫ/t/Km
int GetMaximumFareRateNotDependingOnWeight(void)
{
	return GetConstValue(GrecordIndex,9);	
}
//��΢����
//eg��1300��ʾ ����30%����30%��
int GetRateLimitOfWeightToApplyTheFirstMultiplier(void)
{
	return GetConstValue(GrecordIndex,10);		
}
//��С�������� 
//eg��3000��ʾ ����������3������
int GetMultiplierOfTheFirstRateLimit(void)
{
	return GetConstValue(GrecordIndex,11);	
}
//���س���
//Eg��eg��2000��ʾ ����100%����100%��
int GetRateLimitOfWeightToApplyTheSecondMultiplier(void)
{
	return GetConstValue(GrecordIndex,12);		
}
//��󲹳�����
//eg��6000��ʾ ����������6������
int GetMultiplierOfTheSecondRateLimit(void)
{
	return GetConstValue(GrecordIndex,13);		
}
//�Ѷ���С��λ
//eg��0500 ��ʾ��С��λΪ5Ԫ ����5Ԫ��5Ԫ��
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
* ��ͨ��������
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
* ��׼��װ������
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
* �ȴ����ȷ��ʱ�� ��ͨѶ����
***********************************************************************************************************/
int GetConstantTimeOutEntryPlazaConfirmationCOMOK()
{
	char Temp[5];	
	strncpy(Temp,ConstantRecordTable[ErecordIndex].RecordB.Num[1],4);
	Temp[4] = 0x00;
	return atoi(Temp);
}
/***********************************************************************************************************
* �ȴ����ȷ��ʱ�� ��ͨѶʧ��
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
		LogCParameter(LOG_ERROR,"������ %s δ�ҵ�",FileName);
		return 0;
	}
	TrecordCount=0;
	//lseek(FileFd,SEEK_SET,0);
	fread(HeadStr,1,PAEAMHEAD_LENGTH,FileFd);
	//read(FileFd,HeadStr,PAEAMHEAD_LENGTH);
	HeadStr[39] = 0x00;
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
		LogCParameter(LOG_INFOR,"��������� %s ",FileName);
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
		LoadRecordFromConstantTable();//���ؼ��س�����Ϣ��
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
		echoic("��%d����Ϣ�����%d�޳�����Χ", TrecordCount, index);
	}
	echoic("���ݱ��:%d,%s",index, TFIText);
	return TFIText;
}
