#pragma once
#include "PlayerState.h"

class CPl_SuccesTp : public CPlayerState
{
public:
	CPl_SuccesTp(CPlayer* _pPlayer);
	~CPl_SuccesTp();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;

private:
	int m_iChangeTime;
};

