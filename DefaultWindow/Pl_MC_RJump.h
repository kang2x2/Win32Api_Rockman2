#pragma once
#include "PlayerState.h"

class CPl_MC_RJump : public CPlayerState
{
public:
	CPl_MC_RJump(CPlayer* _pPlayer);
	~CPl_MC_RJump();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

