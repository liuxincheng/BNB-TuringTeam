#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "Sys.h"
#include "GameMap.h"
#include "Bubble.h"
#include "PlaySound.h"

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
	virtual void PlayerMove(int FX,CGameMap &gameMap) = 0;         // ����ƶ�
	virtual void CreateBubble(HINSTANCE hIns,CGameMap &gameMap,list<CBubble*> &lstBubble,CPlaySound &playSound,int x,int y) = 0;
public:
	HBITMAP m_hBmpPlayerStart;                   // ��ʼ����λͼ
	HBITMAP m_hBmpPlayerMove;                    // �ƶ�����λͼ
	HBITMAP m_hBmpPlayerDie;                     // ��������λͼ
	HBITMAP m_hBmpPlayerShadow;                  // ������Ӱλͼ
	int m_Start_nShowID;                         // ���￪ʼ�����л�λͼ
	int m_player_x;                              // ����λ�� x
	int m_player_y;                              // ����λ�� y
	int m_Move_ShowId;                           // �����ƶ� �ı�ͼƬ���
	bool m_bMoveFlag;                            // ����ĸ������ƶ�

	// ��¼���״̬ �л���ͬλͼ����
	Player_Status m_player_status;
	// ��¼����ƶ�����
	Direction m_direction;
};

#endif // !CPLAYER_H_
