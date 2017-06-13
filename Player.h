#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "Sys.h"

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual void PlayerInit(HINSTANCE hIns) = 0; // ��ҳ�ʼ��
	virtual void PlayerStartShow(HDC hdc) = 0;   // ��ҳ�������
public:
	HBITMAP m_hBmpPlayer;
	HBITMAP m_hBmpPlayerShadow;
	int m_Start_nShowID;
	int m_player_x;
	int m_player_y;	
};

#endif // !CPLAYER_H_
