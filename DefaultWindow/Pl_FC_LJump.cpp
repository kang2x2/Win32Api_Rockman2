#include "stdafx.h"
#include "Pl_FC_LJump.h"

#include "Pl_FC_RJump.h"
#include "Pl_FC_LIdle.h"
#include "Pl_FC_LWalk.h"
#include "Pl_LJump_Atk.h"

CPl_FC_LJump::CPl_FC_LJump(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_FC_LJump::~CPl_FC_LJump()
{
}

void CPl_FC_LJump::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LF_JUMP_CHARGE);

	// ���� �߿� �������� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));
	}

	// ���� �� ���� ��ȯ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_FC_RJump(m_pPlayer));
		return;
	}

	// nullptr ���� ����
	if (m_pPlayer == nullptr) return;

	// ���� ����� ��
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// �̵� �� ����
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
			m_pPlayer->Set_State(new CPl_FC_LWalk(m_pPlayer));
			return;
		}
		// �׳� ����
		else {
			m_pPlayer->Set_State(new CPl_FC_LIdle(m_pPlayer));
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
			Create_FCBullet_L();
		}
		m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
		return;
	}
}
