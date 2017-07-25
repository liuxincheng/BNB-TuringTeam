#include "PlayerOne.h"

CPlayerOne::CPlayerOne()
{
}

CPlayerOne::~CPlayerOne()
{
} 

void CPlayerOne::PlayerInit(HINSTANCE hIns)
{
	m_player_x = 15;     // ͼƬ��480 ��64 -->  ÿ�������48
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

	// ������Ӱ
	SelectObject(hTempDC,m_hBmpPlayerShadow); 
	TransparentBlt(hdc,m_player_x+8,m_player_y+48,32,15,hTempDC,0,0,32,15,RGB(255,0,255));

	switch (m_player_status)
	{
	// ��������
	case BEGIN:
		SelectObject(hTempDC,m_hBmpPlayerStart);
		TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Start_nShowID*48,0,48,64,RGB(255,0,255));
		break;

	// �ƶ�����
	case MOVE:
		switch (m_direction)
		{
		case UP:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,UP*64,48,64,RGB(255,0,255));
			break;
		case DOWN:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,DOWN*64,48,64,RGB(255,0,255));
			break;
		case LEFT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,LEFT*64,48,64,RGB(255,0,255));
			break;
		case RIGHT:
			SelectObject(hTempDC,m_hBmpPlayerMove);
			TransparentBlt(hdc,m_player_x,m_player_y,48,64,hTempDC,m_Move_ShowId*48,RIGHT*64,48,64,RGB(255,0,255));
			break;
		}
		break;

	// ��������
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

void CPlayerOne::CreateBubble(HINSTANCE hIns,CGameMap &gameMap,list<CBubble*> &lstBubble,CPlaySound &playSound,int x,int y)
{
	//-------����ת��-------------------//
	x += 15;
	y = y + 64 - 15;

	if (x >= 20 && x <= 620 && y >= 41 && y <= 561)
	{
		// ������ת���ɶ�Ӧ��ͼ��������
		int temp_x = (x - 20) / 40; 
		int temp_y = (y - 41) / 40;
		// �жϸ�λ���Ƿ����ϰ��� û���ϰ��� ���������
		if (gameMap.map_type[temp_y][temp_x] == No)
		{
			// ����λ�ø�ֵ
			gameMap.map_type[temp_y][temp_x] = Popo;
			// ȷ������λ��
			temp_x = temp_x * 40 + 20;
			temp_y = temp_y * 40 + 41 - 1;
			// ��������
			CBubble* bubble = new CBubble;
			bubble->BubbleInit(hIns,temp_x,temp_y,1);
			lstBubble.push_back(bubble);

			// ����������Ч
			playSound.Play(PUT_BUEBLE_SOUND);
		}
	}
}