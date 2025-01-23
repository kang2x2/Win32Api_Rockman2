#include "stdafx.h"
#include "GoblinTrigger.h"

#include "ScrollMgr.h"

CGoblinTrigger::CGoblinTrigger(INFO _myInfo, INFO _targetInfo)
{
	m_sType = "GoblinTrigger";
	m_tInfo = _myInfo;
	m_tTargetInfo = _targetInfo;
}


CGoblinTrigger::~CGoblinTrigger()
{
}

void CGoblinTrigger::Initialize(void)
{
}

int CGoblinTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();
	
	return OBJ_NOEVENT;
}

void CGoblinTrigger::Late_Update(void)
{
}

void CGoblinTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tDrawRect.left + fScrollX,
	//	m_tDrawRect.top + fScrollY,
	//	m_tDrawRect.right + fScrollX,
	//	m_tDrawRect.bottom + fScrollY);
}

void CGoblinTrigger::Release(void)
{
}
