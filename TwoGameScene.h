/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CTwoGameScene.h
 *  ��Ҫ����: ˫����Ϸ������ ˫����Ϸ���������ɸ������
 *
 *  ����: ���³�
 *  ��������: 2017��6��3��
 *  ˵��:
 *
 *  �޸�����:
 *  ����:
 *  ˵��:
 *  ��ǰ�汾: 1.0
 ******************************************************************/ 
#ifndef CTWOGAMESCENE_H_
#define CTWOGAMESCENE_H_

#include "Sys.h"

class CTwoGameScene
{
public:
	CTwoGameScene();
	~CTwoGameScene();
public:
	void GameSceneInit(HINSTANCE hIns);
	void GameSceneShow(HDC hdc);
	void MouseMove(POINT point);
public:
	/* �������Ƿ��������˳�ѡ���
	** true: ������˳�����
	** false: ���δ���˳�����
	*/
	bool m_isSelect;
private:
	HBITMAP m_bitmap_gameBack;
	HBITMAP m_bitmap_quit;
	HBITMAP m_bitmap_quit_select;
};

#endif // !CTWOGAMESCENE_H_

