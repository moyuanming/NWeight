//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _MsgEI_H_
#define _MsgEI_H_
struct MSG_MSGEI
{
      char Equipment[2];
      char Status;
      char Memo[10];
      char MARK;
};//endstructMsgEI
#define  LENGHT_MSG_MSGEI 14

#define  MSGEI_RROWNOUT                              "00" //卡箱断电
#define  MSGEI_KEEPCARD                                 "01" //卡箱卡卡
#define  MSGEI_CROSSEDCOIL                           "10"  //通过线圈故障
#define  MSGEI_CATCHCOIL                               "11" //捕捉线圈故障
#define  MSGEI_IC_CARDREADERFAULT              "20" //IC卡读写器故障
#define  MSGEI_PRINTER_UNKNOW                    "30" //打印机(不明原因的故障)
#define  MSGEI_PRINTER_NEED_PAPER              "31" //打印机缺纸
#define  MSGEI_PRINTER_ERROR                       "32" //打印机故障
#define  MSGEI_PRINTER_RROWNOUT               "33" //打印机断电
#define  MSGEI_REPRINTBILL                             "34" //重打票据
#define  MSGEI_FOOTSWITCH                           "40" //脚踏开关
#define  MSGEI_EMERGENCYVEHICLES                "50" // 紧急车
#define  MSGEI_CARTEAM_STARTED                  "51" //车队开始
#define  MSGEI_CARTEAM_END                          "52" //车队结束
#define  MSGEI_ARREARS_DEAL                         "80" //欠款处理
#define  MSGEI_VEHICLES_DONOT_MATCH         "81" //车种不符
#define  MSGEI_CARTYPE_DONOT_MATCH          "82" // 车型不符
#define  MSGEI_ MANDAROEY_PLACEMENT          "83" //强制替换
#define  MSGEI_CARD_NONE                               "84" //无卡
#define  MSGEI_CARD_BAD                                 "85"// 坏卡
#define  MSGEI_CARD_DAMAGE                           "86"// 卡恶意损坏
#define  MSGEI_ROUNDAS_U                               "87"// U型车
#define  MSGEI_ROUNDAS_TIMEOUT                    "88"// 超时车
#define  MSGEI_DEFENDERS_UNCONFIRMED          "90" //维护员上岗未经站确认
#define  MSGEI_IDCARD_INVALID                          "91"// 无效身份卡上岗
#define  MSGEI_EXPORTDATAFEES                       "92" //导出收费数据
#define  MSGEI_IMPORT_PAEAMFILES                   "93"// 导入收费参数文件
#define  MSGEI_SERVER_CONNECTED                   "A0"// 与站的通讯建立 ok
#define  MSGEI_SERVER_DISCONNECT                  "A1" //与站的通讯中断 ok

#define MSGEI_STATUS_ERROR_OCCURRED           '0'// 发生错误
#define MSGEI_STATUS_ERROR_FIX                      '1' // 成功修复错误
#define MSGEI_STATUS_EVENT_OCCURRED           '2'// 事件发生
#define MSGEI_STATUS_MSGINFO                         'W'    // 提示信息

#define MSGEI_BOOL_TURE  '1'
#define MSGEI_BOOL_FALSE '0'
void InitMsgMsgEI(void);
struct MSG_MSGEI *GetMsgMsgEI(void);
void SetMsgEIMsgEquipment(char* InputEquipment);
void SetMsgEIMsgStatus(char InputStatus);
void SetMsgEIMsgMemo(char* InputMemo);
void SetMsgEIMsgMARK(char InputMARK);
#endif //define t_tablename

