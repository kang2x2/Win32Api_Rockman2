#pragma once
#include "PlayerState.h"

class CPl_RJump : public CPlayerState
{
public:
	CPl_RJump(CPlayer* _pPlayer);
	~CPl_RJump();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

