#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_LOGO), m_ePreScene(SC_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete<CScene*>(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_SELECT_BOSS:
			m_pScene = new CSelectBoss;
			break;

		case SC_BOSS_INTRO:
			m_pScene = new CBossIntro;
			break;

		case SC_STAGE_AIRMAN:
			m_pScene = new CStgAirman;
			break;

		case SC_GAME_END:
			m_pScene = new CGameEnd;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_END:
			break;

		}

		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Init_Scene(SCENEID eID)
{
	Safe_Delete<CScene*>(m_pScene);
	m_pScene = new CStgAirman;
	m_pScene->Initialize();
	m_ePreScene = m_eCurScene;
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
