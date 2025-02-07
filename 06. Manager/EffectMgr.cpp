#include "stdafx.h"
#include "EffectMgr.h"

CEffectMgr*	CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
{
}


CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Add_Effect(EFFECT_ID eID, CEffect * pEft)
{
	if (EFFECT_END <= eID || pEft == nullptr)
		return;
	m_eftList[eID].push_back(pEft);
}

void CEffectMgr::Update(void)
{
	for (size_t i = 0; i < EFFECT_END; ++i)
	{
		for (auto iter = m_eftList[i].begin();
			iter != m_eftList[i].end();)
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CEffect*>(*iter);
				iter = m_eftList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CEffectMgr::Late_Update(void)
{
	for (size_t i = 0; i < EFFECT_END; ++i)
	{
		for (auto& iter : m_eftList[i])
		{
			iter->Late_Update();

			if (m_eftList[i].empty())
				break;
		}
	}
}

void CEffectMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < EFFECT_END; ++i)
	{
		for (auto& iter : m_eftList[i])
			iter->Render(hDC);
	}
}

void CEffectMgr::Release(void)
{
	for (size_t i = 0; i < EFFECT_END; ++i)
	{
		for_each(m_eftList[i].begin(), m_eftList[i].end(), CDeleteObj());
		m_eftList[i].clear();
	}
}
