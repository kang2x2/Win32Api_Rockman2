#pragma once
#include "Air_ManState.h"

class CAM_Opening : public CAir_ManState
{
public:
	CAM_Opening(CAir_Man* _pAirMan);
	~CAM_Opening();

	// CAir_ManState을(를) 통해 상속됨
	virtual void Update() override;

private:
	float	m_fOpeningTime;
};

