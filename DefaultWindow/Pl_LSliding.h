#pragma once
#include "PlayerState.h"

class CPl_LSliding : public CPlayerState
{
public:
	CPl_LSliding(CPlayer* _pPlayer);
	~CPl_LSliding();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;

private:
	float				m_fSlideTime;
};

