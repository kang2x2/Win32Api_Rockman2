#pragma once
#include "PlayerState.h"

class CPl_FC_LWalk : public CPlayerState
{
public:
	CPl_FC_LWalk(CPlayer* _pPlayer);
	~CPl_FC_LWalk();

	virtual void Update() override;
};

