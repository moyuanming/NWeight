//定义收费键盘键值

#ifndef __i_dev_keyboard_H__
#define __i_dev_keyboard_H__

#define MSG_BAR_DOWN		5004
#define MSG_BAR_UP			5003
#define MSG_PIC_DOWN		5002
#define MSG_PIC_UP			5001
#define MSG_TCORET			(MSG_USER+14)
#define MSG_REMOTECONTROL	(MSG_USER+15)
#define S_PASSLINEUP    1000 //通过线圈上升沿 用于代码内部使用，一般不用于事件发送
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
#define VK_RETURN 28 
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

#define  VK_CardBox 45
#define  VK_HappyDay 20
#define  VK_TranCard 44
#define VK_SVC 24
#define	VK_JZK 25
#define VK_BEIYONG2 16
#define 	VK_BEIYONG3 19

int GetKeyMapValue(char *ItemName);
int LoadKeyBoardFile(void);
int  KeyTran(int keyvalue);
int  KeyNameTran(char *KeyName);
void InitKeyBoard_KeyMap(void);
int KeyChangCode(int nKey);

#endif
