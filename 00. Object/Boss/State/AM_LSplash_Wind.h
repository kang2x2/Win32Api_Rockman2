#pragma once
#include "Air_ManState.h"

class CAM_LSplash_Wind : public CAir_ManState
{
public:
	CAM_LSplash_Wind(CAir_Man* _pAirMan);
	~CAM_LSplash_Wind();

	virtual void Update() override;

private:
	float m_fAtkTime;
};

