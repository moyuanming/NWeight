//By GER.Cmd.buildgcc   CreateDate:2008-7-1 11:10:09
#ifndef _LaneInfo_H_
#define _LaneInfo_H_
struct MSG_LANEINFO
{
      char LaneNo[3];
      char CollName[16];
      char CollNo[10];
      char ClientMsg[32];
      char CarType[5];
      char Money[10];
      char CarKind[16];
      char WrokMode[16];
      char JobBeginTime[32];
      char YuPengDeng;
      char JiaoTongDeng;
      char LanGan;
      char Printer;
      char Network;
};//endstructLaneInfo
#define  LENGHT_MSG_LANEINFO 145
void InitMsgLaneInfo(void);
struct MSG_LANEINFO *GetMsgLaneInfo(void);
void SetLaneInfoMsgLaneNo(char* InputLaneNo);
void SetLaneInfoMsgCollName(char* InputCollName);
void SetLaneInfoMsgCollNo(char* InputCollNo);
void SetLaneInfoMsgClientMsg(char* InputClientMsg);
void SetLaneInfoMsgCarType(char* InputCarType);
void SetLaneInfoMsgMoney(char* InputMoney);
void SetLaneInfoMsgCarKind(char* InputCarKind);
void SetLaneInfoMsgWrokMode(char* InputWrokMode);
void SetLaneInfoMsgJobBeginTime(char* InputJobBeginTime);
void SetLaneInfoMsgYuPengDeng(char InputYuPengDeng);
void SetLaneInfoMsgJiaoTongDeng(char InputJiaoTongDeng);
void SetLaneInfoMsgLanGan(char InputLanGan);
void SetLaneInfoMsgPrinter(char InputPrinter);
void SetLaneInfoMsgNetwork(char InputNetwork);

#endif //define t_tablename

