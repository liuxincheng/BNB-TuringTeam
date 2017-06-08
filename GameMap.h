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

class CGameMap
{
public:
	CGameMap();
	~CGameMap();

	void MapInit(HINSTANCE hIns);
	void MapShow(HDC hdc);
private:
	HBITMAP m_bitmap_road;
	HBITMAP m_bitmap_redbrick;
	HBITMAP m_bitmap_redhouse;
	HBITMAP m_bitmap_yellowbrick;
	HBITMAP m_bitmap_yellowhouse;
	HBITMAP m_bitmap_tree;
	HBITMAP m_bitmap_box;
	HBITMAP m_bitmap_bluehouse;
};

#endif // !CGMAEMAP_H_

