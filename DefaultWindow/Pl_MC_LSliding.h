#pragma once
#include "PlayerState.h"

class CPl_MC_LSliding : public CPlayerState
{
public:
	CPl_MC_LSliding(CPlayer* _pPlayer);
	~CPl_MC_LSliding();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

