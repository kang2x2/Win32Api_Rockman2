#include "stdafx.h"
#include "Pl_FC_RSliding.h"

#include "Pl_FC_LSliding.h"
#include "Pl_FC_RIdle.h"
#include "Pl_RSliding.h"
#include "Pl_FC_RJump.h"

CPl_FC_RSliding::CPl_FC_RSliding(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_FC_RSliding::~CPl_FC_RSliding()
{
}

void CPl_FC_RSliding::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RF_SLIDE_CHARGE);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_Speed(5.0f);

	m_pPlayer->Set_X(m_pPlayer->Get_Speed());

	// �����̵� �� ���� ��ȯ
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_FC_LSliding(m_pPlayer));
		return;
	}

	// �����̵� ���߿� ���
	if (CKeyMgr::Get_Instance()->Key_Up('C')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_FC_RIdle(m_pPlayer));
		return;
	}

	// �����̵� �� ������� ���
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		CPlayerState::m_fChargeTime = 0;
		m_pPlayer->Set_Charge(false);
		m_pPlayer->Set_State(new CPl_RSliding(m_pPlayer));
		return;
	}

	// �����̵� �� ����
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_FC_RJump(m_pPlayer));
		return;
	}

	// �����̵� �ð�����
	if (CPlayerState::m_fCurTime_S < GetTickCount()) {
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_FC_RIdle(m_pPlayer));
		return;
	}
}
