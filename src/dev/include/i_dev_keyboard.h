//�����շѼ��̼�ֵ

#ifndef __i_dev_keyboard_H__
#define __i_dev_keyboard_H__

#define MSG_BAR_DOWN		5004
#define MSG_BAR_UP			5003
#define MSG_PIC_DOWN		5002
#define MSG_PIC_UP			5001
#define MSG_TCORET			(MSG_USER+14)
#define MSG_REMOTECONTROL	(MSG_USER+15)
#define S_PASSLINEUP    1000 //ͨ����Ȧ������ ���ڴ����ڲ�ʹ�ã�һ�㲻�����¼�����

#define G30KEYBORD

#ifdef S303KEYBORD
	#define VK_0				11	//'0'
	#define VK_1				2	//'1'
	#define VK_2				3	//'2'
	#define VK_3				4	//'3'
	#define VK_4				5	//'4'
	#define VK_5				6	//'5'
	#define VK_6				7	//'6'
	#define VK_7				8	//'7'
	#define VK_8				9	//'8'
	#define VK_9				10	//'9'
	#define VK_CANCEL			1	//19	//ȡ��		'r'
	#define VK_YOUHUICARD		24	//'o'	�Żݿ���
	#define VK_MOUNTHCARD		25	//	 ��Ʊ��
	#define VK_QIANKUAN			34  //25	//'p'	//48	//����1		'b'
	#define VK_LVSETONGDAO		47	//'v'	//48	//����1		'b'
	#define VK_RETURN			28	//ȷ��
	#define VK_WEIZHANG			360	//'j'	//Υ��		'n'
	#define VK_JUNCHE			37	//'k'	//16	//����		'q'
	#define VK_GONGWU			38	//'l'	//25	//����		'p'
	#define VK_BEIYONG			19	//'R'	//48	//����
	#define VK_LONGYONG			52	//'T'	//48	//����
	#define VK_SHANGBAN			48	//'b'	//�ϰ�		'y'
	#define VK_XIABAN			46	//'c'    //�°�		'z'
	#define VK_CLOSE_YPD		    45	//'x'	//��ͣ�շ�	'i'
	#define VK_OPEN_YPD			44	//'z'	//�����շ�	'v'
	#define VK_OPEN				1600	//'q'    //����		'u'
	#define VK_CLOSE			1800	//'e'    //���		'x'
	#define VK_MONI				35	//'h'	//ģ��		'o'
	#define VK_CHEDUI_G			33	//'f'	//����-���� 'k'
	#define VK_CHEDUI_R			90	//����-��ͨ 'l'
	#define VK_URGENT			23	//'i' ����
	#define VK_LEFT				330	//'a'    //����	qQ
	#define VK_RIGHT			32	//'d'   //�ҹ��	rR
	#define VK_UP				17	//'w'	//�Ϲ��	sS
	#define VK_DOWN				31	//'s'	//�¹��	tT
	#define VK_LANGAN			-2	//30 ������
	#define VK_BREAKAUTOMAN			36	//'j'	//Υ��		'n'
	#define VK_CHAHAO			21
#endif
#ifdef G30KEYBORD
	#define VK_System 18 
	#define VK_CANCEL 1 
	#define VK_URGENT 23 
	#define VK_XIABAN 46 
	#define VK_SHANGBAN 48 
	#define VK_CLOSE_YPD 45 
	#define VK_OPEN_YPD 44 
	#define VK_QIANKUAN 34 
	#define VK_BEIYONG 19 
	#define VK_UP 31 
	#define VK_DOWN 17 
	#define VK_WEIZHANG 36 
	#define VK_JUNCHE 37 
	#define VK_GONGWU 38 
	#define VK_Dot 52 
	#define VK_0 11 
	#define VK_00 0 
	#define VK_1 2 
	#define VK_2 3 
	#define VK_3 4 
	#define VK_4 5 
	#define VK_5 6 
	#define VK_6 7 
	#define VK_7 8 
	#define VK_8 9 
	#define VK_9 10 
	#define VK_YOUHUICARD 24 
	#define VK_MOUNTHCARD 25 
	#define VK_LVSETONGDAO 47 
	#define VK_LONGYONG 49 
	#define VK_SVCCARD 20 
	#define VK_TYYLCARD 50 
	#define VK_Weight 16 
	#define VK_IC 22 
	#define VK_WeightDaoche 33 
	#define VK_WeightShouwei 21 
	#define VK_MONI 35 
	#define VK_RETURN 28 
	#define VK_TRUCK 13 
	#define VK_JIAOJIE 251 
	#define VK_QIANKUANCHE 252 
	#define VK_CHANGE 253 
	#define VK_CHEDUI_G 254 
	#define VK_RIGHT 255 
	#define VK_LEFT 256 
	#define VK_CLOSE 257 
	#define VK_OPEN 258 
	#define VK_CHAHAO 259
	#define VK_BREAKAUTOMAN			260
#endif
int GetKeyMapValue(char *ItemName);
int LoadKeyBoardFile(void);
int  KeyTran(int keyvalue);
int  KeyNameTran(char *KeyName);
void InitKeyBoard_KeyMap(void);
int KeyChangCode(int nKey);
#endif
