#include "stdafx.h"
#include "Pl_LAtk.h"

#include "Pl_LIdle.h"
#include "Pl_LWalk_Atk.h"
#include "Pl_RWalk_Atk.h"
#include "Pl_LJump_Atk.h"

CPl_LAtk::CPl_LAtk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_LAtk::~CPl_LAtk()
{
}

void CPl_LAtk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LATK);

	CCollisionMgr::Colision_CloudTile(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));

	// �߰� ����
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// �⺻����
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_L();
		}
		// ��Ż ���̵�
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(-90.f);
			return;
		}
		// ���� �ǵ�
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(-90.f);
			return;
		}
	}

	// ���� �� ���� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_LWalk_Atk(m_pPlayer));
		return;
	}

	// ���� �� ������ �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_RWalk_Atk(m_pPlayer));
		return;
	}


	// ���� �� ����
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
		return;
	}

	// ���� ��� �ð��� ������
	if (CPlayerState::m_fCurTime_A < GetTickCount()) {
		m_fCurTime_A = 0;
		m_pPlayer->Set_State(new CPl_LIdle(m_pPlayer));
		return;
	}
}
