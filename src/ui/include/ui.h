#ifndef __EMRC_UI_H__
#define __EMRC_UI_H__

#define CHARSET "GB2312"
typedef int color ;
//½á¹¹Ìå
typedef struct ui_border
{
		int width ;
		color linecolor1 ;
		color linecolor2 ;
} UI_Border ;

typedef struct ui_background
{
		color color ;
		BITMAP *image ;
} UI_Background ;

typedef struct ui_text
{
		color color ;
		int size ;
		int align ;
		int valign ;
		int isSingleline ;
		char *type ;
		char *family ;
		char *charset ;
		char *info ;
		char weight ;
		char slant ;
		char set_width ;
		char spacing ;
		char underline ;
		char struckout ;
		int rotation ;
		PLOGFONT *plogfont ;
} UI_Text ;
typedef enum{Customize,GroupBox,RadioButton}UI_Type;
typedef struct ui_object
{
		HWND hWnd ;
		int x ;
		int y ;
		int width ;
		int height ;
		int padding ;
		int ispanel ;
		UI_Border border ;
		UI_Background background ;
		UI_Text text ;
		UI_Text paneltext ;
		struct ui_object *parent ;
		HWND me;
		UI_Type type;
		int IDC_ID;
		int isGroup;
		int enable;
		int checked;
} UI_Object ;

UI_Object * create_Object ( HWND hWnd ) ;

void destruction_Object ( UI_Object * object ) ;

void init_Object ( UI_Object * object ) ;

void Draw_Object ( UI_Object * object ) ;

void Draw_Border ( UI_Object * object ) ;

PLOGFONT get_Font ( UI_Text *font ) ;

void Draw_Background ( UI_Object * object ) ;

void Draw_Text ( UI_Object *object ) ;

void Draw_PanelText ( UI_Object *object ) ;

void set_Text ( UI_Object *object , char *info ) ;

void set_BackGround_Image ( UI_Object *object , BITMAP *image ) ;

void set_XYWH ( UI_Object *object , RECT rt ) ;

void set_Parent ( UI_Object *pobject , UI_Object *object ) ;
int get_x ( UI_Object *object ) ;
int get_y ( UI_Object *object ) ;
int get_width ( UI_Object *object ) ;
int get_height ( UI_Object *object ) ;

void set_Font ( UI_Text *font ) ;

void set_Enable(UI_Object *object,int flag);
int  get_Enable(UI_Object *object);
void set_RadioButtonCheck(UI_Object *object,int flag);
int  get_RadioButtonCheck(UI_Object *object);

void UI_Show(UI_Object *object);
void UI_Hide(UI_Object *object);
void UI_Init_SEM(void);
void UI_Destroy_SEM(void);
void UI_Wait(void);
void UI_Post(void);
//camera
//void Create_camera ( int x , int y );
#endif
