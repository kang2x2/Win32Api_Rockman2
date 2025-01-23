#pragma once
#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	list<CObj*> Get_ObjList(OBJID eID) { return m_ObjList[eID]; }

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJID eID);

private:
	list<CObj*>		m_ObjList[OBJ_END];

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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
	static CObjMgr*		m_pInstance;

};

