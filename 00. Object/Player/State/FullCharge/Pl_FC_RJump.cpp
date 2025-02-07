#include "stdafx.h"
#include "Pl_FC_RJump.h"

#include "Pl_RJump_Atk.h"
#include "Pl_FC_LJump.h"
#include "Pl_FC_RWalk.h"
#include "Pl_FC_RIdle.h"

CPl_FC_RJump::CPl_FC_RJump(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_FC_RJump::~CPl_FC_RJump()
{
}

void CPl_FC_RJump::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RF_JUMP_CHARGE);

	// ���� �߿� ���������� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_X(m_pPlayer->Get_Speed());
	}

	// ���� �� ���� ��ȯ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_FC_LJump(m_pPlayer));
		return;
	}

	if (m_pPlayer == nullptr) return;

	// ���� ����� ��
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// �̵� �� ����
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
			m_pPlayer->Set_State(new CPl_FC_RWalk(m_pPlayer));
			return;
		}
		// �׳� ����
		else {
			m_pPlayer->Set_State(new CPl_FC_RIdle(m_pPlayer));
			return;
		}
	}

	// Ǯ ���� �߻�
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		if (CPlayerState::m_iBltCount == 0) {
			CPlayerState::m_iBltCount += 3;
			CPlayerState::m_fChargeTime = 0;
			m_pPlayer->Set_Charge(false);
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_FCBullet_R();
		}
		m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
		return;
	}
}
