#include "stdafx.h"
#include "Pl_RJump.h"

#include "Pl_RIdle.h"
#include "Pl_RAtk.h"
#include "Pl_RWalk.h"
#include "Pl_RWalk_Atk.h"
#include "Pl_RJump_Atk.h"
#include "Pl_LJump.h"
#include "Pl_MC_RJump.h"

CPl_RJump::CPl_RJump(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_RJump::~CPl_RJump()
{
}

void CPl_RJump::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RJUMP);

	// ���� �߿� ���������� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_X(m_pPlayer->Get_Speed());
	}

	// ���� �� ���� ��ȯ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}

	// ���� �� ����
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// �⺻ ����
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_R();
			m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
			return;
		}
		// ��Ż ���̵�
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(90.f);
			m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
			return;
		}
		// ���� �ǵ�
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(90.f);
			m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
			return;
		}
	}

	// �������
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fMCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_RJump(m_pPlayer));
			return;
		}
	}

	// ������� �ʱ�ȭ
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CPlayerState::m_fChargeTime = 0;
	}

	// nullptr ���� ����
	if (m_pPlayer == nullptr) return;

	// ���� ����� ��
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// �̵� �� ����
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
			m_pPlayer->Set_State(new CPl_RWalk(m_pPlayer));
			return;
		}
		// �׳� ����
		else {
			m_pPlayer->Set_State(new CPl_RIdle(m_pPlayer));
			return;
		}
	}
}

