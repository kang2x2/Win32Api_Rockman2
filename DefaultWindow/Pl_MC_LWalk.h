#pragma once
#include "PlayerState.h"

class CPl_MC_LWalk : public CPlayerState
{
public:
	CPl_MC_LWalk(CPlayer* _pPlayer);
	~CPl_MC_LWalk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

