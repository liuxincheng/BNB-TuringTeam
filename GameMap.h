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
};

#endif // !CGMAEMAP_H_

