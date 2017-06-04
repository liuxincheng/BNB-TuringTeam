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
};

#endif // !CGMAEMAP_H_

