#pragma once
#include "PlayerState.h"

class CPl_LJump : public CPlayerState
{
public:
	CPl_LJump(CPlayer* _pPlayer);
	~CPl_LJump();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

