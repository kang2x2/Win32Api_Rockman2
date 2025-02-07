#pragma once
#include "Air_ManState.h"

class CAM_LIdle : public CAir_ManState
{
public:
	CAM_LIdle(CAir_Man* _pAirMan);
	~CAM_LIdle();

	virtual void Update() override;

private:
	float	m_IntorHpTime;
};

