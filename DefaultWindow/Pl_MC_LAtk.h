#pragma once
#include "PlayerState.h"

class CPl_MC_LAtk : public CPlayerState
{
public:
	CPl_MC_LAtk(CPlayer* _pPlayer);
	~CPl_MC_LAtk();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

