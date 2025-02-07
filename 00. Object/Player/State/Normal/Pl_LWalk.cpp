#include "stdafx.h"
#include "Pl_LWalk.h"

#include "Pl_LIdle.h"
#include "Pl_RWalk.h"
#include "Pl_LJump.h"
#include "Pl_LWalk_Atk.h"
#include "Pl_LSliding.h"
#include "Pl_MC_LWalk.h"

CPl_LWalk::CPl_LWalk(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_LWalk::~CPl_LWalk()
{
}

void CPl_LWalk::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LWALK);
	CCollisionMgr::Colision_CloudTileY(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));

	// 오른쪽으로 방향 전환
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_RWalk(m_pPlayer));
		return;
	}

	// 이동 멈춤
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_LIdle(m_pPlayer));
		return;
	}

	// 이동 중 공격
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		// 기본공격
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_L();
			m_pPlayer->Set_State(new CPl_LWalk_Atk(m_pPlayer));
			return;
		}
		// 메탈 블레이드
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(-90.f);
			m_pPlayer->Set_State(new CPl_LWalk_Atk(m_pPlayer));
			return;
		}

		// 리프 실드
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(-90.f);
			m_pPlayer->Set_State(new CPl_LWalk_Atk(m_pPlayer));
			return;
		}
	}

	// 이동 중 점프
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"land.wav", SOUND_EFFECT, 1.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}

	// 이동 중 낙하
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_LJump(m_pPlayer));
		return;
	}

	// 이동 중 슬라이딩
	if (CKeyMgr::Get_Instance()->Key_Down('C')) {
		CPlayerState::m_fCurTime_S = GetTickCount() + m_fSlideTime;
		m_pPlayer->Set_State(new CPl_LSliding(m_pPlayer));
		return;
	}

	// 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fMCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_LWalk(m_pPlayer));
			return;
		}
	}

	// 기모으기 초기화
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CPlayerState::m_fChargeTime = 0;
	}
}
