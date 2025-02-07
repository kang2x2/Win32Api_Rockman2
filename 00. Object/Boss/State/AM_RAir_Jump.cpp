#include "stdafx.h"
#include "AM_RAir_Jump.h"

#include "AM_LIdle.h"

CAM_RAir_Jump::CAM_RAir_Jump(CAir_Man* _pAirMan)
{
	m_pAirMan = _pAirMan;
}


CAM_RAir_Jump::~CAM_RAir_Jump()
{
}

void CAM_RAir_Jump::Update()
{
	m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_RAIR_JUMP);

	if (m_pAirMan->Get_Ground()) {
		// 2단 점프
		if (CAir_ManState::m_iJumpCount > 0) {
			CAir_ManState::m_iJumpCount -= 1;
			m_pAirMan->Set_JumpPower(20.f);
		}
		// 목적지 도착 시 방향 바꿔서 다시 패턴 진행
		else {
			CAir_ManState::m_iJumpCount = 2;
			CAir_ManState::m_iAtkCount = 3;
			m_pAirMan->Set_Jump(false);
			m_pAirMan->Set_State(new CAM_LIdle(m_pAirMan));
		}
	}
}
