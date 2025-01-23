#include "stdafx.h"
#include "GameEnd.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CGameEnd::CGameEnd()
{
}


CGameEnd::~CGameEnd()
{
	Release();
}

void CGameEnd::Initialize(void)
{	
	m_hVideo = MCIWndCreate(g_hWnd,			// �θ� ������ �ڵ�
		nullptr,		// mci �����츦 ����ϴ� �ν��Ͻ� �ڵ�
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD : �ڽ� â, WS_VISIBLE : �� ��� ȭ�鿡 �ÿ�, MCIWNDF_NOPLAYBAR : �÷��� �ٸ� �������� ����
		L"../Video/Mega Man 2 - Ending.wmv");	// ����� ������ ���

									//MoveWindow : �������� ����� ũ�⸦ ����
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

int CGameEnd::Update(void)
{
	return 0;
}

void CGameEnd::Late_Update(void)
{
}

void CGameEnd::Render(HDC hDC)
{
}

void CGameEnd::Release(void)
{
	MCIWndClose(m_hVideo);
}
