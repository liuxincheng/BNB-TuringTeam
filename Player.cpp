#include "Player.h"

CPlayer::CPlayer(void)
{
	m_hBmpPlayer = NULL;
	m_hBmpPlayerShadow = NULL;
	m_Start_nShowID = 0;
	m_player_x = 0;
	m_player_y = 0;
}

CPlayer::~CPlayer(void)
{
	DeleteObject(m_hBmpPlayer);
	DeleteObject(m_hBmpPlayerShadow);
	m_hBmpPlayer = NULL;
	m_hBmpPlayerShadow = NULL;
}
