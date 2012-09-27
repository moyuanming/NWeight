#ifndef __MsgEvent_H__
#define __MsgEvent_H__
struct CARTYPE
{
	char   CarType[12];
};
struct CARKINDUNTYPE
{
	char Kind_Total[12];
	struct CARTYPE CarTypes[7];
};

void SendMsgEI(char* InputEquipment,char InputStatus,char* InputMemo);
void SendMsgAK(char InputFileType,char InputRecStatus);
void SendMsgEM(char InputDetectorError);
void SendMsgGR(char InputCanopy);
void SendMsgOF(char InputFLAG,char* InputVehicleCount);
void SendTCOMsg(char MsgType,char*MsgContext);
void SendLaneInfo(char* InputClientMsg);
void SendMsgInfo(char* InputMsgType,char* InputException,char* InputPromptMsg);
void SendLaneInfo_default(void);
void InitReadWriteFile(void);

int AddStrAtFileTail(char *InputStr, char *InputFileName);
void CreateMsgFile(char *FilePath,int FileLength);
int SaveMsgToFile(char *MessageBody,int MessageLength,char *MsgSaveFile);
int ReadMsgFile(char *MsgSaveFile,int isSyncDiskQueye);

char *GetSendedFileName(char *SendedFileName);
char *GetNotSendFileName(char *SendedFileName);
int FileExists(char *filename);
int DeleteFileFirstLine(char *FileName);
#endif
