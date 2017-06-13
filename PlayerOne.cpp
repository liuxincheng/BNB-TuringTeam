#include "PlayerOne.h"

CPlayerOne::CPlayerOne(void)
{

}

CPlayerOne::~CPlayerOne(void)
{
} 

void CPlayerOne::PlayerInit(HINSTANCE hIns)
{
	m_player_x = 16;	// 图片宽480 高64 -->  每个人物宽48
	m_player_y = 15;
	m_Start_nShowID = 0;
	m_hBmpPlayer = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_ONE_START));
	m_hBmpPlayerShadow = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SHADOW_ROLE));
}

void CPlayerOne::PlayerStartShow(HDC hdc)
{
	HDC hTempDC = CreateCompatibleDC(hdc);
	// 阴影
	SelectObject(hTempDC,m_hBmpPlayerShadow); 
	TransparentBlt(hdc,m_player_x+8,m_player_y+48,32,15,hTempDC,0,0,32,15,RGB(255,0,255));
	// 人物
	SelectObject(hTempDC,m_hBmpPlayer);       
	TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Start_nShowID*48,0,48,64,RGB(255,0,255));

	DeleteObject(hTempDC);
}