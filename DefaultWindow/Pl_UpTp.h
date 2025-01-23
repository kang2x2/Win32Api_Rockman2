#pragma once
#include "PlayerState.h"

class CPl_UpTp : public CPlayerState
{
public:
	CPl_UpTp(CPlayer* _pPlayer);
	~CPl_UpTp();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;
};

