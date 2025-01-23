#include "stdafx.h"
#include "Pl_MC_LWalk.h"

#include "Pl_MC_RWalk.h"
#include "Pl_MC_LIdle.h"
#include "Pl_FC_LWalk.h"
#include "Pl_LWalk_Atk.h"
#include "Pl_MC_LJump.h"
#include "Pl_MC_LSliding.h"

CPl_MC_LWalk::CPl_MC_LWalk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_MC_LWalk::~CPl_MC_LWalk()
{
}

void CPl_MC_LWalk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LM_WALK_CHARGE);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));

	// 오른쪽으로 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_MC_RWalk(m_pPlayer));
		return;
	}

	// 이동 멈춤
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_MC_LIdle(m_pPlayer));
		return;
	}

	// 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fFCTime) {
			m_pPlayer->Set_State(new CPl_FC_LWalk(m_pPlayer));
			return;
		}
	}

	// 미들 차지 발사
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		CPlayerState::m_fChargeTime = 0;
		m_pPlayer->Set_Charge(false);
		CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
		Create_MCBullet_L();
		m_pPlayer->Set_State(new CPl_LWalk_Atk(m_pPlayer));
		return;
	}

	// 이동 중 점프
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_MC_LJump(m_pPlayer));
		return;
	}

	// 이동 중 슬라이딩
	if (CKeyMgr::Get_Instance()->Key_Down('C')) {
		CPlayerState::m_fCurTime_S = GetTickCount() + m_fSlideTime;
		m_pPlayer->Set_State(new CPl_MC_LSliding(m_pPlayer));
		return;
	}
}
