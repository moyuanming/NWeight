//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _Image_H_
#define _Image_H_
struct MSG_IMAGE
{
	char ID[18];
	char NetWork[2];
	char Plaza[2];
	char Year[4];
	char Day[4];
	char Hour[6];
	char YMD[8];
	char Time[14];
	char LaneType;
	char LaneName[3];
	char Trans[4];
	char SubTrans;
	char EntryNetwork[2];
	char EntryPlaza[2];
	char Type[3];
	char Class;
	char Status;
	char Collector[6];
	char TollFare[4];
	char PictureNum[10];
	char MARK;
	char ReceiptNo[8];
	char DisputeType;
	char Method_Pay;
	char WeightCarClass;
	char FWeightTotal[53];
	char FAxleCount[10];
	char FFareBase[10];
	char WeightTollFare[53];
	char WeightLimit[10];
	char WeightLimitTollFare[53];
	char OverloadWeight[10];
	char OverLoadWeightRate[53];
	char OverloadFare[53];
	char Speed[10];
	char Acceleration[10];
	char FlagOverWeight[10];
	char FlagDisCount[10];
	char DetectWeightTotal[53];
	char RateFareWeight[10];
	char DetectAxleCount[10];
	char tmp[2];
};//endstructImage
void InitMsgImage(void);
struct MSG_IMAGE *GetMsgImage(void);
void SetImageMsgID(char* InputID);
void SetImageMsgNetWork(char* InputNetWork);
void SetImageMsgPlaza(char* InputPlaza);
void SetImageMsgYear(char* InputYear);
void SetImageMsgDay(char* InputDay);
void SetImageMsgHour(char* InputHour);
void SetImageMsgYMD(char* InputYMD);
void SetImageMsgTime(char* InputTime);
void SetImageMsgLaneType(char InputLaneType);
void SetImageMsgLaneName(char* InputLaneName);
void SetImageMsgTrans(char* InputTrans);
void SetImageMsgSubTrans(char InputSubTrans);
void SetImageMsgEntryNetwork(char* InputEntryNetwork);
void SetImageMsgEntryPlaza(char* InputEntryPlaza);
void SetImageMsgType(char *InputType);
void SetImageMsgClass(char InputClass);
void SetImageMsgStatus(char InputStatus);
void SetImageMsgCollector(char* InputCollector);
void SetImageMsgTollFare(char* InputTollFare);
void SetImageMsgPictureNum(int InputPictureNum);
void SetImageMsgMARK(char InputMARK); 
void BuildImageFiles(char * msghead,     struct MSG_EXITTR*exittr);
char * BuildTCOImage(char msgtype ,char *msg);
int CaptureImg(char imageid);
char *CreateCapImgName(void);
struct MSG_IMAGE *GetSyncImageHeader(void);
void LoadImageHeader(void);
void PostImgSync(void);
void InitImgSync(void);
int StructAndFile(struct MSG_IMAGE *CapImageHeader,char *SourFileName,int SourFileLength ,char *DesFileName);
int GetFileSize(char *FileName);



struct MSG_TCOIMAGE
{
	char NetWork[2];
	char Plaza[2];
	char DateTime[14];
	char LaneType;
	char LaneName[3];
	char Trans[4];
	char SubTrans;
	char EntryNetwork[2];
	char EntryPlaza[2];
	char Type;
	char Kind;
	char Status;
	char Collector[6];
	char TollFare[4];
	char SVRCard[10];
	char Rev1[50];
	char MsgInfo[200];
	char MsgType;
	char Rev2[103];
};//endstructMSG_TCOIMAGE

int StructAndFileTCOIMG(struct MSG_TCOIMAGE *CapImageHeader,char *SourFileName,int SourFileLength ,char *DesFileName);
void InitMsgMSG_TCOIMAGE(void);
struct MSG_TCOIMAGE *GetMsgMSG_TCOIMAGE(void);
void SetMSG_TCOIMAGEMsgNetWork(char*  InputNetWork);
void SetMSG_TCOIMAGEMsgPlaza(char*  InputPlaza);
void SetMSG_TCOIMAGEMsgDateTime(char*  InputDateTime);
void SetMSG_TCOIMAGEMsgLaneType(char InputLaneType);
void SetMSG_TCOIMAGEMsgLaneName(char*  InputLaneName);
void SetMSG_TCOIMAGEMsgTrans(char*  InputTrans);
void SetMSG_TCOIMAGEMsgSubTrans(char   InputSubTrans);
void SetMSG_TCOIMAGEMsgEntryNetwork(char*  InputEntryNetwork);
void SetMSG_TCOIMAGEMsgEntryPlaza(char*  InputEntryPlaza);
void SetMSG_TCOIMAGEMsgType(char  InputType);
void SetMSG_TCOIMAGEMsgKind(char InputKind);
void SetMSG_TCOIMAGEMsgStatus(char   InputStatus);
void SetMSG_TCOIMAGEMsgCollector(char*  InputCollector);
void SetMSG_TCOIMAGEMsgTollFare(char*  InputTollFare);
void SetMSG_TCOIMAGEMsgSVRCard(char*  InputSVRCard);
void SetMSG_TCOIMAGEMsgRev1(char*  InputRev1);
void SetMSG_TCOIMAGEMsgMsgInfo(char*  InputMsgInfo);
void SetMSG_TCOIMAGEMsgMsgType(char   InputMsgType);
void SetMSG_TCOIMAGEMsgRev2(char*  InputRev2);
 
#endif //define t_tablename

