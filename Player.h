#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "Sys.h"

enum Player_Status {BEGIN, MOVE, DIE};
enum Direction { UP, DOWN, LEFT, RIGHT };

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual void PlayerInit(HINSTANCE hIns) = 0; // ��ҳ�ʼ��
	virtual void PlayerShow(HDC hdc) = 0;        // ��ҳ�������
	virtual void PlayerMove(int FX) = 0;         // ����ƶ�
public:
	HBITMAP m_hBmpPlayerStart;                   // ��ʼ����λͼ
	HBITMAP m_hBmpPlayerMove;                    // �ƶ�����λͼ
	HBITMAP m_hBmpPlayerDie;                     // ��������λͼ
	HBITMAP m_hBmpPlayerShadow;                  // ������Ӱλͼ
	int m_Start_nShowID;                         // ���￪ʼ�����л�λͼ
	int m_player_x;                              // ����λ�� x
	int m_player_y;                              // ����λ�� y

	// ��¼���״̬ �л���ͬλͼ����
	Player_Status m_player_status;
	// ��¼����ƶ�����
	Direction m_direction;
};

#endif // !CPLAYER_H_
