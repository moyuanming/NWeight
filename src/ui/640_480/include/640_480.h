#ifndef __640_480_H__
#define __640_480_H__


//类编辑框
//依次为, , , , , , , 提示区
//上班时间
RECT rec1 = {84, 26, 274, 48};
//当前时间
RECT rec2 = {288+94, 26, 634, 48};

//车型
RECT rec3 = {28, 54-2,131, 131};

//车种
RECT rec4 = {156, 54-2, 274, 131};

//金额
RECT rec5 = {28, 137, 274, 219};

//提示左
RECT rec6 = {28, 225, 130, 267};

//提示右
RECT rec7 = {135, 225, 274, 267};

//提示区
RECT rec8 = {4, 273, 274, 474};

RECT rec9 = {4, 273, 274, 474};

//视频区
RECT rec10 = {279, 52, 634, 344};

//业务类编辑框位置
RECT rtEdit[5] =
{

	{0,0,0,0},//车型
	{0,0,0,0},//车种
	{0,0,0,0},//金额
	{0,0,0,0},//提示左
	{0,0,0,0}//提示右

};
BITMAP bmYuPengG, bmYuPengR, bmJiaoTongG, bmJiaoTongR, bmLanGanUp, bmLanGanDown;
BITMAP bmXianQuanG, bmXianQuanR, bmPrintG, bmPrintR;
//按钮信号区
//雨棚灯
RECT rt1 = {285, 350, 410, 408};
//交通灯
RECT rt2 = {406-3, 350, 519-3, 408};
//电动栏杆
RECT rt3 = {524-3-7, 350, 632, 408};
//抓拍线圈
RECT rt4 = {285, 412, 410, 470};
//通过线圈
RECT rt5 = {406-3, 412, 519-3, 470};
//票据打印机
RECT rt6 = {524-3, 412, 632, 470};

RECT rt7 = {524-3, 418, 632, 470};
BITMAP g_bmC[11];
BITMAP g_bmP[13];
BITMAP g_bmY[11];

static void UI_In_640_480_DrawEditCtl(HWND hWnd, int x, int y, int w, int h, int nBkColor)
{
	HDC hdc;
	RECT rectParent;
	//获取父窗口位置
	GetClientRect(hWnd, &rectParent);   

	//以下根据父窗口的位置计算并标准化窗口显示

	hdc = BeginPaint (hWnd);    
	SetPenColor(hdc, RGB(128, 128, 128)); 
	//画上侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y);  
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y+1);  

	//画左侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x, rectParent.top+y+h+1);  

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1,rectParent.top+y+2);   
	LineTo (hdc, rectParent.left+x+1, rectParent.top+y+h+2);    

	//画下侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h);  
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h+1);    
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h+1);  

	//画右侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x+w, rectParent.top+y);    
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y+h);  

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+w+1, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h+1);  


	SetBrushColor(hdc, nBkColor);   
	FillBox(hdc, x+3, y+3, w-4, h-4);   

	EndPaint (hWnd, hdc);   
}
static void UI_In_640_480_Show_SeparateRect(HWND hWnd, int x, int y, int w, int h, char *szTitle)
{

	HDC hdc;
	RECT rectParent;
	GetClientRect(hWnd, &rectParent);	//该函数得到的是窗口的相对于自己的相对坐标,
	hdc = BeginPaint (hWnd);    
	//画上侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y);  
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y+1);  

	//画左侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x, rectParent.top+y+h+1);  

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1,rectParent.top+y+2);   
	LineTo (hdc, rectParent.left+x+1, rectParent.top+y+h+2);    

	//画下侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h);  
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h+1);    
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h+1);  

	//画右侧边
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x+w, rectParent.top+y);    
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y+h);  

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+w+1, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h+1);  

	//判断是否在矩形的左上角加标题
	if (NULL!=szTitle)
	{
		SetTextColor(hdc, BTNTEXTCOLOR);    
		SetBkColor(hdc,SUBBKCOLOR); 
		TextOut(hdc, rectParent.left+x+20, rectParent.top+y-6, szTitle);    
	}
	EndPaint (hWnd, hdc);   

}



#endif


