#include "LocalIncludeFile.h"
#include "ui.h"

static PLOGFONT dfount = NULL ;

int UI_IDC_ID_BASE = 100;
UI_Object * create_Object ( HWND hWnd )
{
	UI_Object * object = NULL ;
	object = ( UI_Object * ) malloc ( sizeof(UI_Object) ) ;
	object->hWnd = hWnd ;
	init_Object ( object ) ;
	return object ;
}

void destruction_Object ( UI_Object * object )
{
	if ( object->text.plogfont != dfount )
	{
		free ( object->text.plogfont ) ;
	}

	if ( object->paneltext.plogfont != dfount )
	{
		free ( object->paneltext.plogfont ) ;
	}

	free ( object ) ;
}
void init_Object ( UI_Object *object )
{
	object->parent = NULL ;
	object->x = 0 ;
	object->y = 0 ;
	object->width = 0 ;
	object->height = 0 ;
	object->padding = 0 ;
	object->border.width = 2 ;
	object->border.linecolor1 = RGB(172,168,153) ;
	object->border.linecolor2 = RGB(250,250,250) ;
	object->background.color = RGB(236,233,216) ;
	object->background.image = NULL ;
	object->text.align = DT_CENTER ;
	object->text.valign = DT_VCENTER ;
	object->text.isSingleline = T ;
	object->text.type = NULL ;
	object->text.family = "song" ;
	object->text.charset = CHARSET ;
	object->text.weight = FONT_WEIGHT_REGULAR ;
	object->text.slant = FONT_SLANT_ROMAN ;
	object->text.set_width = FONT_SETWIDTH_NORMAL ;
	object->text.spacing = FONT_SPACING_CHARCELL ;
	object->text.underline = FONT_UNDERLINE_NONE ;
	object->text.struckout = FONT_STRUCKOUT_NONE ;
	object->text.size = 12 ;
	object->text.rotation = 0 ;
	object->text.info = NULL ;
	object->text.color = RGB(0, 0, 0) ;
	object->ispanel = F ;
	object->paneltext.align = DT_LEFT ;
	object->paneltext.valign = DT_VCENTER ;
	object->paneltext.isSingleline = T ;
	object->paneltext.type = NULL ;
	object->paneltext.family = "song" ;
	object->paneltext.charset = CHARSET ;
	object->paneltext.weight = FONT_WEIGHT_REGULAR ;
	object->paneltext.slant = FONT_SLANT_ROMAN ;
	object->paneltext.set_width = FONT_SETWIDTH_NORMAL ;
	object->paneltext.spacing = FONT_SPACING_CHARCELL ;
	object->paneltext.underline = FONT_UNDERLINE_NONE ;
	object->paneltext.struckout = FONT_STRUCKOUT_NONE ;
	object->paneltext.size = 12 ;
	object->paneltext.rotation = 0 ;
	object->paneltext.info = NULL ;
	object->paneltext.color = RGB(0, 0, 0) ;
	if ( dfount == NULL )
	{
		dfount = get_Font ( & ( object->text ) ) ;
	}
	object->text.plogfont = dfount ;
	object->paneltext.plogfont = dfount ;
	object->me = 0;
	object->type = Customize;
	object->IDC_ID = 0;
	object->isGroup = FALSE;
	object->enable = TRUE;
	object->checked = FALSE;
}

int get_x ( UI_Object *object )
{
	return object->x + ( object->parent != NULL ? get_x ( object->parent ) + object->parent->border.width
	        + object->parent->padding : 0 ) ;
}
int get_y ( UI_Object *object )
{
	return object->y + ( object->parent != NULL ? get_y ( object->parent ) + object->parent->border.width
	        + object->parent->padding : 0 ) ;
}
int get_width ( UI_Object *object )
{
	return object->width + ( object->parent != NULL ? get_width ( object->parent ) + object->parent->border.width
	        + object->parent->padding : 0 ) ;
}
int get_height ( UI_Object *object )
{
	return object->height + ( object->parent != NULL ? get_height ( object->parent ) + object->parent->border.width
	        + object->parent->padding : 0 ) ;
}

void set_Parent ( UI_Object *pobject , UI_Object *object )
{
	object->parent = pobject ;
}

void set_XYWH ( UI_Object *object , RECT rt )
{
	object->x = rt.left ;
	object->y = rt.top ;
	object->width = rt.right - rt.left ;
	object->height = rt.bottom - rt.top ;
}

PLOGFONT get_Font ( UI_Text *font )
{
	return CreateLogFont ( font->type , font->family , font->charset , font->weight , font->slant , font->set_width ,
	        font->spacing , font->underline , font->struckout , font->size , font->rotation ) ;
}

void set_Font ( UI_Text *font )
{
	font->plogfont = get_Font ( font ) ;
}
//void set_Text_Value ( char ** info , char * str )
//{
//	char *newstr ;
//	int l = 0 ;
//	if ( *info != NULL )
//	{
//		l = strlen ( str ) ;
//
//		free ( *info ) ;
//		newstr = ( char * ) malloc ( sizeof(char) * l ) ;
//		memset ( newstr , 0x00 , l ) ;
//		strcpy ( newstr , str ) ;
//		*info = newstr ;
//	}
//
//}
void UI_Init(UI_Object *object)
{
	DWORD style = WS_CHILD;
	char* dsclass="";
	if(object!=NULL)
	{
		if(object->me==0)
		{
			switch(object->type)
			{
			case RadioButton:
				dsclass = CTRL_BUTTON;
				style = WS_CHILD | BS_AUTORADIOBUTTON;
				break;
			case GroupBox:
				dsclass = CTRL_STATIC;
				style = WS_CHILD | SS_GROUPBOX;
				break;
			default:
				object->type= Customize;
				object->me=0;
				return;
				break;
			}
			if(object->isGroup==TRUE)
			{
				style = style | WS_GROUP;
			}
			object->me = CreateWindow(dsclass,object->text.info,style,UI_IDC_ID_BASE++,object->x,object->y,object->width,object->height,object->hWnd,0);
		}
	}
}
void UI_Show(UI_Object *object)
{
	if(object==NULL)
	{
		return;
	}
	if(object->type!= Customize)
	{
		//UpdateWindow(object->me, TRUE);
		//InvalidateRect(object->me,NULL,TRUE);
		ShowWindow(object->me, SW_SHOW);
	}
}
void UI_Hide(UI_Object *object)
{
	if(object==NULL)
	{
		return;
	}
	if(object->type!= Customize)
	{
		ShowWindow(object->me, SW_HIDE);
	}
}
sem_t ui_sem_t;
void UI_Init_SEM()
{
	sem_init (&ui_sem_t, 0, 1);
}
void UI_Destroy_SEM()
{
	sem_destroy(&ui_sem_t);
}
void UI_Wait()
{
	sem_wait(&ui_sem_t);
}
void UI_Post()
{
	sem_post(&ui_sem_t);
}
void Draw_Object ( UI_Object *object )
{
	UI_Wait();
	UI_Init(object);
	UI_Hide(object);
	Draw_Border ( object ) ;
	Draw_Background ( object ) ;
	Draw_Text ( object ) ;
	Draw_PanelText ( object ) ;
	UI_Show(object);
	UI_Post();
}
void Draw_Text ( UI_Object *object )
{
	if ( object->text.info != NULL )
	{
		if(object->type== Customize)
		{
			SetBkMode ( HDC_SCREEN , BM_TRANSPARENT ) ;
			SelectFont ( HDC_SCREEN , object->text.plogfont ) ;
			SetTextColor ( HDC_SCREEN , object->text.color ) ;
			RECT rt ;
			rt.left = get_x ( object ) + object->border.width + object->padding ;
			rt.top = get_y ( object ) + object->border.width + object->padding ;
			rt.right = get_x ( object ) + object->width - object->border.width - object->padding ;
			rt.bottom = get_y ( object ) + object->height - object->border.width - object->padding ;
			DrawText ( HDC_SCREEN , object->text.info , -1 , &rt , object->text.align | object->text.valign
					| ( object->text.isSingleline == T ? DT_SINGLELINE : DT_WORDBREAK ) ) ;
		}

		else
		{
			SetWindowFont ( object->me , object->text.plogfont ) ;
			SetWindowElementColorEx(object->me,FGC_CONTROL_NORMAL,object->text.color);
			SetWindowText(object->me,object->text.info);
		}
	}
}

void Draw_PanelText ( UI_Object *object )
{
	if ( object->ispanel == T && object->paneltext.info != NULL )
	{
		//SetBkMode(HDC_SCREEN, BM_TRANSPARENT);
		SelectFont ( HDC_SCREEN , object->paneltext.plogfont ) ;
		SetBrushColor ( HDC_SCREEN , object->background.color ) ;
		SetTextColor ( HDC_SCREEN , object->paneltext.color ) ;
		SetBkMode ( HDC_SCREEN , BM_OPAQUE ) ;
		SetBkColor ( HDC_SCREEN , object->background.color ) ;
		TextOut ( HDC_SCREEN , get_x ( object ) + 10 , get_y ( object ) - object->paneltext.size / 2 ,
		        object->paneltext.info ) ;
	}
}

void Draw_Background ( UI_Object *object )
{
	if(object->type== Customize)
	{
		SetBrushColor ( HDC_SCREEN , object->background.color ) ;
		FillBox ( HDC_SCREEN , get_x ( object ) + object->border.width , get_y ( object ) + object->border.width ,
				object->width - object->border.width * 2 + 1 , object->height - object->border.width * 2 + 1 ) ;
		if ( object->background.image != NULL )
		{
			FillBoxWithBitmap ( HDC_SCREEN , get_x ( object ) , get_y ( object ) , 0 , 0 , object->background.image ) ;
		}
	}
	else
	{
		SetWindowBkColor ( object->me , object->background.color ) ;
	}
}

void Draw_Border ( UI_Object *object )
{
	if ( object->border.width > 0 )
	{
		if(object->type== Customize)
		{
			RECT rectParent ;
			GetClientRect ( object->hWnd , &rectParent ) ;


			//»­ÉÏ²à±ß
			SetPenColor ( HDC_SCREEN , object->border.linecolor1 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) , rectParent.top + get_y ( object ) ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width , rectParent.top + get_y ( object ) ) ;

			SetPenColor ( HDC_SCREEN , object->border.linecolor2 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) , rectParent.top + get_y ( object ) + 1 ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width , rectParent.top + get_y ( object )
					+ 1 ) ;


			//»­×ó²à±ß
			SetPenColor ( HDC_SCREEN , object->border.linecolor1 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) , rectParent.top + get_y ( object ) ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) , rectParent.top + get_y ( object ) + object->height ) ;

			SetPenColor ( HDC_SCREEN , object->border.linecolor2 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + 1 , rectParent.top + get_y ( object ) ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + 1 , rectParent.top + get_y ( object )
					+ object->height ) ;


			//»­ÏÂ²à±ß
			SetPenColor ( HDC_SCREEN , object->border.linecolor1 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) , rectParent.top + get_y ( object ) + object->height
					- 1 ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width , rectParent.top + get_y ( object )
					+ object->height - 1 ) ;

			SetPenColor ( HDC_SCREEN , object->border.linecolor2 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) , rectParent.top + get_y ( object ) + object->height ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width , rectParent.top + get_y ( object )
					+ object->height ) ;


			//»­ÓÒ²à±ß
			SetPenColor ( HDC_SCREEN , object->border.linecolor1 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width - 1 , rectParent.top + get_y ( object ) ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width - 1 , rectParent.top + get_y ( object )
					+ object->height ) ;

			SetPenColor ( HDC_SCREEN , object->border.linecolor2 ) ;
			MoveTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width , rectParent.top + get_y ( object ) ) ;
			LineTo ( HDC_SCREEN , rectParent.left + get_x ( object ) + object->width , rectParent.top + get_y ( object )
					+ object->height ) ;
		}
		else
		{
			MoveWindow (object->me, get_x ( object ), get_y ( object ),object->width, object->height, TRUE);
			SetWindowElementColorEx(object->me,WEC_3DBOX_LIGHT,object->border.linecolor1);
			SetWindowElementColorEx(object->me,WEC_3DBOX_DARK ,object->border.linecolor2);
		}
	}
}

void set_Text ( UI_Object *object , char *info )
{
	//set_Text_Value(&(object->text.info),info);
	object->text.info = info ;
	Draw_Object ( object ) ;
}
void set_BackGround_Image ( UI_Object *object , BITMAP *image )
{
	object->background.image = image ;
	Draw_Object ( object ) ;
}

void set_Enable(UI_Object *object,int flag)
{
	if(object==NULL)
	{
		return;
	}
	if(object->type!= Customize)
	{
		UI_Init(object);
		object->enable = flag;
		EnableWindow (object->me, object->enable);
	}
}
int get_Enable(UI_Object *object)
{
	if(object==NULL)
	{
		return TRUE;
	}
	return object->enable;
}
void set_RadioButtonCheck(UI_Object *object,int flag)
{
	if(object==NULL)
	{
		return;
	}
	if(object->type== RadioButton)
	{
		UI_Init(object);
		object->checked = flag;
		SendMessage ( object->me, BM_SETCHECK , object->checked==TRUE?BST_CHECKED:BST_UNCHECKED , 0 ) ;
	}
}
int  get_RadioButtonCheck(UI_Object *object)
{
	if(object==NULL)
	{
		return FALSE;
	}
	return object->checked;
}
//camera
//int cam_fd ;
//static unsigned char *row_rgb = NULL ;
//static unsigned char *rgb = NULL ;
//void Create_camera ( int x , int y )
//{
//	unsigned long arg ;
//	cam_fd = open ( "/dev/camera" , O_RDONLY ) ;
//	if ( cam_fd != -1 )
//	{
//		arg = y << 16 ;
//		arg += x ;
//		ioctl ( cam_fd , 0x1111 , arg ) ;
//		ioctl ( cam_fd , 0x2222 , arg ) ;
//	}
//}
