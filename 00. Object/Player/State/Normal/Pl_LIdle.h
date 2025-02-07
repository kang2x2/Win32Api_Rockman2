#pragma once
#include "PlayerState.h"

class CPl_LIdle : public CPlayerState
{
public:
	CPl_LIdle(CPlayer* _pPlayer);
	~CPl_LIdle();

	virtual void Update() override;
};

