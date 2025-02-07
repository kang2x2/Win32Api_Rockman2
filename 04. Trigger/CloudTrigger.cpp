#include "stdafx.h"
#include "CloudTrigger.h"

#include "ScrollMgr.h"

CCloudTrigger::CCloudTrigger(INFO _myInfo, INFO _targetInfo)
{
	m_sType = "CloudTrigger";
	m_tInfo = _myInfo;
	m_tTargetInfo = _targetInfo;
}


CCloudTrigger::~CCloudTrigger()
{
}

void CCloudTrigger::Initialize(void)
{
}

int CCloudTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CCloudTrigger::Late_Update(void)
{
}

void CCloudTrigger::Render(HDC hDC)
{
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
}

void CCloudTrigger::Release(void)
{
}
