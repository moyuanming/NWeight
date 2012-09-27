#ifndef _MessageBuild_H_
#define _MessageBuild_H_
void SendMessageToQueue(char   InputMsgCode);
void InitMsgTCO(void );
void InitMsgHead(void );
struct MSG_HEAD  *GetMsgHead(void);
struct MSG_SubHead  *GetMsgSubHead(void);
struct TCOMSG  *GetMsgTCO(void);
void InitMsgSubHead(void);
void SetMsgSubHeadStaffName(char *InputStaffName);
void SetMsgSubHeadStaffID(char *InputStaffID);
void LoadMsgSubHead(void);
void SetMsgSubHeadLaneMode(char InputLaneMode);
void SetMsgSubHeadJobNo(char *InputJobNo);
struct MSG_SubHead  *GetSystemInfor(void);
char *GetMessageHead(char MsgType);
#endif

