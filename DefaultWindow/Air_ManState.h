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

	// ���� ������ ��Ÿ��
	float	m_fCoolTime;
	// ȸ���� ���� ����
	static int	m_iRandWind;
	// ������ ���� Ƚ��.
	static int	m_iAtkCount;
	// ������ ���� Ƚ��.
	static int	m_iJumpCount;
};

