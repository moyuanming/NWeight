
#ifndef   _parameterCarType_H_
#define  _parameterCarType_H_

#define  LENGHT_CARKIND_PARA     38+6+2//4位是IC卡加的内容

struct CARKIND_PARA
{
	char carKindId[2];
	char carKineNumber[2];
	char carKindExplian[8];
	char carKindChargeComputeMethod[3];
	char carkindHandl[8];
	char carKindType[8];
	char carKindCharge[2];
	char keyboardValue[2];
	char imageIndex[1];
	char onceOk[1];
	char BillFlag[1];
	char PosCount[2];//数据库表中的位置
	char PaidSum[2];	
	char AskTCO;
	char NewCarKindSite[2];
};

char   GetCarKindCharge(int  index);
char *GetCarKeyNames(void);
char  *GetCarKindKeyName(int  index);
char  *GetCarKindNameByIndex(int  index);
struct CARKIND_PARA  CarKindRecord[MAXCARKINDCOUNT];
int ParseCarKindRecord(char *RecordStr,int Rowindex);
int LoadCarKindRecord(int IsFirst);
float   GetCarKindChargeComputeMethod(int  keyboardvalue);
float   GetCarKindChargeComputeMethod_byindex(int  index);
char     GetCarKindChar(int  index);
int      GetCarKindInt(int  index);
char     GetNeedAskTCO(int  index);
char *GetCarKindName(int  keyboardvalue);
int  GetOnceOk(int  keyboardvalue);
int GetImageIndex(int  keyboardvalue);
int  GetBillFlag(int  keyboardvalue);
int GetBillFlagbyIndex(int index);
int  GetCarKindIndex(int  keyboardvalue);
#endif


