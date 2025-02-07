#include "stdafx.h"
#include "Pl_MC_LSliding.h"

#include "Pl_FC_LSliding.h"
#include "Pl_LSliding.h"
#include "Pl_MC_RSliding.h"
#include "Pl_MC_LIdle.h"
#include "Pl_MC_LJump.h"

CPl_MC_LSliding::CPl_MC_LSliding(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_MC_LSliding::~CPl_MC_LSliding()
{
}

void CPl_MC_LSliding::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LM_SLIDE_CHARGE);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_Speed(5.0f);

	m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));

	// �����̵� �� �������
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fFCTime) {
			m_pPlayer->Set_State(new CPl_FC_LSliding(m_pPlayer));
			return;
		}
	}

	// �����̵� �� ������� ���
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		CPlayerState::m_fChargeTime = 0;
		m_pPlayer->Set_Charge(false);
		m_pPlayer->Set_State(new CPl_LSliding(m_pPlayer));
		return;
	}

	// �����̵� �� ���� ��ȯ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_MC_RSliding(m_pPlayer));
		return;
	}

	// �����̵� ���߿� ���
	if (CKeyMgr::Get_Instance()->Key_Up('C')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_MC_LIdle(m_pPlayer));
		return;
	}

	// �����̵� �� ����
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_MC_LJump(m_pPlayer));
		return;
	}

	// �����̵� �ð�����
	if (CPlayerState::m_fCurTime_S < GetTickCount()) {
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_MC_LIdle(m_pPlayer));
		return;
	}
}
