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
};

#endif // !CPLAYERTWO_H_
