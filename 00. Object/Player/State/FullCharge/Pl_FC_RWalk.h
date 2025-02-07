#pragma once
#include "PlayerState.h"

class CPl_FC_RWalk : public CPlayerState
{
public:
	CPl_FC_RWalk(CPlayer* _pPlayer);
	~CPl_FC_RWalk();

	virtual void Update() override;
};

