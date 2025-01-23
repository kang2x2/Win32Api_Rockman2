#include "stdafx.h"
#include "AM_RIdle.h"

#include "AM_RSplash_Wind.h"
#include "AM_RAir_Jump.h"

CAM_RIdle::CAM_RIdle(CAir_Man* _pAirMan)
{
	m_pAirMan = _pAirMan;
}


CAM_RIdle::~CAM_RIdle()
{
}

void CAM_RIdle::Update()
{
	m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_RIDLE);

	// 공격 횟수가 남아있으면
	if (CAir_ManState::m_iAtkCount > 0) {
		m_pAirMan->Set_State(new CAM_RSplash_Wind(m_pAirMan));
	}
	// 공격 횟수 모두 소진시
	else {
		m_pAirMan->Set_Jump(true);
		m_pAirMan->Set_JumpPower(11.f);
		CAir_ManState::m_iJumpCount -= 1;
		m_pAirMan->Set_State(new CAM_RAir_Jump(m_pAirMan));
	}
}
