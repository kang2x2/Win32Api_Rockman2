#pragma once

#include "Scene.h"

#include "Logo.h"
#include "MyMenu.h"
#include "SelectBoss.h"
#include "BossIntro.h"
#include "StgAirman.h"
#include "GameEnd.h"
#include "MyEdit.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eID);
	void		Init_Scene(SCENEID eID);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	SCENEID			Get_SceneID() { return m_eCurScene; }

public:
	static CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;
};