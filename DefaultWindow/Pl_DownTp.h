#pragma once
#include "PlayerState.h"

class CPl_DownTp : public CPlayerState
{
public:
	CPl_DownTp(CPlayer* _pPlayer);
	~CPl_DownTp();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;

};

