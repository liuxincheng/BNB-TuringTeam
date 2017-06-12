/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  文件名称: CTwoGameScene.h
 *  简要描述: 双人游戏场景类 双人游戏操作交互由该类控制
 *
 *  作者: 刘新成
 *  创建日期: 2017年6月3日
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 *  当前版本: 1.0
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

	// 地图
	CGameMap gameMap;
	// 音效
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

	void ShowTime(HDC hdc); // 倒计时显示
public: 
	/* 标记鼠标是否悬浮于退出选择框
	** true: 鼠标在退出框上
	** false: 鼠标未在退出框上
	*/
	bool m_isSelect;
private:
	HBITMAP m_bitmap_gameBack;
	HBITMAP m_bitmap_quit;
	HBITMAP m_bitmap_quit_select;
	HBITMAP m_bitmap_timeNum;

	HWND m_twoGameWnd;
	int m_gameTime; // 倒计时时间 默认五分钟（300s）

	// 泡泡链表
	list<CBubble*> m_lstBubble;
};

#endif // !CTWOGAMESCENE_H_

