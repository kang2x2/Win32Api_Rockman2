#pragma once
#include "PlayerState.h"

class CPl_RJump : public CPlayerState
{
public:
	CPl_RJump(CPlayer* _pPlayer);
	~CPl_RJump();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

