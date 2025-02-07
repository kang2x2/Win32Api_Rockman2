#include "stdafx.h"
#include "Pl_SuccesTp.h"

#include "Pl_RIdle.h"

CPl_SuccesTp::CPl_SuccesTp(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_iChangeTime = GetTickCount() + 100;
}


CPl_SuccesTp::~CPl_SuccesTp()
{
}

void CPl_SuccesTp::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_SUCCESTP);

	if (m_iChangeTime < GetTickCount()) {
		m_pPlayer->Set_Tp(true);
		m_pPlayer->Set_State(new CPl_RIdle(m_pPlayer));
		return;
	}
}
