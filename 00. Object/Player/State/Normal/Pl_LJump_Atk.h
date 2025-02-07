#pragma once
#include "PlayerState.h"

class CPl_LJump_Atk : public CPlayerState
{
public:
	CPl_LJump_Atk(CPlayer* _pPlayer);
	~CPl_LJump_Atk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

