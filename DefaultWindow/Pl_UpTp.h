#pragma once
#include "PlayerState.h"

class CPl_UpTp : public CPlayerState
{
public:
	CPl_UpTp(CPlayer* _pPlayer);
	~CPl_UpTp();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;
};

