#include "stdafx.h"
#include "Pl_MC_LJump.h"

#include "Pl_MC_RJump.h"
#include "Pl_FC_LJump.h"
#include "Pl_LJump_Atk.h"
#include "Pl_MC_LWalk.h"
#include "Pl_MC_LIdle.h"

CPl_MC_LJump::CPl_MC_LJump(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_MC_LJump::~CPl_MC_LJump()
{
}

void CPl_MC_LJump::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LM_JUMP_CHARGE);

	// 점프 중에 왼쪽으로 이동
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));
	}

	// 점프 중 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_MC_RJump(m_pPlayer));
		return;
	}

	// nullptr 에러 방지
	if (m_pPlayer == nullptr) return;

	// 땅에 닿았을 때
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// 이동 중 착지
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
			m_pPlayer->Set_State(new CPl_MC_LWalk(m_pPlayer));
			return;
		}
		// 그냥 착지
		else {
			m_pPlayer->Set_State(new CPl_MC_LIdle(m_pPlayer));
			return;
		}
	}

	// 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fFCTime) {
			m_pPlayer->Set_State(new CPl_FC_LJump(m_pPlayer));
			return;
		}
	}

	// 미들 차지 발사
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		CPlayerState::m_fChargeTime = 0;
		m_pPlayer->Set_Charge(false);
		CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
		Create_MCBullet_L();
		m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
		return;
	}
}
