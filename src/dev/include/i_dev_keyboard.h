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
	#define VK_System 300 
	#define VK_CANCEL 301
	#define VK_URGENT 302
	#define VK_XIABAN 303
	#define VK_SHANGBAN 304 
	#define VK_CLOSE_YPD 305 
	#define VK_OPEN_YPD 3050
	#define VK_QIANKUAN 307 
	#define VK_BEIYONG 308
	#define VK_UP 310 
	#define VK_DOWN 311 
	#define VK_WEIZHANG 312 
	#define VK_JUNCHE 313
	#define VK_GONGWU 314
	#define VK_Dot 315 

	#define VK_00 317 
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
	#define VK_YOUHUICARD 327 
	#define VK_MOUNTHCARD 328 
	#define VK_LVSETONGDAO 329 
	#define VK_LONGYONG 330 
	#define VK_SVCCARD 331 
	#define VK_TYYLCARD 332 
	#define VK_Weight 334 
	#define VK_IC 335
	#define VK_WeightDaoche 336 
	#define VK_WeightShouwei 337 
	#define VK_MONI 338
	#define VK_RETURN 339 
	#define VK_TRUCK 340
	#define VK_JIAOJIE 341 
	#define VK_QIANKUANCHE 342 
	#define VK_CHANGE 343 
	#define VK_CHEDUI_G 345
	#define VK_RIGHT 346
	#define VK_LEFT 347 
	#define VK_CLOSE 348 
	#define VK_OPEN 349 
	#define VK_CHAHAO 350
	#define VK_BREAKAUTOMAN			260
	
#endif
int GetKeyMapValue(char *ItemName);
int LoadKeyBoardFile(void);
int  KeyTran(int keyvalue);
int  KeyNameTran(char *KeyName);
void InitKeyBoard_KeyMap(void);
int KeyChangCode(int nKey);
#endif
