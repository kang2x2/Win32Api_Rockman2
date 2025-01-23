#include "stdafx.h"
#include "AM_LIdle.h"

#include "SoundMgr.h"

#include "AM_LSplash_Wind.h"
#include "AM_LAir_Jump.h"

CAM_LIdle::CAM_LIdle(CAir_Man* _pAirMan)
{
	m_pAirMan = _pAirMan;
	m_IntorHpTime = GetTickCount() + 100.f;
}


CAM_LIdle::~CAM_LIdle()
{
}

void CAM_LIdle::Update()
{
	m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_LIDLE);
	

	// hp 조금씩 증가
	if (m_pAirMan->Get_Opening() && m_pAirMan->Get_Hp() < 20) {
		if (m_IntorHpTime < GetTickCount()) {
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"hpRepill.wav", SOUND_EFFECT, 1.0f);
			m_IntorHpTime = GetTickCount() + 50.f;
			m_pAirMan->Intro_Hp(); // hp 1씩 증가
		}
	}
	// hp바가 다 차면 오프닝(인트로) 종료. 패턴으로 전환
	if (m_pAirMan->Get_Hp() == 20) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		if (GetTickCount() % 400 == 0) {
			m_pAirMan->Set_Opening();
		}
	}

	if (!m_pAirMan->Get_Opening()) {
		// 공격 횟수가 남아있으면
		if (CAir_ManState::m_iAtkCount > 0) {
			m_pAirMan->Set_State(new CAM_LSplash_Wind(m_pAirMan));
		}
		// 공격 횟수 모두 소진시
		else {
			m_pAirMan->Set_Jump(true);
			m_pAirMan->Set_JumpPower(11.f);
			CAir_ManState::m_iJumpCount -= 1;
			m_pAirMan->Set_State(new CAM_LAir_Jump(m_pAirMan));
		}
	}

}
