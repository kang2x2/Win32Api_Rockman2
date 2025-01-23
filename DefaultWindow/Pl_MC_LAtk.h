#pragma once
#include "PlayerState.h"

class CPl_MC_LAtk : public CPlayerState
{
public:
	CPl_MC_LAtk(CPlayer* _pPlayer);
	~CPl_MC_LAtk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

