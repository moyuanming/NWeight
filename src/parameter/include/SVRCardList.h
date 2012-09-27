//By GER.Cmd.buildgcc   CreateDate:2009-3-10 11:28:43
#ifndef _SVRCardList_H_
#define _SVRCardList_H_
struct MSG_SVRCARDLIST
{
      char SvrID[10];//0-10
      char SvrICKind[2]; //11-12
      char SvrICDate[8];//13-20
      char SVCUsedTypeCount[2];//21-22
      char CarType[40];//cartype01 02 03 ,如果支持3车型， 则 CarType[3*2]=="01" 22-62
      char SVCName[20];//63-82
      char Spendlimit[9];//  -91
      char Kind[2];    //93
      char NumPlateLen[2]; //95
      char NumPlate[20];  //115
      char InputPlate[3]; //118
      char DisRate[4]; //122
	    char Status[2]; //124
      char Reserved2[18]; //142
      char JourneyCode[6]; //148
      char EnableDate[14]; //162
      char DisEnableDate[14]; //176 
};//endstructSVRCardList
#define  LENGHT_MSG_SVRCARDLIST 176
struct MSG_JOUDESC
{
	char JouCode[6];
	char  BeginSiteNetNo[2];
	char  BeginSitePlaza[2];
	char  EndSiteNetNo[2];
	char EndSitePlaza[2];
};//JouDesc
#define LENGHT_MSG_JOUDESC 14 

int LoadJOUListRecord(int IsFirst);
int  ParseRecordJOUList(char *RecordStr,int Rowindex);
int LoadSVRListRecord(int IsFirst);
int  ParseRecordSVRList(char *RecordStr,int Rowindex);
int GetIsCardDateLimit(struct MSG_SVRCARDLIST * _SVRList);
BOOL  CanPayForThisCarType( struct MSG_SVRCARDLIST * _SVRList, char * _cartype );
struct MSG_SVRCARDLIST *  FindCardInParamList(char *cardnumber );
BOOL Get_CardContext_InJouRouter(char * joucode);
#endif //define t_tablename


