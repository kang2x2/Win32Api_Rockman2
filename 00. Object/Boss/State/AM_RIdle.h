#pragma once
#include "Air_ManState.h"

class CAM_RIdle : public CAir_ManState
{
public:
	CAM_RIdle(CAir_Man* _pAirMan);
	~CAM_RIdle();

	virtual void Update() override;
};

