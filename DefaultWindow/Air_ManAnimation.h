#pragma once
#include "Air_Man.h"

class CAir_ManAnimation
{
public:
	CAir_ManAnimation();
	~CAir_ManAnimation();

	void Air_Man_Animation(CAir_Man* _pAirman, BOSS_STATE _eState);

private:
	BOSS_STATE				m_ePreState;
};

