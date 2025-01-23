#pragma once
#include "PlayerState.h"

class CPl_RSliding : public CPlayerState
{
public:
	CPl_RSliding(CPlayer* _pPlayer);
	~CPl_RSliding();

	// CPlayerState을(를) 통해 상속됨
	virtual void Update() override;

private:
	float				m_fSlideTime;
};

