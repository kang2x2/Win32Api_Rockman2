#pragma once
#include "PlayerState.h"

class CPl_FC_LJump : public CPlayerState
{
public:
	CPl_FC_LJump(CPlayer* _pPlayer);
	~CPl_FC_LJump();

	virtual void Update() override;
};

