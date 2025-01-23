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

	// ���� �߿� �������� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));
	}

	// ���� �� ���� ��ȯ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_MC_RJump(m_pPlayer));
		return;
	}

	// nullptr ���� ����
	if (m_pPlayer == nullptr) return;

	// ���� ����� ��
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// �̵� �� ����
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
			m_pPlayer->Set_State(new CPl_MC_LWalk(m_pPlayer));
			return;
		}
		// �׳� ����
		else {
			m_pPlayer->Set_State(new CPl_MC_LIdle(m_pPlayer));
			return;
		}
	}

	// �������
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fFCTime) {
			m_pPlayer->Set_State(new CPl_FC_LJump(m_pPlayer));
			return;
		}
	}

	// �̵� ���� �߻�
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
