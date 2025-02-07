#include "stdafx.h"
#include "Pl_RSliding.h"

#include "Pl_RIdle.h"
#include "Pl_LSliding.h"
#include "Pl_RJump.h"
#include "Pl_MC_RSliding.h"

CPl_RSliding::CPl_RSliding(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_RSliding::~CPl_RSliding()
{
}

void CPl_RSliding::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RSLIDE);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_Speed(5.0f);

	m_pPlayer->Set_X(m_pPlayer->Get_Speed());

	// 슬라이딩 중 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_LSliding(m_pPlayer));
		return;
	}

	// 슬라이딩 중 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fFCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_RSliding(m_pPlayer));
			return;
		}
	}

	// 슬라이딩 중 기모으기 취소
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CPlayerState::m_fChargeTime = 0;
		return;
	}

	// 슬라이딩 도중에 취소
	if (CKeyMgr::Get_Instance()->Key_Up('C')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_RIdle(m_pPlayer));
		return;
	}

	// 슬라이딩 중 점프
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}

	// 슬라이딩 중 낙하
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}

	// 슬라이딩 시간종료
	if (CPlayerState::m_fCurTime_S < GetTickCount()) {
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_RIdle(m_pPlayer));
		return;
	}
}
