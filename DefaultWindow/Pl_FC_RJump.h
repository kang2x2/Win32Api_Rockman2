#pragma once
#include "PlayerState.h"

class CPl_FC_RJump : public CPlayerState
{
public:
	CPl_FC_RJump(CPlayer* _pPlayer);
	~CPl_FC_RJump();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

