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

	m_gameTime = 300;      // ����ʱ������ 300s
	m_statusInfo_y = 70;   // ����Ĭ��λ�� y = 70
	m_gameStatus = STATRT; // ��Ϸ��ʼ ��ʾ��Ϸ��ʼ����

	// ��ʼ����ͼ
	gameMap.MapInit(hIns);

	// ��ʼ����Ϸ����
	PlayerOne.PlayerInit(hIns);
	PlayerTwo.PlayerInit(hIns);

	SetTimer(m_twoGameWnd, STOPSOUND_TIMER_ID, 50, NULL);
	SetTimer(m_twoGameWnd, BUBBLE_CHANGE_TIMER_ID, 200, NULL);
	SetTimer(m_twoGameWnd, GAME_TIME_TIMER_ID, 1000, NULL);
	SetTimer(m_twoGameWnd, STATUS_INFO_TIMER_ID, 80, NULL);
	SetTimer(m_twoGameWnd, PLAYERSTART_TIMER_ID,70, NULL);

	// ��Ϸ��ʼ��Ч
	playSound.Play(START_GAME_SOUND);
}

void CTwoGameScene::TwoGameSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_gameBack);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);

	// �˳���ť
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

	// ��ͼ��ʾ
	gameMap.MapShow(hdc);
	// ������ʾ
	this->AllBubbleShow(hdc);
	// ����ʱ
	this->ShowTime(hdc);
	//���������ʾ
	PlayerOne.PlayerStartShow(hdc);
	PlayerTwo.PlayerStartShow(hdc);

	// ������Ϸ�����в����øú�����ֻҪ��Ϸ��ʼ����ʱ������ʱ�����ϵ���
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
	// �ر���Ч
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

	// ��������������ʱ��
	if (nTimerID == BUBBLE_CHANGE_TIMER_ID)
	{

		this->ChangeBubbleShowID();

	}

	// �ı䵹��ʱ������--
	if (nTimerID == GAME_TIME_TIMER_ID)
	{
		if (m_gameTime == 0)
		{
			// ֹͣ����ʱ
			KillTimer(m_twoGameWnd,GAME_TIME_TIMER_ID);

			// ����ƽ������
			m_gameStatus = DRAW;
			m_statusInfo_y = 60;

			// ����ƽ����Ч
			playSound.Play(DRAW_GAME_SOUND);
		}
		else
		{
			m_gameTime--;
		}
	}

	// �ı�����λ��
	if (nTimerID == STATUS_INFO_TIMER_ID)
	{
		if (m_statusInfo_y <= -80)
		{
			KillTimer(m_twoGameWnd,STATUS_INFO_TIMER_ID); // ֹͣ��ʱ��
			m_gameStatus = NO_SHOW;                       // ����Ϸ����״̬�����ΪĬ��
		}
		else
		{
			m_statusInfo_y -= 20;
		}
	}

	// ��ҳ���������ʱ��
	if (nTimerID == PLAYERSTART_TIMER_ID)
	{
		this->ChangePlayerStartShowID();
	}

}

void CTwoGameScene::OnLButtonDown(HINSTANCE hIns,POINT point)
{
	//�������³����ݣ���괫���Ӧ�ĵ�x,y
	this->CreateBubble(hIns, point.x, point.y);

}

void CTwoGameScene::ChangeBubbleShowID()
{
	list<CBubble*>::iterator ite_Bubble = m_lstBubble.begin();
	while(ite_Bubble != m_lstBubble.end())
	{
		//�ж��������ڼ��Σ���κ���ʧ
		if((*ite_Bubble)->m_nBubbleBj == 0)
		{
			delete(*ite_Bubble);
			ite_Bubble = m_lstBubble.erase(ite_Bubble);

			playSound.Play(BLAST_SOUND); // ��ը��Ч
		}
		else
		{
			//�ı����ݵ�showidʵ�����������任
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

	playSound.Play(PUT_BUEBLE_SOUND); // ����������Ч
}

void CTwoGameScene::ShowTime(HDC hdc)
{
	// ʱ���ʽ00:00
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
	// ƽ��!!!
	if (m_gameStatus == DRAW) word_y = 160; 
	// ��һ��� ʤ������
	else if (m_gameStatus == PLAYER_ONE_WIN) 
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,0,110,25,RGB(255,0,255));
	}
	// �ڶ���� ʤ������
	else if (m_gameStatus == PLAYER_TWO_WIN)
	{
		word_y = 80;
		SelectObject(hdcMem,m_bitmap_win_word);
		TransparentBlt(hdc,260,40,110,25,hdcMem,0,25,110,25,RGB(255,0,255));
	}
	// ��������ʾ
	else word_y = 0;

	// ѡ��������Ϣ
	SelectObject(hdcMem,m_bitmap_statusInfo);
	TransparentBlt(hdc,200,m_statusInfo_y,240,80,hdcMem,0,word_y,240,80,RGB(255,0,255));
	DeleteObject(hdcMem);
}

void CTwoGameScene::ChangePlayerStartShowID()
{

	if (PlayerOne.m_Start_nShowID == 9 && PlayerTwo.m_Start_nShowID == 9)
	{

		PlayerOne.m_Start_nShowID = 8; //���1
		PlayerTwo.m_Start_nShowID = 8; //���2

		KillTimer(m_twoGameWnd,PLAYERSTART_TIMER_ID);
	} 
	else
	{
		PlayerOne.m_Start_nShowID++;
		PlayerTwo.m_Start_nShowID++;
	}
}