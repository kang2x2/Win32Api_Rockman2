#pragma once
#include "Air_ManState.h"

class CAM_LAir_Jump : public CAir_ManState
{
public:
	CAM_LAir_Jump(CAir_Man* _pAirMan);
	~CAM_LAir_Jump();

	// CAir_ManState을(를) 통해 상속됨
	virtual void Update() override;
};

