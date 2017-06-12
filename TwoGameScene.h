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
#include "Bubble.h"
#include <list>

class CTwoGameScene
{
public:
	CTwoGameScene();
	~CTwoGameScene();

	// ��ͼ
	CGameMap gameMap;
	// ��Ч
	CPlaySound playSound;
public:
	void TwoGameSceneInit(HINSTANCE hIns, HWND hWnd);
	void TwoGameSceneShow(HDC hdc);
	void MouseMove(POINT point);
	void OnLButtonDown(HINSTANCE hIns,POINT point);
	void OnKeyDown(WPARAM nKey);
	void OnTwoGameRun(WPARAM nTimerID);

	void ChangeBubbleShowID();
	void AllBubbleShow(HDC hdc);
	void CreateBubble(HINSTANCE hIns,int x,int y);

	void ShowTime(HDC hdc); // ����ʱ��ʾ
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
	HBITMAP m_bitmap_timeNum;

	HWND m_twoGameWnd;
	int m_gameTime; // ����ʱʱ�� Ĭ������ӣ�300s��

	// ��������
	list<CBubble*> m_lstBubble;
};

#endif // !CTWOGAMESCENE_H_

