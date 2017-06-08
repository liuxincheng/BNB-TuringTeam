#include "TwoGameScene.h"

CTwoGameScene::CTwoGameScene()
{
	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
	m_isSelect = false;

	m_twoGameWnd = NULL;
}

CTwoGameScene::~CTwoGameScene()
{
	DeleteObject(m_bitmap_gameBack);
	DeleteObject(m_bitmap_quit);
	DeleteObject(m_bitmap_quit_select);
	m_bitmap_gameBack = NULL;
	m_bitmap_quit = NULL;
	m_bitmap_quit_select = NULL;
}

void CTwoGameScene::TwoGameSceneInit(HINSTANCE hIns, HWND hWnd)
{
	m_twoGameWnd = hWnd;
	m_bitmap_gameBack = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_GAME_BACK));
	m_bitmap_quit = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME));
	m_bitmap_quit_select = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_QUIT_GAME_SELECT));

	// ��ʼ����ͼ
	gameMap.MapInit(hIns);
	
	SetTimer(m_twoGameWnd, STOPSOUND_TIMER_ID, 50, NULL);

	// ��Ϸ��ʼ��Ч
	playSound.Play(START_GAME_SOUND);
	//�������ݴ�С�仯�Ķ�ʱ��
	SetTimer(m_twoGameWnd,BubbleChange_TIMER_ID,150,NULL);
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
	//������ʾ
	Bubble.BubbleShow(hdc);
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
	//ͨ����ʱ���ı�showidʵ������
	if (nTimerID == BubbleChange_TIMER_ID)
	{
		this->ChangeBubbleShowID();
	}
}
void CTwoGameScene::OnLButtonDown(HINSTANCE hIns,POINT point)
{
	//�������³����ݣ��������Ӧ�ĵ�x,y
	Bubble.BubbleInit(hIns,point.x,point.y);
	
}
void CTwoGameScene::ChangeBubbleShowID()
{
	//�ı����ݵ�showidʵ�����������任
	if(Bubble.m_nShowID == 0)
	{
		Bubble.m_nShowID=2;
	}
	else
	{
		Bubble.m_nShowID--;
	}
}