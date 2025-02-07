#pragma once
#include "Air_ManState.h"

class CAM_RPush_Wind : public CAir_ManState
{
public:
	CAM_RPush_Wind(CAir_Man* _pAirMan);
	~CAM_RPush_Wind();

	virtual void Update() override;
};

