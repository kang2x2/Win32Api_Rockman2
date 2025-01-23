#pragma once
#include "PlayerState.h"

class CPl_FC_RIdle : public CPlayerState
{
public:
	CPl_FC_RIdle(CPlayer* _pPlayer);
	~CPl_FC_RIdle();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

