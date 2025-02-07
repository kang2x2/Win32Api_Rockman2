#include "stdafx.h"
#include "AM_RSplash_Wind.h"

#include "AM_RPush_Wind.h"

CAM_RSplash_Wind::CAM_RSplash_Wind(CAir_Man* _pAirMan)
{
	m_pAirMan = _pAirMan;
	m_fAtkTime = GetTickCount() + 1500.f;
}


CAM_RSplash_Wind::~CAM_RSplash_Wind()
{
}

void CAM_RSplash_Wind::Update()
{
	m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_RSPLASH_WIND);
	// È¸¿À¸® Èð»Ñ¸®±â
	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_EBULLET).empty())
	{
		CAir_ManState::m_iAtkCount -= 1;
		CAir_ManState::m_iRandWind = rand() % 3;
		Boss_RSplashWind();
	}

	if (m_fAtkTime < GetTickCount()) {
		m_pAirMan->Set_State(new CAM_RPush_Wind(m_pAirMan));
		return;
	}
}
