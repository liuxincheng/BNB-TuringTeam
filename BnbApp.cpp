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
	// ��������ʼ��
	mainScene.MainSceneInit(m_hIns);
	twoGameScene.GameSceneInit(m_hIns);
	helpScene.HelpSceneInit(m_hIns);
}


void CBnbApp::OnGameDraw()
{
	HDC hdc = GetDC(m_hMainWnd);

	// ��ͼ����ͬ����
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
	// F3���� ����˫����Ϸ���水��F3�ɷ��������� MAIN_SCENE
	case VK_F3:
		if (this->m_seclectScene == TWO_GAME_SCENE || this->m_seclectScene == ONE_GAME_SCENE)
		{
			// ������ͣ���˳�ѡ�� ���������� �轫���λ��Ϊ false
			if (twoGameScene.m_isSelect)
			{
				twoGameScene.m_isSelect = false;
			}

			// �л���������
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
	// �����ǰ����Ϊ��������������ڿ�ѡ��Χ�ڣ�������������ѡ��ͬ����
	if (m_seclectScene == MAIN_SCENE && (mainScene.m_seclectNum == ONE_GAME || mainScene.m_seclectNum == TWO_GAME || mainScene.m_seclectNum == HLEP_GAME || mainScene.m_seclectNum == QUIT_GAME))
	{
		this->ChangeScene();
	}

	// �����ǰ����Ϊ����������������ڷ��ؿ��ڣ���������������������
	if (m_seclectScene == HLEP_GAME_SCENE && helpScene.m_isSelect)
	{
		m_seclectScene = MAIN_SCENE;
		helpScene.m_isSelect = false; // ���غ󽫰������������λ�ñ����Ϊfalse
	}

	if ((m_seclectScene == TWO_GAME_SCENE || m_seclectScene == ONE_GAME_SCENE) && twoGameScene.m_isSelect)
	{
		if ( MessageBox( NULL, TEXT("���ˣ� ��Ϸ���ڽ���, ȷ���˳�ô?"), \
			TEXT("�˳�"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
		{
			PostQuitMessage(0);
		}
	}

	// �ػ�
	this->OnGameDraw();
}

void CBnbApp::OnMouseMove(POINT point)
{
	//��ǰ����Ϊ����������£��������λ�ã����Ƿ�������������ĳ��ѡ��
	if (m_seclectScene == MAIN_SCENE)
	{
		mainScene.MouseMove(point);
	}

	//��ǰ����Ϊ������������£��������λ�ã����Ƿ������ڷ���ѡ��
	if (m_seclectScene == HLEP_GAME_SCENE)
	{
		helpScene.MouseMove(point);
	}

	// ��ǰ����Ϊ��Ϸ��������£��������λ�ã����Ƿ��������Ƴ�ѡ��
	if (m_seclectScene == TWO_GAME_SCENE || m_seclectScene == ONE_GAME_SCENE)
	{
		twoGameScene.MouseMove(point);
	}

	// �ػ�
	this->OnGameDraw();
}

void CBnbApp::ChangeScene()
{
	// ������� ������������ı�� �ж�Ӧ�л����ĸ�����
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
		if ( MessageBox( NULL, TEXT("���ˣ� ��Ĳ�������ô? ������˼����"), \
			TEXT("�˳�"), MB_OKCANCEL | MB_ICONQUESTION ) == IDOK )
		{
			PostQuitMessage(0);
		}
		else
		{
			this->m_seclectScene = MAIN_SCENE;
		}
	}

	// �ػ�
	this->OnGameDraw();
}
