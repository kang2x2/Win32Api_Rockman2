#pragma once
#include "PlayerState.h"

class CPl_LWalk : public CPlayerState
{
public:
	CPl_LWalk(CPlayer* _pPlayer);
	~CPl_LWalk();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

