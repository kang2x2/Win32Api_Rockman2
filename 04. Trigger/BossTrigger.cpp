#include "stdafx.h"
#include "BossTrigger.h"

#include "ScrollMgr.h"

CBossTrigger::CBossTrigger(INFO _myInfo, INFO _targetInfo)
{
	m_sType = "BossTrigger";
	m_tInfo = _myInfo;
	m_tTargetInfo = _targetInfo;
}


CBossTrigger::~CBossTrigger()
{
}

void CBossTrigger::Initialize(void)
{
}

int CBossTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBossTrigger::Late_Update(void)
{
}

void CBossTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
}

void CBossTrigger::Release(void)
{
}
