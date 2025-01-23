#pragma once
#include "Effect.h"

class CSmallDead : public CEffect
{
public:
	CSmallDead(INFO _info);
	~CSmallDead();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
};

