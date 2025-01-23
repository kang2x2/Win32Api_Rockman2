#pragma once
#include "PlayerState.h"

class CPl_RAtk : public CPlayerState
{
public:
	CPl_RAtk(CPlayer* _pPlayer);
	~CPl_RAtk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

