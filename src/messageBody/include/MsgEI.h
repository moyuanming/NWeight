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

#define  MSGEI_RROWNOUT                              "00" //����ϵ�
#define  MSGEI_KEEPCARD                                 "01" //���俨��
#define  MSGEI_CROSSEDCOIL                           "10"  //ͨ����Ȧ����
#define  MSGEI_CATCHCOIL                               "11" //��׽��Ȧ����
#define  MSGEI_IC_CARDREADERFAULT              "20" //IC����д������
#define  MSGEI_PRINTER_UNKNOW                    "30" //��ӡ��(����ԭ��Ĺ���)
#define  MSGEI_PRINTER_NEED_PAPER              "31" //��ӡ��ȱֽ
#define  MSGEI_PRINTER_ERROR                       "32" //��ӡ������
#define  MSGEI_PRINTER_RROWNOUT               "33" //��ӡ���ϵ�
#define  MSGEI_REPRINTBILL                             "34" //�ش�Ʊ��
#define  MSGEI_FOOTSWITCH                           "40" //��̤����
#define  MSGEI_EMERGENCYVEHICLES                "50" // ������
#define  MSGEI_CARTEAM_STARTED                  "51" //���ӿ�ʼ
#define  MSGEI_CARTEAM_END                          "52" //���ӽ���
#define  MSGEI_ARREARS_DEAL                         "80" //Ƿ���
#define  MSGEI_VEHICLES_DONOT_MATCH         "81" //���ֲ���
#define  MSGEI_CARTYPE_DONOT_MATCH          "82" // ���Ͳ���
#define  MSGEI_ MANDAROEY_PLACEMENT          "83" //ǿ���滻
#define  MSGEI_CARD_NONE                               "84" //�޿�
#define  MSGEI_CARD_BAD                                 "85"// ����
#define  MSGEI_CARD_DAMAGE                           "86"// ��������
#define  MSGEI_ROUNDAS_U                               "87"// U�ͳ�
#define  MSGEI_ROUNDAS_TIMEOUT                    "88"// ��ʱ��
#define  MSGEI_DEFENDERS_UNCONFIRMED          "90" //ά��Ա�ϸ�δ��վȷ��
#define  MSGEI_IDCARD_INVALID                          "91"// ��Ч��ݿ��ϸ�
#define  MSGEI_EXPORTDATAFEES                       "92" //�����շ�����
#define  MSGEI_IMPORT_PAEAMFILES                   "93"// �����շѲ����ļ�
#define  MSGEI_SERVER_CONNECTED                   "A0"// ��վ��ͨѶ���� ok
#define  MSGEI_SERVER_DISCONNECT                  "A1" //��վ��ͨѶ�ж� ok

#define MSGEI_STATUS_ERROR_OCCURRED           '0'// ��������
#define MSGEI_STATUS_ERROR_FIX                      '1' // �ɹ��޸�����
#define MSGEI_STATUS_EVENT_OCCURRED           '2'// �¼�����
#define MSGEI_STATUS_MSGINFO                         'W'    // ��ʾ��Ϣ

#define MSGEI_BOOL_TURE  '1'
#define MSGEI_BOOL_FALSE '0'
void InitMsgMsgEI(void);
struct MSG_MSGEI *GetMsgMsgEI(void);
void SetMsgEIMsgEquipment(char* InputEquipment);
void SetMsgEIMsgStatus(char InputStatus);
void SetMsgEIMsgMemo(char* InputMemo);
void SetMsgEIMsgMARK(char InputMARK);
#endif //define t_tablename

