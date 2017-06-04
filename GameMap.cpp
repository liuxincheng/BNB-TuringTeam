#include "GameMap.h"

CGameMap::CGameMap()
{
	m_bitmap_road = NULL;
}


CGameMap::~CGameMap()
{
	DeleteObject(m_bitmap_road);
	m_bitmap_road = NULL;
}

void CGameMap::MapInit(HINSTANCE hIns)
{
	m_bitmap_road = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ROAD));
}

void CGameMap::MapShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_road);
	BitBlt(hdc,20,41,800,600,hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);
}
