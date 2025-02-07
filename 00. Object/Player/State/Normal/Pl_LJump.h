#pragma once
#include "PlayerState.h"

class CPl_LJump : public CPlayerState
{
public:
	CPl_LJump(CPlayer* _pPlayer);
	~CPl_LJump();

	virtual void Update() override;
};

