#pragma once
#include "PlayerState.h"

class CPl_RWalk_Atk : public CPlayerState
{
public:
	CPl_RWalk_Atk(CPlayer* _pPlayer);
	~CPl_RWalk_Atk();

	virtual void Update() override;
};

