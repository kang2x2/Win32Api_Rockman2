#include "stdafx.h"
#include "AM_Opening.h"

#include "AM_LIdle.h"

CAM_Opening::CAM_Opening(CAir_Man* _pAirMan)
{
	m_pAirMan = _pAirMan;
	m_fOpeningTime = GetTickCount() + 1000.f;
}


CAM_Opening::~CAM_Opening()
{
}

void CAM_Opening::Update()
{
	m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_OPIENING);

	// ������(��Ʈ��)�ð� ������ Idle�� ��ȯ
	if (m_fOpeningTime < GetTickCount()) {
		m_pAirMan->Set_State(new CAM_LIdle(m_pAirMan));
		return;
	}

}
