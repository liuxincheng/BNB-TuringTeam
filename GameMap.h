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

