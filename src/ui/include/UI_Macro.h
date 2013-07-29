#ifndef __UI_Macro_H__
#define __UI_Macro_H__
#define RGB888(r,g,b)	\
	(((r)  << 16) | ((g) << 8) | (b) )

//create 16 bit 5/6/5 format pixel from RGB triplet
#define RGB565(r,g,b)	\
	((((r) & 0xf8) << 8) | (((g) & 0xfc) << 3) | (((b) & 0xf8) >> 3))

//create 15 bit 5/5/5 format pixel from RGB triplet
#define RGB555(r,g,b)	\
	((((r) & 0xf8) << 7) | (((g) & 0xf8) << 3) | (((b) & 0xf8) >> 3))

//create 8 bit 3/3/2 format pixel from RGB triplet
#define RGB332(r,g,b)	\
	(((r) & 0xe0) | (((g) & 0xe0) >> 3) | (((b) & 0xc0) >> 6))

#define RGB(r,g,b)	RGB565(r,g,b)

//����RGB��ɫ

//create 24 bit 8/8/8 format pixel (0x00RRGGBB) from RGB triplet


//����ӵ���ɫ��
#define GLOAB_BACK_COLOR            RGB(100,200,100)     //ȫ�ֱ���ɫ
#define BACK_COLOR                  RGB(227,227,227)     //��򱳾�ɫ
#define KAXIANG_BACK_COLOR          RGB(193,193,193)     //������Ϣ���¼������򱳾�ɫ
#define WHITE_COLOR       RGB(255,255,255)
#define LOGINAFTER_COLOR            RGB(204,102,102)				//��¼�ɹ��󣬳����ǹرյġ�
#define REDALARM_COLOR		RGB(255,0,0)
#define ALARMBOXTEXTCOLOR   RGB(0,0,255)


//���崰�ڡ��ؼ����߿����ɫֵ������ֵ

#define WND_BORDER_COLOR	RGB(192, 192, 250)	//������߿���ɫ
#define WND_TITLEBAR_COLOR	RGB(97, 92, 173)		//���ڱ�������ɫ
#define WND_BACK_COLOR		RGB(188, 192, 199)	//���ڱ���ɫ
#define TEXT_COLOR		    RGB(0, 0, 0)	        //������ɫ
#define TITLE_TEXT_COLOR		RGB(254, 254, 254)	//������ɫ
#define EDIT_BORDER_COLOR	RGB(0, 192, 192)		//�༭��߿���ɫ	
#define EDIT_SELECTED_COLOR	RGB(0, 128, 128)		//�༭��ѡ��ʱ�ĵ�ɫ
#define EDIT_INPUT_COLOR		RGB(0, 128, 0)		//�༭��༭ʱ�ĵ�ɫ
#define EDIT_SLIDER_COLOR	RGB(250, 128, 0)		//�༭���Ҳ��������ɫ
#define EDIT_SLIDER_COLOR	RGB(250, 128, 0)		//�༭���Ҳ��������ɫ
#define EDIT_BACK_COLOR	    RGB(254, 254, 254)	//�༭��δ��ѡ��ʱ�ı�����ɫ
#define EDIT_FRONT_COLOR	RGB(0, 0, 0)	//�༭��δ��ѡ��ʱ�ı�����ɫ
#define BTN_BORDER_COLOR	RGB(255, 172, 214)	//��ť�ؼ��߿���ɫ
#define BTN_SELECTED_COLOR	RGB(128, 0, 128)		//��ťѡ��ʱ�ĵ�ɫ

#define TISHI_BACK_COLOR	    RGB(59, 37, 120)		//��ťѡ��ʱ�ĵ�ɫ





//�����񴰿���Ҫ����ɫ

#define SUBBKCOLOR              RGB(236,233,216)//���屳����ǳ��ɫ
#define SUBTITLECOLOR           RGB(0,0,255)//��������ɫ
#define EDITCTLBKCOLOR          RGB(250,250,250)//��������ɫ
#define OUTPICBKCOLOR           RGB(189,191,208)//��ͼ���ֱ���ɫ
#define INPICBKCOLOR            RGB(180,230,255)//��ͼ���ֱ���ɫ
#define SUBMENUBKCOLOR          RGB(255,255,192)//С�����˵�������ɫ
#define SUBMENUFRAMCOLOR        RGB(0,0,0)//С�����˵��߿��ɫ
#define SUBMENUEDITFRAMCOLOR    RGB(0,255,0)//С�����˵�ѡ��ʱ��ɫ
#define SUBMENUSELECTBKCOLOR    RGB(255,128,0)//С�����˵�ѡ��ʱ������ɫ
#define SEPLINECOLOR1           RGB(172,168,153)//�����ָ������Ϸ����ߵ���ɫ�����±߿�������ɫ
#define SEPLINECOLOR2           RGB(250,250,250)//�����ָ������·����ߵ���ɫ�����ϱ߿������ɫ
#define RBFRAMECOLOR            RGB(113,111,100)//���±߿�������ɫ
#define LTFRAMECOLOR            RGB(241,239,226)//���ϱ߿�������ɫ
#define BTNTEXTCOLOR            RGB(0,0,0)	//��񴰿��а�ť�ϵĺ�����ɫ





#endif
