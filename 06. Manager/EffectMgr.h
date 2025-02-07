#pragma once

#include "Effect.h"

class CEffectMgr
{
private:
	CEffectMgr();
	~CEffectMgr();

public:
	void		Add_Effect(EFFECT_ID eID, CEffect* pEft);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	static CEffectMgr* Get_Instance() {
		if (!m_pInstance) {
			m_pInstance = new CEffectMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	list<CEffect*> m_eftList[EFFECT_END];
	static CEffectMgr* m_pInstance;
};

