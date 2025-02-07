#pragma once
#include "PlayerState.h"

class CPl_RWalk : public CPlayerState
{
public:
	CPl_RWalk(CPlayer* _pPlayer);
	~CPl_RWalk();

	virtual void Update() override;
};

