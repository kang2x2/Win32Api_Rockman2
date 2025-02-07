#pragma once
#include "PlayerState.h"

class CPl_RJump_Atk : public CPlayerState
{
public:
	CPl_RJump_Atk(CPlayer* _pPlayer);
	~CPl_RJump_Atk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

