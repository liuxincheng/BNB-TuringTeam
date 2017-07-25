#ifndef CPLAYERTWO_H_
#define CPLAYERTWO_H_

#include "player.h"

class CPlayerTwo : public CPlayer
{
public:
	CPlayerTwo();
	virtual ~CPlayerTwo();
public:
	virtual void PlayerInit(HINSTANCE hIns);
	virtual void PlayerShow(HDC hdc);
	virtual void PlayerMove(int FX);
	virtual void CreateBubble(HINSTANCE hIns,CGameMap &gameMap,list<CBubble*> &lstBubble,CPlaySound &playSound,int x,int y);
};

#endif // !CPLAYERTWO_H_
