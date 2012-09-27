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

//定义RGB颜色

//create 24 bit 8/8/8 format pixel (0x00RRGGBB) from RGB triplet


//新添加的颜色宏
#define GLOAB_BACK_COLOR            RGB(100,200,100)     //全局背景色
#define BACK_COLOR                  RGB(227,227,227)     //框框背景色
#define KAXIANG_BACK_COLOR          RGB(193,193,193)     //卡箱信息和事件报警框背景色
#define WHITE_COLOR       RGB(255,255,255)
#define LOGINAFTER_COLOR            RGB(204,102,102)				//登录成功后，车道是关闭的。
#define REDALARM_COLOR		RGB(255,0,0)
#define ALARMBOXTEXTCOLOR   RGB(0,0,255)


//定义窗口、控件、边框等颜色值、度量值

#define WND_BORDER_COLOR	RGB(192, 192, 250)	//窗口外边框颜色
#define WND_TITLEBAR_COLOR	RGB(97, 92, 173)		//窗口标题栏底色
#define WND_BACK_COLOR		RGB(188, 192, 199)	//窗口背景色
#define TEXT_COLOR		    RGB(0, 0, 0)	        //文字颜色
#define TITLE_TEXT_COLOR		RGB(254, 254, 254)	//文字颜色
#define EDIT_BORDER_COLOR	RGB(0, 192, 192)		//编辑框边框颜色	
#define EDIT_SELECTED_COLOR	RGB(0, 128, 128)		//编辑框选中时的底色
#define EDIT_INPUT_COLOR		RGB(0, 128, 0)		//编辑框编辑时的底色
#define EDIT_SLIDER_COLOR	RGB(250, 128, 0)		//编辑框右侧滚动条颜色
#define EDIT_SLIDER_COLOR	RGB(250, 128, 0)		//编辑框右侧滚动条颜色
#define EDIT_BACK_COLOR	    RGB(254, 254, 254)	//编辑框未被选中时的背景颜色
#define EDIT_FRONT_COLOR	RGB(0, 0, 0)	//编辑框未被选中时的背景颜色
#define BTN_BORDER_COLOR	RGB(255, 172, 214)	//按钮控件边框颜色
#define BTN_SELECTED_COLOR	RGB(128, 0, 128)		//按钮选中时的底色

#define TISHI_BACK_COLOR	    RGB(59, 37, 120)		//按钮选中时的底色





//定义风格窗口需要的颜色

#define SUBBKCOLOR              RGB(236,233,216)//窗体背景的浅灰色
#define SUBTITLECOLOR           RGB(0,0,255)//标题栏底色
#define EDITCTLBKCOLOR          RGB(250,250,250)//标题栏底色
#define OUTPICBKCOLOR           RGB(189,191,208)//阳图文字背景色
#define INPICBKCOLOR            RGB(180,230,255)//阴图文字背景色
#define SUBMENUBKCOLOR          RGB(255,255,192)//小弹出菜单背景黄色
#define SUBMENUFRAMCOLOR        RGB(0,0,0)//小弹出菜单边框黑色
#define SUBMENUEDITFRAMCOLOR    RGB(0,255,0)//小弹出菜单选中时绿色
#define SUBMENUSELECTBKCOLOR    RGB(255,128,0)//小弹出菜单选中时背景褐色
#define SEPLINECOLOR1           RGB(172,168,153)//两条分隔线中上方单线的颜色和右下边框里层的颜色
#define SEPLINECOLOR2           RGB(250,250,250)//两条分隔线中下方单线的颜色和左上边框里层颜色
#define RBFRAMECOLOR            RGB(113,111,100)//右下边框外层的颜色
#define LTFRAMECOLOR            RGB(241,239,226)//左上边框外层的颜色
#define BTNTEXTCOLOR            RGB(0,0,0)	//风格窗口中按钮上的黑字颜色





#endif
