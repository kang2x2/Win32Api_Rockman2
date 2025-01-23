#include "stdafx.h"
#include "Pl_RWalk_Atk.h"

#include "Pl_RIdle.h"
#include "Pl_RWalk.h"
#include "Pl_RAtk.h"
#include "Pl_LWalk.h"
#include "Pl_LWalk_Atk.h"
#include "Pl_RJump_Atk.h"

CPl_RWalk_Atk::CPl_RWalk_Atk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_RWalk_Atk::~CPl_RWalk_Atk()
{
}

void CPl_RWalk_Atk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RWALK_ATK);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));

	// 공격 중 이동
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_X(m_pPlayer->Get_Speed());
	}

	// 공격 중 점프
	if (CKeyMgr::Get_Instance()->Key_Pressing('X')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"land.wav", SOUND_EFFECT, 1.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
		return;
	}

	// 공격 중 낙하
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_RJump_Atk(m_pPlayer));
		return;
	}

	// 이동을 멈췄을 때
	if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT)) {
		m_pPlayer->Set_X(m_pPlayer->Get_Speed());
		m_pPlayer->Set_State(new CPl_RAtk(m_pPlayer));
		return;
	}

	// 추가 공격
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// 기본 공격
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_R();
		}
		// 메탈 블레이드
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(90.f);
			return;
		}
		// 리프 실드
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(90.f);
			return;
		}
	}

	// 왼쪽으로 방향을 틀었을 때
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		// 공격중이면
		if (CPlayerState::m_fCurTime_A > GetTickCount()) {
			m_pPlayer->Set_State(new CPl_LWalk_Atk(m_pPlayer));
			return;
		}
		// 아니면
		else {
			m_pPlayer->Set_State(new CPl_LWalk(m_pPlayer));
			return;
		}
	}

	// 공격 모션 시간이 끝나면
	if (CPlayerState::m_fCurTime_A < GetTickCount()) {
		m_pPlayer->Set_State(new CPl_RWalk(m_pPlayer));
		return;
	}
}

