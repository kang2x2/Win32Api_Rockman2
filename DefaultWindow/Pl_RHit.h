#pragma once
#include "PlayerState.h"

class CPl_RHit : public CPlayerState
{
public:
	CPl_RHit(CPlayer* _pPlayer);
	~CPl_RHit();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;

private:
	float	m_fHitTime;
};

