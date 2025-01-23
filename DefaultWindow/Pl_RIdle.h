#pragma once
#include "PlayerState.h"

class CPl_RIdle : public CPlayerState
{
public:
	CPl_RIdle(CPlayer* _pPlayer);
	~CPl_RIdle();

	virtual void Update() override;
};

