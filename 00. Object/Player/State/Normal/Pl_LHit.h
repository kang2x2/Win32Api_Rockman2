#pragma once
#include "PlayerState.h"

class CPl_LHit : public CPlayerState
{
public:
	CPl_LHit(CPlayer* _pPlayer);
	~CPl_LHit();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;

private:
	float	m_fHitTime;
};

