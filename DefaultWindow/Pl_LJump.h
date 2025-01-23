#pragma once
#include "PlayerState.h"

class CPl_LJump : public CPlayerState
{
public:
	CPl_LJump(CPlayer* _pPlayer);
	~CPl_LJump();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

