#include "stdafx.h"
#include "PipiTrigger.h"

#include "ScrollMgr.h"

CPipiTrigger::CPipiTrigger(INFO _myInfo, INFO _targetInfo)
{
	m_sType = "PipiTrigger";
	m_tInfo = _myInfo;
	m_tTargetInfo = _targetInfo;
}


CPipiTrigger::~CPipiTrigger()
{
}

void CPipiTrigger::Initialize(void)
{
}

int CPipiTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPipiTrigger::Late_Update(void)
{
}

void CPipiTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
}

void CPipiTrigger::Release(void)
{
}
