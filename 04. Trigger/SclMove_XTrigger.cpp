#include "stdafx.h"
#include "SclMove_XTrigger.h"

#include "ScrollMgr.h"

CSclMove_XTrigger::CSclMove_XTrigger(INFO _myInfo, bool _bRight, int _scrollPos, int _leftRockPos)
{
	if (_bRight) m_sType = "MoveRightX";
	if (!_bRight) m_sType = "MoveLeftX";
	m_iScrollPos = _scrollPos;
	m_tInfo = _myInfo;
	
	m_LeftRockPos = _leftRockPos;
}


CSclMove_XTrigger::~CSclMove_XTrigger()
{
}

void CSclMove_XTrigger::Initialize(void)
{
}

int CSclMove_XTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSclMove_XTrigger::Late_Update(void)
{
}

void CSclMove_XTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
}

void CSclMove_XTrigger::Release(void)
{
}
