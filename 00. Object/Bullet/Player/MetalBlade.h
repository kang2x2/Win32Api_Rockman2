#pragma once
#include "obj.h"

class CMetalBlade : public CObj
{
public:
	CMetalBlade(float _fX, float _fY, float _fAngle);
	~CMetalBlade();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

