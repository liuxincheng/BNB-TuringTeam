#include "TwoGameScene.h"

CTwoGameScene::CTwoGameScene()
{
	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_bitmap_timeNum = NULL;
	m_bitmap_statusInfo = NULL;
	m_bitmap_win_word = NULL;
	m_isSelect = false;
	m_gameTime = 0;
	m_statusInfo_y = 0;

	m_twoGameWnd = NULL;
	m_gameStatus = NO_SHOW;
}

CTwoGameScene::~CTwoGameScene()
{
	DeleteObject(m_bitmap_gameBack);
	DeleteObject(m_bitmap_quit);
	DeleteObject(m_bitmap_quit_select);
	DeleteObject(m_bitmap_timeNum);
	DeleteObject(m_bitmap_statusInfo);
	DeleteObject(m_bitmap_win_word);

	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_bitmap_timeNum = NULL;
	m_bitmap_statusInfo = NULL;
	m_bitmap_win_word = NULL;
}

void CTwoGameScene::TwoGameSceneInit(HINSTANCE hIns, HWND hWnd)
{
	m_twoGameWnd = hWnd;
	m_bitmap_gameBack = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_GAME_BACK));
	m_bitmap_quit = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME));
	m_bitmap_quit_select = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME_SELECT));
	m_bitmap_timeNum = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TIME_NUMBER));
	m_bitmap_statusInfo = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GAMEOVER_WORD));
	m_bitmap_win_word = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYER_NUM_WORD));

	m_gameTime = 300;      // 倒计时计数器 300s
	m_statusInfo_y = 70;   // 文字默认位置 y = 70
	m_gameStatus = STATRT; // 游戏开始 显示游戏开始文字

	// 初始化地图
	gameMap.MapInit(hIns);

	// 初始化游戏人物
	PlayerOne.PlayerInit(hIns);
	PlayerTwo.PlayerInit(hIns);

	SetTimer(m_twoGameWnd, STOPSOUND_TIMER_ID, 50, NULL);
	SetTimer(m_twoGameWnd, BUBBLE_CHANGE_TIMER_ID, 200, NULL);
	SetTimer(m_twoGameWnd, GAME_TIME_TIMER_ID, 1000, NULL);
	SetTimer(m_twoGameWnd, STATUS_INFO_TIMER_ID, 80, NULL);
	SetTimer(m_twoGameWnd, PLAYERSTART_TIMER_ID,70, NULL);

	// 游戏开始音效
	playSound.Play(START_GAME_SOUND);
}

void CTwoGameScene::TwoGameSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_gameBack);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);

	// 退出按钮
	if (m_isSelect)
	{
		SelectObject(hdcMem,m_bitmap_quit_select);
	} 
	else
	{
		SelectObject(hdcMem,m_bitmap_quit);
	}

	BitBlt(hdc,650,556,130,30,hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);

	// 地图显示
	gameMap.MapShow(hdc);
	// 泡泡显示
	this->AllBubbleShow(hdc);
	// 倒计时
	this->ShowTime(hdc);
	//人物出场显示
	PlayerOne.PlayerStartShow(hdc);
	PlayerTwo.PlayerStartShow(hdc);

	// 正常游戏过程中不调用该函数，只要游戏开始结束时启动定时器不断调用
	if (m_gameStatus != NO_SHOW)
	{
		this->ShowGameStatus(hdc);
	}

}

void CTwoGameScene::MouseMove(POINT point)
{
	if (point.x > 650 && point.x < 780 && point.y > 556 && point.y < 586)
	{
		m_isSelect = true;
	}
	else
	{
		m_isSelect = false;
	}
}

void CTwoGameScene::OnKeyDown(WPARAM nKey)
{
	switch (nKey)
	{
	// 关闭音效
	case VK_F7:
		if (playSound.isKeyToStop) 
		{
			playSound.isKeyToStop = false;
			SetTimer(m_twoGameWnd,STOPSOUND_TIMER_ID,50,NULL);
		}
		else 
		{
			playSound.isKeyToStop = true;
			KillTimer(m_twoGameWnd,STOPSOUND_TIMER_ID);
		}		
		break;

	}
}

void CTwoGameScene::OnTwoGameRun(WPARAM nTimerID)
{
	if (nTimerID == STOPSOUND_TIMER_ID)
	{
		if (playSound.isPlay && (playSound.GetPos() >= playSound.GetFileLen()))
		{
			playSound.Stop();
		}
	}

	// 泡泡跳动动画定时器
	if (nTimerID == BUBBLE_CHANGE_TIMER_ID)
	{

		this->ChangeBubbleShowID();

	}

	// 改变倒计时计数器--
	if (nTimerID == GAME_TIME_TIMER_ID)
	{
		if (m_gameTime == 0)
		{
			// 停止倒计时
			KillTimer(m_twoGameWnd,GAME_TIME_TIMER_ID);

			// 弹出平局文字
			m_gameStatus = DRAW;
			m_statusInfo_y = 60;

			// 播放平局音效
			playSound.Play(DRAW_GAME_SOUND);
		}
		else
		{
			m_gameTime--;
		}
	}

	// 改变文字位置
	if (nTimerID == STATUS_INFO_TIMER_ID)
	{
		if (m_statusInfo_y <= -80)
		{
			KillTimer(m_twoGameWnd,STATUS_INFO_TIMER_ID); // 停止计时器
			m_gameStatus = NO_SHOW;                       // 将游戏文字状态标记置为默认
		}
		else
		{
			m_statusInfo_y -= 20;
		}
	}

	// 玩家出场动画定时器
	if (nTimerID == PLAYERSTART_TIMER_ID)
	{
		this->ChangePlayerStartShowID();
	}

}

void CTwoGameScene::OnLButtonDown(HINSTANCE hIns,POINT point)
{
	//按键按下出泡泡，鼠标传入对应的点x,y
	this->CreateBubble(hIns, point.x, point.y);

}

void CTwoGameScene::ChangeBubbleShowID()
{
	list<CBubble*>::iterator ite_Bubble = m_lstBubble.begin();
	while(ite_Bubble != m_lstBubble.end())
	{
		//判断跳动到第几次，五次后消失
		if((*ite_Bubble)->m_nBubbleBj == 0)
		{
			delete(*ite_Bubble);
			ite_Bubble = m_lstBubble.erase(ite_Bubble);

			playSound.Play(BLAST_SOUND); // 爆炸音效
		}
		else
		{
			//改变泡泡的showid实现它的跳动变换
			if((*ite_Bubble)->m_nShowID == 0)
			{
				(*ite_Bubble)->m_nShowID = 2;

			}
			else
			{
				((*ite_Bubble)->m_nShowID)--;
			}
			((*ite_Bubble)->m_nBubbleBj)--;

			ite_Bubble++;
		}
	}
}

void CTwoGameScene::AllBubbleShow(HDC hdc)
{
	list<CBubble*>::iterator ite_Bubble = m_lstBubble.begin();
	while(ite_Bubble != m_lstBubble.end())
	{
		(*ite_Bubble)->BubbleShow(hdc);
		++ite_Bubble;
	}
}

void CTwoGameScene::CreateBubble(HINSTANCE hIns,int x,int y)
{
	CBubble* bubble = new CBubble;
	bubble->BubbleInit(hIns,x,y);
	m_lstBubble.push_back(bubble);

	playSound.Play(PUT_BUEBLE_SOUND); // 放置泡泡音效
}

void CTwoGameScene::ShowTime(HDC hdc)
{
	// 时间格式00:00
	int time_one = 0; 
	int time_two = m_gameTime / 60;
	int time_three = (m_gameTime - time_two * 60) / 10;
	int time_four = (m_gameTime - time_two * 60) % 10;

	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_timeNum);
	TransparentBlt(hdc,708,43,12,10,hdcMem,12*time_one,0,12,10,RGB(255,0,255));
	TransparentBlt(hdc,722,43,12,10,hdcMem,12*time_two,0,12,10,RGB(255,0,255));
	TransparentBlt(hdc,741,43,12,10,hdcMem,12*time_three,0,12,10,RGB(255,0,255));
	TransparentBlt(hdc,756,43,12,10,hdcMem,12*time_four,0,12,10,RGB(255,0,255));
	DeleteObject(hdcMem);
}

void CTwoGameScene::ShowGameStatus(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);

	static int word_y = 0;
	// 平局!!!
	if (m_gameStatus == DRAW) word_y = 160; 
	// 第一玩家 胜利！！
	else if (m_gameStatus == PLAYER_ONE_WIN) 
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,0,110,25,RGB(255,0,255));
	}
	// 第二玩家 胜利！！
	else if (m_gameStatus == PLAYER_TWO_WIN)
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,25,110,25,RGB(255,0,255));
	}
	// 无文字提示
	else word_y = 0;

	// 选择文字信息
	SelectObject(hdcMem,m_bitmap_statusInfo);
	TransparentBlt(hdc,200,m_statusInfo_y,240,80,hdcMem,0,word_y,240,80,RGB(255,0,255));
	DeleteObject(hdcMem);
}

void CTwoGameScene::ChangePlayerStartShowID()
{

	if (PlayerOne.m_Start_nShowID == 9 && PlayerTwo.m_Start_nShowID == 9)
	{

		PlayerOne.m_Start_nShowID = 8; //玩家1
		PlayerTwo.m_Start_nShowID = 8; //玩家2

		KillTimer(m_twoGameWnd,PLAYERSTART_TIMER_ID);
	} 
	else
	{
		PlayerOne.m_Start_nShowID++;
		PlayerTwo.m_Start_nShowID++;
	}
}