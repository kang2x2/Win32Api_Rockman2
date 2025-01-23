#include "stdafx.h"
#include "Pl_RJump_Atk.h"

#include "Pl_RIdle.h"
#include "Pl_RWalk_Atk.h"
#include "Pl_RAtk.h"
#include "Pl_RJump.h"
#include "Pl_LJump.h"
#include "Pl_LJump_Atk.h"

CPl_RJump_Atk::CPl_RJump_Atk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_RJump_Atk::~CPl_RJump_Atk()
{
}

void CPl_RJump_Atk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RJUMP_ATK);

	// �߰� ����
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// �⺻ ����
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_R();
		}
		// ��Ż ���̵�
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(90.f);
			return;
		}
		// ���� �ǵ�
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(90.f);
			return;
		}
	}

	// ���� �� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_X(m_pPlayer->Get_Speed());
	}

	// nullptr ���� ����
	if (m_pPlayer == nullptr) return;

	// ���� �� �������� ������ Ʋ���� ��
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		// �������̸�
		if (CPlayerState::m_fCurTime_A > GetTickCount()) {
			m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
			return;
		}
		// �ƴϸ�
		else {
			m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
			return;
		}
	}

	// ���� ����� ��
	if (m_pPlayer->Get_Ground()) {
		m_pPlayer->Set_Jump(false);
		// �̵� + ���� �� ����
		if (CKeyMgr::Get_Instance()->Key_Down('Z') && CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
			m_pPlayer->Set_State(new CPl_RWalk_Atk(m_pPlayer));
			return;
		}
		// ���ڸ� ���� �� ����
		else {
			m_pPlayer->Set_State(new CPl_RAtk(m_pPlayer));
			return;
		}
	}

	// ���� ��� �ð��� ������
	if (CPlayerState::m_fCurTime_A < GetTickCount()) {
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}
}
