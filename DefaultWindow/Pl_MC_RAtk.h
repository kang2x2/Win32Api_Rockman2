#pragma once
#include "PlayerState.h"

class CPl_MC_RAtk : public CPlayerState
{
public:
	CPl_MC_RAtk(CPlayer* _pPlayer);
	~CPl_MC_RAtk();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

