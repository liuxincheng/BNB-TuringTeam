#ifndef CGAMEPROPS_H_
#define CGAMEPROPS_H_

#include "Sys.h"
#include "GameMap.h"

enum PropType
{
	noprop=10, energybubble, energywater, rollerskate, redhead, powerball
};


class CGameProps
{
public:
	CGameProps();
	~CGameProps();
public:
	HBITMAP m_bitmap_energybubble;
	HBITMAP m_bitmap_energywater;
	HBITMAP m_bitmap_rollerskate;
	HBITMAP m_bitmap_redhead;
	HBITMAP m_bitmap_powerball;

	int m_nposw;
	int m_nposh;
	int m_nShowID;
	int m_bj[MAP_WIDTH][MAP_HEIGHT];
	int energybubblewpos[4];
	int energybubblehpos[4];
	int energywaterwpos[4];
	int energywaterhpos[4];
	int rollerskatewpos[3];
	int rollerskatehpos[3];
	int	edheadwpos[2];
	int	edheadhpos[2];
	int	powerballwpos[2];
	int	powerballhpos[2];
	CGameMap map;
public:
	void PropInit(HINSTANCE hIns);
	void PropPositionShow(HDC hdc);
};

#endif // !CGAMEPROPS_H_
