#pragma once
#include "PlayerState.h"

class CPl_MC_RSliding : public CPlayerState
{
public:
	CPl_MC_RSliding(CPlayer* _pPlayer);
	~CPl_MC_RSliding();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

