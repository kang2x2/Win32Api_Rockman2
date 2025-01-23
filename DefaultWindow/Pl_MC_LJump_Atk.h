#pragma once
#include "PlayerState.h"

class CPl_MC_LJump_Atk : public CPlayerState
{
public:
	CPl_MC_LJump_Atk(CPlayer* _pPlayer);
	~CPl_MC_LJump_Atk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

