#include "stdafx.h"
#include "Pl_LIdle.h"

#include "Pl_RWalk.h"
#include "Pl_LWalk.h"
#include "Pl_LAtk.h"
#include "Pl_LJump.h"
#include "Pl_LSliding.h"
#include "Pl_MC_LIdle.h"

#include "RushCoil.h"

CPl_LIdle::CPl_LIdle(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_LIdle::~CPl_LIdle()
{
}

void CPl_LIdle::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LIDLE);

	CCollisionMgr::Colision_CloudTile(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));

	// �������� �ȱ�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_LWalk(m_pPlayer));
		return;
	}

	// ���������� �ȱ�
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_RWalk(m_pPlayer));
		return;
	}

	// ���ڸ����� �������� ����
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// �⺻����
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_L();
			m_pPlayer->Set_State(new CPl_LAtk(m_pPlayer));
			return;
		}
		// ��Ż ���̵�
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(-90.f);
			m_pPlayer->Set_State(new CPl_LAtk(m_pPlayer));
			return;
		}
		// ���� �ǵ�
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(-90.f);
			m_pPlayer->Set_State(new CPl_LAtk(m_pPlayer));
			return;
		}
		if (m_pPlayer->Get_WeaponType() == WEAPON_RUSH) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			CObjMgr::Get_Instance()->Add_Object(OBJ_PBULLET, new CRushCoil({(m_pPlayer->Get_Info().fX - 100), (m_pPlayer->Get_Info().fY - 500),60, 52}, m_pPlayer->Get_Info().fY + 6.f));
			return;
		}
	}

	// �������
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fMCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_LIdle(m_pPlayer));
			return;
		}
	}

	// ������� �ʱ�ȭ
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CPlayerState::m_fChargeTime = 0;
	}

	// ���ڸ����� ���������� ����
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"land.wav", SOUND_EFFECT, 1.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}

	// ����
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}

	// ���ڸ����� ���������� �����̵�
	if (CKeyMgr::Get_Instance()->Key_Down('C')) {
		CPlayerState::m_fCurTime_S = GetTickCount() + m_fSlideTime;
		m_pPlayer->Set_State(new CPl_LSliding(m_pPlayer));
		return;
	}
}
