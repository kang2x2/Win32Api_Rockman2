#include "stdafx.h"
#include "Pl_MC_RJump.h"

#include "Pl_MC_LJump.h"
#include "Pl_MC_RWalk.h"
#include "Pl_MC_RIdle.h"
#include "Pl_RJump_Atk.h"
#include "Pl_FC_RJump.h"

CPl_MC_RJump::CPl_MC_RJump(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_MC_RJump::~CPl_MC_RJump()
{
}

void CPl_MC_RJump::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RM_JUMP_CHARGE);

	// 점프 중에 오른쪽으로 이동
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_X(m_pPlayer->Get_Speed());
	}

	// 점프 중 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_MC_LJump(m_pPlayer));
		return;
	}

	if (m_pPlayer == nullptr) return;

	// 땅에 닿았을 때
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// 이동 중 착지
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
			m_pPlayer->Set_State(new CPl_MC_RWalk(m_pPlayer));
			return;
		}
		// 그냥 착지
		else {
			m_pPlayer->Set_State(new CPl_MC_RIdle(m_pPlayer));
			return;
		}
	}

	// 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fFCTime) {
			m_pPlayer->Set_State(new CPl_FC_RJump(m_pPlayer));
			return;
		}
	}

	// 미들 차지 발사
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		CPlayerState::m_fChargeTime = 0;
		m_pPlayer->Set_Charge(false);
		CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
		Create_MCBullet_R();
		m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
		return;
	}


}
