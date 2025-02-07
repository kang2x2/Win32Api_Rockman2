#include "stdafx.h"
#include "Pl_FC_LSliding.h"

#include "Pl_FC_RSliding.h"
#include "Pl_FC_LIdle.h"
#include "Pl_LSliding.h"
#include "Pl_FC_LJump.h"

CPl_FC_LSliding::CPl_FC_LSliding(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_FC_LSliding::~CPl_FC_LSliding()
{
}

void CPl_FC_LSliding::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LF_SLIDE_CHARGE);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_Speed(5.0f);

	m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));

	// 슬라이딩 중 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_FC_RSliding(m_pPlayer));
		return;
	}

	// 슬라이딩 도중에 취소
	if (CKeyMgr::Get_Instance()->Key_Up('C')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_FC_LIdle(m_pPlayer));
		return;
	}

	// 슬라이딩 중 기모으기 취소
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		CPlayerState::m_fChargeTime = 0;
		m_pPlayer->Set_Charge(false);
		m_pPlayer->Set_State(new CPl_LSliding(m_pPlayer));
		return;
	}

	// 슬라이딩 중 점프
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_FC_LJump(m_pPlayer));
		return;
	}

	// 슬라이딩 시간종료
	if (CPlayerState::m_fCurTime_S < GetTickCount()) {
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_FC_LIdle(m_pPlayer));
		return;
	}
}
