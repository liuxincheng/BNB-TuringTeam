#ifndef CGAMEPROPS_H_
#define CGAMEPROPS_H_

#include "Sys.h"
#include "GameMap.h"

#define EBNUMBER   3    //水泡放3个
#define EWNUMBER   3    //能量水放3个
#define RSNUMBER   2    //旱冰鞋增加速度放2个
#define RHNUMBER   2    //红魔头速度增到最大放2个
#define PBNUMBER   1    //大力丸爆炸范围最大放1个

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
	int m_nShowID;
	int m_bj[MAP_WIDTH][MAP_HEIGHT];
	int energybubblewpos[EBNUMBER];
	int energybubblehpos[EBNUMBER];
	int energywaterwpos[EWNUMBER];
	int energywaterhpos[EWNUMBER];
	int rollerskatewpos[RSNUMBER];
	int rollerskatehpos[RSNUMBER];
	int	edheadwpos[RHNUMBER];
	int	edheadhpos[RHNUMBER];
	int	powerballwpos[PBNUMBER];
	int	powerballhpos[PBNUMBER];
	CGameMap map;
public:
	void PropInit(HINSTANCE hIns);
	void PropPositionShow(HDC hdc);
};

#endif // !CGAMEPROPS_H_
