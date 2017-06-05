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
#include "GameMap.h"
#include "PlaySound.h"

class CTwoGameScene
{
public:
	CTwoGameScene();
	~CTwoGameScene();

	// ��ͼ
	CGameMap gameMap;
	CPlaySound playSound;
public:
	void TwoGameSceneInit(HINSTANCE hIns, HWND hWnd);
	void TwoGameSceneShow(HDC hdc);
	void MouseMove(POINT point);
	void OnKeyDown(WPARAM nKey);
	void OnTwoGameRun(WPARAM nTimerID);
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

	HWND m_twoGameWnd;
};

#endif // !CTWOGAMESCENE_H_

