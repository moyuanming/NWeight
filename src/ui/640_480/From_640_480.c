#include "linux_include.h"
#include "UI_Macro.h"
#include "640_480.h"
#include "From_640_480.h"
static HWND From_Handl=HWND_INVALID;
HWND  UI_Out_640_480_Get_From_Handl(void)
{	
	return From_Handl;
}
void UI_Out_640_480_Set_From_Handl(HWND hwnd)
{	
	From_Handl=hwnd;

}
void UI_Out_640_480_InitFrom(HWND hWnd)
{
	HDC hDC;
	//风格化窗口标题条和边框
	hDC = GetClientDC(hWnd);      
	 
	UI_In_640_480_DrawEditCtl(hWnd,rec10.left ,rec10.bottom +5,rec10.right-rec10.left,rec9.bottom-rec10.bottom-5,WND_BACK_COLOR);
	UI_In_640_480_Show_SeparateRect(hWnd,rec10.left ,rec10.bottom +5,rec10.right-rec10.left,(rec9.bottom-rec10.bottom-5)/2 -2,NULL);
	UI_In_640_480_Show_SeparateRect(hWnd,rec10.left +(rec10.right-rec10.left)/3 ,rec10.bottom +5,(rec10.right-rec10.left)/3,rec9.bottom-rec10.bottom-5,NULL);
	UI_In_640_480_DrawEditCtl(hWnd, rec1.left, rec1.top, rec1.right-rec1.left, rec1.bottom-rec1.top, EDIT_BACK_COLOR);		//当前时间
	UI_In_640_480_DrawEditCtl(hWnd, rec2.left, rec2.top, rec2.right-rec2.left, rec2.bottom-rec2.top, EDIT_BACK_COLOR);   
	//车型
	UI_In_640_480_DrawEditCtl(hWnd, rec3.left, rec3.top, rec3.right-rec3.left, rec3.bottom-rec3.top, EDIT_BACK_COLOR); 
	//车种
	UI_In_640_480_DrawEditCtl(hWnd, rec4.left, rec4.top, rec4.right-rec4.left, rec4.bottom-rec4.top, EDIT_BACK_COLOR);    

	//金额
	UI_In_640_480_DrawEditCtl(hWnd, rec5.left, rec5.top, rec5.right-rec5.left, rec5.bottom-rec5.top, EDIT_BACK_COLOR);    

	//提示左
	UI_In_640_480_DrawEditCtl(hWnd, rec6.left, rec6.top, rec6.right-rec6.left, rec6.bottom-rec6.top, EDIT_BACK_COLOR);    
	//提示右
	UI_In_640_480_DrawEditCtl(hWnd, rec7.left, rec7.top, rec7.right-rec7.left, rec7.bottom-rec7.top, EDIT_BACK_COLOR);    
	//视频窗口
	UI_In_640_480_DrawEditCtl(hWnd, rec10.left, rec10.top, rec10.right-rec10.left, rec10.bottom-rec10.top, WND_BACK_COLOR);
	//提示窗口
	UI_In_640_480_DrawEditCtl(hWnd, rec9.left, rec9.top, rec9.right-rec9.left, rec9.bottom-rec9.top, TISHI_BACK_COLOR);   

	//画上班时间
	SetBkColor(hDC, WND_BACK_COLOR);    
	UI_In_640_480_DrawEditCtl(hWnd,4,rec1.top,80,rec1.bottom-rec1.top,WND_BACK_COLOR);
	SetTextColor(hDC, TEXT_COLOR);  
	TextOut(hDC, rec1.left-16*4-8, rec1.bottom-18, "上班时间"); 
	SetBkColor(hDC, EDIT_BACK_COLOR);   
	SetTextColor(hDC, TEXT_COLOR);  
	DrawText(hDC, "                   ", -1, &rec1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);    

	//画当前时间
	UI_In_640_480_DrawEditCtl(hWnd,rec10.left ,rec1.top,rec2.left-rec1.right-5,rec1.bottom-rec1.top,WND_BACK_COLOR);
	SetBkColor(hDC, WND_BACK_COLOR);    

	SetTextColor(hDC, TEXT_COLOR);  
	TextOut(hDC, rec2.left-16*4-12, rec2.bottom-18, "当前时间");    
	SetBkColor(hDC, EDIT_BACK_COLOR);   
	SetTextColor(hDC, TEXT_COLOR);  
	DrawText(hDC, "2004-11-09 00:06:35", -1, &rec2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);    


	//画车型
	UI_In_640_480_DrawEditCtl(hWnd,4,rec3.top,24,rec3.bottom-rec3.top,WND_BACK_COLOR);
	SetBkColor(hDC, WND_BACK_COLOR);    
	SetTextColor(hDC, TEXT_COLOR);  
	TextOut(hDC, rec3.left-16-3, rec3.top+20, "车");    
	TextOut(hDC, rec3.left-16-3, rec3.top+20+16, "型"); 

	//画车种
	UI_In_640_480_DrawEditCtl(hWnd,rec3.right ,rec3.top,rec4.left-rec3.right,rec3.bottom-rec3.top,WND_BACK_COLOR);
	SetBkColor(hDC, WND_BACK_COLOR);    
	SetTextColor(hDC, TEXT_COLOR);  
	TextOut(hDC, rec4.left-16-3, rec4.top+20, "车");    
	TextOut(hDC, rec4.left-16-3, rec4.top+20+16, "种"); 

	//画金额
	UI_In_640_480_DrawEditCtl(hWnd,4,rec5.top,24,rec5.bottom-rec5.top,WND_BACK_COLOR);
	SetBkColor(hDC, WND_BACK_COLOR);    
	SetTextColor(hDC, TEXT_COLOR);  
	TextOut(hDC, rec5.left-16-3, rec5.top+25, "金");    
	TextOut(hDC, rec5.left-16-3, rec5.top+25+16, "额"); 

	//画提示
	//左提示
	UI_In_640_480_DrawEditCtl(hWnd,4,rec6.top,24,rec6.bottom-rec6.top,WND_BACK_COLOR);

	SetBkColor(hDC, WND_BACK_COLOR);    
	SetTextColor(hDC, TEXT_COLOR);  
	TextOut(hDC, rec6.left-16-3, rec6.top+7, "提"); 
	TextOut(hDC, rec6.left-16-3, rec6.top+7+16, "示");  
	//画提示区
	ReleaseDC(hDC); 
}
void UI_Out_640_480_LoadRes(void)
{
	char szFileName[80];
	int i;	
	LoadBitmap(HDC_SCREEN, &bmYuPengG, "res/button/bmYuPengG.bmp"); 
	LoadBitmap(HDC_SCREEN, &bmYuPengR, "res/button/bmYuPengR.bmp"); 
	LoadBitmap(HDC_SCREEN, &bmJiaoTongG, "res/button/bmJiaoTongG.bmp"); 
	LoadBitmap(HDC_SCREEN, &bmJiaoTongR, "res/button/bmJiaoTongR.bmp"); 
	LoadBitmap(HDC_SCREEN, &bmLanGanUp, "res/button/bmLanGanUp.bmp");   
	LoadBitmap(HDC_SCREEN, &bmLanGanDown, "res/button/bmLanGanDown.bmp");   
	LoadBitmap(HDC_SCREEN, &bmXianQuanG, "res/button/bmXianQuanG.bmp"); 
	LoadBitmap(HDC_SCREEN, &bmXianQuanR, "res/button/bmXianQuanR.bmp"); 
	LoadBitmap(HDC_SCREEN, &bmPrintG, "res/button/bmPrintG.bmp");   
	LoadBitmap(HDC_SCREEN, &bmPrintR, "res/button/bmPrintR.bmp");   
	rtEdit[0] =rec3;
	rtEdit[1] =rec4;
	rtEdit[2] =rec5;
	rtEdit[3] =rec6;
	rtEdit[4] =rec7;
	for(i=0;i<5;i++)
	{
		rtEdit[i].left +=3;
		rtEdit[i].top +=3;
		rtEdit[i].right -=3;
		rtEdit[i].bottom -=3;

	}
	for (i=0; i<11; i++)
	{
		sprintf(szFileName, "res/font/c%d.gif", i); 
		LoadBitmap(HDC_SCREEN, &(g_bmC[i]), szFileName);
		sprintf(szFileName, "res/font/y%d.gif", i); 
		LoadBitmap(HDC_SCREEN, &(g_bmY[i]), szFileName);
	}
	for (i=0;i<13;i++)
	{
		sprintf(szFileName, "res/font/p%d.gif", i); 
		LoadBitmap(HDC_SCREEN, &(g_bmP[i]), szFileName);
		//出错处理
	}
	
}
void UI_Out_640_480_SetMainFromColor(int nBkColor)
{
	HWND hWnd = From_Handl;
	HDC hDC;
	hDC = GetClientDC(hWnd); 
	SetBrushColor(hDC, nBkColor);   
	FillBox(hDC, 2, 23, 636,3); 
	FillBox(hDC, 2, rec3.top-2, 636,2);
	FillBox(hDC, 2, rec5.top-3, 275,3); 
	FillBox(hDC, 2, rec6.top-3, 275,3);
	FillBox(hDC, 2, rec8.top-3, 275,3);
	FillBox(hDC, rec10.left, rec10.bottom+2, rec10.right-rec10.left+2,3);
	FillBox(hDC, 2, rec8.bottom+2, 636,2);
	FillBox(hDC, 2, 23, 2,453);
	FillBox(hDC,rec1.right+2, 23, 2, 453);
	FillBox(hDC,rec2.right+2, 23, 2, 453);
	FillBox(hDC,rec6.right+2, rec6.top-2, 3, rec6.bottom-rec6.top +6);
	ReleaseDC(hDC); 
}
void UI_Out_640_480_ShowTime_MMI(char * szInfo )
{
	HDC hDC; 
	RECT rt;
	hDC =     GetClientDC(From_Handl);    
	SetBkColor(hDC, RGB(254, 254, 254));    
	SetTextColor(hDC, RGB(0, 0, 0));    
	rt.left = rec2.left+2;
	rt.top = rec2.top+2;
	rt.right = rec2.right-2;
	rt.bottom = rec2.bottom-2;
	DrawText(hDC, szInfo, -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
	ReleaseDC(hDC); 
}
void UI_Out_640_480_ClearAbateChargeEditC()
{
	HDC hDC;
	hDC = GetClientDC(From_Handl);   
	FillBoxWithBitmap(hDC,rec5.left+2, rec5.top+2,0,0,&g_bmP[12]);  
	ReleaseDC(hDC); 
}
extern BOOL U_SBtn_Flag;
void UI_Out_640_480_ShowDeviceState_MMI(int btnindex,BOOL flag)
{
	HDC hDC;
	if (U_SBtn_Flag==0)
		return;
	hDC = GetClientDC(From_Handl);   
	switch (btnindex)
	{
	case 1:
		FillBoxWithBitmap (hDC, rt1.left+4, rt1.top+4, 0, 0, flag  ? &bmYuPengG : &bmYuPengR);  
		break;
	case 2:
		FillBoxWithBitmap (hDC, rt2.left+4, rt2.top+4, 0, 0, flag ? &bmJiaoTongG : &bmJiaoTongR); 
		break;
	case 3:
		FillBoxWithBitmap (hDC, rt3.left+4, rt3.top+4, 0, 0, flag? &bmLanGanUp : &bmLanGanDown);   
		break;
	case 4:
		FillBoxWithBitmap (hDC, rt4.left+4, rt4.top+4, 0, 0, flag ? &bmXianQuanR:&bmXianQuanG );   
		break;
	case 5:
		FillBoxWithBitmap (hDC, rt5.left+4, rt5.top+4, 0, 0, flag? &bmXianQuanR:&bmXianQuanG);    
		break;
	case 6:
		FillBoxWithBitmap (hDC, rt6.left+4, rt6.top+4, 0, 0, flag ? &bmPrintG : &bmPrintR);  
		break;
	default:
		break;
	}
	ReleaseDC(hDC); 

}

void UI_Out_640_480_ShowLoginTime_MMI( char *szInfo)
{

	HDC hDC;
	RECT rt;
	hDC =     GetClientDC(From_Handl);  
	//显示日期, 时间
	SetBkColor(hDC, RGB(254, 254, 254));    
	SetTextColor(hDC, RGB(0, 0, 0));    
	rt.left = rec1.left+2;
	rt.top = rec1.top+2;
	rt.right = rec1.right-2;
	rt.bottom = rec1.bottom-2;
	DrawText(hDC, szInfo, -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
	ReleaseDC(hDC); 
}

void UI_Out_640_480_Show_BigFont(int nEditAt, short sVal,BOOL Flag)
{
	HDC hDC;
	RECT rt;
	short sBits[4];
	int nFontW,nFontH;
	int x,y;



	hDC = GetDC(From_Handl); 
	rt.left = rtEdit[nEditAt].left+2;
	rt.top = rtEdit[nEditAt].top+2;
	rt.right = rtEdit[nEditAt].right-2;
	rt.bottom = rtEdit[nEditAt].bottom-2;
	if (0x4000 == sVal)
	{
		sBits[0] = 10;
		sBits[1] = 10;
		sBits[2] = 10;
		sBits[3] = 10;
	}
	else
	{
		sBits[3] = 10;
		if (0 == (sVal/100)%10)
		{
			sBits[2] = 10;
		}
		else
		{
			sBits[2] = (sVal/100)%10;
		}
		if (0 == (sVal/10)%10)
		{
			if (sBits[2]==10)
			{
				sBits[1] = 10;
			}
			else
			{
				sBits[1] = 0;
			}

		}
		else
		{
			sBits[1] = sVal/10%10;
		}
		sBits[0] = sVal%10;
	}

	switch (nEditAt)
	{
	case 0://车型
		nFontW = g_bmC[1].bmWidth;
		nFontH = g_bmC[1].bmHeight;
		if (sVal<10)
		{
			x = (rt.right-rt.left-nFontW)/2;
			x +=rt.left;
			y = rt.top + (rt.bottom-rt.top-nFontH)/2;
			FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmC[sBits[0]]);   
		}
		else if (sVal<100)
		{
			x = (rt.right-rt.left-2*nFontW)/2;
			x +=rt.left;
			y = rt.top + (rt.bottom-rt.top-nFontH)/2;
			FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmC[sBits[1]]);   
			x +=nFontW;
			FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmC[sBits[0]]);   
		}
		else
		{
			x = rt.left -2;//(rt.right-rt.left-nFontW)/2;
			y = rt.top + (rt.bottom-rt.top-nFontH)/2;
			FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmC[sBits[2]]);		   //显示百位数
			x += nFontW;
			FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmC[sBits[1]]);		   //显示十位数
			x += nFontW;
			FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmC[sBits[0]]);   

		}

		break;
	case 1://车种
		nFontW = g_bmY[1].bmWidth;
		nFontH = g_bmY[1].bmHeight;
		x = rt.left + (rt.right-rt.left-nFontW)/2;
		y = rt.top + (rt.bottom-rt.top-nFontH)/2;
		FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmY[sBits[0]]);		   //显示车种
		break;
	case 2://金额
		nFontW = g_bmP[1].bmWidth;
		nFontH = g_bmP[1].bmHeight;
		if (Flag)
		{
			if (sVal<10)
			{
				x = (rt.right-rt.left-nFontW)/2;
				x +=rt.left;
				y = rt.top + (rt.bottom-rt.top-nFontH)/2;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[0]]);   
			}
			else if (sVal<100)
			{
				x = (rt.right-rt.left-2*nFontW)/2;
				x +=rt.left;
				y = rt.top + (rt.bottom-rt.top-nFontH)/2;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[1]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[0]]);   
			}
			else
			{
				x = (rt.right-rt.left-3*nFontW)/2;
				x +=rt.left;
				y = rt.top + (rt.bottom-rt.top-nFontH)/2;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[2]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[1]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[0]]);   
			}
		}
		else
		{
			if (sVal<10)
			{
				x = (rt.right-rt.left-2*nFontW)/2;
				x +=rt.left;
				y = rt.top + (rt.bottom-rt.top-nFontH)/2;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[0]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[11]); 
			}
			else if (sVal<100)
			{
				x = (rt.right-rt.left-3*nFontW)/2;
				x +=rt.left;
				y = rt.top + (rt.bottom-rt.top-nFontH)/2;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[1]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[0]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[11]); 
			}
			else
			{
				x = (rt.right-rt.left-4*nFontW)/2;
				x +=rt.left;
				y = rt.top + (rt.bottom-rt.top-nFontH)/2;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[2]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[1]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[sBits[0]]);   
				x +=nFontW;
				FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmP[11]); 

			}
		}
		break;
	}

	ReleaseDC(hDC); 
}
void UI_Out_640_480_Show_Image(int  nEditAt ,int sVal)
{
	HDC hDC;
	RECT rt;
	short sBits[4];
	int nFontW,nFontH;
	int x,y;
	hDC = GetDC(From_Handl); 
	if (0x4000 == sVal)
	{
		sBits[0] = 10;
		sBits[1] = 10;
		sBits[2] = 10;
		sBits[3] = 10;
	}
	else
	{
		sBits[3] = 10;
		if (0 == (sVal/100)%10)
		{
			sBits[2] = 10;
		}
		else
		{
			sBits[2] = (sVal/100)%10;
		}
		if (0 == (sVal/10)%10)
		{
			if (sBits[2]==10)
			{
				sBits[1] = 10;
			}
			else
			{
				sBits[1] = 0;
			}
		}
		else
		{
			sBits[1] = sVal/10%10;
		}       sBits[0] = sVal%10;
	}
	rt.left = rtEdit[nEditAt].left;
	rt.top = rtEdit[nEditAt].top;
	rt.right = rtEdit[nEditAt].right;
	rt.bottom = rtEdit[nEditAt].bottom;
	nFontW = g_bmY[1].bmWidth;
	nFontH = g_bmY[1].bmHeight;
	x = rt.left + (rt.right-rt.left-nFontW)/2;
	y = rt.top + (rt.bottom-rt.top-nFontH)/2;
	FillBoxWithBitmap(hDC, x, y, 0, 0, &g_bmY[sBits[0]]);   
	ReleaseDC(hDC); 
}

void UI_Out_640_480_Show_Edit(int nEditAt, char *pszInfo)
{

	HDC hDC;
	RECT rt;

	hDC = GetDC(From_Handl); 
	rt.left = rtEdit[nEditAt].left+2;
	rt.top = rtEdit[nEditAt].top+2;
	rt.right = rtEdit[nEditAt].right-2;
	rt.bottom = rtEdit[nEditAt].bottom-2;
	SetBrushColor(hDC, EDIT_BACK_COLOR);    
	FillBox(hDC, rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top);  
	SetBkMode(hDC, BM_TRANSPARENT); 
	SetTextColor(hDC, EDIT_FRONT_COLOR);    
	DrawText(hDC , pszInfo, -1, &rt, DT_SINGLELINE | DT_LEFT | DT_VCENTER); 
	ReleaseDC(hDC); 

}
void UI_Out_640_480_Show_Info_ByColor(char *pszInfo, unsigned int  bc,unsigned int  tc)
{
	HDC hDC;
	RECT rt;	
	hDC = GetDC(From_Handl); 
	rt.left = rec9.left+16;
	rt.top = rec9.top+16;
	rt.right = rec9.right-16;
	rt.bottom = rec9.bottom-16;
	SetBrushColor(hDC, bc); 
	FillBox(hDC, rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top);  
	SetBkMode(hDC, BM_TRANSPARENT); 
	SetTextColor(hDC,  tc); 
	DrawText(hDC , pszInfo, -1, &rt, DT_WORDBREAK | DT_LEFT | DT_VCENTER);  
	ReleaseDC(hDC); 
}

void UI_Out_640_480_Show_Info(char *pszInfo)
{
	UI_Out_640_480_Show_Info_ByColor(pszInfo,TISHI_BACK_COLOR,RGB(250, 250, 250));
}


void UI_Out_640_480_Set_Help_Info(char *pszInfo)
{
	HDC hDC;
	RECT rt;
	hDC = GetDC(From_Handl); 
	rt.left = rec9.left+5;
	rt.top = rec9.bottom-17;
	rt.right = rec9.right-5;
	rt.bottom = rec9.bottom-1;
	SetBrushColor(hDC, TISHI_BACK_COLOR);   
	FillBox(hDC, rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top);  
	SetBkMode(hDC, BM_TRANSPARENT); 
	SetTextColor(hDC, RGB(255, 255, 0));    
	DrawText(hDC , pszInfo, -1, &rt, DT_WORDBREAK | DT_LEFT | DT_VCENTER);  
	ReleaseDC(hDC); 
	
}


void UI_Out_640_480_Set_From_Title(HWND hWnd, char* sTitle)
{
	HDC hdc;
	RECT recttitle;
	RECT rectParent; 
	GetClientRect(hWnd, &rectParent);
	hdc = BeginPaint (hWnd); 
	recttitle.left=rectParent.left + 1;
	recttitle.top=rectParent.top + 2;
	recttitle.right=rectParent.right - 3;
	recttitle.bottom=rectParent.top + 21;
	SetBrushColor (hdc, SUBTITLECOLOR); 
	FillBox (hdc, recttitle.left, recttitle.top, recttitle.right-recttitle.left, recttitle.bottom-recttitle.top);   
	SetBkColor(hdc,SUBTITLECOLOR);  
	SetTextColor(hdc,TITLE_TEXT_COLOR); 
	DrawText (hdc, sTitle, -1, &recttitle,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);   
	SetPenColor (hdc, SEPLINECOLOR2 );	//里层SEPLINECOLOR2
	MoveTo (hdc,rectParent.left + 1, rectParent.top +1);    
	LineTo (hdc, rectParent.right -1,rectParent.top + 1);   
	MoveTo (hdc, rectParent.left +1,rectParent.top +1); 
	LineTo (hdc, rectParent.left +1, rectParent.bottom -1); 
	SetPenColor (hdc, LTFRAMECOLOR );	//外层LTFRAMECOLOR
	MoveTo (hdc, rectParent.left , rectParent.top); 
	LineTo (hdc, rectParent.right, rectParent.top); 
	MoveTo (hdc, rectParent.left , rectParent.top); 
	LineTo (hdc, rectParent.left , rectParent.bottom);  
	//画窗体右下两对边框线
	SetPenColor (hdc, SEPLINECOLOR1 );	//里层SEPLINECOLOR1
	MoveTo (hdc, rectParent.right-2, rectParent.top+1); 
	LineTo (hdc, rectParent.right-2, rectParent.bottom-2);  
	MoveTo (hdc, rectParent.left+1 ,rectParent.bottom -2);  
	LineTo (hdc, rectParent.right-2 , rectParent.bottom -2);    
	SetPenColor (hdc, RBFRAMECOLOR );	//外层RBFRAMECOLOR
	MoveTo (hdc, rectParent.right-1, rectParent.top);   
	LineTo (hdc, rectParent.right-1, rectParent.bottom-1);  
	MoveTo (hdc, rectParent.left, rectParent.bottom-1); 
	LineTo (hdc, rectParent.right-1, rectParent.bottom-1);  
	EndPaint (hWnd, hdc);   
}
