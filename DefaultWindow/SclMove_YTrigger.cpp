#include "stdafx.h"
#include "SclMove_YTrigger.h"

#include "ScrollMgr.h"

CSclMove_YTrigger::CSclMove_YTrigger(INFO _myInfo)
{
	m_sType = "MoveY";
	m_tInfo = _myInfo;
}


CSclMove_YTrigger::~CSclMove_YTrigger()
{
}

void CSclMove_YTrigger::Initialize(void)
{
}

int CSclMove_YTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSclMove_YTrigger::Late_Update(void)
{
}

void CSclMove_YTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tDrawRect.left + fScrollX,
	//	m_tDrawRect.top + fScrollY,
	//	m_tDrawRect.right + fScrollX,
	//	m_tDrawRect.bottom + fScrollY);
}

void CSclMove_YTrigger::Release(void)
{
}
