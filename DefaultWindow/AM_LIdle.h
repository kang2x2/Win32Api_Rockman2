#pragma once
#include "Air_ManState.h"

class CAM_LIdle : public CAir_ManState
{
public:
	CAM_LIdle(CAir_Man* _pAirMan);
	~CAM_LIdle();

	// CAir_ManState을(를) 통해 상속됨
	virtual void Update() override;

private:
	float	m_IntorHpTime;
};

