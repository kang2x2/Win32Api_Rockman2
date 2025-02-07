#pragma once
#include "Effect.h"

class CBsDeadEffect : public CEffect
{
public:
	CBsDeadEffect(INFO _info, float _fAngle);
	~CBsDeadEffect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;

private:
	float	m_fSpeed;
	float	m_fAngle;
};

