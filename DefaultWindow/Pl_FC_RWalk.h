#pragma once
#include "PlayerState.h"

class CPl_FC_RWalk : public CPlayerState
{
public:
	CPl_FC_RWalk(CPlayer* _pPlayer);
	~CPl_FC_RWalk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

