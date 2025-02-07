#pragma once
#include "PlayerState.h"

class CPl_FC_LIdle : public CPlayerState
{
public:
	CPl_FC_LIdle(CPlayer* _pPlayer);
	~CPl_FC_LIdle();

	virtual void Update() override;
};

