#pragma once
#include "PlayerState.h"

class CPl_MC_RSliding : public CPlayerState
{
public:
	CPl_MC_RSliding(CPlayer* _pPlayer);
	~CPl_MC_RSliding();

	virtual void Update() override;
};

