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
*�ļ�ȷ������MsgAK ��Ϣ��Ҫ�õı���
*********************************************************************************************************************/
//�·��ļ�����
/*
 #define  MSGAK_COLLECTORLIST                "1"  // �շ�Ա������
 #define  MSGAK_VINDICATOR                       "2"  //ά��Ա������
 #define  MSGAK_PERSONNELBACKLIST       "3"  //��Ա������
 #define  MSGAK_OFFICECARD_BACKLIST      "4"  //���񿨺�����
 #define  MSGAK_PREPAY_BACKLIST            "5"  //Ԥ����������
 #define  MSGAK_NATURAL_RATETABLE       "6"   //�������ʱ�
 #define  MSGAK_U_RATETABLE                      "7"   // U���ʱ�
 #define  MSGAK_J_RATETABLE                      "8"   // J���ʱ�
 #define  MSGAK_MAX_OR_MIN_RUNTIME       "9"   //   վ�������С��ʻʱ��
 #define  MSGAK_CARTYPE_CLASSTABLE   "A"   //   ���ͷ����
 #define  MSGAK_YOUHUI_RATETABLE             "B"   //   �Ż��ʱ�
 #define  MSGAK_MONTHCARD_BACKLIST       "C"   //   ��Ʊ��������
 #define  MSGAK_YOUHUICARD_BACKLIST      "D"   //   �Żݿ�������
 #define  MSGAK_MONTHCARD_LIST               "E"   //   ��Ʊ��������
 #define  MSGAK_YOUHUICRD_LIST           "F"   //   �Żݿ�������
*/

 #define  MSGAK_COLLECTORLIST         "1"   //ְԱ��
 #define  MSGAK_YPKList                       "2"   //   ��Ʊ�� 
 #define  MSGAK_YHKList                       "3"   //   �Żݿ�
 #define  MSGAK_FareList                        "4"   // ���ʱ� 	
 #define  MSGAK_YHRateDescription		 "5"  //�Ż���������


//����״̬
#define  MSGAK_RECSTATUS_OK              "0"  //������ȷ
#define  MSGAK_RECSTATUS_ERROR       "1"  //���ܴ���

#define MSGAK_BOOL_TURE  '1'
#define MSGAK_BOOL_FALSE '0'
void InitMsgMsgAK(void);
struct MSG_MSGAK *GetMsgMsgAK(void);
void SetMsgAKMsgFileType(char InputFileType);
void SetMsgAKMsgRecStatus(char InputRecStatus);
void SetMsgAKMsgMARK(char InputMARK);
#endif //define t_tablename

