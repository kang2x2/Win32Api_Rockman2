#include "stdafx.h"
#include "Pl_DownTp.h"

#include "Pl_SuccesTp.h"

CPl_DownTp::CPl_DownTp(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_DownTp::~CPl_DownTp()
{
}

void CPl_DownTp::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_DOWNTP);


	if (m_pPlayer->Get_Ground()) {
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"teleport_in.wav", SOUND_EFFECT, 1.0f);
		m_pPlayer->Set_State(new CPl_SuccesTp(m_pPlayer));
		return;
	}
}
