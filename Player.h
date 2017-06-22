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
	virtual void PlayerInit(HINSTANCE hIns) = 0; // 玩家初始化
	virtual void PlayerShow(HDC hdc) = 0;        // 玩家出场动画
	virtual void PlayerMove(int FX) = 0;         // 玩家移动
public:
	HBITMAP m_hBmpPlayerStart;                   // 开始动画位图
	HBITMAP m_hBmpPlayerMove;                    // 移动动画位图
	HBITMAP m_hBmpPlayerDie;                     // 死亡动画位图
	HBITMAP m_hBmpPlayerShadow;                  // 人物阴影位图
	int m_Start_nShowID;                         // 人物开始动画切换位图
	int m_player_x;                              // 人物位置 x
	int m_player_y;                              // 人物位置 y

	// 记录玩家状态 切换不同位图动画
	Player_Status m_player_status;
	// 记录玩家移动方向
	Direction m_direction;
};

#endif // !CPLAYER_H_
