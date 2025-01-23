#pragma once
#include "Player.h"

class CPl_Animation
{
public:
	CPl_Animation();
	~CPl_Animation();

	void Player_Animation(CPlayer* _pPlayer, STATE _eState);

private:
	STATE				m_ePreState;
};

