/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CGameMap.h
 *  ��Ҫ����: ��Ϸ��ͼ��
 *
 *  ����: 
 *  ��������: 2017��6��4��
 *  ˵��:
 *
 *  �޸�����:
 *  ����:
 *  ˵��:
 *  ��ǰ�汾: 1.0
 ******************************************************************/ 

#ifndef CGMAEMAP_H_
#define CGMAEMAP_H_

#include "Sys.h"

#define MAP_WIDTH  15
#define MAP_HEIGHT 12

enum MapType
{
	No, RedBrick, YellowBrick, RedHouse, YellowHouse, BlueHouse, Tree, Box 
};

class CGameMap
{
public:
	CGameMap();
	~CGameMap();

	void MapInit(HINSTANCE hIns);
	void MapShow(HDC hdc);
public:
	static int map_type[MAP_HEIGHT][MAP_WIDTH];
private:
	HBITMAP m_bitmap_road;
	HBITMAP m_bitmap_redBrick;
	HBITMAP m_bitmap_redHouse;
	HBITMAP m_bitmap_yellowBrick;
	HBITMAP m_bitmap_yellowHouse;
	HBITMAP m_bitmap_Tree;
	HBITMAP m_bitmap_Box;
	HBITMAP m_bitmap_blueHouse;
};

#endif // !CGMAEMAP_H_

