#pragma once
#include "PlayerState.h"

class CPl_RSliding : public CPlayerState
{
public:
	CPl_RSliding(CPlayer* _pPlayer);
	~CPl_RSliding();

	// CPlayerState��(��) ���� ��ӵ�
	virtual void Update() override;

private:
	float				m_fSlideTime;
};

