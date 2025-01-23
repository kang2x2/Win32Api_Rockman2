#pragma once
#include "PlayerState.h"

class CPl_MC_RAtk : public CPlayerState
{
public:
	CPl_MC_RAtk(CPlayer* _pPlayer);
	~CPl_MC_RAtk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

