#ifndef __640_480_H__
#define __640_480_H__


//��༭��
//����Ϊ, , , , , , , ��ʾ��
//�ϰ�ʱ��
RECT rec1 = {84, 26, 274, 48};
//��ǰʱ��
RECT rec2 = {288+94, 26, 634, 48};

//����
RECT rec3 = {28, 54-2,131, 131};

//����
RECT rec4 = {156, 54-2, 274, 131};

//���
RECT rec5 = {28, 137, 274, 219};

//��ʾ��
RECT rec6 = {28, 225, 130, 267};

//��ʾ��
RECT rec7 = {135, 225, 274, 267};

//��ʾ��
RECT rec8 = {4, 273, 274, 474};

RECT rec9 = {4, 273, 274, 474};

//��Ƶ��
RECT rec10 = {279, 52, 634, 344};

//ҵ����༭��λ��
RECT rtEdit[5] =
{

	{0,0,0,0},//����
	{0,0,0,0},//����
	{0,0,0,0},//���
	{0,0,0,0},//��ʾ��
	{0,0,0,0}//��ʾ��

};
BITMAP bmYuPengG, bmYuPengR, bmJiaoTongG, bmJiaoTongR, bmLanGanUp, bmLanGanDown;
BITMAP bmXianQuanG, bmXianQuanR, bmPrintG, bmPrintR;
//��ť�ź���
//�����
RECT rt1 = {285, 350, 410, 408};
//��ͨ��
RECT rt2 = {406-3, 350, 519-3, 408};
//�綯����
RECT rt3 = {524-3-7, 350, 632, 408};
//ץ����Ȧ
RECT rt4 = {285, 412, 410, 470};
//ͨ����Ȧ
RECT rt5 = {406-3, 412, 519-3, 470};
//Ʊ�ݴ�ӡ��
RECT rt6 = {524-3, 412, 632, 470};

RECT rt7 = {524-3, 418, 632, 470};
BITMAP g_bmC[11];
BITMAP g_bmP[13];
BITMAP g_bmY[11];

static void UI_In_640_480_DrawEditCtl(HWND hWnd, int x, int y, int w, int h, int nBkColor)
{
	HDC hdc;
	RECT rectParent;
	//��ȡ������λ��
	GetClientRect(hWnd, &rectParent);   

	//���¸��ݸ����ڵ�λ�ü��㲢��׼��������ʾ

	hdc = BeginPaint (hWnd);    
	SetPenColor(hdc, RGB(128, 128, 128)); 
	//���ϲ��
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y);  
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y+1);  

	//������
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x, rectParent.top+y+h+1);  

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1,rectParent.top+y+2);   
	LineTo (hdc, rectParent.left+x+1, rectParent.top+y+h+2);    

	//���²��
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h);  
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h+1);    
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h+1);  

	//���Ҳ��
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
	GetClientRect(hWnd, &rectParent);	//�ú����õ����Ǵ��ڵ�������Լ����������,
	hdc = BeginPaint (hWnd);    
	//���ϲ��
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y);  
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y+1);  

	//������
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x, rectParent.top+y+h+1);  

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1,rectParent.top+y+2);   
	LineTo (hdc, rectParent.left+x+1, rectParent.top+y+h+2);    

	//���²��
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h);  
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h);    

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+1, rectParent.top+y+h+1);    
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h+1);  

	//���Ҳ��
	SetPenColor (hdc, SEPLINECOLOR1 );  
	MoveTo (hdc, rectParent.left+x+w, rectParent.top+y);    
	LineTo (hdc, rectParent.left+x+w, rectParent.top+y+h);  

	SetPenColor (hdc, SEPLINECOLOR2 );  
	MoveTo (hdc, rectParent.left+x+w+1, rectParent.top+y+1);    
	LineTo (hdc, rectParent.left+x+w+1, rectParent.top+y+h+1);  

	//�ж��Ƿ��ھ��ε����ϽǼӱ���
	if (NULL!=szTitle)
	{
		SetTextColor(hdc, BTNTEXTCOLOR);    
		SetBkColor(hdc,SUBBKCOLOR); 
		TextOut(hdc, rectParent.left+x+20, rectParent.top+y-6, szTitle);    
	}
	EndPaint (hWnd, hdc);   

}



#endif


