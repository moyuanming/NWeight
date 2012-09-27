//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _ExitEI_H_
#define _ExitEI_H_





	//EI_Type EI_Desc                                            EI_OperType
	//------- -------------------------------------------------- --------------------------------------------------
#define  EI_Type_MN_GGCX 	"01"      //���ĳ���                                               ģ��
#define  EI_Type_MN_GGCZ  	"02"      //���ĳ���                                               ģ��
#define  EI_Type_MN_TC 		"03"      //�ϳ�                                                 ģ��
#define  EI_Type_MN_GCMN 	"04"      //����ģ��                                               ģ��
#define  EI_Type_MN_CDPJ 	"05"      //�ش�Ʊ��                                               ģ��
#define  EI_Type_JZ_XZCLXX 	"06"      //����������Ϣ                                             ���ز˵�
#define  EI_Type_JZ_TJCLXX 	"07"      //��ӳ�����Ϣ                                             ���ز˵�
#define  EI_Type_JZ_SCCLXX 	"08"      //ɾ��������Ϣ                                             ���ز˵�
#define  EI_Type_JZ_XZCLZS	"09"      //������������                                             ���ز˵�
#define  EI_Type_JZ_CC 		"10"      //����                                                 ���ز˵�
#define  EI_Type_JZ_TZCL 	"11"      //���ֳ���                                               ���ز˵�
#define  EI_Type_JZ_ZHCL 	"12"      //ת������                                               ���ز˵�
#define  EI_Type_DYJGZ 		"13"      //��ӡ������                                              
#define  EI_Type_JJC 		"14"      //��������                                               
#define  EI_Type_CK_CKTY 	"15"      //�忨����                                               �忨��
#define  EI_Type_CK_CKWTY 	"16"      //�忨δ����                                              �忨��
#define  EI_Type_CK_WBJ 	"17"      //�󱨾�                                                �忨��
#define  EI_Type_JZ_DJHC 	"18"      //�������                                               ���ز˵�

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

