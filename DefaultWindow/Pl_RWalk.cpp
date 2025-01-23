#include "stdafx.h"
#include "Pl_RWalk.h"

#include "Pl_RIdle.h"
#include "Pl_LWalk.h"
#include "Pl_RWalk_Atk.h"
#include "Pl_RJump.h"
#include "Pl_RSliding.h"
#include "Pl_MC_RWalk.h"

CPl_RWalk::CPl_RWalk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_RWalk::~CPl_RWalk()
{
}

void CPl_RWalk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RWALK);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_X(m_pPlayer->Get_Speed());

	// �������� ���� ��ȯ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_LWalk(m_pPlayer));
		return;
	}

	// �̵� ����
	if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_RIdle(m_pPlayer));
		return;
	}

	// �̵� �� ����
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// �⺻ ����
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_R();
			m_pPlayer->Set_State(new CPl_RWalk_Atk(m_pPlayer));
			return;
		}
		
		// ��Ż ���̵�
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(90.f);
			m_pPlayer->Set_State(new CPl_RWalk_Atk(m_pPlayer));
			return;
		}

		// ���� �ǵ�
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(90.f);
			m_pPlayer->Set_State(new CPl_RWalk_Atk(m_pPlayer));
			return;
		}
	}

	// �̵� �� ����
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"land.wav", SOUND_EFFECT, 1.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}

	// �̵� �� ����
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}

	// �̵� �� �����̵�
	if (CKeyMgr::Get_Instance()->Key_Down('C')) {
		CPlayerState::m_fCurTime_S = GetTickCount() + m_fSlideTime;
		m_pPlayer->Set_State(new CPl_RSliding(m_pPlayer));
		return;
	}

	// �������
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fMCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_RWalk(m_pPlayer));
			return;
		}
	}

	// ������� �ʱ�ȭ
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CPlayerState::m_fChargeTime = 0;
	}
}

