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
	m_hVideo = MCIWndCreate(g_hWnd,			// 부모 윈도우 핸들
		nullptr,		// mci 윈도우를 사용하는 인스턴스 핸들
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD : 자식 창, WS_VISIBLE : 그 즉시 화면에 시연, MCIWNDF_NOPLAYBAR : 플레이 바를 생성하지 않음
		L"../Video/Mega Man 2 - Ending.wmv");	// 재생할 파일의 경로

									//MoveWindow : 동영상을 재생할 크기를 설정
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
