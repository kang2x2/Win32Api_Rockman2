#pragma once
#include "PlayerState.h"

class CPl_MC_LJump_Atk : public CPlayerState
{
public:
	CPl_MC_LJump_Atk(CPlayer* _pPlayer);
	~CPl_MC_LJump_Atk();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

