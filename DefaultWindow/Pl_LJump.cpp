#include "stdafx.h"
#include "Pl_LJump.h"

#include "Pl_LIdle.h"
#include "Pl_LAtk.h"
#include "Pl_LWalk.h"
#include "Pl_LWalk_Atk.h"
#include "Pl_LJump_Atk.h"
#include "Pl_RJump.h"
#include "Pl_MC_LJump.h"

CPl_LJump::CPl_LJump(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_LJump::~CPl_LJump()
{
}

void CPl_LJump::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LJUMP);
	
	// 점프 중에 왼쪽으로 이동
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));
	}

	// 점프 중 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}

	// 점프 중 공격
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// 기본공격
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_L();
			m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
			return;
		}
		// 메탈 블레이드
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(-90.f);
			m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
			return;
		}
		// 리프 실드
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(-90.f);
			m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
			return;
		}
	}

	// 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fMCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_LJump(m_pPlayer));
			return;
		}
	}

	// 기모으기 초기화
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CPlayerState::m_fChargeTime = 0;
	}

	// nullptr 에러 방지
	if (m_pPlayer == nullptr) return;

	// 땅에 닿았을 때
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);	
		// 이동 중 착지
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
			m_pPlayer->Set_State(new CPl_LWalk(m_pPlayer));
			return;
		}
		// 그냥 착지
		else {
			m_pPlayer->Set_State(new CPl_LIdle(m_pPlayer));
			return;
		}
	}
}

