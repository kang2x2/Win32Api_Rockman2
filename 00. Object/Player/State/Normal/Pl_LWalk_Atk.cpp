#include "stdafx.h"
#include "Pl_LWalk_Atk.h"

#include "Pl_LIdle.h"
#include "Pl_LWalk.h"
#include "Pl_LAtk.h"
#include "Pl_RWalk.h"
#include "Pl_RWalk_Atk.h"
#include "Pl_LJump_Atk.h"

CPl_LWalk_Atk::CPl_LWalk_Atk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_LWalk_Atk::~CPl_LWalk_Atk()
{
}

void CPl_LWalk_Atk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LWALK_ATK);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));

	// ���� �� �̵�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));
	}

	// ���� �� ����
	if (CKeyMgr::Get_Instance()->Key_Pressing('X')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"land.wav", SOUND_EFFECT, 1.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
		return;
	}

	// ���� �� ����
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_LJump_Atk(m_pPlayer));
		return;
	}

	// �̵��� ������ ��
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT)) {
		m_pPlayer->Set_X(m_pPlayer->Get_Speed());
		m_pPlayer->Set_State(new CPl_LAtk(m_pPlayer));
		return;
	}

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

	// ���������� ������ Ʋ���� ��
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		// �������̸�
		if (CPlayerState::m_fCurTime_A > GetTickCount()) {
			m_pPlayer->Set_State(new CPl_RWalk_Atk(m_pPlayer));
			return;
		}
		// �ƴϸ�
		else {
			m_pPlayer->Set_State(new CPl_RWalk(m_pPlayer));
			return;
		}
	}

	// ���� ��� �ð��� ������
	if (CPlayerState::m_fCurTime_A < GetTickCount()) {
		m_pPlayer->Set_State(new CPl_LWalk(m_pPlayer));
		return;
	}
}
