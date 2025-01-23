#pragma once
#include "PlayerState.h"

class CPl_LWalk_Atk : public CPlayerState
{
public:
	CPl_LWalk_Atk(CPlayer* _pPlayer);
	~CPl_LWalk_Atk();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

