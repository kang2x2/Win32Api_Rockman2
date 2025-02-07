#include "stdafx.h"
#include "Pl_UpTp.h"


CPl_UpTp::CPl_UpTp(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


CPl_UpTp::~CPl_UpTp()
{
}

void CPl_UpTp::Update()
{
	m_animation.Player_Animation(m_pPlayer, ST_UPTP);	
}
