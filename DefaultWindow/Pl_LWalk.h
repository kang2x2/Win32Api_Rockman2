#pragma once
#include "PlayerState.h"

class CPl_LWalk : public CPlayerState
{
public:
	CPl_LWalk(CPlayer* _pPlayer);
	~CPl_LWalk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

