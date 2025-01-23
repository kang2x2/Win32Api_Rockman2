#include "stdafx.h"
#include "Pl_RHit.h"

#include "Pl_RIdle.h"

CPl_RHit::CPl_RHit(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_fHitTime = GetTickCount() + 750.f;
}


CPl_RHit::~CPl_RHit()
{
}

void CPl_RHit::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_RHIT);
	CCollisionMgr::Colision_CloudTile(m_pPlayer, CObjMgr::Get_Instance()->Get_ObjList(OBJ_TILE));
	CPlayerState::m_fChargeTime = 0;

	m_pPlayer->Set_Charge(false);
	m_pPlayer->Set_Jump(false);
	m_pPlayer->Set_Speed(1.0f);
	m_pPlayer->Set_X(-(m_pPlayer->Get_Speed()));

	if (m_fHitTime < GetTickCount()) {
		m_pPlayer->Set_Speed(3.0f);
		m_pPlayer->Set_State(new CPl_RIdle(m_pPlayer));
		return;
	}


}
