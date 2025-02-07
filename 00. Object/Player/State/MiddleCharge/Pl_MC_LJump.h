#pragma once
#include "PlayerState.h"

class CPl_MC_LJump : public CPlayerState
{
public:
	CPl_MC_LJump(CPlayer* _pPlayer);
	~CPl_MC_LJump();

	virtual void Update() override;
};

