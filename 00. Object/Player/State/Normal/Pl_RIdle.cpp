#include "stdafx.h"
#include "Pl_RIdle.h"

#include "Pl_RWalk.h"
#include "Pl_LWalk.h"
#include "Pl_RAtk.h"
#include "Pl_RJump.h"
#include "Pl_RSliding.h"
#include "Pl_MC_RIdle.h"

#include "RushCoil.h"

CPl_RIdle::CPl_RIdle(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_RIdle::~CPl_RIdle()
{
}

void CPl_RIdle::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RIDLE);

	CCollisionMgr::Colision_CloudTile(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));

	// 오른쪽으로 걷기
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) {
		m_pPlayer->Set_State(new CPl_RWalk(m_pPlayer));
		return;
	}

	// 왼쪽으로 걷기
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) {
		m_pPlayer->Set_State(new CPl_LWalk(m_pPlayer));
		return;
	}

	// 제자리에서 오른쪽으로 공격
	if (CPlayerState::m_iBltCount < 3 && CKeyMgr::Get_Instance()->Key_Down('Z')) {
		if (m_pPlayer->Get_WeaponType() == WEAPON_NORMAL) {
			CPlayerState::m_iBltCount += 1;
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_NBullet_R();
			m_pPlayer->Set_State(new CPl_RAtk(m_pPlayer));
			return;
		}
		// 메탈 블레이드
		if (m_pPlayer->Get_WeaponType() == WEAPON_MB) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_MetalBlade(90.f);
			m_pPlayer->Set_State(new CPl_RAtk(m_pPlayer));
			return;
		}
		// 리프 실드
		if (m_pPlayer->Get_WeaponType() == WEAPON_RS) {
			CPlayerState::m_fCurTime_A = GetTickCount() + m_fAtkTime;
			Create_ReefShield(90.f);
			m_pPlayer->Set_State(new CPl_RAtk(m_pPlayer));
			return;
		}
	}


	// 기모으기
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z')) {
		CPlayerState::m_fChargeTime += 1.0f;
		if (CPlayerState::m_fChargeTime > m_fMCTime) {
			m_pPlayer->Set_Charge(true);
			m_pPlayer->Set_State(new CPl_MC_RIdle(m_pPlayer));
			return;
		}
	}

	// 기모으기 초기화
	if (CKeyMgr::Get_Instance()->Key_Up('Z')) {
		CPlayerState::m_fChargeTime = 0;
	}

	// 제자리에서 오른쪽으로 점프
	if (CKeyMgr::Get_Instance()->Key_Down('X')) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"land.wav", SOUND_EFFECT, 1.0f);
		m_pPlayer->Set_Jump(true);
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}

	// 낙하
	if (m_pPlayer->Get_DropTime() > 6.0f) {
		m_pPlayer->Set_State(new CPl_RJump(m_pPlayer));
		return;
	}

	// 제자리에서 오른쪽으로 슬라이딩
	if (CKeyMgr::Get_Instance()->Key_Down('C')) {
		CPlayerState::m_fCurTime_S = GetTickCount() + m_fSlideTime;
		m_pPlayer->Set_State(new CPl_RSliding(m_pPlayer));
		return;
	}
}







