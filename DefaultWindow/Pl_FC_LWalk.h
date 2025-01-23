#pragma once
#include "PlayerState.h"

class CPl_FC_LWalk : public CPlayerState
{
public:
	CPl_FC_LWalk(CPlayer* _pPlayer);
	~CPl_FC_LWalk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

