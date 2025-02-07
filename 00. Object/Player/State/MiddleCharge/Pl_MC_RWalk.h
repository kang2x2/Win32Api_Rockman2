#pragma once
#include "PlayerState.h"

class CPl_MC_RWalk : public CPlayerState
{
public:
	CPl_MC_RWalk(CPlayer* _pPlayer);
	~CPl_MC_RWalk();

	virtual void Update() override;
};

