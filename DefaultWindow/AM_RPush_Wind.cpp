#include "stdafx.h"
#include "AM_RPush_Wind.h"

#include "AM_RIdle.h"

extern float m_fPushPower;

CAM_RPush_Wind::CAM_RPush_Wind(CAir_Man* _pAirMan)
{
	m_pAirMan = _pAirMan;
}


CAM_RPush_Wind::~CAM_RPush_Wind()
{
}

void CAM_RPush_Wind::Update()
{
	// 밀기
	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_EBULLET).empty()) {
		m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_RPUSH_WIND);
		m_fPushPower -= 0.15f;
	}

	// 회오리 다 밀고 나면 대기
	else {
		m_fCoolTime += 10.f;
		m_fPushPower = 0;
		m_animation.Air_Man_Animation(m_pAirMan, BOSS_ST_RIDLE);
		if (m_fCoolTime >= 500) {
			m_fCoolTime = 0;
			m_pAirMan->Set_State(new CAM_RIdle(m_pAirMan));
			return;
		}
	}
}
