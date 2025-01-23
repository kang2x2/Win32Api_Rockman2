#include "stdafx.h"
#include "TriggerMgr.h"

CTriggerMgr*	CTriggerMgr::m_pInstance = nullptr;

CTriggerMgr::CTriggerMgr()
{
}


CTriggerMgr::~CTriggerMgr()
{
	Release();
}

void CTriggerMgr::Add_Trigger(TRIGGER_ID eID, CTrigger * pTgr)
{
	if (TRIGGER_END <= eID || pTgr == nullptr)
		return;
	m_tgrList[eID].push_back(pTgr);
}

void CTriggerMgr::Update(void)
{
	for (size_t i = 0; i < TRIGGER_END; ++i)
	{
		for (auto iter = m_tgrList[i].begin();
			iter != m_tgrList[i].end();)
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CTrigger*>(*iter);
				iter = m_tgrList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CTriggerMgr::Late_Update(void)
{
	for (size_t i = 0; i < TRIGGER_END; ++i)
	{
		for (auto& iter : m_tgrList[i])
		{
			iter->Late_Update();

			if (m_tgrList[i].empty())
				break;
		}
	}
}

void CTriggerMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < TRIGGER_END; ++i)
	{
		for (auto& iter : m_tgrList[i])
			iter->Render(hDC);
	}
}

void CTriggerMgr::Release(void)
{
	for (size_t i = 0; i < TRIGGER_END; ++i)
	{
		for_each(m_tgrList[i].begin(), m_tgrList[i].end(), CDeleteObj());
		m_tgrList[i].clear();
	}
}
