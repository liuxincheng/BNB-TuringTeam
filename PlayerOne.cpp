#include "PlayerOne.h"

CPlayerOne::CPlayerOne()
{
}

CPlayerOne::~CPlayerOne()
{
} 

void CPlayerOne::PlayerInit(HINSTANCE hIns)
{
	m_player_x = 15;     // 图片宽480 高64 -->  每个人物宽48
	m_player_y = 15;
	m_Start_nShowID = 0;
	m_player_status = BEGIN;
	m_direction = DOWN;
	m_hBmpPlayerStart = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_ONE_START));
	m_hBmpPlayerShadow = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SHADOW_ROLE));
	m_hBmpPlayerMove = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_ONE_MOVE));
}

void CPlayerOne::PlayerShow(HDC hdc)
{
	HDC hTempDC = CreateCompatibleDC(hdc);

	// 人物阴影
	SelectObject(hTempDC,m_hBmpPlayerShadow); 
	TransparentBlt(hdc,m_player_x+8,m_player_y+48,32,15,hTempDC,0,0,32,15,RGB(255,0,255));

	switch (m_player_status)
	{
	// 开场动画
	case BEGIN:
		SelectObject(hTempDC,m_hBmpPlayerStart);
		TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Start_nShowID*48,0,48,64,RGB(255,0,255));
		break;

	// 移动动画
	case MOVE:
		switch (m_direction)
		{
		case UP:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,0*48,UP*64,48,64,RGB(255,0,255));
			break;
		case DOWN:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,0*48,DOWN*64,48,64,RGB(255,0,255));
			break;
		case LEFT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,0*48,LEFT*64,48,64,RGB(255,0,255));
			break;
		case RIGHT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,0*48,RIGHT*64,48,64,RGB(255,0,255));
			break;
		}
		break;

	// 死亡动画
	case DIE:
		break;
	}
	
	DeleteObject(hTempDC);
}

void CPlayerOne::PlayerMove(int FX)
{
	if (FX == VK_LEFT)
	{
		m_direction = LEFT;
		if (this->m_player_x > 15)
		{
			this->m_player_x -= 5;
		}
	}

	if (FX == VK_RIGHT)
	{
		m_direction = RIGHT;
		if (this->m_player_x < 20 + 600 - 48)
		{
			this->m_player_x += 5;
		}
	}

	if (FX == VK_UP)
	{
		m_direction = UP;
		if (this->m_player_y > 15)
		{
			this->m_player_y -= 5;
		}
	}

	if (FX == VK_DOWN)
	{
		m_direction = DOWN;
		if (this->m_player_y < 41 + 520 - 64)
		{
			this->m_player_y += 5;
		}
	}
}