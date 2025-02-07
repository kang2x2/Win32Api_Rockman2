#pragma once
#include "PlayerState.h"

class CPl_FC_RSliding : public CPlayerState
{
public:
	CPl_FC_RSliding(CPlayer* _pPlayer);
	~CPl_FC_RSliding();

	virtual void Update() override;
};

