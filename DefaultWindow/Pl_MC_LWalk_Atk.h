#pragma once
#include "PlayerState.h"

class CPl_MC_LWalk_Atk : public CPlayerState
{
public:
	CPl_MC_LWalk_Atk(CPlayer* _pPlayer);
	~CPl_MC_LWalk_Atk();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

