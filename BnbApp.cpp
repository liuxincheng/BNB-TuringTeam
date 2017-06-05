#include "BnbApp.h"

IMPLEMENT(CBnbApp)

	CBnbApp::CBnbApp()
{
	m_seclectScene = MAIN_SCENE;
	isKey_stopMusic = false;

	playMusic = NULL;
}

CBnbApp::~CBnbApp()
{
	delete playMusic;
	playMusic = NULL;
}

void CBnbApp::OnCreateGame()
{
	// 各场景初始化
	mainScene.MainSceneInit(m_hIns);
	twoGameScene.TwoGameSceneInit(m_hIns,m_hMainWnd);
	helpScene.HelpSceneInit(m_hIns);

	// 播放相应背景音乐
	playMusic = new CPlayMusic;
	if (playMusic != NULL)
	{
		this->PlayBackMusic();
	}
	else
	{
		MessageBox( NULL, TEXT("音乐加载失败!"), TEXT("提示"), MB_OK | MB_ICONERROR );
	}
}

void CBnbApp::OnGameDraw()
{
	HDC hdc = GetDC(m_hMainWnd);

	// 解决闪屏问题
	HDC hdcMem = ::CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,800,600);
	SelectObject(hdcMem,hBitmap);

	// 绘图：不同场景
	if(this->m_seclectScene == ONE_GAME_SCENE)
	{
		twoGameScene.TwoGameSceneShow(hdcMem);
	}
	else if (this->m_seclectScene == TWO_GAME_SCENE)
	{
		twoGameScene.TwoGameSceneShow(hdcMem);
	}
	else if (this->m_seclectScene == HLEP_GAME_SCENE)
	{
		helpScene.HelpSceneShow(hdcMem);
	}
	else
	{
		mainScene.MainSceneShow(hdcMem);
	}

	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
	ReleaseDC(m_hMainWnd,hdc);
}

void CBnbApp::OnGameRun(WPARAM nTimerID)
{
	if (m_seclectScene == TWO_GAME_SCENE)
	{
		twoGameScene.OnTwoGameRun(nTimerID);
	}
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

			// 播放相应背景音乐
			if (!this->isKey_stopMusic)
			{
				this->PlayBackMusic();
			}
		}
		break;

	// F8键 背景音乐开关
	case VK_F8:
		if (this->isKey_stopMusic)
		{
			playMusic = new CPlayMusic;
			this->isKey_stopMusic = false;
		}

		else
		{
			this->isKey_stopMusic = true;
		}
		this->PlayBackMusic();
		break;
	}

	twoGameScene.OnKeyDown(nKey);
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

	// 主场景进去帮助场景，背景音乐不变
	if (this->m_seclectScene != HLEP_GAME_SCENE && (!this->isKey_stopMusic))
	{
		this->PlayBackMusic();
	}

	// 重绘
	this->OnGameDraw();
}

void CBnbApp::PlayBackMusic()
{
	// F8键按下 播放或停止背景音乐
	if (this->isKey_stopMusic)
	{
		if(!playMusic->isStop)
		{
			playMusic->SotpBackMusic();

			// 删除播放音乐对象
			delete playMusic;
			playMusic = NULL;
		}
		else
		{
			if (playMusic != NULL)
			{
				if (this->m_seclectScene == ONE_GAME_SCENE) playMusic->PlayBackMusic(ONEGAME_BACK_MUSIC);
				else if(this->m_seclectScene == TWO_GAME_SCENE) playMusic->PlayBackMusic(TWOGAME_BACK_MUSIC);
				else playMusic->PlayBackMusic(MAIN_BACK_MUSIC);
			}
		}
	}

	// F8键未按下 根据场景播放不同背景音乐
	else
	{
		if (this->m_seclectScene == ONE_GAME_SCENE) playMusic->PlayBackMusic(ONEGAME_BACK_MUSIC);
		else if(this->m_seclectScene == TWO_GAME_SCENE) playMusic->PlayBackMusic(TWOGAME_BACK_MUSIC);
		else playMusic->PlayBackMusic(MAIN_BACK_MUSIC);
	}	
}
