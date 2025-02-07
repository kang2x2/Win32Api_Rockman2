#pragma once
#include "PlayerState.h"

class CPl_RAtk : public CPlayerState
{
public:
	CPl_RAtk(CPlayer* _pPlayer);
	~CPl_RAtk();

	virtual void Update() override;
};

