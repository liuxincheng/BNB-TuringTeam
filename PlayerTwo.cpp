#include "PlayerTwo.h"

CPlayerTwo::CPlayerTwo()
{
}

CPlayerTwo::~CPlayerTwo()
{
} 

void CPlayerTwo::PlayerInit(HINSTANCE hIns)
{
	m_player_x = 575;	// 图片宽560 高71 每个人物宽56,
	m_player_y = 494;
	m_Start_nShowID = 0;
	m_player_status = BEGIN;
	m_direction = DOWN;
	m_hBmpPlayerStart = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_TWO_START));
	m_hBmpPlayerShadow = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SHADOW_ROLE));
	m_hBmpPlayerMove = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_TWO_MOVE));
}

void CPlayerTwo::PlayerShow(HDC hdc)
{
	HDC hTempDC = CreateCompatibleDC(hdc);
	// 阴影
	SelectObject(hTempDC,m_hBmpPlayerShadow);
	TransparentBlt(hdc,m_player_x+12,m_player_y+53,32,15,hTempDC,0,0,32,15,RGB(255,0,255));
	
	switch (m_player_status)
	{
	// 开场动画
	case BEGIN:
		SelectObject(hTempDC,m_hBmpPlayerStart);
		TransparentBlt(hdc,m_player_x,m_player_y,56,71,hTempDC,m_Start_nShowID*56,0,56,71,RGB(255,0,255));
		break;

	// 移动动画
	case MOVE:
		switch (m_direction)
		{
		case UP:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,0*56,UP*67,56,67,RGB(255,0,255));
			break;
		case DOWN:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,0*56,DOWN*67,56,67,RGB(255,0,255));
			break;
		case LEFT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,0*56,LEFT*67,56,67,RGB(255,0,255));
			break;
		case RIGHT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,56,67,hTempDC,0*56,RIGHT*67,56,67,RGB(255,0,255));
			break;
		}
		break;
	
	// 死亡动画
	case DIE:
		break;
	}
	

	DeleteObject(hTempDC);
}

void CPlayerTwo::PlayerMove(int FX)
{
	if (FX == 'A')
	{
		m_direction = LEFT;
		if (this->m_player_x > 15)
		{
			this->m_player_x -= 5;
		}
	}

	if (FX == 'D')
	{
		m_direction = RIGHT;
		if (this->m_player_x < 575)
		{
			this->m_player_x += 5;
		}
	}

	if (FX == 'W')
	{
		m_direction = UP;
		if (this->m_player_y > 15)
		{
			this->m_player_y -= 5;
		}
	}

	if (FX == 'S')
	{
		m_direction = DOWN;
		if (this->m_player_y < 41 + 520 - 67)
		{
			this->m_player_y += 5;
		}
	}
}