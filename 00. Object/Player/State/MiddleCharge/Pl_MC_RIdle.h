#pragma once
#include "PlayerState.h"

class CPl_MC_RIdle : public CPlayerState
{
public:
	CPl_MC_RIdle(CPlayer* _pPlayer);
	~CPl_MC_RIdle();

	virtual void Update() override;
};

