#pragma once
#include "Air_ManState.h"

class CAM_RAir_Jump : public CAir_ManState
{
public:
	CAM_RAir_Jump(CAir_Man* _pAirMan);
	~CAM_RAir_Jump();

	virtual void Update() override;
};

