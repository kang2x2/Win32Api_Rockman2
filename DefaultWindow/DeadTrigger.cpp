#include "stdafx.h"
#include "DeadTrigger.h"


CDeadTrigger::CDeadTrigger(INFO _myInfo)
{
	m_sType = "DeadTrigger";
	m_tInfo = _myInfo;
}


CDeadTrigger::~CDeadTrigger()
{
}

void CDeadTrigger::Initialize(void)
{
}

int CDeadTrigger::Update(void)
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CDeadTrigger::Late_Update(void)
{
}

void CDeadTrigger::Render(HDC hDC)
{
}

void CDeadTrigger::Release(void)
{
}
