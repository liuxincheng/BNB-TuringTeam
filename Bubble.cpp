#include "Bubble.h"
#pragma comment(lib,"Msimg32.lib")
CBubble::CBubble()
{
	m_hBmpBubble=0;
	m_nShowID=2;
	x=0;
	y=0;
}

CBubble::~CBubble()
{
	DeleteObject(m_hBmpBubble);
	m_hBmpBubble=0;
}
void CBubble::BubbleInit(HINSTANCE hIns,int a,int b)
{
	this->x=a;
	this->y=b;
	m_hBmpBubble=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Bubble));
}
void CBubble::BubbleShow(HDC hMemDC)
{
	HDC hdcMem=CreateCompatibleDC(hMemDC);
	SelectObject(hdcMem,m_hBmpBubble);
	TransparentBlt(hMemDC,x,y,44,41,hdcMem,(2-m_nShowID)*44,0,44,41,RGB(255,0,255));
	DeleteObject(hdcMem);	
}