#pragma once
#include "PlayerState.h"

class CPl_FC_RWalk : public CPlayerState
{
public:
	CPl_FC_RWalk(CPlayer* _pPlayer);
	~CPl_FC_RWalk();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

