#pragma once
#include "PlayerState.h"

class CPl_LAtk : public CPlayerState
{
public:
	CPl_LAtk(CPlayer* _pPlayer);
	~CPl_LAtk();

	virtual void Update() override;
};

