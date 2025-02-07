#pragma once
#include "PlayerState.h"

class CPl_DownTp : public CPlayerState
{
public:
	CPl_DownTp(CPlayer* _pPlayer);
	~CPl_DownTp();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;

};

