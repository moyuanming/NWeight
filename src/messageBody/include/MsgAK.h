//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _MsgAK_H_
#define _MsgAK_H_
struct MSG_MSGAK
{
      char FileType;
      char RecStatus;
      char MARK;
};//endstructMsgAK
#define  LENGHT_MSG_MSGAK 3

/********************************************************************************************************************
*文件确认数据MsgAK 消息将要用的变量
*********************************************************************************************************************/
//下发文件类型
/*
 #define  MSGAK_COLLECTORLIST                "1"  // 收费员白名单
 #define  MSGAK_VINDICATOR                       "2"  //维护员白名单
 #define  MSGAK_PERSONNELBACKLIST       "3"  //人员黑名单
 #define  MSGAK_OFFICECARD_BACKLIST      "4"  //公务卡黑名单
 #define  MSGAK_PREPAY_BACKLIST            "5"  //预付卡黑名单
 #define  MSGAK_NATURAL_RATETABLE       "6"   //正常费率表
 #define  MSGAK_U_RATETABLE                      "7"   // U费率表
 #define  MSGAK_J_RATETABLE                      "8"   // J费率表
 #define  MSGAK_MAX_OR_MIN_RUNTIME       "9"   //   站间最大最小行驶时间
 #define  MSGAK_CARTYPE_CLASSTABLE   "A"   //   车型分类表
 #define  MSGAK_YOUHUI_RATETABLE             "B"   //   优惠率表
 #define  MSGAK_MONTHCARD_BACKLIST       "C"   //   月票卡黑名单
 #define  MSGAK_YOUHUICARD_BACKLIST      "D"   //   优惠卡黑名单
 #define  MSGAK_MONTHCARD_LIST               "E"   //   月票卡白名单
 #define  MSGAK_YOUHUICRD_LIST           "F"   //   优惠卡白名单
*/

 #define  MSGAK_COLLECTORLIST         "1"   //职员表
 #define  MSGAK_YPKList                       "2"   //   月票卡 
 #define  MSGAK_YHKList                       "3"   //   优惠卡
 #define  MSGAK_FareList                        "4"   // 费率表 	
 #define  MSGAK_YHRateDescription		 "5"  //优惠率描述表


//接受状态
#define  MSGAK_RECSTATUS_OK              "0"  //接受正确
#define  MSGAK_RECSTATUS_ERROR       "1"  //接受错误

#define MSGAK_BOOL_TURE  '1'
#define MSGAK_BOOL_FALSE '0'
void InitMsgMsgAK(void);
struct MSG_MSGAK *GetMsgMsgAK(void);
void SetMsgAKMsgFileType(char InputFileType);
void SetMsgAKMsgRecStatus(char InputRecStatus);
void SetMsgAKMsgMARK(char InputMARK);
#endif //define t_tablename

