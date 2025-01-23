#include "stdafx.h"
#include "Trigger.h"

#include "ObjMgr.h"
#include "GoblinTile.h"
#include "CloudTile.h"
#include "Pipi.h"

CTrigger::CTrigger() : m_bDead(false)
{
}


CTrigger::~CTrigger()
{
}

void CTrigger::Create_GoblinTile(INFO _info)
{
	if (!m_bDead) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_TILE, new CGoblinTile(_info));
		m_bDead = true;
	}
}

void CTrigger::Create_CloudTile(INFO _info)
{
	if (!m_bDead) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_TILE, new CCloudTile(_info));
		m_bDead = true;
	}
}

void CTrigger::Create_Pipi(INFO _info)
{
	if (!m_bDead) {
		CObjMgr::Get_Instance()->Add_Object(OBJ_ENEMY, new CPipi(_info));
		m_bDead = true;
	}
}

void CTrigger::Update_Rect(void)
{
	m_tDrawRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tDrawRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tDrawRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tDrawRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
