#include "stdafx.h"
#include "Pl_LHit.h"

#include "Pl_LIdle.h"

CPl_LHit::CPl_LHit(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_fHitTime = GetTickCount() + 750.f;
}


CPl_LHit::~CPl_LHit()
{
}

void CPl_LHit::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_LHIT);
	CCollisionMgr::Colision_CloudTile(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	CPlayerState::m_fChargeTime = 0;

	m_pPlayer->Set_Charge(false);
	m_pPlayer->Set_Jump(false);
	m_pPlayer->Set_Speed(1.0f);
	m_pPlayer->Set_X(m_pPlayer->Get_Speed());

	if (m_fHitTime < GetTickCount()) {
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_LIdle(m_pPlayer));
		return;
	}
}
