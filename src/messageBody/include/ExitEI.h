//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _ExitEI_H_
#define _ExitEI_H_





	//EI_Type EI_Desc                                            EI_OperType
	//------- -------------------------------------------------- --------------------------------------------------
#define  EI_Type_MN_GGCX 	"01"      //更改车型                                               模拟
#define  EI_Type_MN_GGCZ  	"02"      //更改车种                                               模拟
#define  EI_Type_MN_TC 		"03"      //拖车                                                 模拟
#define  EI_Type_MN_GCMN 	"04"      //过车模拟                                               模拟
#define  EI_Type_MN_CDPJ 	"05"      //重打票据                                               模拟
#define  EI_Type_JZ_XZCLXX 	"06"      //修正车辆信息                                             计重菜单
#define  EI_Type_JZ_TJCLXX 	"07"      //添加车辆信息                                             计重菜单
#define  EI_Type_JZ_SCCLXX 	"08"      //删除车辆信息                                             计重菜单
#define  EI_Type_JZ_XZCLZS	"09"      //修正车辆轴数                                             计重菜单
#define  EI_Type_JZ_CC 		"10"      //长车                                                 计重菜单
#define  EI_Type_JZ_TZCL 	"11"      //特种车辆                                               计重菜单
#define  EI_Type_JZ_ZHCL 	"12"      //转换车辆                                               计重菜单
#define  EI_Type_DYJGZ 		"13"      //打印机故障                                              
#define  EI_Type_JJC 		"14"      //紧急车队                                               
#define  EI_Type_CK_CKTY 	"15"      //冲卡逃逸                                               冲卡车
#define  EI_Type_CK_CKWTY 	"16"      //冲卡未逃逸                                              冲卡车
#define  EI_Type_CK_WBJ 	"17"      //误报警                                                冲卡车
#define  EI_Type_JZ_DJHC 	"18"      //大件货车                                               计重菜单

struct MSG_EXITEI
{
      char ErrorNO[2];
      char Occ_Rec;
      char MARK;
};//endstructExitEI
#define  LENGHT_MSG_EXITEI 4
void InitMsgExitEI(void);
struct MSG_EXITEI *GetMsgExitEI(void);
void SetExitEIMsgErrorNO(char* InputErrorNO);
void SetExitEIMsgOcc_Rec(char InputOcc_Rec);
void SetExitEIMsgMARK(char InputMARK);
void SendExitEI(char* EI_Type);
#endif //define t_tablename

