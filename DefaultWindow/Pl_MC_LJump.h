#pragma once
#include "PlayerState.h"

class CPl_MC_LJump : public CPlayerState
{
public:
	CPl_MC_LJump(CPlayer* _pPlayer);
	~CPl_MC_LJump();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

