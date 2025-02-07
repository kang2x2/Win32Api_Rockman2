#include "stdafx.h"
#include "Pl_FC_LIdle.h"

#include "Pl_LAtk.h"
#include "Pl_FC_RWalk.h"
#include "Pl_FC_LWalk.h"
#include "Pl_FC_LJump.h"
#include "Pl_FC_LSliding.h"

CPl_FC_LIdle::CPl_FC_LIdle(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_FC_LIdle::~CPl_FC_LIdle()
{
}

void CPl_FC_LIdle::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LF_CHARGE);
	CCollisionMgr::Colision_CloudTile(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));

	// 풀 차지 발사
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_CHARGE);
		if (CPlayerState::m_iBltCount == 0) {
			CPlayerState::m_iBltCount += 3;
			CPlayerState::m_fChargeTime = 0;
			m_pPlayer->Set_Charge(false);
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_FCBullet_L();
		}
		m_pPlayer->Set_State(new CPl_LAtk(m_pPlayer));
		return;
	}

	// 왼쪽으로 걷기
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_FC_LWalk(m_pPlayer));
		return;
	}

	// 오른쪽으로 걷기
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_FC_RWalk(m_pPlayer));
		return;
	}

	// 제자리에서 왼쪽으로 점프
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_FC_LJump(m_pPlayer));
		return;
	}

	// 제자리에서 왼쪽으로 슬라이딩
	if (CKeyMgr::Get_Instance()->Key_Down('C')) {
		CPlayerState::m_fCurTime_S = GetTickCount() + m_fSlideTime;
		m_pPlayer->Set_State(new CPl_FC_LSliding(m_pPlayer));
		return;
	}

}
