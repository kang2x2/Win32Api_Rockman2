#pragma once
#include "PlayerState.h"

class CPl_FC_RIdle : public CPlayerState
{
public:
	CPl_FC_RIdle(CPlayer* _pPlayer);
	~CPl_FC_RIdle();

	virtual void Update() override;
};

