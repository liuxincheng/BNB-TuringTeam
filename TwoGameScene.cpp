#include "TwoGameScene.h"

CTwoGameScene::CTwoGameScene()
{
	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_bitmap_timeNum = NULL;
	m_isSelect = false;
	m_gameTime = 300;

	m_twoGameWnd = NULL;
}

CTwoGameScene::~CTwoGameScene()
{
	DeleteObject(m_bitmap_gameBack);
	DeleteObject(m_bitmap_quit);
	DeleteObject(m_bitmap_quit_select);
	DeleteObject(m_bitmap_timeNum);

	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_bitmap_timeNum = NULL;
}

void CTwoGameScene::TwoGameSceneInit(HINSTANCE hIns, HWND hWnd)
{
	m_twoGameWnd = hWnd;
	m_bitmap_gameBack = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_GAME_BACK));
	m_bitmap_quit = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME));
	m_bitmap_quit_select = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME_SELECT));
	m_bitmap_timeNum = LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TIME_NUMBER));

	// ��ʼ����ͼ
	gameMap.MapInit(hIns);
	
	SetTimer(m_twoGameWnd, STOPSOUND_TIMER_ID, 50, NULL);
	SetTimer(m_twoGameWnd, BUBBLE_CHANGE_TIMER_ID, 200, NULL);
	SetTimer(m_twoGameWnd, GAME_TIME_TIMER_ID, 1000, NULL);

	// ��Ϸ��ʼ��Ч
	playSound.Play(START_GAME_SOUND);
}

void CTwoGameScene::TwoGameSceneShow(HDC hdc)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem,m_bitmap_gameBack);
	BitBlt(hdc,0,0,800,600,hdcMem,0,0,SRCCOPY);

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
			KillTimer(m_twoGameWnd,GAME_TIME_TIMER_ID);
		}
		else
		{
			m_gameTime--;
		}
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
	int time_one = 0;
	int time_two = m_gameTime / 60;
	int time_three = (m_gameTime - time_two * 60) / 10;
	int time_four = (m_gameTime - time_two * 60) % 10;

	HDC hdcMem = CreateCompatibleDC(hdc);

	SelectObject(hdcMem,m_bitmap_timeNum);
	TransparentBlt(hdc,708,43,12,10,hdcMem,12*time_one,0,12,10,RGB(255,0,255));

	SelectObject(hdcMem,m_bitmap_timeNum);
	TransparentBlt(hdc,722,43,12,10,hdcMem,12*time_two,0,12,10,RGB(255,0,255));

	SelectObject(hdcMem,m_bitmap_timeNum);
	TransparentBlt(hdc,741,43,12,10,hdcMem,12*time_three,0,12,10,RGB(255,0,255));

	SelectObject(hdcMem,m_bitmap_timeNum);
	TransparentBlt(hdc,756,43,12,10,hdcMem,12*time_four,0,12,10,RGB(255,0,255));

	DeleteObject(hdcMem);
}