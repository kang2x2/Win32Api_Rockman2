#pragma once
#include "PlayerState.h"

class CPl_MC_RJump : public CPlayerState
{
public:
	CPl_MC_RJump(CPlayer* _pPlayer);
	~CPl_MC_RJump();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

