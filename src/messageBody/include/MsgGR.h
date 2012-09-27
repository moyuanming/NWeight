//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _MsgGR_H_
#define _MsgGR_H_
struct MSG_MSGGR
{
      char Canopy;
      char MARK;
};//endstructMsgGR
#define  LENGHT_MSG_MSGGR 2
/********************************************************************************************************************
*顶棚灯数据 MsgGR 消息将要用的变量
*********************************************************************************************************************/
#define  MSGGR_CANOPY_ON      'G'     // 绿
#define  MSGGR_CANOPY_OFF      'R'   // 红

#define MSGGR_BOOL_TURE  '1'
#define MSGGR_BOOL_FALSE '0'
void InitMsgMsgGR(void);
struct MSG_MSGGR *GetMsgMsgGR(void);
void SetMsgGRMsgCanopy(char InputCanopy);
void SetMsgGRMsgMARK(char InputMARK);
#endif //define t_tablename

