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
	virtual void PlayerStartShow(HDC hdc);
};

#endif // !CPLAYERTWO_H_
