#pragma once
#include "PlayerState.h"

class CPl_MC_LIdle : public CPlayerState
{
public:
	CPl_MC_LIdle(CPlayer* _pPlayer);
	~CPl_MC_LIdle();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

