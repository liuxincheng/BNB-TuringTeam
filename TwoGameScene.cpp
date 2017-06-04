#include "TwoGameScene.h"

CTwoGameScene::CTwoGameScene()
{
	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_isSelect = false;
}

CTwoGameScene::~CTwoGameScene()
{
	DeleteObject(m_bitmap_gameBack);
	DeleteObject(m_bitmap_quit);
	DeleteObject(m_bitmap_quit_select);
	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
}

void CTwoGameScene::GameSceneInit(HINSTANCE hIns)
{
	m_bitmap_gameBack = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GAME_BACK));
	m_bitmap_quit = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_QUIT_GAME));
	m_bitmap_quit_select = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_QUIT_GAME_SELECT));

	// 初始化地图
	gameMap.MapInit(hIns);
}

void CTwoGameScene::GameSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_gameBack);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);

	if (m_isSelect)
	{
		SelectObject(hdcMem,m_bitmap_quit_select);
	} 
	else
	{
		SelectObject(hdcMem,m_bitmap_quit);
	}

	BitBlt(hdc,650,556,130,30,hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);

	// 地图显示
	gameMap.MapShow(hdc);
}

void CTwoGameScene::MouseMove(POINT point)
{
	if (point.x > 650 && point.x < 780 && point.y > 556 && point.y < 586)
	{
		m_isSelect = true;
	}
	else
	{
		m_isSelect = false;
	}
}
