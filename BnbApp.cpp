#include "BnbApp.h"

IMPLEMENT(CBnbApp)

	CBnbApp::CBnbApp()
{
	m_seclectScene = MAIN_SCENE;
}

CBnbApp::~CBnbApp()
{
}

void CBnbApp::OnCreateGame()
{
	// 各场景初始化
	mainScene.MainSceneInit(m_hIns);
	twoGameScene.GameSceneInit(m_hIns);
	helpScene.HelpSceneInit(m_hIns);
}


void CBnbApp::OnGameDraw()
{
	HDC hdc = GetDC(m_hMainWnd);

	// 绘图：不同场景
	if(this->m_seclectScene == ONE_GAME_SCENE)
	{
		twoGameScene.GameSceneShow(hdc);
	}
	else if (this->m_seclectScene == TWO_GAME_SCENE)
	{
		twoGameScene.GameSceneShow(hdc);
	}
	else if (this->m_seclectScene == HLEP_GAME_SCENE)
	{
		helpScene.HelpSceneShow(hdc);
	}
	else
	{
		mainScene.MainSceneShow(hdc);
	}
	ReleaseDC(m_hMainWnd,hdc);
}

void CBnbApp::OnGameRun(WPARAM nTimerID)
{
}

void CBnbApp::OnKeyDown(WPARAM nKey)
{
	switch (nKey)
	{
	// F3键： 当在双人游戏界面按下F3可返回主场景 MAIN_SCENE
	case VK_F3:
		if (this->m_seclectScene == TWO_GAME_SCENE || this->m_seclectScene == ONE_GAME_SCENE)
		{
			// 如果鼠标停留退出选项 返回主场景 需将标记位置为 false
			if (twoGameScene.m_isSelect)
			{
				twoGameScene.m_isSelect = false;
			}

			// 切换回主场景
			m_seclectScene = MAIN_SCENE;
			this->OnGameDraw();
		}
		break;
	}
}

void CBnbApp::OnLButtonDown(POINT point)
{
}

void CBnbApp::OnLButtonUp(POINT point)
{
	// 如果当前场景为主场景并且鼠标在可选范围内，鼠标左键才允许选择不同场景
	if (m_seclectScene == MAIN_SCENE && (mainScene.m_seclectNum == ONE_GAME || mainScene.m_seclectNum == TWO_GAME || mainScene.m_seclectNum == HLEP_GAME || mainScene.m_seclectNum == QUIT_GAME))
	{
		this->ChangeScene();
	}

	// 如果当前场景为帮助场景并且鼠标在返回框内，鼠标左键才允许返回主场景
	if (m_seclectScene == HLEP_GAME_SCENE && helpScene.m_isSelect)
	{
		m_seclectScene = MAIN_SCENE;
		helpScene.m_isSelect = false; // 返回后将帮助场景的鼠标位置标记置为false
	}

	if ((m_seclectScene == TWO_GAME_SCENE || m_seclectScene == ONE_GAME_SCENE) && twoGameScene.m_isSelect)
	{
		if ( MessageBox( NULL, TEXT("大人： 游戏正在进行, 确认退出么?"), \
			TEXT("退出"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
		{
			PostQuitMessage(0);
		}
	}

	// 重绘
	this->OnGameDraw();
}

void CBnbApp::OnMouseMove(POINT point)
{
	//当前场景为主场景情况下，传入鼠标位置，看是否悬浮于主界面某个选项
	if (m_seclectScene == MAIN_SCENE)
	{
		mainScene.MouseMove(point);
	}

	//当前场景为帮助场景情况下，传入鼠标位置，看是否悬浮于返回选项
	if (m_seclectScene == HLEP_GAME_SCENE)
	{
		helpScene.MouseMove(point);
	}

	// 当前场景为游戏场景情况下，传入鼠标位置，看是否悬浮于推出选项
	if (m_seclectScene == TWO_GAME_SCENE || m_seclectScene == ONE_GAME_SCENE)
	{
		twoGameScene.MouseMove(point);
	}

	// 重绘
	this->OnGameDraw();
}

void CBnbApp::ChangeScene()
{
	// 鼠标点击后 根据鼠标悬浮的标记 判断应切换到哪个场景
	if (mainScene.m_seclectNum == ONE_GAME)
	{
		this->m_seclectScene = ONE_GAME_SCENE;
	}
	else if (mainScene.m_seclectNum == TWO_GAME)
	{
		this->m_seclectScene = TWO_GAME_SCENE;
	}
	else if (mainScene.m_seclectNum == HLEP_GAME)
	{
		this->m_seclectScene = HLEP_GAME_SCENE;
	}
	else if (mainScene.m_seclectNum == QUIT_GAME)
	{
		if ( MessageBox( NULL, TEXT("大人： 真的不想玩了么? 请您三思啊！"), \
			TEXT("退出"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
		{
			PostQuitMessage(0);
		}
		else
		{
			this->m_seclectScene = MAIN_SCENE;
		}
	}

	// 重绘
	this->OnGameDraw();
}
