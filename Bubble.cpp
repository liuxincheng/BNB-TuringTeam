#include "Bubble.h"
#pragma comment(lib,"Msimg32.lib")
CBubble::CBubble()
{
	m_bitmap_bubble = NULL;
	m_bitmap_shadow_bubble = NULL;
	m_nShowID = 0;
	m_nBubble_x = 0;
	m_nBubble_y = 0;
	m_nBubbleBj = 0;
}

CBubble::~CBubble()
{
	DeleteObject(m_bitmap_bubble);
	DeleteObject(m_bitmap_shadow_bubble);
	m_bitmap_shadow_bubble = NULL;
	m_bitmap_bubble = NULL;
}

void CBubble::BubbleInit(HINSTANCE hIns, int x, int y)
{
	m_bitmap_bubble = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BUBBLE));
	m_bitmap_shadow_bubble = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_SHADOW_BUBBLE));
	m_nShowID = 2;
	m_nBubbleBj = 16;
	this->m_nBubble_x = x;
	this->m_nBubble_y = y;

}

void CBubble::BubbleShow(HDC hdc)
{
	HDC hdcMem=CreateCompatibleDC(hdc);
	// ≈›≈›“ı”∞
	SelectObject(hdcMem,m_bitmap_shadow_bubble);
	TransparentBlt(hdc,m_nBubble_x,m_nBubble_y+28,35,16,hdcMem,(2-m_nShowID)*35,0,35,16,RGB(255,0,255));
	// ≈›≈›
	SelectObject(hdcMem,m_bitmap_bubble);
	TransparentBlt(hdc,m_nBubble_x,m_nBubble_y,44,41,hdcMem,(2-m_nShowID)*44,0,44,41,RGB(255,0,255));
	DeleteObject(hdcMem);
}
