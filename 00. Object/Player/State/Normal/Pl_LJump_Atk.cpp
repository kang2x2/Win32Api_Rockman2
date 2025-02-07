#include "stdafx.h"
#include "Pl_LJump_Atk.h"

#include "Pl_LIdle.h"
#include "Pl_LWalk_Atk.h"
#include "Pl_LAtk.h"
#include "Pl_LJump.h"
#include "Pl_RJump.h"
#include "Pl_RJump_Atk.h"

CPl_LJump_Atk::CPl_LJump_Atk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_LJump_Atk::~CPl_LJump_Atk()
{
}

void CPl_LJump_Atk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LJUMP_ATK);

	// 추가 공격
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// 기본공격
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_L();
		}
		// 메탈 블레이드
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(-90.f);
			return;
		}
		// 리프 실드
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(-90.f);
			return;
		}
	}

	// 점프 중 이동
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));
	}

	// nullptr 에러 방지
	if (m_pPlayer == nullptr) return;

	// 점프 중 오른쪽으로 방향을 틀었을 때
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		// 공격중이면
		if (CPlayerState::m_fCurTime_A > GetTickCount()) {
			m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
			return;
		}
		// 아니면
		else {
			m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
			return;
		}
	}

	// 땅에 닿았을 때
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// 이동 + 공격 중 착지
		if (CKeyMgr::Get_Instance()->Key_Down('Z') && CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
			m_pPlayer->Set_State(new CPl_LWalk_Atk(m_pPlayer));
			return;
		}
		// 제자리 공격 중 착지
		else {
			m_pPlayer->Set_State(new CPl_LAtk(m_pPlayer));
			return;
		}
	}

	// 공격 모션 시간이 끝나면
	if (CPlayerState::m_fCurTime_A < GetTickCount()) {
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}
}
