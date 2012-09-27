#ifndef __800_600_H__
#define __800_600_H__

RECT RtBaojing = { 5 , 11 , 50 , 54 } ;
RECT RtJiaotong = { 5 , 54 , 50 , 91 } ;
RECT RtLangan = { 50 , 12 , 128 , 91 } ;
RECT RtZhuaPaiXianQuan = { 164 , 12 , 203 , 44 } ;
RECT RtTongGuoXianQuan = { 164 , 55 , 203 , 87 } ;
RECT RtZhuaPaiXianQuanText = { 132 , 20 , 156 , 44 } ;
RECT RtTongGuoXianQuanText = { 132 , 62 , 156 , 86 } ;
RECT RtYupeng = { 5 , 17 , 69 , 81 } ;
RECT RtPrint = { 75 , 17 , 180 , 72 } ;
//�༭��
RECT RtCarText = { 4 , 25 , 167 , 47+3 } ; //�����ı���
RECT RtEquipmentState = { 583 , 25 , 795 , 47+3 } ; //�豸״̬�ı���
RECT RtEnterInfoText = { 171 , 25 , 338 , 47+3 } ;//�����Ϣ
RECT RtPassChargeText = { 342 , 25 , 459 , 47+3 } ; //ͨ�з�
RECT RtPaymentText = { 463 , 25 , 580 , 47+3 } ; //����

//�ڶ���
RECT RtCarTextInfo = { 4 , 51+3 , 167 , 148+3 } ; //������Ϣ��
RECT RtEquipmentStateInfo = { 583 , 51+3 , 795 , 148+3 } ;//�豸״̬��Ϣ��
RECT RtEnterInfo = { 171 , 51+3 , 338 , 148+3 } ; //�����Ϣ
RECT RtEnterInfoBJ = { 171+2 , 131 , 338-2 , 148+3-2 } ; //�����Ϣ
RECT RtPassChargeInfo = { 342 , 51+3 , 459 , 148+3 } ; //ͨ�з���Ϣ
RECT RtPaymentInfo = { 463 , 51+3 , 580 , 148+3 } ; //������Ϣ

//������
RECT RtCarNoInfo = { 4 , 152+3 , 167 , 170+6 } ;
RECT RtRorwardEnterInfo = { 171 , 152+3 , 338 , 170+6 } ;
RECT RtForwardChargeInfo = { 342 , 152+3 , 459 , 170+6 } ;
RECT RtForwardPaymentInfo = { 463 , 152+3 , 580 , 170+6 } ;

RECT RtPassCarNum = { 583 , 152+3 , 620 , 170+6 } ;
RECT RtAutoLanganState = { 624 , 152+3 , 682 , 170+6 } ;
RECT RtWeightInfo = { 685 , 152+3 , 795 , 170+6 } ;

//������
//��
RECT RtOperateInfo = { 4 , 180 , 356 , 203 } ;
RECT RtWorkMode1 = { 360 , 180 , 529 , 203 } ;
RECT RtWorkMode2 = { 533 , 180 , 682 , 203 } ;
RECT RtCurrentWeightInfo = { 685 , 180 , 795 , 203 } ;

RECT RtInformation = { 4 , 208 , 356 , 305 } ;

RECT RtVideo = { 4 , 308 , 356 , 596 } ;//352,288

RECT RtInputDataArea = { 360 , 208 , 682 , 481 } ;

RECT RtCurrentTime = { 360 , 484 , 682 , 506 } ;

RECT RtArrivedCarWeightInfo = { 685 , 208 , 795 , 506 } ;

RECT RtCardBoxInfo = { 360 , 509 , 795 , 596 } ;

//�¼�
RECT RtEvent = { 180 , 17 , 425 , 72 } ;
RECT RtEventText = { 180 , 1 , 425 , 16 } ;

//�û���
RECT RtLoginUSRPanel = { 5+40 , 5+20 , 205+40 , 50+20 } ;
RECT RtLoginUSR = { 5 , 5 , 180 , 25 } ;
RECT RtLoginPWDPanel = { 5+40 , 10+20+50 , 205+40 , 5+20+50 +50} ;
RECT RtLoginPWD = { 5 , 5 , 180 , 25 } ;

//�˵�ѡ��
RECT RtMenu = {45,25,245,200};
RECT RtShiShou = {45,210,245,230};
RECT RtZhaoling = {45,240,245,260};
/***************************************************************
 *�����࿪�����ź�λͼ
 ***************************************************************/
BITMAP bmSLstop ;
BITMAP bmBaojingG , bmBaojingA , bmAutoLanganDown , bmAutoLanganUp , bmYupengR , bmCarArrived , bmJiaotongR ,
        bmJiaotongG , bmCarGo , bmGuanggeArrived , bmYupengG , bmHandLanganUp , bmHandLanganDown , bmGuanggeGo , bmLup ,axlet1,axlet2,axlet3;
/***************************************************************
 *�������źŰ�ť
 ***************************************************************/

#endif 

