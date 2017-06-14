#include "PlayerTwo.h"

CPlayerTwo::CPlayerTwo()
{
}

CPlayerTwo::~CPlayerTwo()
{
} 

void CPlayerTwo::PlayerInit(HINSTANCE hIns)
{
	m_player_x = 573;	// 图片宽560 每个人物宽56,
	m_player_y = 490;
	m_Start_nShowID = 0;
	m_hBmpPlayer = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_TWO_START));
	m_hBmpPlayerShadow = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SHADOW_ROLE));
}

void CPlayerTwo::PlayerStartShow(HDC hdc)
{
	HDC hTempDC = CreateCompatibleDC(hdc);
	// 阴影
	SelectObject(hTempDC,m_hBmpPlayerShadow);
	TransparentBlt(hdc,m_player_x+12,m_player_y+57,32,15,hTempDC,0,0,32,15,RGB(255,0,255));
	// 人物
	SelectObject(hTempDC,m_hBmpPlayer);
	TransparentBlt(hdc,m_player_x,m_player_y,56,71,hTempDC,m_Start_nShowID*56,0,56,71,RGB(255,0,255));

	DeleteObject(hTempDC);
}