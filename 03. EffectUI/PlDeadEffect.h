#pragma once
#include "Effect.h"

class CPlDeadEffect : public CEffect
{
public:
	CPlDeadEffect(INFO _info, float _fAngle);
	~CPlDeadEffect();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;

private:
	float	m_fSpeed;
	float	m_fAngle;
};

