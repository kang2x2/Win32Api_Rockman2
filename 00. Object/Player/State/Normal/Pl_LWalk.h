#pragma once
#include "PlayerState.h"

class CPl_LWalk : public CPlayerState
{
public:
	CPl_LWalk(CPlayer* _pPlayer);
	~CPl_LWalk();

	virtual void Update() override;
};

