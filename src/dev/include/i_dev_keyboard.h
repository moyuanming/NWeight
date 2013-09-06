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
#define  VK_CardBox 261
#define  VK_HappyDay 262
#define  VK_TranCard 263
#define VK_SVC 264
#define	VK_JZK 265
#define VK_BEIYONG2 267
#define 	VK_BEIYONG3 268
#define VK_BREAKAUTOMAN			260
int GetKeyMapValue(char *ItemName);
int LoadKeyBoardFile(void);
int  KeyTran(int keyvalue);
int  KeyNameTran(char *KeyName);
void InitKeyBoard_KeyMap(void);
int KeyChangCode(int nKey);
#endif
