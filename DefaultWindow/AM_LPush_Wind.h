#pragma once
#include "Air_ManState.h"

class CAM_LPush_Wind : public CAir_ManState
{
public:
	CAM_LPush_Wind(CAir_Man* _pAirMan);
	~CAM_LPush_Wind();

	// CAir_ManState을(를) 통해 상속됨
	virtual void Update() override;
};

