#pragma once
#include "PlayerState.h"

class CPl_MC_LSliding : public CPlayerState
{
public:
	CPl_MC_LSliding(CPlayer* _pPlayer);
	~CPl_MC_LSliding();

	virtual void Update() override;
};

