#pragma once

#include "Trigger.h"

class CTriggerMgr
{
private:
	CTriggerMgr();
	~CTriggerMgr();

public:
	void		Add_Trigger(TRIGGER_ID eID, CTrigger* pTgr);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	list<CTrigger*> Get_TgrList(TRIGGER_ID eID) { return m_tgrList[eID]; }
	list<CTrigger*>* Get_TgrListAry() { return m_tgrList; }

public:
	static CTriggerMgr* Get_Instance() {
		if (!m_pInstance) {
			m_pInstance = new CTriggerMgr;
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
	list<CTrigger*> m_tgrList[TRIGGER_END];
	static CTriggerMgr* m_pInstance;
};

