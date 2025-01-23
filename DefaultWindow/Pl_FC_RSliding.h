#pragma once
#include "PlayerState.h"

class CPl_FC_RSliding : public CPlayerState
{
public:
	CPl_FC_RSliding(CPlayer* _pPlayer);
	~CPl_FC_RSliding();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

