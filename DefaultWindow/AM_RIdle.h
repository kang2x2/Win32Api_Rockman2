#pragma once
#include "Air_ManState.h"

class CAM_RIdle : public CAir_ManState
{
public:
	CAM_RIdle(CAir_Man* _pAirMan);
	~CAM_RIdle();

	// CAir_ManState��(��) ���� ��ӵ�
	virtual void Update() override;
};

