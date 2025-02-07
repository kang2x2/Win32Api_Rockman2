#include "stdafx.h"
#include "AM_LPush_Wind.h"

#include "AM_LIdle.h"

CAM_LPush_Wind::CAM_LPush_Wind(CAir_Man* _pAirMan)
{
	m_pAirMan = _pAirMan;
}


CAM_LPush_Wind::~CAM_LPush_Wind()
{
}

void CAM_LPush_Wind::Update()
{
	// 밀기
	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_EBULLET).empty()) {
		m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_LPUSH_WIND);
		m_fPushPower += 0.15f;
	}

	// 회오리 다 밀고 나면 대기
	else {
		m_fCoolTime += 10.f;
		m_fPushPower = 0;
		m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_LIDLE);
		if (m_fCoolTime >= 500) {
			m_fCoolTime = 0;
			m_pAirMan->Set_State(new CAM_LIdle(m_pAirMan));
			return;
		}
	}
}
