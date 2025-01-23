#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "TriggerMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"


CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	srand(unsigned(time(NULL)));

	m_DC = GetDC(g_hWnd);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"Back");
	CSoundMgr::Get_Instance()->Initialize();

	CEffectMgr::Get_Instance();

	m_bGameStart = false;
}

void CMainGame::Update(void)
{
	if (!m_bGameStart) {
		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE) && !m_bGameStart) {
			CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
			//CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_AIRMAN);
			m_bGameStart = true;
		}
	}


	if (m_bGameStart) {
		CSceneMgr::Get_Instance()->Update();
	}
}

void CMainGame::Late_Update(void)
{
	if (m_bGameStart) {
		CSceneMgr::Get_Instance()->Late_Update();
	}
}

void CMainGame::Render()
{
	if (SC_GAME_END == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	if (m_bGameStart) {
		CSceneMgr::Get_Instance()->Render(hMemDC);
	}
}

void CMainGame::Release(void)
{
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CTriggerMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CEffectMgr::Get_Instance()->Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}

