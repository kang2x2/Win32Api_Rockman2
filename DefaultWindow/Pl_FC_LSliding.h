#pragma once
#include "PlayerState.h"

class CPl_FC_LSliding : public CPlayerState
{
public:
	CPl_FC_LSliding(CPlayer* _pPlayer);
	~CPl_FC_LSliding();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

