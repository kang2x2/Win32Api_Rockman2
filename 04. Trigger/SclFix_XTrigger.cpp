#include "stdafx.h"
#include "SclFix_XTrigger.h"

#include "ScrollMgr.h"

CSclFix_XTrigger::CSclFix_XTrigger(INFO _myInfo, bool _bRight, int _scrollPos)
{
	if (_bRight) m_sType = "FixRightX";
	if (!_bRight) m_sType = "FixLeftX";
	m_iScrollPos = _scrollPos;
	m_tInfo = _myInfo;
}


CSclFix_XTrigger::~CSclFix_XTrigger()
{
}

void CSclFix_XTrigger::Initialize(void)
{
}

int CSclFix_XTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSclFix_XTrigger::Late_Update(void)
{
}

void CSclFix_XTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
}

void CSclFix_XTrigger::Release(void)
{
}
