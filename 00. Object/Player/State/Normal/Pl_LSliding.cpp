#include "stdafx.h"
#include "Pl_LSliding.h"

#include "Pl_LIdle.h"
#include "Pl_RSliding.h"
#include "Pl_LJump.h"
#include "Pl_MC_LSliding.h"

CPl_LSliding::CPl_LSliding(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_LSliding::~CPl_LSliding()
{
}

void CPl_LSliding::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LSLIDE);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_Speed(6.0f);

	m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));

	// 슬라이딩 중 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_RSliding(m_pPlayer));
		return;
	}

	// 슬라이딩 중 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fFCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_LSliding(m_pPlayer));
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
		m_pPlayer->Set_State(new CPl_LIdle(m_pPlayer));
		return;
	}

	// 슬라이딩 중 점프
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CPlayerState::m_fCurTime_S = 0;
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}

	// 슬라이딩 중 낙하
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}

	// 슬라이딩 시간종료
	if (CPlayerState::m_fCurTime_S < GetTickCount()) {
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_LIdle(m_pPlayer)); 
		return;
	}
}
