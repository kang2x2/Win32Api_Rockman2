#pragma once
#include "PlayerState.h"

class CPl_LJump_Atk : public CPlayerState
{
public:
	CPl_LJump_Atk(CPlayer* _pPlayer);
	~CPl_LJump_Atk();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

