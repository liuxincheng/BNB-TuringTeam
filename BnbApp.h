/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CBnbApp.h
 *  ��Ҫ����: �̳� CGameCtrl �࣬��Ϸ���������࣬���𳡾��л�
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
#ifndef CBNBAPP_H_
#define CBNBAPP_H_

#include "Sys.h"
#include "CGameCtrl.h"
#include "MainScene.h"
#include "TwoGameScene.h"
#include "HelpScene.h"

/*
** ������־����������������Ϸ������˫����Ϸ��������������
*/
enum SeclectScene { MAIN_SCENE, ONE_GAME_SCENE, TWO_GAME_SCENE, HLEP_GAME_SCENE };

class CBnbApp : public CGameCtrl
{
public:
	CBnbApp();
	~CBnbApp();
public:
	DECLARE()

	// ���� ���������ࣺ �������� ˫����Ϸ������ ��������
	CMainScene mainScene;
	CTwoGameScene twoGameScene;
	CHelpScene helpScene;
public:
	// ��д���ຯ��
	virtual void OnCreateGame();
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM nTimerID);
	virtual void OnKeyDown(WPARAM nKey);
	virtual void OnLButtonDown(POINT point);
	virtual void OnLButtonUp(POINT point);
	virtual void OnMouseMove(POINT point);
public:
	/*
	** ����������������Ĳ�ͬѡ��л���Ӧ������BnbApp������Ӧ������̧���� OnLButtonUp ���ã�
	*/
	void ChangeScene();

private:
	// �������: �жϵ�ǰ�����ĸ���������ͬ������ͬ���� Ĭ����������CMainScene mainScene��
	SeclectScene m_seclectScene;
};

#endif // !CBNBAPP_H_

