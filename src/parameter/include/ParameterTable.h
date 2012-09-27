

#ifndef _parameterTable_H_
#define _parameterTable_H_


#define PARAMNAME_ACCESLVL  "ACCESLVL"
#define PARAMNAME_CONSTANT  "CONSTANT"
#define PARAMNAME_JOUSERVI  "JOUSERVI"
#define PARAMNAME_LSTORANG  "LSTORANG"
#define PARAMNAME_LSTPERSO  "LSTPERSO"
#define PARAMNAME_LSTSERVI  "LSTSERVI"
#define PARAMNAME_OPPABONN  "OPPABONN"
#define PARAMNAME_OPPCARTE  "OPPCARTE"
#define PARAMNAME_TARI      "TARI"
#define PARAMNAME_TRAJ      "TRAJ"
#define PARAMNAME_OPPLAQUE  "OPPLAQUE"

#define PARAMTYPE_ACCESLVL  37
#define PARAMTYPE_CONSTANT  11
#define PARAMTYPE_JOUSERVI  62
#define PARAMTYPE_LSTORANG  10
#define PARAMTYPE_LSTPERSO  7
#define PARAMTYPE_LSTSERVI  36
#define PARAMTYPE_OPPABONN  9
#define PARAMTYPE_OPPCARTE  8
#define PARAMTYPE_TARI      1
#define PARAMTYPE_TRAJ      2
#define PARAMTYPE_OPPLAQUE  87


#define PARAMSTATUS_ACTUAL "4"
#define PARAMSTATUS_FUTURE "6"
#define PAEAMHEAD_LENGTH    39
#define MAXPAEAMRECORDS     5000
#define MAXRECORDSTRLENRTH  1000
#define MAXCARKINDCOUNT     11           //最大车种数目



#define FRAE                0
#define JOUENEY             1
#define AUTHORIZED          2
#define BLACKLIST           3
#define BLACKLISTSERVICE    4
#define BLACKLISTSTORE      5
#define CONSTANTTABLE       6
#define SERVICE             7
#define ACCESS              8
#define JOUENEYSERVICE      9
#define BLACKLISTPLATE      10
#define ISLOADFIRST         1
#define ISNOTLOADFIRST      0

struct ParameterVersion
{
    char Collect[2];
};
struct PARAM_HEAD
{
    char Type[2];
    char DateCreate[12];
    char DateApply[12];
    char NetNo[2];
    char PlazaNo[2];
    char VerNo[2];
    char Recordcount[6];
};
struct ParameterVersion *CurrentUseParameterVersionNumber;
int ParseHead(char *HeadStr,struct PARAM_HEAD *Head,int InputParameterIndex );
int LoadRecord(char *FileName,struct PARAM_HEAD *Head,int RecordStrLenrth,int (*ParseRecord)(char *RecordStr,int Rowindex),int InputParameterIndex,int IsFirst );
 int  LoadParameter(int IsFirst);
void LoadCurrentUseParameterVersionNumber(void);
int LoadCarKind(char *FileName,int RecordStrLenrth,int (*ParseRecord)(char *RecordStr,int Rowindex));
 int CompareVersion(int InputParameterIndex,char *InputVersion);
 int  LoadParameter_CARDInfo(int IsFirst);
#endif


