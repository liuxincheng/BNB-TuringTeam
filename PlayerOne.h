#ifndef CPLAYERONE_H_
#define CPLAYERONE_H_

#include "player.h"

class CPlayerOne : public CPlayer
{
public:
	CPlayerOne();
	virtual ~CPlayerOne();
public:
	virtual void PlayerInit(HINSTANCE hIns);
	virtual void PlayerShow(HDC hdc);
	virtual void PlayerMove(int FX);
};

#endif // !CPLAYERONE_H_

