#pragma once
#include "Air_ManState.h"

class CAM_LAir_Jump : public CAir_ManState
{
public:
	CAM_LAir_Jump(CAir_Man* _pAirMan);
	~CAM_LAir_Jump();

	virtual void Update() override;
};

