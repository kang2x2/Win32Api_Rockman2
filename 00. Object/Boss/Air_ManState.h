#pragma once
#include "ObjMgr.h"
#include "KeyMgr.h"

#include "Air_ManAnimation.h"

#include "Air_Man.h"
#include "Boss_Wind.h"

class CAir_ManState
{
public:
	CAir_ManState();
	virtual~CAir_ManState();
	
	virtual void Update() PURE;

protected:
	void Boss_LSplashWind();
	void Boss_RSplashWind();

protected:
	CAir_Man* m_pAirMan;
	CAir_ManAnimation m_animation;

	// 보스 동작의 쿨타임
	float	m_fCoolTime;
	// 회오리 랜덤 변수
	static int	m_iRandWind;
	// 보스의 공격 횟수.
	static int	m_iAtkCount;
	// 보스의 점프 횟수.
	static int	m_iJumpCount;
};

