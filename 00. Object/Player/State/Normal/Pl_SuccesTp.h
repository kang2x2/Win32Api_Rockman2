#pragma once
#include "PlayerState.h"

class CPl_SuccesTp : public CPlayerState
{
public:
	CPl_SuccesTp(CPlayer* _pPlayer);
	~CPl_SuccesTp();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;

private:
	int m_iChangeTime;
};

