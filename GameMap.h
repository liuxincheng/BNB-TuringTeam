/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  文件名称: CGameMap.h
 *  简要描述: 游戏地图类
 *
 *  作者: 
 *  创建日期: 2017年6月4日
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 *  当前版本: 1.0
 ******************************************************************/ 

#ifndef CGMAEMAP_H_
#define CGMAEMAP_H_

#include "Sys.h"

#define MAP_WIDTH  15
#define MAP_HEIGHT 13

// 地图上障碍物类型 与mapData中数据一一对应
enum MapType
{
	No, R_B_, Y_B_, R_H_, Y_H_, B_H_, Tree, Box, Popo
};

class CGameMap
{
public:
	CGameMap();
	~CGameMap();

	void MapInit(HINSTANCE hIns);
	void MapShow(HDC hdc);
public:
	int map_type[MAP_HEIGHT][MAP_WIDTH];
private:
	HBITMAP m_bitmap_redBrick;
	HBITMAP m_bitmap_redHouse;
	HBITMAP m_bitmap_yellowBrick;
	HBITMAP m_bitmap_yellowHouse;
	HBITMAP m_bitmap_Tree;
	HBITMAP m_bitmap_Box;
	HBITMAP m_bitmap_blueHouse;
};

#endif // !CGMAEMAP_H_

